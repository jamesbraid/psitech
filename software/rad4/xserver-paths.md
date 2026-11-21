# rad4: X server paths, window IDs, colormaps and the buffered and multi-head arrangements

What the standalone X server, the display-extension module and the start-up scripts of release 1.3k for IRIX 6.5 do with the board, and how the driver's device-type 3 node (the buffered, merged-screen device) behaves. It extends [xserver-decode.md](../../devices/rad4/xserver-decode.md), which holds the DMA register sequence, the plane-mask use and the no-DMA desktop path; none of that is repeated here. Ratings are as defined in [README.md](../../devices/rad4/README.md). Everything is established from the binaries or weaker; none of it is a hardware measurement.

Sources: the standalone server (`var/rad4/Xradsgi`, ELF32 big-endian MIPS II, symbol table kept), the display-extension module (`usr/lib/X11/dyDDX/psitech.so`), the helper programs `rad4d`, `rad4_X_knp` and `rad4setres`, the shipped header `usr/include/rad4pci.h` (request names below are its names), the start-up scripts, the shipped manual pages, the kernel driver object for the Origin 200 class (`rad4pci.o.IP27`) and its tunable file. Server and module addresses are ELF virtual addresses. Driver addresses are offsets from the start of its text section, as in the other pages.

Ratings in this page: "established" means the whole function or table was read in the listing. Where a reading rests on decompiler output not re-read line by line against the listing, or on a partial read, it is "inferred" and says so. "Unverified." marks anything not checked beyond a first pass.

## 1. Where each driver request is issued

All ioctl call sites of both programs were enumerated (39 in `Xradsgi`, 31 in `psitech.so`). The ones that are not driver requests are terminal and STREAMS controls on the input devices (`0x5309` arm-signal, `0x54c9`/`0x54ca` get/put termio-style settings), `AbortDDX` and the input code, and socket helpers in the X core. Two sites pass a request taken from a table (section 3); all others use an immediate. "Board" below means the device node the screen opened. The driver dispatcher accepts 101 to 140; 136 to 139 and anything above 140, including 141, take its "bad ioctl cmd" path and return error 6 (established, dispatcher table read in full; 141 has no handler in this driver build).

