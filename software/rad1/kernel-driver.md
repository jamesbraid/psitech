# The stock RAD1 kernel driver

What SGI's IRIX 6.5.30 kernel driver for the RAD1 does, from `rad1drv.o`, `rad1_init.o`, `rad1_tpinit.o`, `rad1_tport.o` and `rad1data.o` (members of `rad1pci.a`, the IP27 kernel object directory). Ratings are as defined in [../../devices/rad1/README.md](../../devices/rad1/README.md). A software expectation says what the software assumes the board does.

**Reading status.** Read in full in the shipped objects, and so graded as software expectations or established as marked: the PCI registration, the attach routine's first half (state limits, the resource mappings with their selector numbers and sizes, the clock-control branch and the interrupt enable value), the interrupt handler, the request jump table, the mode loader and chip initialiser, the early-console registration and the flash programming routine. The rest was traced from an earlier description of the same driver and checked only for register offsets, constants and call targets, so it is graded inferred and each such passage ends with "Unverified.": the DMA register sequences, the start-up screen fill, the palette ramp, the per-request behaviour, detach, and read, write and map. The registers are in [../../devices/rad1/registers.md](../../devices/rad1/registers.md); the console path is in [textport.md](textport.md); the modes are in [../../devices/rad1/modes.md](../../devices/rad1/modes.md).

## Files and configuration

The driver is linked into the kernel when the system file asks for it: the shipped system file names it in a block that only the IP27 kernel family reaches, and its master file declares four tunables (established, both files read):

| Tunable | Shipped value | Meaning |
|---|---|---|
| user-buffer mode | 1 | map the caller's own pages for DMA instead of copying; 0 when memory is short |
| maximum DMA area | 204800 bytes | the most host memory one DMA transfer covers; the attach routine raises anything below 0x80 to 0x80 (one PCI cache line) and the DMA map is sized to at least 8 KiB |
| no DMA | 0 | 1 turns off the DMA paths and leaves programmed I/O |
| prefetch | 1 | selects prefetching DMA mappings; 0 selects non-prefetching ones |

## Registration (initialisation entry)

The initialisation entry registers the driver for two PCI identities with the driver prefix `rad1`: `104c:3d07` and `3d3d:0009`, with no subsystem match, and takes the DMA mapping flags from the prefetch tunable (established). It fails only if both registrations fail. The kernel therefore attaches to any card that presents either chip identity, whoever made it.

## Attach

Per board, in order (software expectation, the routine read in full):

1. Refuse a fifth board. Allocate the board state and, for the buffered path below, an 8 MiB physically contiguous host buffer per board. Record the board number and whether DMA is enabled (the no-DMA tunable).
2. Initialise the locks and five wait queues: GP sync, bypass-DMA write, output-DMA read, palette load and window load.
3. Map the resources, by selector number: 7, configuration space, 256 bytes; 8, window 0, 128 KiB, the registers; a DMA map; 9, window 1, 8 MiB, the framebuffer (first a direct translation, then a mapped window as the fallback); 10, window 2, 64 KiB, the flash. Any failure returns an I/O error.
4. Read vendor, device and revision from configuration space and log "RAD1 n attached rev r". The log is the only use of the revision.
5. Fill in the mode count from the three-record table.
6. Read the video clock control register. A nonzero value means the PROM console has already initialised the chip; the driver then passes console mode to the chip initialiser, which skips the clock, memory-timing and screen-clear steps. A zero value means a full initialisation, followed by the start-up screen fill. This register is a mode flag, not a gate: the driver attaches either way.
7. Chip initialisation (below), then set video refresh on.
8. Allocate and connect the board's interrupt on PCI line A, to the interrupt handler below, and write the interrupt enable register with 0x83 (bits 0, 1 and 7).
9. Create device nodes: `rad1` for board 0 or `rad1.N` for later boards under the PCI device, a text-terminal node `ttyrdN` under `/hw/ttys` (the first free N below four) and, for board 0, `rad1_b`, the buffered node. Add a PCI inventory entry with the vendor, device and slot.
10. For board 0, register the textport board with the console layer. If the early console left a host buffer, copy it to the framebuffer through the buffered write path and free it.

