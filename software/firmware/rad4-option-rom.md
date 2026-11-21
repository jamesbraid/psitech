# The RAD4 and RAD4-KM expansion ROM image

The 1.3k package ships the contents of the board's expansion ROM as `var/rad4/rad4_rom` (Motorola S-records) and the board's configuration serial EEPROM as `var/rad4/36500202` (also S-records, 128 bytes). The ROM image is console code for the PsiTech IP27 PROM: it brings the board up, fills in the mailbox and draws text. Read in full for the first image; the second differs in the places noted. Ratings as in [which-firmware.md](which-firmware.md). This page does not repeat the register layout, which is in [../../devices/rad4/README.md](../../devices/rad4/README.md); it records what this code does with it, in order.

## Format

| Item | Value | Rating |
|---|---|---|
| File | `rad4_rom`, 98,296 bytes of S1 records; SHA-256 `d9420b62f7411024f5a3279f80bc6620d40df0cf8bd488b8cea943c2931b9e14`. Decodes to a flat image of 41,476 bytes | established |
| Layout | two PCI expansion ROM images back to back, each starting `55 aa` with a pointer at offset 0x18 to a PCI data structure at 0x1c | established |
| Image 1 | at offset 0: vendor `12d1`, device `0104` (RAD4), declared length 0x4600, "last image" flag clear | established |
| Image 2 | at offset 0x4600: vendor `12d1`, device `0105` (RAD4-KM), declared length 0x5e00, "last image" flag set | established |
| Class code in both | `0x038000`, display controller, other | established |
| Code type in both | `0x7f`, not one of the public types (x86, Open Firmware, PA-RISC, EFI), so vendor-defined | inferred |
| Content | position-independent MIPS code (big-endian, 64-bit), a font, the banner text and, in image 2, keyboard translation tables; the code is entered at image offset 0x74 | established |
| Banner text | "RAD4 Console Ready   Copyright 1998 PsiTech, Inc." at image 1 offset 0x4004 (file offset 0x9b2c in image 2); the initialiser draws it, see below | established |

The decoded data stops 508 bytes short of image 2's declared length; the missing bytes are padding (inferred). A physical ROM chip's capacity is not stated anywhere and stays unknown.

## Entry convention

The PsiTech PROM's boot stage copies the image to node memory so that image offset 0 lands at `0x01800104` and relocates the seven 64-bit pointer slots at image offsets 0x3c to 0x73 ([psitech-ip27-prom.md](psitech-ip27-prom.md#where-the-called-code-comes-from)); the stage's install routine then calls offset 0x74. The entry is a three-way dispatcher in the MIPS position-independent convention: it finds its data through `t9`, which the caller loads with the entry address, and the slot table holds the function addresses it uses (slot values less `0xb4` are image offsets: `0x19e0` is the RAMDAC initialiser at `0x192c`). The first argument is a command:

| Command | Arguments | What it does | Rating |
|---|---|---|---|
| 0 | expansion ROM address, base 2 address, base 0 address | initialise the board and the console | established |
| 1 | a character | draw one character | established |
| 2 | none | image 1: return -1 (no input). Image 2: read one key | established |
| other | | return -1 | established |

For commands 1 and 2 the dispatcher first writes `0xf84303c3` to the bus interface's local bus region descriptor (base 0 plus 0x18) and every command leaves it at `0xf84003c0` on return. The initialiser writes `0xf84303c3` to the same register itself, the value the kernel driver writes at attach.

## Command 0: initialisation

Argument roles: base 2 is the framebuffer and board register window, base 0 the bus interface's runtime registers. In order, with the register names of [../../devices/rad4/registers.toml](../../devices/rad4/registers.toml):

