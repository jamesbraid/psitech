# rad4pci: the kernel driver, read through

What PsiTech's kernel driver for the RAD4 does, from the driver object in release 1.3k: probe and attach in order, the interrupt handler, DMA, every ioctl, mapping, the character devices and the board's two helper paths (the 93C46 configuration EEPROM and the flash). Ratings are as defined in [../../devices/rad4/README.md](../../devices/rad4/README.md). Hashes of the files read are in [../../references/binaries.md](../../references/binaries.md). Register meanings are in [../../devices/rad4/registers.toml](../../devices/rad4/registers.toml); the display modes and EEPROM are in [../../devices/rad4/modes.md](../../devices/rad4/modes.md); the X server side is in [../../devices/rad4/xserver-decode.md](../../devices/rad4/xserver-decode.md).

## The object

The package carries two builds of the driver, `rad4pci.o`, selected by CPU board: one for the IP27 and IP30 kernels (ELF64, MIPS IV) and one for the IP32 kernel (ELF32, N32, MIPS III). Their symbol tables list the same 155 names (established, `nm` of both). The IP32 build is the O2 driver: the package's own installation notes describe an O2 setup with the merged and second servers (established, `var/rad4/README`). Whether the two builds differ in code beyond the ABI was not compared; only the IP27 build was read.

Both are relocatable objects with a symbol table, so function names below are the shipped ones. The build banner string reads "RAD4 test driver ... Feb 16 1999 16:46:31" and a second string "1.101" is present (established, rodata). The master file (`var/sysgen/master.d/rad4pci`) registers the driver with flags `cs`, prefix `rad4pci`, soft id 63, three devices, and the system file asks for a PCI vector with module `rad4pci` (established).

### Tunables

Kernel tunables defined in the master file, with the defaults shipped (established). The object references all but one of them; which tunable each use belongs to was checked against the relocation entries (established):

| Tunable | Default | Use |
|---|---|---|
| `rad4pci_no_dma` | 0 | nonzero disables DMA for the board: attach records "DMA enabled" as its inverse |
| `rad4pci_max_dma_area` | 204800 | size of the per-board bounce buffer and the largest span moved in one DMA pass; attach refuses DMA when it is below 0x100 |
| `rad4pci_use_userbuffer` | 1 | transfer straight from the caller's pages instead of copying (comment in the master file: set 0 if memory is short) |
| `rad4pci_dma_read_cmd` | 0xc | PCI command the bus interface uses for DMA reads; only 0x6, 0xc and 0xe are accepted |
| `rad4pci_enable_prefetch` | 1 | selects the flags passed to every DMA mapping call: 0x420 when 1, else 0x20 |
| `rad4pci_latency_override` | 256 | PCI latency timer ceiling |
| `rad4pci_default_resolution` | 0x201 | defined (layout `S P RR`: sync type, sync level, resolution) but not referenced by the object: unknown whether any other component reads it |
| `rad4pci_major` | assigned | the device major number |

## Registration and probe

`rad4pciinit` registers the driver with the PCI layer twice, for `12d1:0104` and `12d1:0105`, and then picks the DMA mapping flags from the prefetch tunable (established). `rad4pciattach` runs once per matching function. Up to four boards are accepted: a counter is kept, and a fifth attach returns ENOMEM (established).

## Attach sequence, in order

Read in full from `rad4pciattach` (established unless stated). The BAR numbering is the driver's mapping selectors: 8 is BAR0, 10 is BAR2 and 1 is the expansion ROM, as in [README.md](../../devices/rad4/README.md#resources-the-driver-maps).

