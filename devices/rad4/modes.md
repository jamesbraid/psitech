# rad4 display modes, mode programming and the configuration EEPROM

How the driver picks and programs a display mode, from the driver and the `rad4setres` tool of release 1.3k, with the RGB561 and 93C46 public datasheets. Ratings are as defined in [README.md](README.md).

## The mode table

The driver holds 13 mode records of 40 bytes, big-endian, in its data; the count, 13, sits beside them (established, read from the binary). Each record:

| Bytes | Field | Use found in the driver |
|---|---|---|
| 0 to 3 | zero in every record | none |
| 4 to 11 | width and height in pixels | stored as the current geometry at attach and by the mode-change request; returned by the geometry requests; the width is the row pitch of rectangle addressing |
| 12 to 15 | refresh label in Hz | stored and returned like the geometry; never programmed into hardware |
| 16 to 23 | horizontal total, blank, parameter 2, parameter 3, in four-pixel words | horizontal timing loader |
| 24 to 31 | vertical total, blank, parameter 2, parameter 3, in lines | vertical timing loader |
| 32 to 35 | pixel clock in Hz | no reader found |
| 36, 37 | RGB561 index 0x21 and 0x22 bytes (PLL) | the mode routine |

| Mode | Geometry | Label (Hz) | Row stride (bytes) | PLL bytes (0x21, 0x22) | Clock field (Hz) | H total, V total |
|--:|---|--:|--:|---|--:|---|
| 0 | 1280 x 1024 | 60 | 5120 | 0x87, 0x0b | 108,000,000 | 422, 1065 |
| 1 | 1280 x 1024 | 72 | 5120 | 0xee, 0x1c | 130,821,428 | 424, 1063 |
| 2 | 1600 x 1200 | 60 | 6400 | 0xc7, 0x10 | 148,500,000 | 500, 1237 |
| 3 | 1600 x 1200 | 72 | 6400 | 0xd0, 0x0f | 178,200,000 | 500, 1237 |
| 4 | 2048 x 1000 | 60 | 8192 | 0xe6, 0x11 | 199,941,176 | 781, 1061 |
| 5 | 1200 x 1600 | 76 | 4800 | 0xfb, 0x16 | 186,000,000 | 368, 1656 |
| 6 | 1600 x 1200 | 79 | 6400 | 0xfb, 0x16 | 186,000,000 | 468, 1256 |
| 7 | 640 x 480 | 72 | 2560 | 0x1c, 0x0c | 31,968,750 | 212, 523 |
| 8 | 800 x 600 | 56 | 3200 | 0x5f, 0x16 | 36,000,000 | 256, 625 |
| 9 | 1024 x 768 | 60 | 4096 | 0xac, 0x1c | 64,232,142 | 332, 799 |
| 10 | 1024 x 768 | 70 | 4096 | 0xa3, 0x16 | 75,000,000 | 332, 806 |
| 11 | 1920 x 1080 | 75 | 7680 | 0xe6, 0x11 | 199,941,176 | 591, 1125 |
| 12 | 1024 x 1024 | 60 | 4096 | 0xa6, 0x14 | 84,975,000 | 332, 1064 |

The eight timing counts of each record, in four-pixel words for the horizontal set and lines for the vertical set, and the refresh rate the clock field gives (`clock / (4 * htotal * vtotal)`, inferred because it uses the 33 MHz reference):

| Mode | H total, blank, p2, p3 | V total, blank, p2, p3 | Rate from the clock (Hz) |
|--:|---|---|--:|
| 0 | 422, 102, 12, 40 | 1065, 41, 1, 3 | 60.08 |
| 1 | 424, 104, 8, 48 | 1063, 39, 3, 3 | 72.56 |
| 2 | 500, 100, 5, 46 | 1237, 37, 0, 3 | 60.02 |
| 3 | 500, 100, 5, 46 | 1237, 37, 0, 3 | 72.03 |
| 4 | 781, 269, 6, 46 | 1061, 61, 0, 3 | 60.32 |
| 5 | 368, 68, 26, 47 | 1656, 56, 3, 3 | 76.30 |
| 6 | 468, 68, 26, 47 | 1256, 56, 3, 3 | 79.11 |
| 7 | 212, 52, 7, 17 | 523, 43, 9, 3 | 72.08 |
| 8 | 256, 56, 6, 24 | 625, 25, 2, 2 | 56.25 |
| 9 | 332, 76, 12, 28 | 799, 31, 1, 4 | 60.54 |
| 10 | 332, 76, 6, 40 | 806, 38, 3, 6 | 70.07 |
| 11 | 591, 111, 8, 43 | 1125, 45, 3, 3 | 75.18 |
| 12 | 332, 76, 6, 14 | 1064, 40, 4, 3 | 60.14 |

