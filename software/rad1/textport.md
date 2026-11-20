# RAD1 textport and early console

How the RAD1 is found and drawn on as the system console, in the IO6 PROM 6.156 and in the IRIX 6.5.30 kernel. Ratings are as defined in [../../devices/rad1/README.md](../../devices/rad1/README.md). The registers are in [../../devices/rad1/registers.md](../../devices/rad1/registers.md); the chip initialisation the PROM shares with the kernel is in [kernel-driver.md](kernel-driver.md#chip-initialisation).

## PROM: finding the card

The PROM's table of PCI devices it can build a graphics console on has one RAD1 row, matched on vendor `3d3d` and device `0009` (established: the row is in the image at file offset 0xae4a8 of the decompressed IO6 PROM 6.156, with the install routine's address after it). The `104c:3d07` identity has no row, so a card that presents only the TVP4020 identity gets no PROM console (inferred from the table; the install routine itself still forces the Permedia 2V identity).

When the row matches and the `console` environment variable does not start with `d` (serial), the PROM prints "Installing RAD1 Graphics Console...", builds a graphics component for the card and calls the install routine (software expectation; both read in full). On success it sets the `gfx` variable to `alive` and sets the console output path to the board's path under module 1; on failure it sets `console` to `d` and falls back to serial. Every other graphics probe slot is cleared, so the textport binds this board only.

The install routine (established, read in full):

1. Read the PCI subsystem identity from configuration space at offsets 0x2c and 0x2e. Accept it only if it is vendor `12d1` with device `0101`, in either halfword order. The either-order test is a guard: the halfwords of that structure can come out swapped on this platform. Any other board is refused with a zero return and the PROM goes on without a RAD1 console.
2. Take the first base address register (configuration offset 0x10) masked to 128 KiB as the registers, and the expansion ROM base register (offset 0x30) masked to 64 KiB as the flash, each added to the base of the node's bridge window.
3. Store the Permedia 2V device identity, 9, in the board state, whatever identity the card presented; store the two base pointers.
4. Initialise the board (below), keep the state pointer for the textport, and set the ARCS component identifier to "Psitech-RAD1".

The board state has room for four boards; the textport uses the first (software expectation: the PROM textport is always board 0).

## PROM: board initialisation

The routine (read in full) resets the chip, runs the chip initialiser with console mode off (so it programs the PLLs, memory timing and the mode from the flash mode word, see [../../devices/rad1/modes.md](../../devices/rad1/modes.md)), and clears the screen:

- Reset: write 0 to the reset register and spin until bit 31 clears.
- Initialise: as in the kernel driver, with the Permedia 2V paths. The PROM's copy of the routine compares the mode index against the real number of table records (3), where the kernel compares against 4.
- Clear: set the logical operation to use constant framebuffer data, set the write data and block colour to 0, rectangle origin 0, rectangle size to the mode's width and height, and render a fast-filled rectangle (0x6000c8: rectangle, fast fill, increasing X and Y). Then the logical operation constant bit goes off again, refresh goes on and the hardware write mask is restored.

The PROM's drawing goes through the textport functions below, which use render commands only (inferred: the PROM's register stores in the textport range are all graphics-processor and RAMDAC offsets; no framebuffer-window or DMA access was found in them).

## The textport functions

Both the PROM and the kernel give the textport layer a table of functions: blank, set colour, map colour, filled box, point, set current position, draw bitmap, block move (absent in both), initialise, move cursor (PROM only) and, in the kernel, unblank and get description. The PROM has all of them; the kernel object holds ten (blank, unblank, colour, map colour, box, point, set position, draw bitmap, initialise, get description) (the kernel object's bodies were read and are software expectations; the PROM's were not each read, so the PROM's behaviour is inferred from the kernel's and from matching register offsets, Unverified).

- **Colour.** Map colour stores a 24-bit colour per index in a table of 256; set colour latches one table entry as the current drawing value.
- **Filled box.** Both corners are normalised, Y is flipped against the screen height (the textport's origin is bottom-left, the chip's top-left), the logical operation is set to constant write data, the write data is the current colour, rectangle origin and size are written and a render of a rectangle with increasing X and Y (0x6000c0, no fast fill) is issued. The hardware lock is taken without blocking in the kernel; if it is busy the call is dropped.
- **Point.** Same set-up, then start Y and start X as 16.16 fixed point and a render of a point primitive (0x80).
- **Draw bitmap.** The current position and the bitmap's origin give the top-left; one point is rendered for each set bit, rows top to bottom, a start Y write per row, with a wait for three free input FIFO slots before each point. After it the current position advances by the bitmap's move values.
- **Blank.** Sets or clears the low-power bit in the DAC control indexed register; the Permedia 2V path only.
- **Initialise (PROM).** Initialises the board if it has not been, unblanks, reports the mode's width and height, and loads the cursor (below).
- **Move cursor (PROM).** Writes the four cursor position index registers.

## PROM: cursor

The PROM textport programs a hardware cursor (Unverified; described from the kernel object's counterpart, which carries the same set-up routine): cursor palette indices 0 to 5 are written 0xff, 0xff, 0xff, 0xff, 0, 0 (the first colour white, the second black), the cursor mode register is set to enabled with the X-window type, the hot spot is set to 0, 0, and a 64 by 64 two-bit pattern of 1 KiB, an arrow, is stored from the object's data. Unverified for the PROM image itself.

## Kernel: early console and handover

The kernel's textport needs a console before the board's driver attaches. The registration entry (read in full):

- reads the `monitor` kernel argument; if absent the value is `h`;
- allocates 8 MiB of physically contiguous host memory;
- registers the textport with the console layer at 1280 by 1024 for `s`, `S`, `h` or `H` and at 1024 by 768 for `l` or `L`, and registers nothing for any other first character.

Until a board is attached, every drawing function writes into that host buffer instead of the chip (the textport state pointer is still empty): a fill or a bitmap store is a 32-bit pixel write at the flipped Y position. The early path's pitch is a fixed 1280 pixels whatever size was registered (inferred: constants read in the object; the 1024 by 768 case is not exercised).

When the kernel driver attaches board 0, it points the textport at the board and, if the early buffer exists, copies the buffer to the framebuffer with the buffered-write path and frees it ([kernel-driver.md](kernel-driver.md#attach), step 10). From then on the kernel textport draws through the chip with the same render sequence as the PROM's, skipping a call if a non-blocking trylock on the hardware lock fails.

## What it implies for a board model

Inferred from the above.

- A PROM console needs: the Permedia 2V identity with the PsiTech subsystem pair, 128 KiB of registers and 64 KiB of readable and writable flash, a reset bit that clears, FIFO space that reads at least 100, and the render path for rectangles and points under a constant colour. It does not need DMA, interrupts or the framebuffer window.
- The kernel's early console does not touch the board at all until the driver attaches.