| Request | Name | Issued by in `Xradsgi` (address of the call) | `psitech.so` | Argument and condition | Rating |
|--:|---|---|---|---|---|
| 101 | SETLUT | none | none | Driver handler copies up to 256 colours into the board's LUT shadow, sets bit 1 of the board-control shadow, writes it to the register and arms a 400 ms timeout (message "lut load no vblank timeout"). On a type-3 node it repeats for every board | established (call-site absence), inferred (handler, first-pass read) |
| 102 | SETLUTSS | the static colormap-install function at 0x48d2c8 (call at 0x48d44c) | same function, named `install_bt463` in the module's symbol table (0x3fcb22ec) | `rad4_lut_t` with start 0, count 1024, 1024 packed 3-byte colours. Issued after every colormap create, install, uninstall and store-colors (each calls `generate_palette`, then this function). Handler clamps start/count to 1024 and loads through the same vblank-timed path as 101 | established (site), inferred (handler) |
| 103-112 | SETDEPTH8_INDEX .. SETDEPTH24_DIRECT | `init_ramdac` (0x48c594, a loop over a 16-entry table, section 3) and the install function (0x48d344, a loop over per-colormap entries, range-checked to 103..112) | `init_ramdac` (0x3fcb0c78), `install_bt463` (0x3fcb2208) | `rad4_wat_i` {id, mask, start}. Programs window attribute table entries; see section 3 | established |
| 113 | GETTIMING | `hfbInit` (0x488ed8) once per screen; `rad4_probe` (0x48a26c, no caller found) | `hfbInit` (0x3fcaa47c), `rad4_probe` (0x3fcab394) | Output: width, height, refresh label. On a type-3 node the driver returns the merged width and the common height (established, driver 0x3f54) | established |
| 114 | SETTIMING | none | none | `rad4setres` only. Type 3 has no branch in the handler | established |
| 115 | SETCURSOR_POS | `rad4_move_cursor` (0x489060, from `move_cursor`); `hfbwarp_cursor` (0x48a318, no caller found) | 0x3fcaa5f4, 0x3fcab468 | `rad4_cursor_pos` {x, y}. Used when the pointer device is the native kind (section 7) | established |
| 116 | SETCURSOR_CLUT | `hfbset_cursor` (0x48a604) | 0x3fcab870 | `rad4_cursor_clut`: the six 16-bit cursor colours shifted down to 8 bits, foreground then background | established |
| 117 | SETCURSOR_MAP | `hfbset_cursor` (0x48a530) | 0x3fcab77c | `rad4_cursor_map`: hot spot plus two 64 x 64 one-bit planes (mask and image). Rows are copied 32 bits at a time and padded to two words, then to 64 rows; sent before 116 | established |
| 118 | RECT_WRITE | `rad4_putrect` (0x48a180) | 0x3fcab27c | `rad4_rect_write`; mask is 0x00ffffff, or 0x0f000000 with data shifted into the overlay nibble for an overlay-visual window (section 4). Reached from the window-copy callback, tiled and masked blit paths, spans, save-unders and tile fills (many call sites in the cfb32 blit, fill and span code) | established |
| 119 | RECT_FILL | `hfbInit` (0x488f2c); `paint_win_type` (0x48b04c, 0x48b1ac); `repaint_win_type` (0x48c09c); `rad4_ValidateVisual` (0x48ec20) | `paint_win_type` (0x3fcaf7a4, 0x3fcaf914), `repaint_win_type` (0x3fcb051c); no fill in the module's `hfbInit` | `rad4_rect_fill`. `hfbInit`: mask all ones, value 0, whole screen, once per screen at start-up (standalone server only). Window-type paints: mask 0xf0000000, value type << 28. Solid window paints: mask 0x00ffffff (0x0f000000 for overlay windows). `rad4_ValidateVisual`: mask 0x0f000000, value 0, over each box of a newly validated region (clears the overlay nibble) | established |
| 120 | SET_MASK | `rad4_setmask` (0x48a1fc, called twice from `cfb32ValidateGC`); `init_ramdac` (0x48c5c0, arg 0x00ffffff) | `rad4_setmask` (0x3fcab314), `init_ramdac` (0x3fcb0cb4) | Value (not a pointer) in the argument slot. On a type-3 node the handler writes the mask to every board | established |
| 121 | RECT_READ | `rad4_getrect` (0x489e3c, 0x489f14) | 0x3fcaafb0, 0x3fcab05c | `rad4_rect_write`-shaped record; mask 0xf0ffffff, or 0x0f000000 for an overlay window, and overlay data shifted down by 24 on return | established |
| 122 | SETCURSOR_ON | `rad4_cursor_onoff` (0x4890e4); `ProcessInputEvents` (0x487ae0) | 0x3fcaa6a8 | `rad4_cursor_onoff` is called from `cross_screen` when the pointer enters a screen. `ProcessInputEvents` issues it for a pointer-back packet in tablet-style mode (section 7). Handler writes 0x21 to RAMDAC index 0x30 of that board (inferred, first-pass read) | established (sites) |
| 123 | SETCURSOR_OFF | `rad4_cursor_onoff` (0x489124); `ProcessInputEvents` (0x487a1c) | 0x3fcaa6fc | Mirror of 122; on a type-3 node applies to every board | established (sites) |
| 124 | SCREEN_ON | `save_screen` (0x488780); `init_ramdac` (0x48c5dc, at start-up) | `save_screen` (0x3fcadef8), `init_ramdac` (0x3fcb0cd0) | Handler sets bit 0 of RAMDAC index 2, on every board for type 3 (read in full) | established |
| 125 | SCREEN_OFF | `save_screen` (0x488764) | 0x3fcaded8 | Clears the same bit | established |
| 126 | SET_PCI_READ_COMMAND | none | none | `rad4setres -rcmd` only. Handler accepts 6, 12 or 14 and writes it into the low nibble of the bus-interface register at offset 0x6c; anything else is ignored (read in full) | established |
| 127 | SET_GAMMA_LUT | none | none | `rad4setres -gamma` only. Handler reads 256 words and writes two bytes per entry (value >> 2, then value << 6) to RAMDAC index regions 0x3000 and 0x3400, then a third table (partial read) | inferred |
| 128 | DAEMON | none | none | `rad4d` only (section 5) | established |
| 129-133 | EEPROM sector and serial-ROM access, debug level | none | none | not used by any shipped program of the package | established (absence) |
| 134 | SET_OVERLAY_START | the install function (0x48d468); `g1TellGainedMap` (0x48d674) | none | Value in the argument slot: the LUT start (in 64-entry units) of the overlay colormap, initially 16. Handler writes ((value & 0xf) << 6) | 0x31 to 256 consecutive RAMDAC entries starting at index 0x1400 | established (sites), inferred (what the RAMDAC does with it) |
| 135 | GETTIMING_EX | none | none | `rad4setres` only | established |
| 140 | RECT_COPY | none | none | no program issues it. Type-3 handler returns success without copying | established |
| 141 | RECT_WRITE_MODE | none | none | named in the header, no handler in this driver build | established |