Detach frees the DMA map, disconnects the interrupt when the last board goes, and destroys the node. The halt entry does nothing. Unverified.

## Chip initialisation

The same routine runs in the kernel and, with a different back end for the wait loop, in the PROM; both are read in full. In order, for the first call (console mode off):

1. Wait for 100 free input FIFO entries. Write the interrupt enable 0, aperture one 0 and aperture two with the ROM-access bit set.
2. Stop and reprogram the memory PLL. On the `3d3d:0009` chip: clear the enable bit in the memory clock control indexed register, write prescale 11, feedback 128 and postscale 1, set enable, and poll the lock bit up to 500 times. On the `104c:3d07` chip: the equivalent through the three memory clock registers and the status register at index 0x33, lock bit 4. Any other device identity prints "bad device id".
3. Clear scissor, window (local buffer update disabled), area stipple, depth, stencil, texture address, texture read, texel LUT, YUV, colour DDA, texture colour, fog, alpha blend, logical op, statistic, filter, rasteriser, delta and all the window, base and offset registers; enable framebuffer writes and the dither unit; set the Y step to 1.0 (16.16) and the S step to 1.0 (12.18); write 8 to the DMA control register; write all ones to the software and hardware framebuffer write masks and 0x00ffffff to the bypass write mask; set framebuffer read pixel size to 32 bits.
4. Read the 128-byte settings sector from offset 0xff00 of the flash, decode the mode word and load the mode (see [modes.md](../../devices/rad1/modes.md#the-mode-word-in-flash)): the pixel PLL, timing registers, partial products, screen size and packed-data limit. Turn refresh off.
5. Write memory control 0 (SGRAM). Write the boot address and memory timing word: 0x20 and 0xe6002021 on the `104c:3d07` chip, 0x30 and 0xe6012021 on the `3d3d:0009` chip.
6. RAMDAC initialisation: pixel mask 0xff. On the Permedia 2V: index auto-increment on, cursor control and cursor mode (64 by 64, X-window type, disabled), colour format RGB 8888, pixel size 32 bits, DAC control with blank pedestal, misc control with high colour resolution, direct colour and overlay, overlay key 0, pan 0. On the Permedia 2: cursor control 64 by 64 with the cursor off, colour mode with RGBA 8888, GUI, RGB and true colour set, mode control 0. Then load a 256-entry palette, three byte stores per entry; its first entries are colour-ramp combinations and the rest a grey ramp (Unverified).

Table: [the memory clock arithmetic and the video modes](../../devices/rad1/modes.md).

The start-up screen fill (full initialisation only): wait for 40 FIFO entries; clear the framebuffer with a fast-fill rectangle; then draw a red-to-green gradient over the whole screen with a trapezoid in Gouraud mode, wait for the pipeline with a sync tag and drain the output FIFO; then draw two bitmap logos with fill-bit loops, offset, in shades of grey and red. The gradient uses the colour DDA registers at 9.11 fixed point. The effect is the PsiTech-branded start-up screen; the two logo bitmaps are in the object's data and are not reproduced here. Unverified.

## Interrupts

The handler reads the interrupt flags; if zero it returns, as the interrupt is not this board's. Otherwise it writes the value back to clear it, takes the board lock, writes the interrupt enable register 0, and wakes waiters according to three bits only: bit 1 wakes the GP sync waiter and cancels its timeout, bit 0 wakes the output-DMA read waiter, bit 7 wakes the bypass-DMA write waiter. The loop runs 200 times over the same status word without re-reading the register, so it signals up to 200 times per interrupt; all that matters is that each wake-up is idempotent. Then it restores the enable register to its shadow and releases the lock (established, handler read in full).

A request that waits arms a timeout of about two ticks plus a configured microsecond count, issues its work, sleeps on the queue, and cancels the timeout. If the timeout fires first it logs the failure; for the write-DMA waiter it also disconnects and reconnects the interrupt before waking the sleeper (software expectation).

Which hardware events raise which bit follows the public chip documentation and the use: a sync tag written with bit 31 set to the sync register raises the sync interrupt (bit 1) when the pipeline reaches it; a started output DMA raises bit 0 when it completes; a bypass DMA raises bit 7 when it completes (inferred from use; the manual naming of bit 7 as the bypass DMA flag was not read). The vertical-retrace and other flag bits are never tested or enabled in the shipped object.

## DMA

There is no descriptor chain. Two engines are used (software expectation; the offsets match the register table):

- **Host to framebuffer: bypass DMA.** The driver writes the source address, the stride, the destination in pixels, the size (height from bit 16, width in the low bits), the byte mask 0x000f000f, and then the control word: implicit mode, patching off, source format 8, 16 or 32 bits, GP restart and the width's partial products. It then sleeps for the bit 7 interrupt. A 32-bit image goes straight to the screen position. An 8-bit or 15-bit image goes to a staging area just past the visible frame, and the driver then runs one texture copy to the screen to expand it: texture address mode on, the staging address in the texture base address, texel size 8 or 16 bits, data format colour-index 8 or 565, the texel LUT on for 8-bit, then a rectangle render with texture enabled and a sync tag. The texture base address is written once in the whole driver, and always with a local-memory address.
- **Framebuffer to host: output DMA.** The driver turns the write path off and the upload-to-host bit on in the framebuffer write mode, sets read-destination and packed data, selects colour data in the filter, issues a rectangle render, and then for each chunk of up to 0xffff words writes the host address and the word count to the output DMA registers and sleeps for the bit 0 interrupt. It clears the error flags before each chunk. Read-back is always 32-bit words; the conversion hooks for narrower formats are not built.

Rectangles of at most a small number of pixels (a constant in the driver), and any rectangle when the no-DMA tunable is set, use programmed I/O instead: stores through the framebuffer window with the bypass write mask set around them. For larger ones the driver maps the caller's buffer (or copies it into a kernel buffer when mapping fails), obtains a device-visible address through the translation first and a DMA map second, and splits the transfer into chunks of at most the maximum DMA area, rounded to whole lines.

Cache coherence: the buffered path writes back the host buffer's data cache before the transfer. Unverified.

The whole DMA section is Unverified except for the register offsets, which every one appear in the object.

## Requests

The device node's control entry serves request numbers 101 to 141 through a 41-entry jump table with a bounds check. Of the 41 entries, 21 reach distinct handlers and the other 20 share a handler that returns success and touches nothing (established: the table, in `rad1drv.o` at object offset 0x5d0, read in full, with the relocation target of each slot checked). The numbers and argument shapes are the RAD4 driver's: see [../../devices/rad4/xserver-decode.md](../../devices/rad4/xserver-decode.md) for the request table that the RAD4 client uses. What the stock RAD1 driver does with each (the code-to-handler mapping is established; the behaviour column is Unverified, inferred from the request's name and the registers each handler touches, except 129 and 130, which share the verified flash routine):

| Request | Handler |
|--:|---|
| 101 | load the full 256-entry colour table; ignored on the `104c:3d07` chip |
| 102 | load a start-and-count part of it; indices clamped; ignored on the `104c:3d07` chip |
| 113 | return the current width, height and rate; the buffered node reports all boards' widths summed |
| 135 | like 113 with the mode index; a negative index asks for the current mode, a valid index returns that mode's size and rate, an index at or above the mode count returns -1 |
| 114 | set the mode word (see modes.md); an index at or above the mode count returns an error; re-programs the clock, timing and RAMDAC, clears the screen with the start-up fill, and writes the word to flash if it changed |
| 115 | cursor position (hot-spot offset applied); for the buffered node, the cursor is enabled on the board whose slice holds it and disabled on the others |
| 116 | cursor colours: background then foreground, three bytes each |
| 117 | cursor image: hot spot (6 bits each) and a 64 by 64 bitmap with mask, folded into the pattern RAM two bits a pixel |
| 122, 123 | cursor on, off |
| 124, 125 | screen on, off (RAMDAC low-power bit on the Permedia 2V; the misc control register on the other chip) |
| 118 | write a rectangle from user memory; modes colour-index 8-bit, 15-bit, 24-bit and 32-bit |
| 121 | read a rectangle back to user memory |
| 119 | fill a rectangle with a value under a mask (fast fill, framebuffer read-destination or the software mask) |
| 140 | copy a rectangle within the screen, with a source offset (see below) |
| 120 | set the plane mask; the buffered node refreshes the host buffer first and then writes every board's mask |
| 141 | load up to 256 colours into the texel LUT, placed in the last 256 words of the 8 MiB memory |
| 128 | on the buffered node, argument 2 forces a full copy of the host buffer to every board; arguments 0 and 1 do nothing |
| 129 | write one flash sector |
| 130 | read one flash sector |

The remaining requests, including the depth set (103 to 112), the gamma table (127), the PCI read command (126), the second-generation serial-ROM pair (131, 132), debug level (133) and the overlay start (134), return success without effect (established, shared handler). Request 129's header carries an offset and a data pointer; on a 32-bit caller the pointer is taken from the second word (Unverified).

A screen-to-screen copy (140), Unverified, sets the framebuffer source delta to the negated offset, enables source and destination reads, applies a logical copy operation, and renders a rectangle at the destination; it chooses decreasing-direction render flags when source and destination overlap in the direction that would corrupt a forward copy. It then writes a sync tag and sleeps for the sync interrupt. The copy does not use the texture unit.

User-pointer layouts depend on the caller's ABI: the handler asks the kernel which pointer size the caller has and picks the pointer out of the second word for 32-bit callers (Unverified).

## Read, write and map

The board node serves the framebuffer as a flat file: read and write at a 4-byte-aligned offset in 4-byte multiples, in page-sized pieces through programmed I/O, failing with a fault if offset plus count reaches 8 MiB. The map entry maps whole pages of the framebuffer window, page-aligned, up to 8 MiB, and the buffered node maps the host buffer, up to width times height times 4 bytes of all boards side by side. The terminal node's read and write handlers are not built into the shipped object (no symbols for them), so reads and writes on it return an error (inferred). The read, write and map paragraph is Unverified.

## Settings sector and flash

The settings sector is 128 bytes, offset 0xff00 of the 64 KiB flash. Programming one sector (software expectation, routine read in full):

1. Reject an odd offset. (The check is meant to reject unaligned sectors; as built it tests bit 0 only, so a misaligned even offset is accepted.)
2. Under the hardware and board locks, write byte 0xaa to byte 0x5556, 0x55 to byte 0x2aa9, and 0xa0 to byte 0x5556: the standard NOR-flash unlock and program command, with the addresses written XOR 3 because the bus lane swapping on this platform turns them into 0x5555 and 0x2aaa (inferred).
3. Write the 128 bytes of the sector, each at its offset, taking the source bytes with the index exclusive-ored with 3.
4. Poll the last byte of the sector, up to 0x80000 times, until it reads back the byte just written (data polling).
5. Verify the whole sector; a timeout or mismatch returns a fault. There is no erase.

Reading is the same byte-by-byte copy with the same index swizzle.

## Known quirks of the stock driver

- The mode limit in the attach path is one too high (see modes.md).
- The sector alignment check is wrong (above).
- The interrupt handler's loop signals 200 times.
- The two palette requests do nothing on the `104c:3d07` chip, so the palette stays at its power-on ramp there.
- The vertical-retrace palette deferral and the depth-change requests are compiled out.
