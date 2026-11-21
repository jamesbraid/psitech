# rad1: display modes, clocks and the settings sector

The stock RAD1 software carries three display modes, a table of memory-width partial products, and one mode word kept in the board's flash. This page records what the mode loader writes for each. Ratings are as defined in [README.md](README.md). Everything here was read from the tables in `rad1data.o` (member of `rad1pci.a`) and the mode loader in `rad1_init.o` (established), and the same loader in the IO6 PROM 6.156 agrees with it. The PROM's table is longer than the driver's: see "The PROM's own table" below.

## The three modes

The table holds three records, in this order. The driver's own counts are per 64-bit unit for the horizontal values, which at 32 bits a pixel is two pixels, and in lines for the vertical values.

| Index | Visible | Label rate | Horizontal total | Sync start | Sync end | Blank end | Gate end | Vertical total | V sync start | V sync end | V blank end | Stride | Clock M | N | P |
|--:|---|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
| 0 | 1280 by 1024 | 60 Hz | 1687 | 48 | 160 | 408 | 408 | 1064 | 0 | 3 | 41 | 640 | 181 | 12 | 1 |
| 1 | 1280 by 1024 | 72 Hz | 1695 | 32 | 192 | 416 | 416 | 1062 | 2 | 5 | 39 | 640 | 183 | 10 | 1 |
| 2 | 1024 by 768 | 60 Hz | 1327 | 48 | 112 | 304 | 304 | 798 | 0 | 4 | 31 | 512 | 219 | 49 | 0 |

The three 1024-class modes the product sheet lists are 1280 by 1024, 1024 by 768 and 1024 by 1024. The stock driver's table has the first two only; a 1024 by 1024 record is not in the shipped table (established, table read in full).

How the loader writes a record to the chip (established, loader read in full):

- The horizontal total, gate end, blank end, sync start and sync end are each written divided by two (integer division), into the horizontal total, gate end, blank end, sync start and sync end registers. The vertical values are written as they are. The two 1280-wide records give a stride of 640 units, which is 1280 pixels, and the 1024 record 512.
- The video FIFO control register gets 0x0b07, the screen base gets 0, the screen size gets the visible width and height, and the packed-data X limit gets the width minus one.
- The memory-width partial products for the visible width are looked up in the 33-row table and written to the framebuffer read, bypass DMA, local buffer read and texture map format registers. A width not in the table falls back to the zero row.
- The video control word is built from: refresh enabled, blank active high, 64-bit data, active-high sync outputs. Refresh is turned off while the clock and timing are programmed and turned on again afterwards. The legacy VGA core is switched off first with one store to the SVGA control register.

## The PROM's own table

The IO6 PROM 6.156 holds eight records of the same 68-byte layout, in a table of its own; its start-up routine compares the mode word's index (bits 6 to 0) with a limit word stored in the data right after the table and prints "rad1 resolution unknown mode" and uses index 0 with the options cleared when the index is not below it (established: the table and the compare were read in the image's decompilation). The limit is 8. It is the seventeenth word of the last record, which in every other record is zero padding, so a reading that stops at the padding sees three records and a limit that is not a record at all.

| Index | Visible | Label rate | Total, blank end | Vertical total | Same record in the kernel's table |
|--:|---|--:|---|--:|---|
| 0 | 1280 by 1024 | 60 Hz | 1687, 408 | 1064 | index 0 |
| 1 | 800 by 600 | 75 Hz | 1055, 256 | 624 | none |
| 2 | 1280 by 1024 | 72 Hz | 1695, 416 | 1062 | index 1 |
| 3 | 640 by 480 | 72 Hz | 847, 208 | 522 | none |
| 4 | 800 by 600 | 56 Hz | 1023, 224 | 624 | none |
| 5 | 1024 by 768 | 60 Hz | 1327, 304 | 798 | index 2 |
| 6 | 1024 by 768 | 70 Hz | 1327, 304 | 805 | none |
| 7 | 1024 by 1024 | 60 Hz | 1327, 304 | 1063 | none |