Reads of tunables and chkconfig flags: no program in the package reads a chkconfig flag, an environment variable or a tunable (string scan of the server, the module, `rad4d`, `rad4_X_knp` and `rad4setres`; the only mention of a display is the X client call in `rad4_X_knp`). The chkconfig flags are read only by the two start-up scripts (section 6). The tunables are driver parameters in its master file: major number, use of a user buffer (default 1), maximum DMA area (default 200 KB), no-DMA (default 0), default resolution word (default 0x201), DMA read command (default 0xc), prefetch (default 1) and PCI latency override (default 256). With 200 KB and a 5,120-byte row, a chain is 40 rows, which matches the 40-row chains already recorded (derived).

## 2. The buffered, merged-screen device (device type 3)

### 2.1 What the driver node types are

The dispatcher keys on a type word in the node's private record (established, 0x3138 to 0x32e0; the record is 16 bytes and points at board 0 for types other than 0):

| Type | Node | Created |
|--:|---|---|
| 0 | the board (`rad4`, `rad4.N`) | each board attach |
| 1, 2 | serial channel A and B, exposed as `rad4_kbd` and `rad4_pntr` (and `.N` forms) for the RAD4-KM | KM board attach |
| 3 | the merged buffer node `rad4_b` | first board attach only; its record points at board 0 |
| 4 | a text-console tty `ttyrdN` | board attach |

Request handlers for types 0 and 3 share one jump table of 40 entries. For type 3 the handler sees board 0's record plus the type word, and 17 handlers branch on it (101, 102, 103-112 as one, 113, 115, 116, 117, 118, 119, 120, 121, 123, 124, 125, 128, 135, 140). Requests 114, 122 and 126 to 134 have no type test; they act on board 0 only (established for the list, by scan of the dispatcher).

### 2.2 How the buffered server decides to run

The decision is made entirely outside the server binary (established, scripts read in full; the server read for the option):

1. `chkconfig rad4X_buffered_server on` makes `/var/rad4/X` (the xdm-started wrapper) run `Xradsgi ... -rad4 16` and makes `rad4XStart` start `rad4d` at boot. With the flag off, the wrapper counts device nodes (`/dev/rad4.2`, `/dev/rad4.1`, `/dev/rad4`) and passes `-nr 3`, `-nr 2` or nothing.
2. `-rad4 N` sets the board number of the first screen, and `hfbInit` opens `/dev/rad4` for board 0 and `/dev/rad4.%d` otherwise. `rad4XStart` links both `/dev/rad4_b` and `/dev/rad4.16` to the same hardware-graph node, so board number 16 opens the type-3 node. The server has no other buffered-mode switch (established).

### 2.3 The shadow framebuffer

Inferred (attach routine read through decompiler output, shadow geometry checked against the type-3 request code in the listing):

- Each board attach reallocates one host-memory buffer of 8 MiB per board attached (up to four boards). Board i's `+0x50` pointer is the buffer base plus i x 8 MiB; the type-3 node uses the base (the open routine resets it to the base for type 3).
- The shadow is one pixel array of 32-bit words. Its row width is the board width times the number of boards attached, its height is the board height. Each attach rewrites both globals from the board being attached.
- `hfbInit` on the type-3 node maps `width x height x 4` bytes, rounded up to 16 KiB, read/write shared, from the node. The driver's map routine for type 3 returns this host buffer (not the board's BAR) and rejects maps larger than the shadow. The server passes the mapped base to `cfb32ScreenInit`, so ordinary cfb32 drawing (fills, text, set-spans) stores straight into the shadow. It then calls `plock`.
- The server records width and height from request 113, which on the type-3 node returns the merged width (established).

### 2.4 How the shadow reaches the boards

Inferred, from decompiled routines (one routine reading per row below) cross-checked for call structure against the listing:

| Path | Trigger | What the driver does |
|---|---|---|
| Rect write (118) | server request | writes the rectangle into the shadow (under the mask: read-modify-write if the mask is not all ones), programs the mask register of every board when it differs from the current one, then uploads the rectangle with the per-board routine below, then restores the old mask |
| Rect fill (119) | server request, including the whole-screen clear in `hfbInit` | same, with a fill value |
| Rect read (121) | server request | uploads any pending rectangle, downloads the rectangle from the boards into the shadow, then copies it to the caller |
| Whole-screen refresh | `rad4d` loop (request 128) | cuts the screen into 8 horizontal bands and uploads each, waiting for a pending timer between bands; see section 5 |
| Rect copy (140) | none issued | returns without copying |
| Timer | first 118 or 119 sets a flag word on board 0 and arms a 250 ms timeout; a timeout callback (not read) clears it; the refresh path waits for it in 50 ms steps | the purpose is not recovered (unknown) |