1. Allocate a 0x1dc8-byte per-board state, a 0x90-byte pointer block (the register pointers below) and a 0x280-byte DMA bookkeeping array of 16 entries. On the first call also allocate an 8 MiB host buffer per board seen so far (the buffered server's shadow framebuffer; the buffer is reallocated larger at every further attach).
2. DMA is enabled when the no-DMA tunable is zero. If the maximum DMA area is below 0x100 a message is logged and DMA is turned off. Allocate the bounce buffer of that size. Read a timestamp function into the state.
3. Initialise the board lock, five sleep locks and three synchronisation variables (named, in the strings, for the LUT load, the window-ID load and DMA timeouts).
4. Allocate two PIO windows: BAR0 for 0x80 bytes and BAR2 for 8 MiB. Allocate seventeen DMA maps of 0x4000 bytes (one for the buffered path plus sixteen in the per-transfer array).
5. Map BAR0 (0x80 bytes), BAR2 (8 MiB) and the expansion ROM resource (8 MiB). BAR2 is mapped through the translated-address call first, falling back to a mapping object; the ROM likewise. Each failure logs and returns EIO.
6. Config space: read the expansion ROM base register (offset 0x30) and write it back with bit 0 set, enabling ROM decode. This is how the DMA register aliases at the ROM resource become reachable (software expectation).
7. BAR0 offset 0x14 (expansion ROM remap) is written with `0xe1000000`.
8. Build the register pointer block. BAR2 plus 0x800000 is the base; the pointers are at these offsets from the start of BAR2: RAMDAC index low 0x900000, index high 0x910000, single-cycle data 0x920000, multi-cycle data 0x930000; horizontal timing banks 0xa00000, 0xa01000, 0xa02000 (never written), 0xa03000; vertical timing 0xb00000; an unused pointer 0xc00000; mask 0xd00000; the keyboard and mouse controller 0xe00000 (see below); board control 0xf00000, both the write pointer and the read pointer (the same address). The base itself, BAR2 plus 0x800000, is the flash window (see "Flash").
9. Read the BAR2 configuration register (offset 0x18) and save it.
10. PCI latency timer (config offset 0x0d, one byte): with the tunable nonzero, the new value is the tunable when the current value is zero and the smaller of the two otherwise; it is written back. With the tunable zero nothing is written.
11. BAR0 offset 0x18 (local bus region descriptor) is written with `0xf84303c3`.
12. BAR0 offset 0x6c: the low four bits are replaced by the DMA read command tunable if it is 6, 0xc or 0xe, else by 0xc. On the PLX 9060 these four bits are the PCI read command code the DMA engines use (public datasheet), so this resolves what the earlier reading called an unexplained nibble (established for the use; the field meaning is the datasheet's).
13. Read the PCI device ID (offset 2, two bytes) and revision (offset 8, one byte) into the state. The attach message reads "RAD4 `<-KM if 0x105>` N attached rev 0xR".
14. If this is the first board, print the driver banner, the DMA enabled or disabled state, the maximum size and the number of DMA maps obtained.
15. If BAR0 offset 0x40 (mailbox) is zero, the driver sets the board up itself: for a `0x105` device it runs the keyboard/mouse controller initialisation ([km-controller](../../devices/rad4/km-controller.md)); then it reads the 40-byte record from the 93C46 at byte address 0x58, takes the mode index (bits 0 to 6, replaced by 0 if out of range), runs the timing programming of [modes.md](../../devices/rad4/modes.md), saves width, height, label and index, and runs `init_RGB561`. If the mailbox is nonzero the driver skips the timing, RAMDAC and framebuffer setup, ORs `0x20` into its saved board-control word and, for a `0x105` device, copies mailbox word 1 (BAR0 offset 0x44) and word 2 (offset 0x48) into the state as the device types found on keyboard/mouse channels A and B. So the mailbox carries the firmware's result in three words: a done flag, and one detected-device code per channel (software expectation for the use; the 0, 1, 2 coding is the one the driver's own detection assigns: none, keyboard, mouse).
16. Shadow tables: a 1024-entry LUT copy filled with `i * 0x010101` (a grey ramp), then the LUT load routine; a 256-entry window attribute shadow filled with `0x36`.
17. If the mailbox was zero: write the three 256-entry gamma tables (index 0x3000, 0x3400, 0x3800, two cycles per entry with the entry's index in the first cycle and zero in the second, so an identity ramp of 10-bit values `i << 2`), set the mask register to `0xffffffff` and clear the framebuffer twice with the fill routine, which stores zero at the stored width and height. The saved mask in the state is `0xffffffff`.
18. Interrupt: allocate and connect the PCI interrupt (failure logs and the board stays attached without an interrupt), then OR `0x50900` into BAR0 offset 0x68.
19. Character devices: the board device `rad4` (`rad4.N` for the Nth board), `/hw/ttys/ttyrdN` (the text terminal, see below), and for a `0x105` device `rad4_kbd` and `rad4_pntr` (`rad4_kbd.N`, `rad4_pntr.N`); for the first board also the buffered device `rad4_b`. Each gets a small record naming its kind: 0 board, 1 keyboard, 2 pointer, 3 buffered, 4 terminal. Failure at any step frees what was allocated and returns the error.
20. Add a hardware inventory entry for the board: class 0x13, type 0x12d1 (the vendor ID), controller field the slot number, unit field the PCI device ID (software expectation; this is what a `hinv` line is built from).
21. Clear the mailbox (BAR0 offset 0x40 = 0). The driver therefore leaves the mailbox zero after every attach, so the firmware marker only matters for the first attach after the firmware ran (established).
22. For the first board, register it as the hardware textport target and copy the early textport buffer into the real framebuffer, then free it (see "Early textport").

Reading the init order gives these board accesses before first use (all established from the code unless noted): BAR0 `0x14`, `0x18`, `0x6c`, `0x40` read, `0x68`; board control through `init_RGB561` and the timing loaders; gamma tables; mask; framebuffer clear.

### Initialisation of the RAMDAC, in order

`init_RGB561` writes the following through the index and data ports. Values are written one per register, the index advancing, through the single-cycle port for the first group (established, read in full). Register names and fields are the public RGB561 specification's (preliminary revision 1.1, pages 28 to 47, read for this page; the decode is established for the part and a software expectation for the board):

| Index | Values written | Meaning |
|---|---|---|
| 0x01 | 0x2c | configuration 1: 4:1 basic serializer, 8 overlay bits, 8 logical window ID bits |
| 0x02 | 0x19 | configuration 2: RGB outputs enabled (screen control bit 0), on-chip PLL enabled, reference clock input, cursor location updates synchronous (bit 3) |
| 0x03 | 0x41 | configuration 3: non-interlaced, serial clock outputs enabled, RGB pixel order |
| 0x04 | 0x45 | configuration 4: 8 frame buffer window ID bits, split window IDs, auxiliary tables addressed by the four most significant window ID bits |
| 0x05 to 0x09 | 0 | interleave control (off) and the four window attribute segment registers |
| 0x10 to 0x13 | 0, 0, 0x0f, 0x0f | the two overlay chroma keys (0) and their masks (0x0f) |
| 0x30 | 0x60 | cursor control: separate cursor and cross-hair, cursor has priority on overlap, nothing enabled |
| 0x31 to 0x39 | 0 | cross-hair control, blink rate and duty, cursor hot spot and location |
| 0x40 to 0x4e | 0 | cross-hair scissor, location and pattern registers |
| 0x50 to 0x56 | 0 | VRAM bit mask registers (masking is off in configuration 2) |
| 0x5f | 0x04 | DAC control: 10-bit DAC mode, normal output current, fast slew |
| 0x82 | 0 | dot clock output disabled (three-state) |

Then the multi-cycle port: the first auxiliary table (index 0x0e00, the frame-buffer auxiliary window attribute table) with sixteen zeros: gamma tables used, no cross-hair, transparency value 0; the second (0x0f00, the overlay auxiliary table) with sixteen entries of 0x28: overlay enabled, no underlay, gamma used, transparent where the overlay data matches chroma key 0 under its mask (so overlay value 0 is transparent); the frame-buffer window attribute table (0x1000), 256 entries, each written as the pair (0x0d, 0x80), which the two-cycle format makes the entry `0x36` (24-bit format, true colour, buffer A, opaque); the overlay window attribute table (0x1400), 256 entries of (0x0c, 0x40), the entry `0x31`; and in the cursor table, the primary colour 1 entry at 0x0a11 as black and primary colour 2 as white, then at 0x0a15 the bytes 255, 255, 0 (blink colour 1 yellow) followed by two zero bytes, the start of blink colour 2 that is never completed (inferred that the last two bytes are stray).

The frame buffer window entry layout (page 47): bits 9 to 6 colour LUT start address, 5 to 4 pixel format (00 8, 01 12, 10 16, 11 24 or 30 bits per pixel), bit 3 buffer select, bits 2 to 1 colour mode (00 index, 01 grey, 10 direct, 11 true colour), bit 0 transparency enable. That is the layout requests 103 to 112 build below. The overlay window entry (page 48) has the same field positions with pixel format 00 8-bit overlay, 01 6-bit overlay with 2-bit underlay, 10 4-bit overlay with 4-bit underlay and 11 4-bit overlay double buffered, and colour mode 00 index, 01 grey, 10 indirect, 11 direct. The value `0x31` written at attach is therefore a 4-bit double-buffered overlay, index mode, colour LUT start 0, transparency enabled, which matches the four-plane overlay visual of the X server (inferred for the match; the field decode is established for the part). Request 134 rewrites every entry with the start field set to its argument.

## Interrupt handler

`rad4_inthandler` (read in full; established unless stated) acts when BAR0 offset 0x68 shows any of bits 13 to 15 and bit 8 (PCI interrupt enable). Bit 8 is cleared for the duration and set again on exit, under the board interrupt lock. The handler loops up to 200 times, re-reading the register:

- **Bit 15 clear:** two non-local causes are logged and masked: for the doorbell cause the enable bit 9 is cleared with the message "rad4int doorbell = N"; for the abort cause enable bit 10 is cleared with "rad4int abort = N". Which status bit selects which of the two was not resolved from the decompilation: Unverified.
- **Bit 15 set, DMA in progress** (the state flag at +0x90 is zero): if bit 21 is set and DMA channel 0's status (offset 0x128 of the expansion ROM window) shows Done (bit 4), write that register with Done kept, clear-interrupt (bit 3) set and enable (bit 0) cleared, and wake the DMA waiter. Nothing else is serviced while a DMA is running.
- **Bit 15 set, no DMA:** BAR0 offset 0x18 is temporarily replaced with `(old & mask) | 0x400300` (the mask is a constant the decompiler did not resolve) and restored at the end. For a `0x105` board the keyboard and mouse controller is serviced (`duart_interrupt_control` called with the "off" argument per channel found, then `duart_interrupt`). Then the board-control register is read through its read pointer: if bit 5 is set, bit 1 is cleared and written back (the frame event has arrived), a pending LUT load and a pending window-ID load are run and their 400 ms fallback timers cancelled.

So the board-control status in bit 5 is polled, but only inside the interrupt handler, through a pointer in the register block, which is why a scan for the register's offset as a constant finds nothing. This corrects the earlier note that nothing reads it.

Timeouts: the 400 ms fallback timer for a LUT or window-ID load that never saw a frame logs "lut load no vblank timeout" or "wid load no vblank timeout" and runs the load itself; the DMA timeout logs "dma int timed out" with counters, bumps a counter, disconnects and reconnects the interrupt and wakes the waiter (established).

## DMA

The engine's registers and the descriptor format are in [xserver-decode.md](../../devices/rad4/xserver-decode.md#dma). Added here from `rad4_rect_dma_move` and its two helpers (established):

- A transfer shorter than seven bytes after alignment is done by the CPU through BAR2 and never uses DMA; so are all transfers when DMA is disabled.
- Rectangle fill (`rad4_rect_dma_fill`) uses DMA only when the rectangle is at least 7 pixels wide, covers more than 32 pixels and DMA is enabled; it fills one row of the bounce buffer with the fill value, then issues one descriptor per row (several rows per pass when the bounce buffer holds them) and starts the transfer. Anything smaller, or any failure to map the buffer, falls back to the CPU fill. The fill argument block is the mask, x, y, width, height and value of the shipped header's fill structure (established).
- Each pass moves at most the maximum DMA area; the pass splits at 0x4000-byte page boundaries, one DMA mapping per page, up to sixteen mappings at a time.
- The descriptor writer stores each 16-byte descriptor through BAR2, in the top of the board's own memory: the first at offset `0x7ffff0`, each later one 16 bytes below the previous. Words: PCI address, local address, byte count, next-pointer word. A new last descriptor's next word is `6` for a PCI-to-local transfer and `0xe` for local-to-PCI (end of chain, interrupt, and the direction bit for reads); when it is appended to a chain the previous descriptor's next word is rewritten as the new descriptor's local offset with only the direction bit. The descriptor area therefore shares memory with the framebuffer top: mode 11 (1920 by 1080) leaves about 94 KB, room for roughly 5,900 descriptors (inferred from the arithmetic). The plane mask is forced to `0xffffffff` while descriptors are written and restored afterwards.
- Starting a transfer: if the board-control frame request (bit 1) is set it is cleared first and both the LUT and window-ID fallback timers cancelled; the keyboard and mouse interrupt enables are dropped; BAR0 offset 0x18 has bit 22 cleared and bit 19 set; the descriptor pointer is written; mode `0x7c3`; a timeout of `size / 20 + 400000` microseconds is armed; the command register is written with `3` (enable and start); the caller sleeps until the interrupt handler wakes it. After waking, bit 10 of the mode register (done interrupt enable) is cleared, a DMA that has not signalled Done is aborted (`4`), and up to 200 polls of two microseconds wait for Done. The command register is then cleared, BAR0 offset 0x18 gets bit 19 cleared and bit 22 set again, the interrupt enables are restored, and a frame request that was pending is re-armed (established). What bits 19 and 22 of the region descriptor do is unknown beyond "bracket DMA".
- A DMA never takes the frame path: while it runs the handler services only completion, so LUT and window-ID loads wait.

## Ioctl interface

The dispatcher bounds the request minus 101 to 40 entries and jumps through a table in the object; entries for 136 to 139 and any number above 140 log "bad ioctl cmd" and return error 6 (established). Request 141, `RAD4_RECT_WRITE_MODE` in the shipped header, is not implemented by this build (established: it lies outside the table). Requests are accepted on the board device (kind 0) and the buffered device (kind 3); on a keyboard or pointer node the only request handled is the termio-style break request, and on the terminal node the usual terminal requests are handled (see "Terminal"). An ioctl issued by a process that fails the ABI check returns ESRCH (`userabi returned ESRCH`).

On the buffered device every request that changes a register is applied to every attached board. Names are the shipped header's (`usr/include/rad4pci.h`).

| Request | Name | What the handler does (established, read) |
|--:|---|---|
| 101 | `RAD4_SETLUT` | copy 256 ints to the board's LUT shadow, set the load-pending flag, set board-control bit 1 (frame request), arm the 400 ms fallback; the load happens in the frame interrupt |
| 102 | `RAD4_SETLUTSS` | same for a start index and count, clamped to 0x3ff start and 1024 total |
| 103 to 112 | `RAD4_SETDEPTH8_INDEX` through `RAD4_SETDEPTH24_DIRECT` | build a window attribute entry and store it in the window shadow for every window ID whose bits, outside those ignored by the mask argument, equal the ID argument. The entry is `(lut start << 6) | format`: pixel format 0x00, 0x10, 0x20, 0x30 for 8, 12, 16, 24 bits; type bits 0 for indexed (103), 2 for grey (104), 6 for true colour (105, 107, 109, 111) and 4 for direct (106, 108, 110, 112). With the fixed entry `0x36` at attach this is "24-bit true colour, LUT start 0". Then request a frame-synchronised load as for 101 |
| 113 | `RAD4_GETTIMING` | return width, height, label |
| 114 | `RAD4_SETTIMING` | see [modes.md](../../devices/rad4/modes.md#how-software-learns-and-changes-the-mode) |
| 115 | `RAD4_SETCURSOR_POS` | write RAMDAC index 0x36: x low, x high, y low, y high. On the buffered device the cursor is positioned on the board whose horizontal span holds x, with x taken modulo the board width, and enabled there (index 0x30 written 0x21); the other boards get index 0x30 written 0 |
| 116 | `RAD4_SETCURSOR_CLUT` | write the multi-cycle port at index 0x0a11: the three background components then the three foreground components. Pixel value 1 is the background colour, 2 the foreground |
| 117 | `RAD4_SETCURSOR_MAP` | write the hot spot (index 0x34, x then y, low eight bits each), then the pixel map at index 0x2000: for each of the 64 rows, two 4-pixel groups per byte interleaving the 1-bit mask and 1-bit image planes of the argument: mask clear gives 0 (transparent); mask set gives 1 if the image bit is clear, 2 if it is set |
| 118 | `RAD4_RECT_WRITE` | rectangle write (PIO or DMA), see [xserver-decode.md](../../devices/rad4/xserver-decode.md) |
| 119 | `RAD4_RECT_FILL` | rectangle fill |
| 120 | `RAD4_SET_MASK` | if different from the saved mask, write the mask register and save it; the buffered device first lets pending DMA complete, then updates every board |
| 121 | `RAD4_RECT_READ` | rectangle read |
| 122, 123 | `RAD4_SETCURSOR_ON`, `RAD4_SETCURSOR_OFF` | write RAMDAC index 0x30 with 0x21 (cursor enabled, cursor priority on overlap, cursor and cross-hair locked) or 0 |
| 124, 125 | `RAD4_SCREEN_ON`, `RAD4_SCREEN_OFF` | set or clear bit 0 of RAMDAC register 0x02, configuration 2, whose bit 0 is the screen control that enables or blanks the RGB outputs (RGB561 page 30). The kernel textport's "screen on" routine does the same write |
| 126 | `RAD4_SET_PCI_READ_COMMAND` | replace the low nibble of BAR0 offset 0x6c with the argument if it is 6, 0xc or 0xe, else ignore |
| 127 | `RAD4_SET_GAMMA_LUT` | write 256 entries of the argument to each of the three gamma tables (index 0x3000, 0x3400, 0x3800), each entry as `(v >> 2) & 0xff` then `(v & 3) << 6` through the multi-cycle port, so the same 10-bit values go to all three colours |
| 128 | `RAD4_DAEMON` | on the buffered device only, runs the interrupt handler's work with the argument (the refresh daemon uses it) |
| 129 | `RAD4_WRITE_EEPROM_SECTOR` | program one 128-byte sector of the flash, see "Flash" |
| 130 | `RAD4_READ_EEPROM_SECTOR` | read 128 bytes of flash |
| 131, 132 | `RAD4_WRITE_SEPROM`, `RAD4_READ_SEPROM` | read or write bytes of the 93C46, argument offset, size, buffer; sizes and offsets must be even; error text "Bad SEPROM size/offset" otherwise |
| 133 | `RAD4_DEBUG_LEVEL` | set the driver's debug level |
| 134 | `RAD4_SET_OVERLAY_START` | rewrite all 256 entries of the overlay window attribute table (index 0x1400) with `((arg & 0xf) << 6) | 0x31` |
| 135 | `RAD4_GETTIMING_EX` | return any record's geometry, or the current one for a negative index |
| 140 | `RAD4_RECT_COPY` | rectangle copy (DMA only) |

The shipped header's mode names (`RAD4_1280_1K_72` is 0 and `RAD4_1280_1K_60` is 1, and so on up to index 6) disagree with the driver's mode table, where mode 0 is the 60 Hz label and mode 1 the 72 Hz label ([modes.md](../../devices/rad4/modes.md#the-mode-table)). The header lists only seven of the thirteen modes. Which is right for a real card is unknown; `rad4setres` and the factory-default note (index 1) agree with the table.

## Mapping, read and write

- **Map** (`rad4pcimap`): on the board device a mapping of the framebuffer, at most 8 MiB, offset and length multiples of 0x4000 (else error 5), through a physical mapping of BAR2 plus the offset. On the buffered device the object maps the per-board host shadow buffer instead, bounded by the total screen size. Error 0x1c (EFBIG) when too large (established).
- **Read and write** on the board device: up to 8 MiB offsets, through the rectangle helper. A write or read past 8 MiB returns error 0xe (established).
- **Open** on the board device resets the per-open state, points the shadow pointer at this board's slice and counts the open; the buffered device additionally clears bit 5 of every board's control register when more than one board exists, and writes it back (established).

## Terminal (`ttyrdN`)

`rad4pciopen` on the terminal kind runs `rad4_tty_init`: a 8 by 15 pixel character cell terminal, drawn by the CPU into the framebuffer with foreground `0xffffff` and background 0, 80 columns by 34 rows when the screen is large enough (columns are the width over 8, rows the height over 15, with an upper cap of 80 and 34), centred. It understands the usual escape sequences through a table (cursor movement, erase, scroll, `ESC D`, `ESC E`, `ESC M`, `ESC H`), the cursor is a block drawn by inverting 24 bits, and the glyphs are 15-byte bitmaps of 128 characters held in the driver's data. The terminal ioctls are the standard termio and termios requests and process group queries (`tty_fill_termio`, `tty_set_termios` and the like). On a `0x105` board the keyboard path of the terminal turns scan codes into characters (`translate_key`, `key_handler`). This makes the RAD4 usable as a console terminal without the X server (software expectation; read at the function-name level only, the escape table and key translation were not decoded: Unverified).

## Early textport

`rad4_earlyinit` is a registered early hook. On its first call it allocates an 8 MiB host buffer and registers the board with the kernel's hardware-textport service as a 1280 by 1024 target (`htp_register_board`, arguments 0x500 and 0x400), passing the table `RAD4_htp_fncs`. Nine functions are in the table (established, each read in full):

1. board init: look the board up in the driver's four-entry list; if not yet initialised mark it so, then switch the screen on;
2. set colour table entry: store `(r << 16) | (g << 8) | b` in a 32-bit table indexed by the colour number;
3. select drawing colour: load the current pixel value from that table;
4. fill rectangle: fill the box with the current pixel value at 32 bits per pixel, rows counted from the bottom (row = height minus y minus 1);
5. put one pixel;
6. draw a bitmap glyph: a 1-bit-per-pixel bitmap in 16-bit rows, bit 15 leftmost, painted only where set in the current colour, then advance the current position by the glyph's advance values; the glyph record carries data pointer, width, rows, x and y offsets, and advances (field positions read from the code; the names are ours);
7. set the current drawing position;
8. screen on (set bit 0 of RAMDAC register 0x0002);
9. a trivial compare used by the service (returns whether its argument is 1).

Until a board has attached, these write to the 8 MiB host buffer at a 1280-pixel pitch. Attach copies the buffer into the framebuffer (width by height words per row, with the board's own width) and frees it. So the early console text is rendered to memory, not to the board, and appears at attach time (established for the copy, software expectation for the purpose).

The board "init" routine does not program the mode itself. The kernel textport therefore depends on the driver's own attach having set the mode first, or on firmware having done so. How the textport selects this board as the console is in [proms-and-kernel.md](proms-and-kernel.md).

## EEPROM and flash

- **93C46 serial EEPROM** (configuration record at byte 0x58): [modes.md](../../devices/rad4/modes.md#configuration-eeprom-and-startup).
- **Flash** (requests 129 and 130): a second, parallel memory reached through BAR2 plus 0x800000, which the earlier notes recorded as a pointer nothing used. The routines, read in full, switch BAR0 offset 0x18 to `0xf84003c0` for the duration and restore it afterwards, and use byte accesses with the address lanes swapped (`address ^ 3`, a big-endian host on a lane-swapped bus). The write routine sends the three-byte unlock `0xaa` at 0x5555, `0x55` at 0x2aaa and `0xa0` at 0x5555 (lane-swapped), writes 128 bytes, then polls the last location until it reads back its own value (up to 0x80000 tries), and verifies all 128 bytes; failures return error 0xe with "EEPROM program timed-out" or "EEPROM program failed". An offset that is not a multiple of 128 logs "Bad EEPROM offset" and returns error 0x16. The header sizes the part at 65,536 bytes with 128-byte sectors (`RAD4_EEPROM_SIZE`, `RAD4_SECTOR_SIZE`), which is the geometry of a 5 V 512 Kbit page-write flash such as the AT29C512 (inferred; the part is not named anywhere). The package's `rad4_prog` tool and ROM image use these two requests; see [proms-and-kernel.md](proms-and-kernel.md).

## Limits

Not read: the escape-sequence table and key translation of the terminal, the read and write buffer helpers (`rad4_read_serial`, `rad4_write_serial`, `rad4_read_tty`), `rad4_rect_dma_fill` and `rad4_rect_dma_copy` beyond what they share with the move routine, and the multi-board corner cases of the buffered device. The ISR's mask constant for BAR0 offset 0x18 and the selection of the doorbell and abort bits are unresolved from the decompilation.
