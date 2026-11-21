# What a model must present for each PROM to find the board and print

Requirements read off the firmware, per firmware. Ratings as in [which-firmware.md](which-firmware.md). Where the shipped software does not decide a value, the item is marked unknown and the model author chooses and documents it. Register layouts are in [../../devices/rad4/README.md](../../devices/rad4/README.md) and [../rad1/textport.md](../rad1/textport.md).

## RAD4 or RAD4-KM under the PsiTech IP27 PROM 5.30

Prerequisites on the machine side: an Origin 200 or Origin 2000 node booting the PsiTech image, with `console` set to `g` (or `g0`) so the selection routine looks for the board.

| Need | Value | Rating |
|---|---|---|
| Identity | configuration word 0 reads `0x010412d1` (RAD4) or `0x010512d1` (RAD4-KM) | established |
| Where | a function the PROM's node walk reaches under the Bridge widget; the console path is not tied to a slot name (unlike the RAD1's) | established for the PROM, inferred for slot freedom |
| Base 0 | at least 0x70 bytes: writes at 0x18 (local bus region descriptor), 0x40 (mailbox) and 0x6c (EEPROM control, bits 24 to 27) | established |
| Base registers | the boot stage assigns them: base 0 from the slot's block, base 2 in the next block, the ROM base at the next 16 MiB boundary after base 2 with its enable bit set; the model must size all three by the usual all-ones write and read-back | established by the RAD4 survey |
| Base 2 | at least 16 MiB: the 8 MiB framebuffer at the bottom of 32-bit pixels, and the board registers from `+0x800000` up to `+0xf00000` (board control). The ROM stores 32-bit words only | established |
| Expansion ROM | an enabled base register whose first 32-bit big-endian load returns `0xaa55`; the ROM image's bytes are `55 aa 00 00`, so the bridge model must apply the byte swap it applies to real PCI memory reads | established (the compare), inferred (the swap) |
| ROM content | the expansion ROM must hold PCI ROM images as in [rad4-option-rom.md](rad4-option-rom.md): the boot stage picks the image whose PCI data structure identity equals the board's configuration word and whose code type is `0x7f`, skipping others by their length, copies it to node memory and the install routine jumps to `0x01800178` | established |
| EEPROM | none is needed: with serial data output (bit 27 of base 0 plus 0x6c) high straight after the address phase the code zeroes the 40-byte block and picks mode 0, 1280 by 1024. To select another mode, answer the read command at word address 0x2c with 20 words | established |
| Chip select | after a successful read chip select (bit 25) ends low; after a failed one it stays high | established |
| Mailbox | base 0 plus 0x40 must hold stores; the code writes `0x424f4f21` last, and the kernel driver treats nonzero as "firmware already initialised" | established |
| Display | after the initialiser, 1280 by 1024 (mode 0) of 32-bit pixels at stride 1280, black with white 8 by 15 text, 80 by 34 centred, and a cursor block that toggles | established |
| RAMDAC, timing banks, mask | accept stores; none of the console path reads them. The mode routine's stores to the timing banks (BAR2 `0xa00000` to `0xa03000`, `0xb00000`) are the part not read here | established (no reads), unknown (mode routine) |
| Board control (`0xf00000`) | only the RAD4-KM keyboard read polls bit 4; the RAD4 console code read here never touches it | established |

The PROM does the loading, so a model that presents the real ROM image and a Bridge-like window the PROM can read through gets the console without any model-side code placement. The copy relies on the window returning the ROM's words byte-swapped, so that the first word reads `0xaa55` and the copy loop's word reordering restores the image order (established for the check, inferred for the ordering; [../rad4/proms-and-kernel.md](../rad4/proms-and-kernel.md#2-psitechs-ip27promimg)). Writing the glyphs into the framebuffer from the model instead would hide the behaviour that must be modelled; do not.

Console input is out of scope for the PROM: nothing calls the ROM's key-read command, and the RAD4-KM keyboard is only used by the ROM's command 2 which the PROM never issues.

## RAD1 under SGI's IO6 PROM 6.27 or later

The RAD1 needs no ROM code. From [../rad1/textport.md](../rad1/textport.md) and [sgi-prom-rad1.md](sgi-prom-rad1.md):

| Need | Value | Rating |
|---|---|---|
| Identity | primary `3d3d:0009` (a TI `104c:3d07` card gets no PROM console), subsystem vendor `12d1` and subsystem device `0101` at configuration offsets 0x2c and 0x2e, in either halfword order | established |
| Where | the base I/O board's PCI bus (the console path names the motherboard slot); a shoebox or other module gets none | inferred from the path format |
| Base 0 | 128 KiB of control registers | established |
| Expansion ROM base | 64 KiB window; the PROM reads a 128-byte record at offset 0xff00 twice. Its first word picks the mode: bits 6:0 below 8 else mode 0 with a warning. A zero record gives 1280 by 1024 at 60 Hz | established |
| `console` | not starting with `d` | established |
| Chip behaviour | reset bit that clears, FIFO space that reads at least 100, render commands for rectangles and points | see [../rad1/textport.md](../rad1/textport.md#what-it-implies-for-a-board-model) |

On IP27 PROMs 6.27 to 6.48 the same board is also reachable from the node PROM; later node PROMs do not install it.

## Origin 300, Octane, O2

No PROM console. The Origin 300 PROM may print `PSITECH` or `PSITECH_RAD1` in a configuration listing, which needs only the identity: the PCI word `3d3d:0009` alone selects the name and the subsystem is not read (established; see [other-firmware.md](other-firmware.md)).

## After the PROM: the kernel

A running guest needs `console` starting with `g` and `gfx` starting with `a` for the kernel textport to start; the PROMs set the second. For the RAD4 the kernel textport also needs PsiTech's `rad4pci.o` and patched `tport.a` linked into the kernel ([console-selection.md](console-selection.md)); the stock 6.5.30 IP27 kernel has the hook as a weak reference and no RAD4 driver, so a stock kernel boots to a RAD4 only for output the PROM draws.