1. Remember base 2 as the framebuffer, base 2 plus `0x800000` as the board register base and base 0 as the bus interface.
2. Write `0xf84303c3` to base 0 plus 0x18.
3. Build a table of register pointers from the board register base: the RAMDAC ports at `+0x100000`, `+0x110000`, `+0x120000` and `+0x130000` (BAR2 offsets `0x900000` to `0x930000`: index low, index high, single-cycle data and multi-cycle data), the timing banks at `+0x200000`, `+0x201000`, `+0x202000` and `+0x203000`, further blocks at `+0x300000`, `+0x400000` and `+0x600000`, the write mask at `+0x500000` and the board control register at `+0x700000`.
4. Write 0 to the board control register.
5. Read the configuration EEPROM: raise chip select (bit 25 of base 0 plus 0x6c), clock a start bit and the 8 bits `0xac` (the read command with word address 0x2c), then read 40 bytes. If the data output (bit 27) is high right after the address the card is taken to have no EEPROM, the 40 bytes become zero and chip select is left raised. This is the sequence and the byte order the driver uses, see [../../devices/rad4/modes.md](../../devices/rad4/modes.md#configuration-eeprom-and-startup).
6. Take the mode index from bits 6:0 of the first word and the three option fields from bits 13:12, 10 and 8, pass them to the mode routine with the index's 40-byte record, and take the record's width and height. The ROM carries the same 13 records, in the same order, as the driver: all 13 widths, heights, refresh labels and clock fields match [../../devices/rad4/modes.md](../../devices/rad4/modes.md) (checked field by field). The mode routine (image offset 0x205c, through the table slot at 0x54), the two timing loaders (the vertical one at 0x2254 through the slot at 0x5c, the horizontal one at 0x23f0 through the slot at 0x64) and the helper in the last slot (0x2c4c) were read in full. The mode routine performs the driver's `set_video_timing` sequence write for write (clear bit 5 of board control, the PLL bytes at RAMDAC indexes 0x21 and 0x22, the vertical then the horizontal timing banks, index 0x20 with 1 or 0x23, set bit 5), and the two loaders are the driver's loaders: their decompiled bodies are identical apart from symbol names, so they write the same words, bit for bit, and the rules are those of [../../devices/rad4/modes.md](../../devices/rad4/modes.md#timing-words) (established; the equality is of two decompilations, each read in full).
7. RAMDAC tables, written through the index and data ports:
   - index `0x3000`, `0x3400` and `0x3800`: 256 entries each through the multi-cycle port, entry `i` then 0, a straight ramp (inferred to be the three gamma tables set to identity);
   - write mask `0xffffffff`.
8. Paint the framebuffer with the helper in the last table slot, twice, at the mode's width and height. It is not a plain clear: it writes every pixel as a gradient (the low byte, the blue channel of the server's pixel layout, is the row times 256 over the height; the next byte, green, is the column times 256 over the width; red is zero), then draws two one-bit bitmaps from the image's data near the lower left of the screen, 70 by 38 and 184 by 41 pixels, first as a shadow (colours `0x404040` and `0x603030`, offset by five pixels) and then by adding the constant `0xd0` to each channel of the pixels under the set bits, without clamping (established, read in full; the bitmaps are not decoded here and are presumed to be PsiTech's logo and name from their size and position, inferred). The driver's `fill_fb`, which stores zero, is a different routine. The text area of step 9 then clears its own cells to background 0 over the gradient.
9. Set the text geometry (below) and the foreground colour to `0xffffff`, clear the text area, draw the cursor and draw the banner "RAD4 Console Ready   Copyright 1998 PsiTech, Inc." through the character routine.
10. Write `0x424f4f21` (the ASCII text "BOO!") to base 0 plus 0x40, the mailbox.

So the mailbox the kernel driver reads at attach is written by this code, with the value `0x424f4f21`, once the console is up (established). That answers who produces it; whether a real Origin 200 PROM ran the code is a separate question: it ran on any board the PsiTech PROM's install routine reached.