The per-board upload routine (decompiler reading, 0x10a698 in decompiler addresses): for each board i it intersects the rectangle with the columns [i x boardWidth, (i + 1) x boardWidth), then moves the pixels. A part of 6 pixels or fewer in width, or with 32 pixels or fewer in total, is copied word by word by the CPU through the board's mapped framebuffer. Anything larger is built into a chain of DMA descriptors, one per row segment, in chains limited by the maximum DMA area, and the descriptor builder (0x10a2a4, read in full: it writes the PCI address, local address, count and a next-pointer word with direction bit and end-of-chain bits, from the top of the board's local memory) feeds the DMA register sequence recorded in xserver-decode.md. Direction 1 is host to board. The buffered path does not read the no-DMA tunable (consistent with xserver-decode.md).

### 2.5 The multi-board arrangement on the type-3 node

Inferred (same sources): boards are placed side by side, left to right, in attach order, which is also the order of `/dev/rad4`, `/dev/rad4.1`, `/dev/rad4.2`. Board i shows shadow columns [i x W, (i + 1) x W) at its own rows 0 and up, where W is the merged width divided by the board count. Nothing arranges boards above or below each other. The cursor position request (115) on the type-3 node divides x by W: the board that contains the cursor gets x modulo W; every other board has its cursor registers zeroed. Cursor on/off (122, 123), screen on/off (124, 125), the mask (120) and both LUT loads (101, 102, and the window attribute loads 103 to 112) are repeated for every board, so all boards share one colormap, one window attribute table and one mask. Mode information for any index (135) on the type-3 node multiplies the width by the board count plus one in the listing, which overstates the width by one board if the counted variable is the board count; the server never issues 135, so this is only visible to `rad4setres` (established for the arithmetic, unknown whether intended).

Opening the type-3 node with more than one board also pulses bit 5 of each board's board-control shadow: the register is written with the bit cleared and then with the saved value (decompiler reading). This is the only place besides the LUT and window attribute loads where that register is touched with a new value; it adds a data point to open question 1 but does not settle it.

## 3. Window attribute programming, the window-type table and window IDs

### 3.1 Request encoding (103 to 112)

Established (handler read in full, driver 0x3a58 to 0x3f4c). The handler builds one word and stores it into every one of 256 attribute entries whose index i satisfies (i with the ignored bits cleared) equal to id, where the "ignored" bits are those set in the request's mask. Word = start << 6, plus a depth field and a mode field:

| Request | Depth field | Mode bits |
|--:|---|---|
| 103 index | 8-bit (0x00) | 0 |
| 104 grey | 8-bit | 2 |
| 105 true | 8-bit | 6 |
| 106 direct | 8-bit | 4 |
| 107 true, 108 direct | 12-bit (0x10) | 6, 4 |
| 109 true, 110 direct | 16-bit (0x20) | 6, 4 |
| 111 true, 112 direct | 24-bit (0x30) | 6, 4 |

The attribute table is then loaded to the board through the same vblank-timed path as the LUT (flag word, board-control bit 1, 400 ms timeout message "wid load no vblank timeout"). The header comment says up to 256 window types exist.

### 3.2 What the server programs

`WTtable` in the server's data (0x10017870, 16 entries of four words {request, id, mask, start}; read in full) is walked by `init_ramdac` at every screen start, before the first colormap is created. Every entry has mask 0xf, so each covers the 16 window ID bytes whose top nibble is its type.

| Type (ID byte) | Request | Meaning | Start |
|--:|--:|---|--:|
| 0 (0x00) | 103 | 8-bit indexed | 0 |
| 1 (0x10) | 104 | 8-bit grey | 0 |
| 2 (0x20) | 105 | 8-bit true | 0 |
| 3 (0x30) | 106 | 8-bit direct | 0 |
| 4 (0x40) | 111 | 24-bit true | 0 |
| 5 (0x50) | 105 | 8-bit true | 0 |
| 6 (0x60) | 104 | 8-bit grey | 0 |
| 7 (0x70) | 107 | 12-bit true | 0 |
| 8 (0x80) | 109 | 16-bit true | 0 |
| 9 (0x90) | 105 | 8-bit true | 0 |
| 10 (0xa0) | 111 | 24-bit true | 16 |
| 11 (0xb0) | 111 | 24-bit true | 32 |
| 12 to 15 (0xc0 to 0xf0) | 111 | 24-bit true | 0 |

