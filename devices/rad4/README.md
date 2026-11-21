# rad4: PsiTech RAD4 board identity and register map

The RAD4 is a PCI graphics card with an 8 MB framebuffer, a PLX PCI 9060-compatible bus interface and an IBM RGB561-compatible RAMDAC. Its PCI IDs are `12d1:0104`; the RAD4-KM variant, with keyboard and mouse connectors on the card, is `12d1:0105`. This page is the board's identity, address map and register summary. The register definitions are [registers.toml](registers.toml) and the generated table [registers.md](registers.md). The display modes and the configuration EEPROM are in [modes.md](modes.md), and the X server and driver findings in [xserver-decode.md](xserver-decode.md).

Every fact carries one of three ratings: **established** (a published document, or a shipped binary or driver read in full, cited), **inferred** (a reasoned reading: what the software assumes about the board where the read was partial, approximations, and emulator runs, which show model behaviour and not hardware) and **unknown** (nothing published or shipped decides it). `registers.toml` uses the same three grades, and each entry's doc text names its source.

## Sources

- PsiTech, *RAD4 Owner's Guide*, software revision 1.3, 15 November 1997: PCI IDs, product roles, host systems, patches, device nodes, RAD4-KM connectors. (A scanned copy was read page by page for this revision; it has no text layer.)
- PLX Technology, *PCI 9060 Data Sheet*, version 1.2, December 1995, and the *PCI 9054 Data Book*, version 1.0, for the bus interface.
- IBM Microelectronics, *RGB561 Architecture*, preliminary revision 1.1, 23 January 1995, for the RAMDAC.
- PsiTech, *RAD4C-KM Graphics Head* product sheet, RAD4-DS-1099.
- The PsiTech release 1.3k package for IRIX 6.5 (kernel driver, standalone X server, `rad4setres`, `rad4d`), read as binaries, graded from the code: established where a routine was read in full, inferred otherwise. Hashes are in [../../references/binaries.md](../../references/binaries.md).

No Linux, OpenBSD or NetBSD driver exists for the RAD4, and no board photograph, schematic, parts list or configuration-space dump has been found.

## Identity