The RAMDAC initialiser, at image offset 0x192c and called from command 0 through the first slot after the mode is loaded, writes: index `0x0001` nine bytes `2c 19 41 45 00 00 00 00 00`; `0x0010` four bytes `00 00 0f 0f`; `0x0030` ten bytes `60` then zeros; `0x0040` fifteen zeros; `0x0050` seven zeros; `0x005f` `04`; `0x0082` `00`; `0x0e00` sixteen zeros; `0x0f00` sixteen `0x28`; `0x1000` and `0x1400` 256 entries each of two cycles (`0d`, `80` and `0c`, `40`); `0x0a11` the six bytes `00 00 00 ff ff ff`; `0x0a15` `ff ff 00 00 00`. The ports and indexes are the ones the driver uses ([../../devices/rad4/README.md](../../devices/rad4/README.md#ramdac-registers-the-software-uses)).

## Command 1: drawing a character

The code draws straight into the 32-bit framebuffer from the host; it issues no command to any drawing logic and uses no DMA. A character cell is 8 pixels wide and 15 high, so (established, read in full):

| Property | Value |
|---|---|
| Text rows | height divided by 15, or 34 when the height is 510 or more |
| Text columns | width divided by 8, or 80 when the width is 640 or more |
| Origin | the text area is centred: half the leftover pixels on each side |
| Pixel | 32 bits: foreground `0xffffff`, background 0; the board's own colour tables are not involved |
| Font | 128 glyphs of 15 bytes, most significant bit leftmost, at image 1 offset 0x3104 (image 2: file offset 0x8c2c); the glyphs are a plain bitmap face with two blank bottom rows |
| Printable | 0x20 to 0x7f |
| Controls | CR to column 0; LF down a row; FF clear the text area and home; BS back one column; HT eight spaces. Nothing else is interpreted: no escape sequences, no colours |
| Cursor | a 6 by 13 pixel block inset one pixel into the cell, drawn by inverting its 24 colour bits (a toggle). It is toggled after every command, and before the move for CR, LF and BS; a printable character overwrites it |
| Scroll | LF on the last row copies the lower half of the text area up, clears the lower half and puts the cursor at the middle row: a half-screen jump |
| Wrap | at the last column the cursor goes to the next line start and a scroll as above |

The geometry constants (cell 8 by 15, 80 by 34 at most, centring) are the same ones the kernel driver's own text screen uses (established, from the driver's initialiser; see [console-selection.md](console-selection.md)).

## Command 2: the RAD4-KM keyboard

Image 2 only (established, read in full). It reads a scan code with a helper that was not read, and then:

- treats `0xf0` as the break prefix and keeps a bit map of held keys;
- translates codes below 0x88 through a pair of tables (plain and shifted, two bytes per code) that sit with the font; the same tables hold the ASCII pairs "zZsSaAwW", "cCxXdDeE", "nNbBhHgGyY" and so on. An earlier reading took the layout for a PC AT set 2 keyboard; the kernel driver's table, which has the same special codes, is a set 3 layout (function keys at 0x07, 0x0f, 0x17 and so on, Caps Lock at 0x14, Num Lock at 0x76, shift at 0x12 and 0x59, control at 0x11 and 0x58), and the driver puts the keyboard in set 3 explicitly ([../rad4/kernel-driver.md](../rad4/kernel-driver.md#keyboard-pointer-and-escape-sequences)). This image's table (image 2, offset 0x5564, 272 bytes) is byte-for-byte the driver's (compared), so it is the same set 3 layout (established for the table, inferred for what keyboard mode the ROM's own scan-code helper, which was not read, expects);
- handles caps lock (`0x8d`), num lock (`0x8e`), the shift keys (`0x9c`, `0x9d`) and the control keys (`0x9a`, `0x9b`), and applies control by masking to the low five bits;
- waits for a key by polling bit 4 of the board control register, with a counter derived from the argument; with a zero argument it returns -1 at once when no key is waiting.

The PsiTech PROM never calls command 2. The use of board control bit 4 here is new evidence for the open question on that register (see [../../questions/open-questions.md](../../questions/open-questions.md)); its meaning is unknown.

## The configuration EEPROM image

`var/rad4/36500202` holds a 128-byte image (SHA-256 `9caa82c0b75366409af6c4f06304b7d45940c6e98c25702bdb28e04d9d750a41`). Read as little-endian halfwords it starts `0105`, `12d1`, `0380`, `0002`, which is a device ID of `0105` and a vendor ID of `12d1` followed by the class and revision words in the order the PLX serial EEPROM format uses (inferred from the values: the class matches the ROM's `0x038000`). The last 40 bytes, the block the mode word comes from, are all zero, so a card programmed from it starts in mode 0 (1280 by 1024 at 60 Hz) with no option bits (established, bytes read). The programming tool `rad4_prog` is a small command-line program that talks to `/dev/rad4` (not read beyond its strings); the ROM file name suggests the package intended both files for the board's own programmers (inferred).

## Review note

Independent review, 2026-11-21 (not the author). The ROM's 272-byte keyboard table was compared with the driver's: identical over the whole table. The offsets of the mode routine, the loaders and the paint helper, and the gradient description, were not re-derived.