Type 12 is the value painted for a window that has no colormap (value 0xc0000000). The start values are in the request's own units (the driver shifts by 6, so 16 and 32 are 1,024 and 2,048); they exceed the 1,024-entry LUT, so what a start beyond the LUT does is unknown.

### 3.3 Window ID bytes (established)

The server treats pixel bits 31 to 28 as the window type nibble and bits 27 to 24 as the overlay nibble, so the window ID byte the attribute table is indexed by is the pixel word's top byte; the attribute mask of 0xf makes the overlay nibble irrelevant (inferred from the masks used in the paints and from the table above).

- `paint_win_type` and `repaint_win_type` fill a window's clip region (request 119, mask 0xf0000000) with value type << 28, where type is the first word of the colormap's private record, or 0xc0000000 when the window has no colormap. A window in the overlay visual is skipped by `paint_win_type`, so overlay windows never change the type nibble (established for the skip; the visual test is the vid comparison discussed in 4.3).
- `repaint_win_type` is what `g1TellLostMap` and `g1TellGainedMap` call when a colormap is installed or removed.
- `next_window_type` (0x48c604, read in full) builds a mask of types in use by the installed colormaps and returns the lowest free type of 0 to 3; if all four are in use it returns the first installed colormap's type. This is why the screen records one to four installed colormaps and why only types 0 to 3 are reassigned dynamically (types 4 and up are fixed-visual types) (inferred for the screen-record limits).
- The install function sets each entry's id to type << 4 before issuing it (inferred from the store shape).
- `generate_palette` (0x48c7b8, partially read) walks the installed colormaps and for each builds a request and start, with LUT positions in 64-entry units. Per visual class: PseudoColor and GrayScale use 103 with start = position; TrueColor and StaticColor use 105/104/109/111 by depth (8, 15, 24 bits) with start 0; DirectColor 24-bit uses 112, other DirectColor depths use 103; StaticGray uses 104. If positions would pass 1,024 entries it sets an overflow bit and skips the colormap. Inferred; class-specific details of the LUT filling are unverified.
- The 1,024-entry LUT is sent as 3-byte colours (16-bit components reduced to 8 bits by (c + 32767) / 65535 scaling), then request 102.

## 4. Visuals and overlay

### 4.1 Visual set

The server and the module carry the same static template of 19 visual records and 5 depth records (read in full: 36-byte records, vid zero, replaced per screen with fresh client IDs).

| Index | Class | Depth | Entries | Notes |
|--:|---|--:|--:|---|
| 0-3 | PseudoColor | 8 | 256 | four copies, so each gets its own colormap and window type |
| 4 | StaticColor | 8 | 256 | masks 0xe0, 0x1c, 0x03 (3-3-2) |
| 5-6 | TrueColor | 8 | 8 | 3-3-2 |
| 7 | PseudoColor | 4 | 16 | the overlay visual |
| 8-13 | TrueColor | 15 | 32 | 5-5-5, offsets 10/5/0 |
| 14-17 | TrueColor | 24 | 256 | 0x00ff0000, 0x0000ff00, 0x000000ff, offsets 16/8/0 |
| 18 | DirectColor | 24 | 256 | same masks |

Pixmap formats: depth 1 (1 bit), 4 (8), 8 (8), 15 (16) and 24 (32 bits per pixel), all 32-bit padded, big-endian byte order (established, `InitOutput`).

### 4.2 Choosing the default visual

Options `-class`/`-vic` (class name or 0 to 5) and `-vid`/`-depth` (depth) select the default visual: `rad4InitVisuals` (0x783840) takes the first record that matches the requested class and depth, and falls back to depth 8 (the PseudoColor copy at index 0) when nothing matches. With no options `InitOutput` forces PseudoColor depth 8 (established). `rad4InitVisuals` assigns a different client ID to each visual and reports 19 visuals in 5 depths.

### 4.3 The overlay visual and what is undecided

`InitInput` sets a root-window property named SERVER_OVERLAY_VISUALS on each screen from a four-word template: the visual ID, transparency type 1 (transparent pixel), transparent value 0, layer 1 (established). The visual ID comes from the array `GLoverlay_vid`, which holds -1 in all four slots in the file. Every use found compares a window's visual ID against that array: the paints, rect read and write, GetSpans, colormap initialisation, window creation, GC validation, and the overlay LUT-start request. No store to the array was found in `Xradsgi` (14 sites load its address; a scan of the code after each found no store through it), nothing in `psitech.so` references it (the module only imports the symbol), and the name does not occur in the RAD GL libraries. So, as shipped, the standalone server's overlay comparisons can match only if something outside these binaries writes the array (unknown). This bears on the overlay behaviours recorded in xserver-decode.md (see the last section).