The record bytes are: horizontal total at 16 to 17, blank at 18 to 19, parameters 2 and 3 at 20 to 23, the vertical set at 24 to 31, the clock at 32 to 35, the two PLL bytes at 36 and 37 and zero padding at 38 to 39. The loaders write at most 1656 vertical words (mode 5) and 781 horizontal words per bank (mode 4), which is the room the timing banks must have. Each timing count set is table data; every timing-memory word is computed by the two loaders, and so are the sync value and the board-control bracket (which the loader takes from a saved control word, not a constant). The table is established (read from the binary). Every mode is four bytes per pixel with a row stride of four times its width; that is the driver's software stride, and the board's scanout pitch is inferred to match. The largest image, mode 11, takes 8,294,400 bytes and fits the 8 MiB framebuffer.

The shipped header `rad4pci.h` names only seven modes (0 to 6) and gives index 0 the 72 Hz label and index 1 the 60 Hz label for 1280 by 1024, the opposite of the driver's table above (established, both read). The header's other five constant names do match the table's geometry and label for modes 2 to 6. Which ordering a real card's EEPROM follows is unknown; the factory default of index 1 recorded further below favours the table.

## Mode programming sequence

One routine programs any record, so the register write order is the same for all modes (established, from the binary):

1. Clear bit 5 of board control.
2. Write 0x21 to the RAMDAC index low port and zero to the index high port, then the record's two PLL bytes to the data port.
3. Write the vertical total's worth of words to the vertical timing bank.
4. Write the horizontal total's worth of words to each of the three horizontal banks.
5. Write index 0x20 and its sync value: 1, or 0x23 when the selector field of the EEPROM configuration word (bits 12 and 13) equals 2.
6. Set bit 5 of board control.