Records 0, 2 and 5 are word for word the kernel's three records (established, compared). The 1024 by 1024 record the product sheet lists is therefore present in the PROM and absent from the kernel's table (see above).

## Clock arithmetic

The pixel clock is programmed through the RAMDAC's phase-locked loop as multiplier M, prescale N and a power-of-two postscale P: the frequency is 14318180 Hz times M, divided by N times two to the P (established: the loader's own recovery-time arithmetic uses exactly this formula). That gives, per mode, with the refresh rate taken as the clock divided by the line length in pixels and by the frame length in lines:

| Index | Pixel clock | Horizontal total (pixels) | Vertical total (lines) | Rate by this arithmetic | Label |
|--:|--:|--:|--:|--:|--:|
| 0 | 107.983 MHz | 1688 | 1065 | 60.07 Hz | 60 Hz |
| 1 | 131.011 MHz | 1696 | 1063 | 72.67 Hz | 72 Hz |
| 2 | 63.993 MHz | 1328 | 799 | 60.31 Hz | 60 Hz |

The horizontal total in pixels is the table value plus one, the vertical total is the table value plus one (inferred: the table's comments call the counts "minus one", and this reading reproduces the 1688-pixel line of the VESA 1280 by 1024 at 60 Hz timing for record 0). The rate column therefore differs from the label by up to 0.7 Hz, and which of the two is the physical refresh is unknown. The PLL's recovery time field is four times the pixel clock divided by 33 MHz, with a floor of five (established).

The memory clock is programmed the same way at start-up: M 128, N 11, P 1, which is 83.3 MHz (established).

## Memory-width partial products

The 33-row table maps a visible width (0, 32, 64, 96, 128, then steps up to 2048) to three small integers. Each row satisfies one identity: the width is sixteen times the sum of two to the power of each nonzero integer (inferred: checked arithmetically on all 33 rows, no row fails). It matches the chip's partial-product scheme for line stride in the public Permedia 2 documentation family.

## The mode word in flash

The mode word is item 0 of a 128-byte settings sector at offset 0xff00 of the 64 KiB flash, which is 256 bytes below its end; the other sector below it is unused by the stock software (established). The sector is read byte by byte into a buffer with each byte index exclusive-ored with 3, which converts the big-endian word layout to the byte order the flash is wired in (established). The loader reads the word at attach and at start-up in the PROM, with these fields:

| Bits | Meaning | Rating |
|---|---|---|
| 6 to 0 | mode index into the table above | established |
| 8 | horizontal sync polarity: 0 negative, 1 positive | established |
| 10 | vertical sync polarity: 0 negative, 1 positive | established |
| 13 to 12 | sync type: 0 separate, 1 composite on horizontal sync, 2 sync on green | established |

The kernel driver accepts an index below 4 and uses index 0 with negative polarities and separate sync for anything else; the PROM accepts an index below 8, the limit its own table carries (the next section). The kernel's limit is one too high for its three-record table: an index of 3 would read past the table (established, comparison constants read in both binaries; the effect is unobserved). The two tables number their modes differently, so one mode word means different modes to the PROM and to the kernel: indexes 1 and 2 are 1280 by 1024 at 72 Hz and 1024 by 768 at 60 Hz in the kernel's table and 800 by 600 at 75 Hz and 1280 by 1024 at 72 Hz in the PROM's (established, both tables read; the consequence for a real card's console is inferred). The Permedia 2V path programs the sync polarity into the RAMDAC's sync control register; sync on green is not supported on that chip and is reported only (established). On the other chip the polarity and sync-on-green bits go into the RAMDAC misc control register.

The mode-change request writes the word back to flash when it changed, one 128-byte sector at a time, with the standard unlock; see [../../software/rad1/kernel-driver.md](../../software/rad1/kernel-driver.md#settings-sector-and-flash). A factory-fresh flash content, and therefore the mode a new card starts in, is unknown: no flash dump has been found.