For the merged server the module takes the host server's defaults (`ddxDfltClass`, depth and visual) and, when the host's overlay flag is set, marks the screen's overlay-default field (inferred).

## 5. Cursor, blanking and the refresh daemon

Cursor (established, whole functions read): `hfbset_cursor` skips everything when given a null cursor. Otherwise it downloads the image (117) then the colours (116); `move_cursor` calls 115 on every move; `cross_screen` calls 122 or 123 when the pointer enters or leaves a screen. The cursor is a 64 x 64 two-plane hardware cursor.

Screen saver: `save_screen`, the screen-record save-screen hook, treats mode 0 (saver on, blank) as request 125, mode 1 (saver off) as 124, and mode 2 (force) as only a reset of the idle timer (established). The server also calls 124 once from `init_ramdac`. `alrmhandler`/`flush_screen` arm a 10 second SIGALRM once and clear three statistics counters; the counters have no other readers (inferred).

`rad4d` (whole program read; main is about 170 instructions): opens `/dev/rad4_b` read/write, and on failure prints a message and exits. Otherwise it loops on `ioctl(fd, 128, 2)` until the call fails (returns below zero), then prints a message and exits with status 0. It has no timer, no signals and no sleep (established). In the driver, request 128 acts only on a type-3 node and only when the board has been opened at least twice (the open count is the counter at offset 0xb8, bumped by every open of the board or the type-3 node; the daemon's own open is one). With two opens it splits the screen into 8 bands of height/8 rows, and for each band waits (50 ms steps) while the 250 ms flag is set, then uploads the band as a host-to-board transfer. With fewer than two opens it returns success at once, so the daemon spins (inferred; the open-count meaning is from decompiler output). The wait is the only blocking point (established for 0x10a4d4 in the listing).

So in buffered mode the guest sees two upload paths: immediate rectangle uploads for the requests the server issues, and a continuous full-frame upload by the daemon. Plain cfb32 stores to the shadow reach the board only through the daemon (inferred; no server code signals the driver after such stores).

`rad4setres` (whole program read): optional device argument (`/dev/rad4` or `/dev/rad1` by default), a mode number, and options `-gamma`, `-rcmd`, `-hsp`, `-vsp`, `-sync`. With no number it lists modes (request 135 per index). It sets the mode with 114 and polarity and sync fields in its option bits (see modes.md), PCI read command with 126 and gamma with 127 (256 integers computed as a power of the normalised index; the scale constants were not decoded, Unverified).

## 6. Start-up and the scripts

All of these were read in full.

`rad4XStart` (boot script; run by init):

- Unless the release is 6.3, deletes `/dev/rad4*` and links each hardware-graph node back under `/dev`: `rad4`, `rad4_b` (also as `rad4.16`), `rad4.1`, `rad4.2`, `rad4_kbd`, `rad4_pntr` and the `.1` and `.2` forms of both.
- If `rad4X_merged_server` is on: only logs that the merged arrangement is enabled; nothing is started here.
- Otherwise, if `rad4X_second_server` is on: in a background job, waits 20 s, sets `DISPLAY=:0`, runs `gamma 1.0`, then runs `rad4_X_knp -right -server /var/rad4/Xradsgi :1` with output to the log; a second background job waits 30 s and sets the second display's root colour. The comment says to replace `-right` with `-left` or `-top` for other positions.
- If neither is on: logs that the second head is disabled.
- If `rad4X_buffered_server` is on: starts `rad4d` in the background (independent of the two flags above).

All four flags ship set to off.

`/var/rad4/X` (xdm-launched server wrapper; Origin 200 and the generic xdm configuration both start it as `:0`):

1. Keyboard: `/dev/input/keyboard` if a character device, else `/dev/rad4_kbd` if one, else `none`. Pointer: `/dev/input/mouse`, else `/dev/rad4_pntr`, else `none`.
2. If `rad4X_usekm_devs` is on, force `/dev/rad4_kbd` and `/dev/rad4_pntr`.
3. If `rad4X_buffered_server` is on: with arguments from xdm it runs `Xradsgi <args> -rad4 16`; without, `Xradsgi -kybd <kb> -pntr <ptr> -once -rad4 16`.
4. Otherwise with arguments it runs `Xradsgi <args>`; with none it counts boards: `-nr 3` if `/dev/rad4.2` exists, `-nr 2` if `/dev/rad4.1`, plain if `/dev/rad4`, always with `-kybd`, `-pntr` and `-once`.

`/var/rad4/X_psi` (the O2 xdm entry) runs the host's own X server with the xdm arguments plus the output of `rad4_merged`, a script that prints `-nodriver psitech,1280,1024` only when `rad4X_merged_server` is on. The host's X server then loads `psitech.so` as a display-extension module; this is the merged arrangement (section 8).

`Xradsgi` options (`ddxProcessArgument`, `ddxUseMsg`, the manual page; established): `-kybd name`, `-pntr name`, `-rad4 n` (first board number, default 0), `-nr n` (number of boards or screens, 1 to 4, default 1), `-dpi n`, `-vic n`, `-class name`, `-vid n`, `-depth n`, plus the standard X server options. Without `-dpi` the screen is told it has a 13.8 by 11.0 inch visible area (pixel size x 10 / 138 horizontally and / 110 vertically in dots per inch). Order of opens (`InitInput`, `InitOutput`, `init_screen`): the input devices are named at `InitInput`, then each screen is added in order: `hfbInit` (opens `/dev/rad4` or `/dev/rad4.N`, request 113, then 119 clear, then the map and `plock`), `init_ramdac` (16 window-type requests, mask 0x00ffffff, screen on), `cfb32ScreenInit`, then screen hooks, the pointer and the default colormap. The input devices themselves are opened later, from the keyboard and pointer device procedures when X enables them.

## 7. Keyboard and pointer devices

Server side only (inferred, first-pass read of the input procedures at 0x486560 to 0x486d98 and of `ProcessInputEvents` at 0x48738c; the driver's serial side was not read here):

- Keyboard: `open` of the named device read/write non-blocking, retried up to 12 times; a failure is fatal. A STREAMS-style signal-arm ioctl (`0x5309`, arg 1) enables SIGPOLL input. If the device name contains "keyboard" or "kbd" the server writes one byte, 0xfa, and uses the native mode (mode 1); any other name is treated as a terminal: the server fetches and writes back its terminal settings (mode 2). The name `none` disables the device.
- Pointer: same open, signal arm and settings handling; names containing "mouse" or "pntr" select the native mode (mode 1), otherwise mode 2.
- `/dev/rad4_kbd` and `/dev/rad4_pntr` both contain the native-mode substrings. The pointer in native mode is decoded as short relative packets (button bits and signed deltas, sync flag 0x08) and moved with `miPointerDeltaCursor`; the cursor is the hardware cursor (requests 115 to 117, 122, 123).
- In terminal mode the pointer is decoded as six-byte absolute packets (0xff, a status byte whose top bit is set, then two 16-bit coordinates scaled to a 0 to 32767 range by the screen size). A status of 0x90 is a proximity-out and the server issues cursor-off (123); the next absolute packet issues cursor-on (122). In this mode `set_cursor` and `warp_cursor` do not touch the hardware cursor: they write a six-byte packet in the same shape back to the pointer device (so the peer learns the position). The hardware cursor image and colours are then never downloaded by the server (inferred).

## 8. Multi-head arrangements

### 8.1 Unbuffered, several boards in one server (`-nr 2` or `-nr 3`)

Established for the screen and pointer functions (whole functions read): the server adds one X screen per board, numbered from the first board, each with its own device node and its own mapped framebuffer; screens share no pixel buffer. The cursor passes between screens by `cursor_off_screen`: past the right edge, it moves to the next screen and subtracts a width (read from the destination screen record, so equal-sized heads work and unequal heads are mis-offset); past the left edge to the previous one and adds a width. `cross_screen` turns the hardware cursor off and on. Vertical placement is not handled, so only a left-to-right row, in board order, is supported. Colormaps, window attribute tables and LUTs are per screen, because each screen programs its own board.

### 8.2 Buffered, one logical screen over up to four boards

See section 2: one X screen, one shared shadow, boards left to right, one colormap for all.

### 8.3 Second server (`rad4_X_knp` and a second `Xradsgi`)

Unverified. From the string table, the option parser (read in full) and the start of `main`; the event loop was not decoded:

- `rad4_X_knp` is a client of the first display. Options: `-top`, `-bottom`, `-right`, `-left` (side codes 0 to 3), `-server path` (the second server binary), `-help`, and everything else goes to the second server. It creates two pseudo-terminal pairs, one for the keyboard and one for the pointer, starts the second server with `-kybd <tty> -pntr <tty>` appended, and holds a window at the chosen edge of the first screen (the constants suggest a strip about 5 pixels wide; inferred). It grabs the pointer and keyboard while the pointer is over the strip, and forwards events into the two terminals in the same packet shapes `Xradsgi` accepts in terminal mode (the program prints "p e x= y= m= d=..." and "k e kc=..." diagnostics). When the first server dies it reports that and retries after 5 s.
- The second `Xradsgi` therefore runs in terminal mode for both devices (section 7), as a normal `-nr 1` server on `/dev/rad4` (or the board named by `-rad4`).

### 8.4 Merged server (`psitech.so`)

Inferred (module read for its init and probe functions only): the host's X server loads the module for the extra screen. `rad4screenProbe` calls the module's probe (opens `/dev/rad4`, request 113) to get the size; `rad4screenInit` builds the screen like `init_screen` does, but wraps MapWindow, UnmapWindow, CreateWindow, DestroyWindow, CopyWindow and ValidateTree, fills three 256-entry byte tables, and calls `XSGIvcScreenInit`, `rrmInit` and `nmbxScreenInit` (host-server hooks; their purpose was not read). `rad4CursorOn` installs a block handler `pointer_poll` that reads the host's cursor position (`GetSpritePosition`) and calls the module's `rad4_move_cursor` (request 115). `rad4Bell` only prints; `rad4KeyClick`, `rad4InitHW` and `rad4CreateXWindow` do nothing. The module also carries copies of the server's input procedures (`InitInput`, `ProcessInputEvents`, `rad4PostKbdEvent`); whether the host server calls them is unknown. Unlike the standalone server it does not clear the screen at start-up and does not issue 119 or 134. The colormap-install function is named `install_bt463` in the module's symbol table; the name is a leftover (the board's RAMDAC is documented in registers.md), and the function's requests are the ones in section 1.

## Resolves open question 10

The type-3 branches of the dispatcher, the buffered server's drawing paths and the second-server arrangement are described in sections 2 and 8. The DMA submission path and its registers are in xserver-decode.md.

## Differences from xserver-decode.md

- The overlay behaviours there (GC validation rewriting colours for overlay-visual windows, the overlay clear on window moves) depend on `GLoverlay_vid` matching a window's visual ID. In the package's standalone server that array holds -1 and nothing in the package writes it. Either something outside these files sets it in the runs that recorded those behaviours, or the paths are not reached in the standalone server. The overlay-nibble format itself (mask 0x0f000000, shift by 24) is confirmed by the request call sites.
- That page's request table lists 140 as a rectangle copy used by the server; no server issues it, and the buffered node ignores it.
- That page says the dispatcher's type-3 branches were not audited; sections 2.1 and 2.5 give the list of handlers that have one.
- It says the buffered path "moves the screen to the board with DMA"; two further facts: small rectangles (6 pixels wide or fewer, or 32 pixels or fewer in area) use CPU copies even on the type-3 path, and plain cfb32 stores reach the board only through the `rad4d` full-frame loop.

## Not covered / unknown

| Item | What would settle it |
|---|---|
| Writer of `GLoverlay_vid` | a full scan of the server's code for stores through a computed address, then a look at the GL or X libraries it loads at run time; the root-window property of a running standalone server would show whether it is -1 |
| Timer callback behind the 250 ms flag, and why a single-board `rad4d` appears to spin | reading the callback registered by the driver's type-3 write path, and the interrupt path that increments the open count |
| `generate_palette` class details and the overflow case | reading the whole function (about 830 instructions) with the colormap record layout |
| Meaning of RAMDAC indices written by requests 115, 122 to 127 and 134 (0x30, 0x21, 0x1400 region, 0x3000 and 0x3400 regions, index 2 bit 0) | the RGB561 public specification's index map, compared with the indices in the driver's handlers, in a RAMDAC page |
| `rad4_X_knp` event loop, strip geometry, packet shapes, restart logic | reading its `main` with the thunk table resolved for the N32 object |
| Terminal-mode and native-mode packet formats, and the driver's serial queue code | reading `ProcessInputEvents` fully and the driver's `add_to_mouse_queue`, `key_handler` and `translate_key` |
| Whether a start of 16 or 32 in a window attribute entry is meaningful | the RAMDAC specification's attribute field widths |
| Bit 5 pulse at type-3 open (open question 1) | the board-control register effects, which no shipped code decides |
| How the host server calls `psitech.so` and what `-nodriver psitech,1280,1024` fields mean | the host server's binary, which is not in the package |
| Type-3 mode-index width multiplier in request 135 | a re-read of the handler against the board-count variable's other uses |
| Contents of the gamma scale constants in `rad4setres` | the program's constant pool |
