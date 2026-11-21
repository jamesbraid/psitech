# rad4: what the X server and driver do to the board

Findings from reading PsiTech's release 1.3k for IRIX 6.5: the standalone X server, the kernel driver (the object for the Origin 200 and Octane-class kernels) and the `rad4setres` and `rad4d` tools. Everything here is established from the binaries or inferred from them, and none of it is a hardware measurement. Ratings are as defined in [README.md](README.md). Server addresses are ELF virtual addresses; driver addresses are relative to the start of its text section, whose file offset is 0x98. Hashes of the files read are in [../../references/binaries.md](../../references/binaries.md).

Four passes over the X server (a linear disassembly, rizin, radare2 and Ghidra) and the same over the driver were made. The listings are not committed. The two indirect-call-resolving engines disagree on function count for the server (6816 and 6259, out of 5308 names in its symbol table), which is a known difference in how they find function starts and has not been reconciled; the driver's two engines agree on 73 functions, all named from its symbol table.

## Driver request interface

The X server and tools reach the board through ioctls on the driver's device nodes (`/dev/rad4`, `/dev/rad4.N`; the buffered server uses `/dev/rad4_b`). The dispatcher subtracts 101 from the request number, bounds the result to 40 entries and jumps through a table (established, from the binary). Requests found:

| Request | Operation | Rating |
|--:|---|---|
| 113 | return current geometry and refresh label | established |
| 114 | change mode: see [modes.md](modes.md#how-software-learns-and-changes-the-mode) | established |
| 115 | cursor position | established |
| 116 | cursor colours | established |
| 117 | cursor image | established |
| 118 | rectangle write (CPU helper when DMA is disabled, else DMA) | established |
| 119 | rectangle fill (CPU helper) | established |
| 121 | rectangle read (CPU helper) | established |
| 122, 123 | cursor enable and disable | established |
| 135 | return any mode record's geometry | established |
| 140 | rectangle copy, DMA only; returns without copying when DMA is unavailable | established |
| 120 (0x78) | set the pixel write mask: the handler writes the mask register when the value differs from the saved one and saves it | established (handler read); the server's per-GC use was also inferred from an emulator run |

The full request table (101 to 140, including the colour map, window-depth, gamma, screen blank, flash and EEPROM requests) and each handler's register writes are in [../../software/rad4/kernel-driver.md](../../software/rad4/kernel-driver.md#ioctl-interface). A device type 3 (the buffered, multi-device mode) takes distinct branches in the dispatcher: the driver side applies a register-changing request to every attached board, positions the cursor on the board whose horizontal span holds it, and the server side is not audited here. Cursor handlers perform CPU writes through the indexed RAMDAC ports under driver locks and call none of the rectangle helpers; this identifies their mechanism, not the RAMDAC's full register set.

## No-DMA desktop path

The unbuffered server is the default and draws through the mapped framebuffer. A tunable disables pixel DMA; the rectangle transfer helper tests it and falls back to the CPU helpers, the fill helper likewise, and the copy helper (request 140) simply returns. Initial attach still allocates DMA-related resources and enables interrupts through the bus interface with DMA disabled (established).

| Operation | Path found | Limit |
|---|---|---|
| Window move | screen initialisation installs the server's window-copy callback into the screen record after the 32-bit framebuffer screen initialisation; the X core's window-move routine calls that slot. The callback reads the source rectangle with request 121 into a temporary buffer and writes the destination with 118 | pixel correctness and overlap behaviour were not executed in this reading. Established connection |
| Solid fill | `cfb32FillRectSolidCopy` stores words with CPU stores | other fill styles unaudited |
| Text | `cfb32PolyGlyphBlt8` has an unclipped path with word stores | clipped glyphs and font variants not traced |
| Image upload | `cfb32PutImage` selects the packed format and joins `cfb32CopyArea`, which for copy with full mask picks `cfb32DoBitbltCopy` | planar images, other raster operations and masks, CopyPlane and every clipping branch unqualified |
| Cursor | requests 115 to 117, 122 and 123 | actual appearance needs the RAMDAC contract |

The server's `hfbInit` opens the device and maps the pixel storage; the driver's mapping routine selects the ordinary device's board pointer, bounds the mapping to 8 MiB and maps it physically. The server is ELF32 big-endian MIPS II and the driver ELF64 big-endian MIPS IV, with user-ABI argument adaptation before dispatch: evidence of the package's mixed user and kernel environment, not of linking against any particular release.

## Plane mask use

The server's GC validation programs the write mask through request 120 before rendering: `0x00ffffff` for ordinary colour drawing and `0x0f000000` for the overlay and window-ID planes. The driver's own CPU helpers restore the full mask `0xffffffff` after a masked operation, and that value is its startup and saved full-mask value (established). A contract that accepted only the full mask would drop essentially all real rendering. Mask arithmetic and the greyed-label quirk are in [README.md](README.md#framebuffer-pixel-and-plane-mask).

## Overlay drawing

The server treats the CPU-visible overlay as bits 24 to 27 of the pixel word, with write mask `0x0f000000` (established, from the binary). Its GC validation, when the drawable is a window in the overlay visual, rewrites the foreground and background as `p | p << 24`, shifts the plane mask left by 24 (or uses all ones when the low nibble is full) and programs hardware mask `0x0f000000`; every other drawable gets `0x00ffffff`. Its set-spans, get-spans and rectangle-write paths shift depth-4 data by 24 and mask it with `0x0f000000` (established).

The one path that does not shift is the tiled span fill (`cfb32FillSpanTile32sCopy`, reached through `cfb32UnnaturalTileFS`): it copies the tile pixmap's words unchanged, and pixmaps never get the shift because the validation test needs a window drawable. Motif draws an insensitive menu label as a tiled fill with its 50 percent tile, so the stores alternate raw values `0x00000001` and `0x00000002` under mask `0x0f000000`. Inferred from an emulator run of IRIX 6.5.30 drawing the 4Dwm window menu: 407 stores all landed on glyph pixels of the greyed entry, with no framebuffer reads and no DMA. Under a plain bitwise mask the overlay nibble is written as 0, which the overlay window attribute table entry 0 makes transparent, so the frame-buffer layer shows through. Re-rendering the captured stores with the values placed in the overlay nibble gives a normal greyed label. A board that routed the low nibble into the overlay would instead break the shifted paths, which argues against that wiring (inferred). Whether PsiTech shipped with this defect is unknown: no capture of a real RAD4 overlay menu exists.

On a window move or resize the server also clears the whole overlay (every pixel of a 1280 by 1024 screen, 1,310,720 stores under mask `0x0f000000`) at button press and again at release, before anything visible changes; the full move issues about 2.2 million framebuffer writes and 0.35 million reads (inferred from an emulator run; the counts depend on the guest's workload, not on the board).

## DMA

The buffered server (`chkconfig rad4X_buffered_server on`) renders into a host-memory shadow of the screen, and the driver moves it to the board with DMA channel 0 of the bus interface in chaining mode (established). The ordinary rectangle path tests the no-DMA tunable and falls back to CPU helpers; the buffered path never checks it.

- **Registers and sequence.** The driver writes the descriptor pointer, then mode `0x7c3`, then starts with `3` in the command register. On its timeout it writes abort (`4`) and polls Done (`0x10`) up to 201 times. The timeout allowed is `size / 20 + 400000` microseconds (established). Mode `0x7c3` decodes, per the public sheet, as 32-bit local bus, TA#/READY# and BTERM# input enable, local burst, chaining and done interrupt enable. Its timeout path clears the done-interrupt bit to silence a transfer it gave up on.
- **Command register** (9060 sheet Table 57, established): bit 0 enable, bit 1 start (write-only, needs enable), bit 2 abort (write-only, needs enable clear; Done sets), bit 3 clear interrupt (write-only), bit 4 Done (read-only, resets set), bits 7 to 5 user, bits 15 to 8 channel 1. Clearing enable while a transfer runs pauses it; that setting it again resumes is inferred, since the table states only the pause.
- **Descriptors.** Chaining loads a 16-byte block (PCI address, local address, byte count, next pointer) from local memory (9060 sheet section 3.6.2 and Table 51; the 23-bit count is from the 9054 Data Book Table 11-79; established). The next-pointer word is loaded into the descriptor pointer register and its low bits describe that descriptor's own transfer: bit 1 ends the chain after it, bit 2 asks for an interrupt when it completes, bit 3 is the direction (1 local to PCI), bits 31 to 4 address the next descriptor. The driver builds one descriptor per scanline downward from the top of the 8 MiB local memory (first pointer `0x7ffff0`), each next-pointer word carrying that entry's direction, ending with `0x6` and a zero address (established). The first transfer after the buffered server starts is a full-screen 1280 by 1024 upload, a 1,024-descriptor chain; after that the driver issues 40-row chains.
- **Pointer bit 0.** Reserved on the 9060 and used by the later 9054 to fetch descriptors from host memory. The driver never sets it, and a trace of its first chain in an emulator found a self-consistent descriptor array at the top of the local extent (inferred, model behaviour). What the part does with the bit set is unknown.
- **Spans.** The channel moves any byte count between any PCI and any local byte address, and only bytes inside the span are written on either side (9060 sheet pages 6, 9 and 26, established).
- **Plane mask in DMA.** That an upload merges under the plane mask as a CPU store does is inferred: the driver's CPU and DMA paths share one mask register and one size threshold. No board document says the mask reaches DMA.
- **Interrupts.** The driver ORs `0x50900` into the interrupt register at attach: bits 8, 11 and 16 and bit 18 (DMA channel 0 interrupt enable). Its handler acknowledges a DMA interrupt by writing the command register with Done and clear-interrupt set and enable clear. The handler looks for the DMA completion bit (21) only after bit 15 is set.
- **Rate.** The 9060 is rated for PCI bus-master transfers up to 132 MB/s (sheet page 1). The board's achieved rate is unknown.

### Byte order

- The 9060 has no byte-order control: PCI byte lane n is local byte lane n on a 32-bit local bus (sheet page 18; established for the 9060). The later 9054 adds an endian register at 0x0C; the driver's BAR0 accesses are only at offsets 0x00, 0x14, 0x18, 0x68 and 0x6c, so the driver never touches it. The bus region descriptor value the driver writes selects a 32-bit local bus, which has no byte-order field.
- What arrives at the card from an IRIX 6.5.30 host: every DMA mapping call in the driver passes the same flags word, which its init routine sets to 0x20, or 0x420 when a driver variable is 1 (established). With the host bridge's per-slot byte-swap bits clear for 32-bit data phases, a big-endian 32-bit value crosses as the same dword value. So a CPU store of V to BAR0 or BAR2 arrives as PCI dword V; a DMA read of a host word holding V arrives as dword V; a DMA write of local dword W leaves W as a big-endian word. This depends on the host bridge's behaviour, which is the host's contract, not the board's, and was checked against an emulated bridge only (inferred, model behaviour).
- Descriptors are written into the top of local memory with ordinary 32-bit stores and the driver does no byte reordering, so the card reads them as the values the CPU stored (established, from the binary).
- The buffered server's host-memory image holds each pixel as a big-endian 32-bit value (inferred from an emulator run: an index-6 background pixel was the bytes 00 00 00 06, produced by guest software). Whether `rad4d` writes DMA buffers was not examined.
- The board's own memory lane order is unknown and invisible to software.

## Server and tools

- `/usr/bin/rad4setres` sets the mode through request 114 (see [modes.md](modes.md#option-fields)).
- `rad4d` is the refresh daemon. The server and daemon copies pulled from a running guest (`/var/rad4/Xradsgi` and `/var/rad4/rad4d`) differ from the standalone server of the package; hashes are in [../../references/binaries.md](../../references/binaries.md). A scan of the daemon and of both servers finds no instruction loading the board-control offset as a constant.
- The standalone server's depth-24 TrueColor and DirectColor visuals, four consecutive 36-byte records from array index 14 of its static visual table, give red, green and blue masks `0x00ff0000`, `0x0000ff00` and `0x000000ff` with offsets 16, 8 and 0, read directly from its data section (established).

## What is not covered

The buffered, multi-device and extension drawing paths; clipped glyphs and planar images; GC validation alternatives and non-copy raster operations; and the physical effect of anything the driver writes to the board-control register.
