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

The table is established (read from the binary). Every mode is four bytes per pixel with a row stride of four times its width; that is the driver's software stride, and the board's scanout pitch is inferred to match. The largest image, mode 11, takes 8,294,400 bytes and fits the 8 MiB framebuffer.

## Mode programming sequence

One routine programs any record, so the register write order is the same for all modes (established, from the binary):

1. Clear bit 5 of board control.
2. Write 0x21 to the RAMDAC index low port and zero to the index high port, then the record's two PLL bytes to the data port.
3. Write the vertical total's worth of words to the vertical timing bank.
4. Write the horizontal total's worth of words to each of the three horizontal banks.
5. Write index 0x20 and its sync value: 1, or 0x23 when the selector field of the EEPROM configuration word (bits 12 and 13) equals 2.
6. Set bit 5 of board control.

Only the PLL bytes, the bank lengths and the bank contents depend on the mode. In every record the horizontal total is a quarter of the width plus the horizontal blank, and the vertical total is the height plus the vertical blank, so horizontal words count four-pixel groups (established as a table property; consistent with the 4:1 serializer the general initialisation selects, which is inferred for the board). Parameters 2 and 3 are inferred to be sync start and end counted from the start of blanking: mode 0 then has the 48-pixel front porch and 112-pixel sync of the VESA 1280 by 1024 at 60 Hz timing.

### Option fields

The mode routine also takes three fields of the configuration word: bit 8 goes to the horizontal loader, bit 10 to the vertical loader, and the selector in bits 12 and 13 to both and to the sync value (established, from the binary). They change the contents of the timing banks and the sync value but not the bank lengths or the PLL bytes. Of the 16 combinations, eight give distinct write sequences for each mode, 104 across the table. `rad4setres` builds its mode word as the mode index ORed with `(hsp & 3) << 8`, `(vsp & 3) << 10` and `(sync & 3) << 12`; its usage text names the fields horizontal sync polarity, vertical sync polarity (0 negative, 1 positive) and sync type (0 separate, 1 composite, 2 sync on green), with negative polarity and sync on green the defaults. These are the vendor's labels. What the fields do electrically is unknown, and so is selector 3, which the tool and driver accept but the usage text does not name.

Modes 4 and 11 program the same PLL bytes, as do modes 5 and 6, and modes 2 and 3 write identical timing banks, so only the whole sequence identifies a mode.

## Pixel clock arithmetic

The RGB561 specification gives the PLL output as `M * fref / (N * L)` for range code 3 and `M * fref / (2 * N * L)` otherwise, with M the index 0x21 value in bits 5 to 0 plus 65, N the index 0x22 value in bits 4 to 0 and L equal to 4, 2, 1 for range codes 0, 1, 2 (and, as it turns out, 1 for code 3). With a 33 MHz reference this reproduces the clock field of all 13 records to the hertz, taking the range code from bits 7 and 6 of the index 0x21 byte. Checked by hand against the table above for all 13 records. That is software consistency, not a measurement: the 33 MHz reference and the range code position are inferred, and a board photograph or a frequency measurement would settle them.

Mode 9 asks for 64.2 MHz with range code 2, which the specification gives for 65 to 128 MHz; whether the PLL locks there is unknown. The label rate is not the rate the clock gives: `clock / (4 * htotal * vtotal)` differs from the label by up to 0.6 Hz (inferred clock, so the difference is approximate).

## How software learns and changes the mode

The geometry requests return the current geometry and label (request 113) or any record's (request 135). The mode-change request (114) rejects a word whose index field (bits 0 to 6) is 13 or more, runs the mode routine at once, records the new geometry, reruns the RAMDAC general initialisation, clears the framebuffer at the new size and writes the EEPROM record. The X server reads the geometry once at startup through request 113, maps four times width times height bytes and never issues request 114, so a mode change takes effect at the next X server start, without a reboot (established, from the driver and server binaries).

## Configuration EEPROM and startup

At attach the driver reads 40 bytes from byte address 0x58 of a serial EEPROM through the bus interface's EEPROM control register. The serial reader raises chip select (bit 25), clocks a start bit and the read command with word address 0x2c, requires the data output (bit 27) to read zero right after the last address bit, then clocks each data bit by raising and lowering the clock (bit 24) and sampling bit 27 after the fall. Each word's first eight bits go into the odd byte of the buffer and the next eight into the even byte (established, from the binary). The first reconstructed word supplies the mode index (bits 0 to 6), option bits 8 and 10 and the selector (bits 12 and 13).

The commands are the 93C46's in 64 by 16 organisation: READ, WRITE, EWEN and EWDS, each a start bit, two opcode bits and six address bits. The opcode match is established from the driver; that the part is a 93C46 is inferred.

When the mode-change request supplies a word that differs from the first word of the record, the driver stores it and writes all 40 bytes back to byte 0x58: the writer sends EWEN, then for each word a start bit, the write command with the word address and 16 data bits (odd buffer byte first, on data bit 26), drops chip select, raises it again and polls the data output with 1 ms delays and no timeout until it reads one, then sends EWDS (established, from the binary). So the new mode holds at the next attach. After `rad4setres 9` (word `0x2009`), word 0x2c reads zero and word 0x2d reads `0x0920`.

The package also carries a ROM programming image whose initialiser performs board setup and writes a nonzero marker to the mailbox. The driver treats a nonzero mailbox as completed firmware initialisation and skips its own mode and RAMDAC setup; a zero mailbox selects driver-side setup. That is two software paths, not a reset state: the image is not a board dump, and what a real card holds in the mailbox after power-on is unknown. Whether an Origin 200 startup ever runs the supplied initialiser, and the relationship between its controller argument and BAR0, are unknown.