| Fact | Value | Rating | Source |
|---|---|---|---|
| RAD4 PCI vendor and device | `12d1:0104` | established | owner's guide, installation example; driver registers the ID |
| RAD4-KM PCI vendor and device | `12d1:0105` | established | owner's guide, installation example; driver registers the ID |
| RAD4-KM role | same line with keyboard and mouse connectors, for the Origin 2000, which has none of its own | established | owner's guide |
| RAD4 and RAD4-KM share framebuffer, RAMDAC and register layout | yes | inferred | one guide section describes both; one driver attaches to both |
| Framebuffer size | 8 MB | established for the RAD4C-KM sheet and the owner's guide description; the driver requests an 8 MiB mapping (established) | owner's guide; product sheet; driver |
| Bus interface | PLX PCI 9060-compatible | inferred, high confidence | register offsets, the expansion ROM route to DMA registers, mailbox, interrupt and EEPROM bits all match the 9060 sheet |
| Exact PLX part suffix and board revision | not identified | unknown | |
| RAMDAC | IBM RGB561-compatible | inferred, high confidence | indexed access through four ports, index 0x20 to 0x22 used as the sync and PLL registers the specification names |
| Framebuffer controller, timing sequencer, address decode, write mask | board-local logic; chip type (ASIC, FPGA, discrete) | unknown | no board image or parts list |
| Dedicated drawing accelerator | not established; CPU rendering and DMA are what the software uses | unknown | |
| PCI revision, class code, subsystem IDs, BAR sizing | class `0x038000`, revision 2, BAR2 16 MiB and expansion ROM 8 MiB as the shipped RAD4-KM serial EEPROM image declares them; subsystem IDs unknown | established (the image), inferred (a card carrying it) | [../../software/rad4/proms-and-kernel.md](../../software/rad4/proms-and-kernel.md#36500202-the-serial-eprom-image); no captured value from a real card exists |
| Board reference clock | 33 MHz | inferred | reproduces all 13 mode clocks, see [modes.md](modes.md) |
| Configuration EEPROM part | 93C46-compatible, 64 by 16 bits | inferred | the driver's command set matches the public part |

Later product: the RAD4C-KM (product sheet, October 1999) lists 8 MB VRAM, a programmable video clock to 200 MHz, an 8-bit overlay, 3 by 256 by 10-bit gamma tables, a 3 by 10-bit DAC and two 9-pin DIN keyboard and mouse connectors (established, the sheet). It gives no PCI IDs and no registers, and nothing here transfers to it.

## Supported systems and releases

| Fact | Value | Rating | Source |
|---|---|---|---|
| Host systems | O2, Octane and Origin 200 and 2000 file servers; the Origin 200 uses the RAD4, the Origin 2000 needs a RAD4-KM for its first head because it has no native keyboard and mouse port; on the O2 and Octane a single RAD4 is an additional head | established | owner's guide, "RAD4 Graphics Head" and section 2 |
| Octane | listed as a host in the guide's description; the release 1.3k README says "not officially supported, call PsiTech" | established (both statements) | owner's guide; package README |
| IRIX releases | guide revision 1.3: IRIX 6.3 and 6.4 (Origin 200 and 2000: 6.4 build 02121744 or newer with the PCI rollup patch SG0001887); package release 1.3k: IRIX 6.5 | established | owner's guide; package install descriptions |
| SGI patches named | 2009 (O2 and Octane, merged server) and 2082 (Origin 200 and 2000, a six-second launch delay) | established | owner's guide, appendix D; package README |
| Driver builds | IP27 and IP30 kernels (one 64-bit object) and IP32 (a 32-bit N32 object), each with its own master file; the master files differ by one byte | established | package file list; object headers |
| Boards per system | the guide's change list says "increased number of RAD4 in a system to 16"; the 1.3k driver refuses a fifth board at attach | established (both); the difference is a release difference or a stale note: unknown | owner's guide, appendix A; driver attach |
| Slot and numbering | the software numbers boards by ascending PCI slot starting at 0 (the `-rad4 n` server option) | established | owner's guide, "Xservers file" discussion |
| How the machines list the card | O2 `hinv`: "Unknown Type PCI: Bus 0, Slot 3, Function 0, Vendor ID 0x12d1, Device ID 0x104 (RAD4) or 0x105 (RAD4-KM)"; Origin 200 and 2000 power-on text: "PCI slot x (x=5, 6 or 7) pci 010412d1 UNKNOWN" | established | owner's guide, hardware installation and section 2 |
| Prefetch on the Origin 2000 | the guide tells the installer to set the prefetch tunable to 0 there; the shipped default is 1 | established | owner's guide, Origin 2000 steps; driver master file |
| RAMDAC rating | "200 MHz RAMDAC" and "8 MB frame buffer" in the product description | established (claims of the guide) | owner's guide |
| Release changes (1.3) | new three-level PCI driver, DMA control tools, buffered server (beta), 1920 by 1080 monitor settings, gamma and sync settings, X-software move between screens | established | owner's guide, appendix A |

Known problems the guide lists for release 1.3: cursor trouble with a maximised window on the second head of an O2 or Octane (the keyboard and pointer redirection program), no GL on the merged server, no double buffering, stereo, genlock or sync with the native head (established).

## Resources the driver maps

The driver names its resources by the Bridge-family selector numbers: selector 8 is the first base address region (BAR0), selector 10 the third (BAR2) and selector 1 the expansion ROM (established; the numbering is that of public Linux Bridge code and the driver's own configuration read of BAR2 agrees).

| Resource | Use | Rating |
|---|---|---|
| BAR0, 128 bytes requested | PLX runtime registers: mailbox, interrupt control, EEPROM control | established (size requested); the register layout is established from the 9060 sheet |
| BAR2, 8 MiB requested | framebuffer at the bottom, board registers above it | established for the requested size. The driver forms pointers beyond the 8 MiB it requests, so inferred: BAR2 must be larger than the request; the real size is unknown |
| Expansion ROM, 8 MiB requested | aliases of the DMA channel registers; the driver asks for an 8 MiB window, so a smaller declared size does not satisfy it. The driver sets the enable bit (bit 0) of the card's expansion ROM base register in configuration space before use | established |
| BAR2 plus 0xe00000 (RAD4-KM only) | keyboard and mouse controller, sixteen registers 64 KiB apart; not a separate BAR | established (use), inferred (layout); see [km-controller.md](km-controller.md) |

Every access the driver makes to BAR0, BAR2 and the expansion ROM is an aligned 32-bit load or store, except the flash at BAR2 plus 0x800000, which it reads and writes a byte at a time with the bus region descriptor switched (established). The RAMDAC ports take their payload from the low eight bits of the store.

## BAR0: bus interface

Offsets follow the 9060 runtime register layout.

| Offset | Name | What the driver does | Rating |
|---|---|---|---|
| 0x14 | expansion ROM remap | writes a value with top byte 0xe1 at attach, never reads | established |
| 0x18 | local bus region descriptor | writes `0xf84303c3` at attach, selecting a 32-bit local bus | established |
| 0x40 | mailbox | reads it at attach; nonzero means a firmware initialiser ran and the driver skips its own mode and RAMDAC setup; the driver writes zero to it at the end of every attach. Words 1 and 2 (0x44, 0x48) carry the keyboard and mouse device codes the firmware found, read only when word 0 is nonzero on a RAD4-KM | established. The shipped serial EEPROM image loads zero into mailbox words 0 and 1, so a card with that image starts with zero (established for the image, inferred for a card); who writes it on a real card is the option ROM, see [proms-and-kernel.md](../../software/rad4/proms-and-kernel.md) |
| 0x68 | interrupt control and status | ORs `0x50900` in at attach, with or without DMA; bits 8, 11, 15, 16, 18, 21 are the ones used | established (layout), established (use) |
| 0x6c | serial EEPROM control | clock bit 24, chip select bit 25, data to the EEPROM bit 26, data from it bit 27; the driver also sets the low nibble, the PCI read command of the DMA engines, to 0xc by default (6 and 0xe are the other values it accepts) | established (bits and nibble) |

Bit 15 of the interrupt register is the local interrupt input. Frame events and DMA completion both reach the host through it: the driver enables the DMA interrupt only towards the 9060's local output and looks for the channel's bit 21 only after bit 15, so the output is inferred to be wired back to the local input, as the 9060 sheet suggests. The board's frame event drives the same input (inferred).

## Expansion ROM route: DMA channel 0

| Offset | Name | Rating |
|---|---|---|
| 0x100 | DMA channel 0 mode (`0x7c3`: 32-bit local bus, chaining, done interrupt enable) | established (offsets, 9060 Tables 47, 51, 57 and 9054 Tables 11-76, 11-80, 11-86); the route through the expansion ROM is established |
| 0x110 | descriptor pointer | |
| 0x128 | command and status | |

The board's DMA use, descriptor layout and byte order are in [xserver-decode.md](xserver-decode.md#dma), and the full driver reading, attach order, interrupt handler and ioctl table in [../../software/rad4/kernel-driver.md](../../software/rad4/kernel-driver.md).

## BAR2: framebuffer and board registers

| Offset | Name | Rating |
|---|---|---|
| 0x000000 to 0x7fffff | framebuffer, 32-bit pixels | established |
| 0x800000 to 0x80ffff | parallel flash, 64 KiB in 128-byte sectors, used by driver requests 129 and 130 and the package's ROM programming tool | established (use), inferred (part); see [kernel-driver.md](../../software/rad4/kernel-driver.md#eeprom-and-flash) |
| 0x900000, 0x910000 | RAMDAC index low and high byte | inferred |
| 0x920000 | RAMDAC data, single cycle, index auto-increments | inferred |
| 0x930000 | RAMDAC data, multi cycle | inferred |
| 0xa00000, 0xa01000, 0xa03000 | horizontal timing banks | established (use and the bit rules the loader applies, [modes.md](modes.md#timing-words)); what the bits do in hardware inferred; depth unknown |
| 0xa02000 | pointer built but never written by the loader | unknown |
| 0xb00000 | vertical timing bank | established (use and bit rules, [modes.md](modes.md#timing-words)); hardware meaning inferred; depth unknown |
| 0xc00000 | pointer built, never used in the driver | unknown |
| 0xe00000 to 0xef0000 | RAD4-KM keyboard and mouse controller registers | see [km-controller.md](km-controller.md) |
| 0xd00000 | pixel write mask | established (use); which bit reaches which plane is unknown |
| 0xf00000 | board control and status | established (use); physical effect unknown |

Port numbering of the four RAMDAC ports in address order matches the RGB561's index low, index high, data and multi-cycle ports, which is inferred from how the driver uses them. They take the low eight bits of a store.

### Board control

Bit 5 (0x20) is cleared while the driver programs a mode and set afterwards, and its interrupt handler tests it through a stored pointer, which is why a search for the offset as a constant finds nothing (established). Bit 1 (0x02) asks for an interrupt at the next frame: the driver sets it, with a 400 ms fallback timer, when a palette or cursor update has to wait for the frame, its handler clears it when the frame arrives, and it clears it around every DMA transfer because during a transfer the handler services only DMA completion (established). That the board raises a frame event only while bit 1 is set follows from that last point and is inferred. The saved control word the driver writes back can also carry bit 7 (0x80), set by a helper that looks like the keyboard and mouse controller's interrupt path (established; role inferred). Whether the status in bit 5 is gated by bit 1 or only the interrupt is: unknown. A scan of the standalone server and `rad4d` finds no instruction loading the offset of this register as a constant, so they appear not to poll it; a scan misses offsets computed from a base. The keyboard and mouse controller's interrupt enable is bit 7 of this register (set while any enable is on).

### Framebuffer pixel and plane mask

A pixel is a 32-bit word. The X server's depth-24 TrueColor and DirectColor visuals are defined with red, green and blue masks `0x00ff0000`, `0x0000ff00` and `0x000000ff` and shifts 16, 8 and 0, read directly from the server's data (established). The RAMDAC configuration the driver writes selects 24-bit true colour from frame buffer A with no lookup, which reads the low 24 bits as direct colour (established from the RGB561 window attribute table field layout; the RGB561 input format alone does not say how CPU word bits reach the RAMDAC pins). The top byte holds the overlay and window ID: the server's four-plane overlay visual draws into it with plane mask `0x0f000000` (established); wiring the RAMDAC's window-ID inputs to that byte is inferred.

The server programs the write mask before almost every drawing operation: `0x0fffffff` once at screen start (read from the instruction words, not the `0x00ffffff` an earlier note gave), then `0x00ffffff` for ordinary colour and `0x0f000000` for the overlay, and it paints the window-type nibble with a rectangle fill under `0xf0000000`. A store therefore merges as `new = (old & ~mask) | (value & mask)`: that is the generic plane-mask convention, inferred. The driver takes the mask live around a DMA upload (set before it, restored after the transfer completes) and opens it to `0xffffffff` only to store DMA descriptors, which are words of board memory (established for the order, inferred for what the board does). Which mask bit reaches which board plane is unknown: the software divides the word into colour (bits 23 to 0), overlay (27 to 24) and window type (31 to 28) and nothing else decides it. No shipped server code tells window IDs apart by bits 27 to 24 (every window attribute request carries mask `0xf`, so the overlay nibble is ignored in the window ID), and the Kona-compatible GL libraries of the package never reach the driver; see [../../software/rad4/xserver-paths.md](../../software/rad4/xserver-paths.md#33-window-id-bytes-established).

One software quirk matters for anyone building a model: the X server draws Motif's greyed menu labels with a tiled fill that stores raw 4-bit tile values unshifted under the `0x0f000000` mask, while all its other overlay drawing shifts the index to bit 24. With a plain plane mask those labels leave the overlay transparent and the window behind shows through. Whether a real card does the same is unknown; a photograph of a 4Dwm menu on one would settle it.

## RAMDAC registers the software uses

The RGB561 is reached through the four BAR2 ports as an indexed register file. The RAMDAC's own registers are the public specification's; the ones the software touches are:

| Index | Use | Rating |
|---|---|---|
| 0x20 | sync control: the mode routine writes 1, or 0x23 when the EEPROM selector field is 2 | established (register), established (values) |
| 0x21 | PLL VCO divider M (bits 5 to 0, plus 65) and range code (bits 7 to 6) | established (M); range code position inferred |
| 0x22 | PLL reference divider N (bits 4 to 0) | established |
| 0x30 | cursor enable (bit 0) | established |
| 0x34, 0x35 | cursor hot spot x, y, six bits each | established |
| 0x36 to 0x39 | cursor position, 16-bit signed x and y | established |
| 0x2000 to 0x23ff | cursor pixel map, 64 by 64 two-bit pixels, leftmost pixel in bits 7 to 6 | established |
| 0x0a10 to 0x0a1f | cursor colour table; pixel value 0 is transparent, 1 to 3 select entries 0x0a11 to 0x0a13; each entry is three bytes, red first (inferred, from the driver's palette upload) | established (layout) |
| 0x1000, 0x1400 | frame-buffer and overlay window attribute tables | established |
| 0x0e00, 0x0f00 | the two 16-entry auxiliary tables | established |
| 0x3000, 0x3400, 0x3800 | red, green and blue gamma tables, 256 entries of 10 bits | established |
| 0x4000 to 0x43ff | colour look-up table | established |

The complete ordered list of the general initialisation, with every register decoded, is in [../../software/rad4/kernel-driver.md](../../software/rad4/kernel-driver.md#initialisation-of-the-ramdac-in-order). In short, initialisation values the driver writes (decoded with the public specification): configuration 1 `0x2c` (4:1 basic serializer, eight overlay bits, eight window-ID bits), configuration 2 `0x19` (on-chip PLL and RGB outputs on, reference clock input, cursor location latching), configuration 3 `0x41` (non-interlaced RGB order, serial clock on, synchronous cursor and scissor updates), configuration 4 `0x45` (split window IDs, eight frame-buffer window-ID bits, upper-bit auxiliary table addressing), frame-buffer window table entry `0x36` (24 or 30-bit true colour, buffer A, opaque), auxiliary frame-buffer table entry zero (gamma enabled) and cursor control `0x60` (cursor and cross-hair disabled). Rating: established that the driver writes these values (established); the meaning of each is the public specification's (established for the RGB561 part, inferred for the board). Which RGB561 revision is fitted and how the board wires the RAMDAC's pixel and window-ID pins: unknown.

The multi-cycle port loads every table with more than one byte per entry: two cycles for a window attribute or gamma entry (bits 9 to 2, then bits 1 to 0 in bits 7 to 6) and three for a colour or cursor table entry. The index advances once per complete entry, and writing either index register restarts a partial entry (established, RGB561 specification pages 1 and 4).

## Colour output chain and gamma

Ratings as above. Datasheet pages are the printed pages of the IBM RGB561 architecture preliminary revision 1.1 (23 January 1995); the Library copy is image-only, so these were read from page images.

- **established (datasheet pp. 1 to 3).** The RAMDAC has three 1K x 8 colour tables (bypassed in grey-scale and true-colour modes), three 256 x 10 gamma tables ("display colour enhancement", can be bypassed) and a cursor table of 12 to 24 RGB 8/8/8 entries for the cursor and cross-hair. The gamma tables' output drives the three DACs. Gamma tables "are always bypassed when cursor pixels are displayed", so the cursor bypasses gamma and everything else, overlay included, passes it when the window's attribute selects it.
- **established (datasheet p. 3).** The gamma table address is the 8-bit colour. When the tables are bypassed the 10-bit output is the 8-bit input in the top eight bits with its two top bits copied into the two low bits, that is c << 2 | c >> 6.
- **established (driver code, `software/rad4/kernel-driver.md`).** The driver's own start-up "identity" ramp writes entry i as i << 2 (first cycle i, second cycle 0), so its white is 0x3fc, three steps under the datasheet's bypass white of 0x3ff. A model that treats the start-up ramp and the bypass as the same function is off in the low two bits.
- **established.** Component depth is 8 bits: the pixel is a 32-bit word with the 24-bit true-colour masks 0x00ff0000, 0x0000ff00 and 0x000000ff, the server treating bits 27:24 as the overlay and 31:28 as the window type (inferred, `software/rad4/xserver-paths.md`); the window attribute entries the driver writes select 24-bit true colour from buffer A with gamma used (the auxiliary tables' "gamma used" bit is set). The widest the server offers is therefore 8 bits a channel in, 10 bits out of the gamma tables, and the DACs are 10-bit (RAD4C-KM product sheet: 3 x 10-bit DAC, 3 x 256 x 10-bit gamma).
- **inferred.** The IRIX `gamma` command works through the XSGIvc extension (see the odsy repository's record of its code), which the RAD4's standalone server is not known to implement; the card's start-up script runs `gamma 1.0` against the native display (`:0`) for the second-head case, and the board's own gamma control is `rad4setres -gamma` (ioctl 127, writes the same 10-bit values to all three tables). No program in the package reads `/etc/config/system.glGammaVal` (string scan of the server, module, `rad4d`, `rad4_X_knp` and `rad4setres`). The power curve `rad4setres` computes has undecoded scale constants (**unknown**, `software/rad4/xserver-paths.md` section 5): a read of its constant pool settles it.
- **unknown.** What ramp a RAD4 shows by default after the X server starts: the driver's identity ramp is loaded only when the firmware mailbox was zero (no firmware initialiser ran), and the server's colormap code was not read for a gamma step. Test: read the gamma tables back through the RAMDAC index 0x3000 after a server start.

## RAD4-KM controller

Under device `0x105` the driver also initialises a keyboard and mouse controller, exposed as `/dev/rad4_kbd` and `/dev/rad4_pntr`, separate from the system's own devices. It sits in BAR2 at 0xe00000, sixteen registers 64 KiB apart, and matches the SCN2681/SCC68681 dual UART index for index; that the card carries that part or a compatible one is inferred. The driver resets each channel with the PS/2 reset command and assigns keyboard or mouse from the reply, whichever channel it is on. The board-level interrupt enable is bit 7 of board control. The register map is in [registers.toml](registers.toml) and the full reading in [km-controller.md](km-controller.md). The connector type and the controller part are unknown.

## Limits

- Subsystem IDs of a real card: unknown. Revision, class code and BAR sizes are what the shipped serial EEPROM image declares, not a card's own values. Reset behaviour of the board-local registers, and cold, warm and PCI reset: unknown.
- Timing bank depths and the board's frame rate: unknown. The timing words' bit rules and a reading of them are in [modes.md](modes.md#timing-words).
- The mailbox's producer and power-on value on a real card: unknown.
- More than one card in a machine: not examined in the driver.

## Review note

Independent review, 2026-11-21 (not the author). Checked: the start-up gamma loop (index 0x3000, 0x3400, 0x3800; the entry index on the first cycle and zero on the second, 256 entries, only when the mailbox word is zero), the `0xf84303c3` descriptor value and the 0x7c3 DMA mode constant in the driver, and the shipped serial EEPROM image (the file is an S-record text; decoded values match [../../software/rad4/proms-and-kernel.md](../../software/rad4/proms-and-kernel.md)). Fixed: the colour-chain bullet about the `gamma` command still carried the retired "software expectation" rating; it is inferred, since it rests on a name and a script line. The datasheet page citations (RGB561, PLX 9060) were not re-read.