Only the PLL bytes, the bank lengths and the bank contents depend on the mode. In every record the horizontal total is a quarter of the width plus the horizontal blank, and the vertical total is the height plus the vertical blank, so horizontal words count four-pixel groups (established as a table property; consistent with the 4:1 serializer the general initialisation selects, which is inferred for the board). Parameters 2 and 3 are the front porch and the sync end, counted from the start of blanking in words, horizontally; vertically they are the front porch and the sync width in lines (inferred: the loaders' structure and a comparison with VESA timings, in the section below).

### Timing words

The horizontal loader (`load_horiz_video_timing_ram`) and the vertical loader (`load_vert_video_timing_ram`) were read in full in the driver, and the option ROM's two loaders are the same code (the decompilations are identical apart from symbol names). Take horizontal total T, blank B and parameters S and E for a record, in words; the loop index `i` runs over 0 to T minus 1. `sel` is the sync-type selector (bits 12 and 13 of the configuration word) and `hp` and `vp` the polarity options (bits 8 and 10). Every word is built from the bits below and nothing else (established, from the binary):

| Bank | Bit | Set when | What it looks like (inferred) |
|---|--:|---|---|
| horizontal bank 0 (first) | 3 | `i >= B` | display enable: blanking occupies the first B words of a line and the visible part is the last T minus B |
| horizontal bank 0 | 1 | `B - 2 <= i < T - 2` | the same window two words early: a fetch or pipeline lead |
| horizontal banks 0, 1 and 3 | 0 and 2 | `i == T - 2` | an end-of-line mark, both bits together |
| horizontal banks 0 and 1 | 6 | `i < S` or `i >= E` | the sync window, inverted: clear for `S <= i < E` |
| horizontal bank 3 | 6 | `S <= i < E` | the same window, not inverted |
| horizontal banks 0 and 1 | 7 | outside `S + 5 <= i < E + 5`: set when `sel` is 1 or 2, or `hp` is 0; inside: set only when `sel` is 0 and `hp` is 1 | the sync output, delayed five words, in the polarity `hp` selects when the sync is separate (`sel` 0); a fixed negative pulse for `sel` 1 and 2; for `sel` 3 the bit follows `hp` outside the window and is never set inside it |
| horizontal bank 3 | 7 | outside the delayed window: set only when `sel` is 0 and `hp` is 0; inside: set when `sel` is 1 or 2 or `hp` is 1 | the same level as banks 0 and 1 for `sel` 0, the complement of it for `sel` 1 and 2, and neither for `sel` 3 |
| vertical | 6 | `i < B - S` or `i >= T - S` | vertical blank: the window is the B blank lines shifted earlier by S lines |
| vertical | 1 | `i < E` | the sync-pulse lines, at the start of the frame |
| vertical | 7 | on the pulse lines: set when `sel` is 1 or (`sel` 0 and `vp` 1); on the others: set unless `sel` is 0 and `vp` is 1 | the vertical sync output; held high for `sel` 1, the composite case |
| vertical | 0 | `i == T - 1` | the last line of the frame |

The register block's fourth horizontal slot, one 4 KiB step above bank 1, is built by the driver and never written by either loader.

So the fields the table gives are, in order: horizontal total, blank, front porch (S), sync end (E) and, vertically, total, blank, front porch, sync width. The names are a reading, not a statement about the board, but three of the modes checked agree with the VESA tables for their resolution and rate: mode 10 (1024 by 768 at 70 Hz) reproduces every number, horizontally 1328 total, 304 blank, 24-pixel front porch and 136-pixel sync, and vertically 806 total, 38 blank, 3-line front porch and 6-line sync; mode 0 (1280 by 1024 at 60 Hz) has the 1688-pixel line, 48-pixel front porch and 112-pixel sync and the 1-line front porch and 3-line sync, with a frame one line short; mode 8 (800 by 600 at 56 Hz) matches horizontally and has the 2-line sync but a 2-line front porch. Modes 7 and 9 differ from the VESA totals (mode 7's line is 848 pixels, not 832, and mode 9's 1328, not 1344); modes 1 to 6 and 11 and 12 were not compared. The meaning of each parameter is inferred, since only the vendor's code and the VESA tables are compared; the bit rules above are established.

Bank depth: the loaders write T words to each horizontal bank (781 at most, mode 4) and the frame's lines to the vertical bank (1656 at most, mode 5), so the banks hold at least that many words. The bank spacing in the register map is 4 KiB, which is 1024 words, and nothing in the shipped software writes past the lengths above, so the real depth is unknown: no shipped software or published source depends on it.

### Option fields

The mode routine also takes three fields of the configuration word: bit 8 goes to the horizontal loader, bit 10 to the vertical loader, and the selector in bits 12 and 13 to both and to the sync value (established, from the binary). They change the contents of the timing banks and the sync value but not the bank lengths or the PLL bytes. Of the 16 combinations, eight give distinct write sequences for each mode, 104 across the table. `rad4setres` builds its mode word as the mode index ORed with `(hsp & 3) << 8`, `(vsp & 3) << 10` and `(sync & 3) << 12`; its usage text names the fields horizontal sync polarity, vertical sync polarity (0 negative, 1 positive) and sync type (0 separate, 1 composite, 2 sync on green), with negative polarity and sync on green the defaults. These are the vendor's labels. What the fields do electrically is unknown, and so is selector 3, which the tool and driver accept but the usage text does not name.

Modes 4 and 11 program the same PLL bytes, as do modes 5 and 6, and modes 2 and 3 write identical timing banks, so only the whole sequence identifies a mode.

## Pixel clock arithmetic

The RGB561 specification gives the PLL output as `M * fref / (N * L)` for range code 3 and `M * fref / (2 * N * L)` otherwise, with M the index 0x21 value in bits 5 to 0 plus 65, N the index 0x22 value in bits 4 to 0 and L equal to 4, 2, 1 for range codes 0, 1, 2 (and, as it turns out, 1 for code 3). With a 33 MHz reference this reproduces the clock field of all 13 records to the hertz, taking the range code from bits 7 and 6 of the index 0x21 byte. Checked by hand against the table above for all 13 records. That is software consistency, not a measurement: the 33 MHz reference and the range code position are inferred, and a board photograph or a frequency measurement would settle them.

Mode 9 asks for 64.2 MHz with range code 2, which the specification gives for 65 to 128 MHz; whether the PLL locks there is unknown. The label rate is not the rate the clock gives: `clock / (4 * htotal * vtotal)` differs from the label by up to 0.6 Hz (inferred clock, so the difference is approximate).

## How software learns and changes the mode

The geometry requests return the current geometry and label (request 113) or any record's (request 135). The mode-change request (114) rejects a word whose index field (bits 0 to 6) is 13 or more, runs the mode routine at once, records the new geometry, reruns the RAMDAC general initialisation, clears the framebuffer at the new size and writes the EEPROM record. A mode index of 13 or more makes request 114 fail with error 6. Request 135 given a negative index returns the current mode and its index, which is what lists the modes in `rad4setres`. On the separate buffered (type 3) device request 113 returns a multiplied width instead; that case was not analysed. The X server reads the geometry once at startup through request 113, fills the screen with request 119, maps four times width times height bytes rounded up to 16 KiB and never issues request 114 or 135, so a mode change takes effect at the next X server start, without a reboot (established, from the driver and server binaries).

## Configuration EEPROM and startup

At attach the driver reads 40 bytes from byte address 0x58 of a serial EEPROM through the bus interface's EEPROM control register. The serial reader raises chip select (bit 25), clocks a start bit and the read command with word address 0x2c, requires the data output (bit 27) to read zero right after the last address bit, then clocks each data bit by raising and lowering the clock (bit 24) and sampling bit 27 after the fall. Each word's first eight bits go into the odd byte of the buffer and the next eight into the even byte (established, from the binary). The first reconstructed word supplies the mode index (bits 0 to 6), option bits 8 and 10 and the selector (bits 12 and 13).

The commands are the 93C46's in 64 by 16 organisation: READ, WRITE, EWEN and EWDS, each a start bit, two opcode bits and six address bits. The opcode match is established from the driver; that the part is a 93C46 is inferred.

When the mode-change request supplies a word that differs from the first word of the record, the driver stores it and writes all 40 bytes back to byte 0x58: the writer sends EWEN, then for each word a start bit, the write command with the word address and 16 data bits (odd buffer byte first, on data bit 26), drops chip select, raises it again and polls the data output with 1 ms delays and no timeout until it reads one, then sends EWDS (established, from the binary). So the new mode holds at the next attach (established for the driver's writes; not observed on a real card). A period installation page records a factory default resolution of index 1 (1280 x 1024 at 72 Hz), which suggests real EEPROMs often held index 1 rather than 0 (inferred; the page may describe another release). After `rad4setres 9` (word `0x2009`), word 0x2c reads zero and word 0x2d reads `0x0920`.

The package also carries a ROM programming image whose initialiser performs board setup and writes a nonzero marker to the mailbox. The driver treats a nonzero mailbox as completed firmware initialisation and skips its own mode and RAMDAC setup; a zero mailbox selects driver-side setup. That is two software paths, not a reset state: the image is not a board dump, and what a real card holds in the mailbox after power-on is unknown. Whether an Origin 200 startup ever runs the supplied initialiser, and the relationship between its controller argument and BAR0, are unknown.

## Review note

Independent review, 2026-11-21 (not the author). Re-read in `var/sysgen/boot/rad4pci.o` (the Origin 200 and Octane build, decoded from the release archive, SHA-256 matches `references/binaries.md`): the vertical loader bit by bit, the horizontal loader's window comparisons, the five-word sync delay, the end-of-line mark at T minus 2, and the constant 2 that `set_video_timing` passes as the fetch lead. Error fixed: for horizontal banks 0 and 1, bit 7 outside the delayed sync window is set when the sync type is 1 or 2, or when the horizontal polarity option is 0 (the table said it is set unless type 0 with polarity 1, which is wrong for type 3 with polarity 1). The vertical rules, the bank-3 rules and the other horizontal bits hold. The VESA comparisons were not repeated.
