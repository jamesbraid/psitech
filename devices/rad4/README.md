# rad4: PsiTech RAD4 board identity and register map

The RAD4 is a PCI graphics card with an 8 MB framebuffer, a PLX PCI 9060-compatible bus interface and an IBM RGB561-compatible RAMDAC. Its PCI IDs are `12d1:0104`; the RAD4-KM variant, with keyboard and mouse connectors on the card, is `12d1:0105`. This page is the board's identity, address map and register summary. The register definitions are [registers.toml](registers.toml) and the generated table [registers.md](registers.md). The display modes and the configuration EEPROM are in [modes.md](modes.md), and the X server and driver findings in [xserver-decode.md](xserver-decode.md).

Every fact carries one of six ratings: **established** (a published document, or a shipped binary read in full), **observed** (seen when the shipped software ran on an emulator; model behaviour, not hardware), **software expectation** (what the shipped software assumes the board does), **inferred** (a reasoned reading), **approximation** (a value chosen where the evidence stops) and **unknown**. `registers.toml` can only say established, inferred or unknown: it files software expectations under established and approximations under inferred, and says so in each entry's doc text.

## Sources

- PsiTech, *RAD4 Owner's Guide*, software revision 1.3, 15 November 1997: PCI IDs, product roles, device nodes, RAD4-KM connectors.
- PLX Technology, *PCI 9060 Data Sheet*, version 1.2, December 1995, and the *PCI 9054 Data Book*, version 1.0, for the bus interface.
- IBM Microelectronics, *RGB561 Architecture*, preliminary revision 1.1, 23 January 1995, for the RAMDAC.
- PsiTech, *RAD4C-KM Graphics Head* product sheet, RAD4-DS-1099.
- The PsiTech release 1.3k package for IRIX 6.5 (kernel driver, standalone X server, `rad4setres`, `rad4d`), read as binaries, rated as software expectations. Hashes are in [../../references/binaries.md](../../references/binaries.md).

No Linux, OpenBSD or NetBSD driver exists for the RAD4, and no board photograph, schematic, parts list or configuration-space dump has been found.

## Identity

| Fact | Value | Rating | Source |
|---|---|---|---|
| RAD4 PCI vendor and device | `12d1:0104` | established | owner's guide, installation example; driver registers the ID |
| RAD4-KM PCI vendor and device | `12d1:0105` | established | owner's guide, installation example; driver registers the ID |
| RAD4-KM role | same line with keyboard and mouse connectors, for the Origin 2000, which has none of its own | established | owner's guide |
| RAD4 and RAD4-KM share framebuffer, RAMDAC and register layout | yes | inferred | one guide section describes both; one driver attaches to both |
| Framebuffer size | 8 MB | established for the RAD4C-KM sheet and the owner's guide description; the driver requests an 8 MiB mapping (software expectation) | owner's guide; product sheet; driver |
| Bus interface | PLX PCI 9060-compatible | inferred, high confidence | register offsets, the expansion ROM route to DMA registers, mailbox, interrupt and EEPROM bits all match the 9060 sheet |
| Exact PLX part suffix and board revision | not identified | unknown | |
| RAMDAC | IBM RGB561-compatible | inferred, high confidence | indexed access through four ports, index 0x20 to 0x22 used as the sync and PLL registers the specification names |
| Framebuffer controller, timing sequencer, address decode, write mask | board-local logic; chip type (ASIC, FPGA, discrete) | unknown | no board image or parts list |
| Dedicated drawing accelerator | not established; CPU rendering and DMA are what the software uses | unknown | |
| PCI revision, class code, subsystem IDs, BAR sizing | | unknown | the driver reads the revision but no captured value exists |
| Board reference clock | 33 MHz | inferred | reproduces all 13 mode clocks, see [modes.md](modes.md) |
| Configuration EEPROM part | 93C46-compatible, 64 by 16 bits | inferred | the driver's command set matches the public part |

Later product: the RAD4C-KM (product sheet, October 1999) lists 8 MB VRAM, a programmable video clock to 200 MHz, an 8-bit overlay, 3 by 256 by 10-bit gamma tables, a 3 by 10-bit DAC and two 9-pin DIN keyboard and mouse connectors (established, the sheet). It gives no PCI IDs and no registers, and nothing here transfers to it.

## Resources the driver maps

The driver names its resources by the Bridge-family selector numbers: selector 8 is the first base address region (BAR0), selector 10 the third (BAR2) and selector 1 the expansion ROM (software expectation; the numbering is that of public Linux Bridge code and the driver's own configuration read of BAR2 agrees).

| Resource | Use | Rating |
|---|---|---|
| BAR0, 128 bytes requested | PLX runtime registers: mailbox, interrupt control, EEPROM control | software expectation (size requested); the register layout is established from the 9060 sheet |
| BAR2, 8 MiB requested | framebuffer at the bottom, board registers above it | software expectation. The driver forms pointers beyond the 8 MiB it requests, so BAR2 must be larger than the request: the real size is unknown |
| Expansion ROM, 8 MiB requested | aliases of the DMA channel registers; the driver asks for an 8 MiB window, so a smaller declared size does not satisfy it | software expectation |
| BAR3 (RAD4-KM only) | keyboard and mouse controller, sixteen registers 64 KiB apart | software expectation (use), inferred (layout; see [COVERAGE.md](../../COVERAGE.md)) |

Every access the driver makes to BAR0, BAR2 and the expansion ROM is an aligned 32-bit load or store (software expectation). The RAMDAC ports take their payload from the low eight bits of the store.

## BAR0: bus interface

Offsets follow the 9060 runtime register layout.

| Offset | Name | What the driver does | Rating |
|---|---|---|---|
| 0x14 | expansion ROM remap | writes a value with top byte 0xe1 at attach, never reads | software expectation |
| 0x18 | local bus region descriptor | writes `0xf84303c3` at attach, selecting a 32-bit local bus | software expectation |
| 0x40 | mailbox | reads it at attach; nonzero means a firmware initialiser ran and the driver skips its own mode and RAMDAC setup | software expectation. The reset value and who writes it on a real card: unknown |
| 0x68 | interrupt control and status | ORs `0x50900` in at attach, with or without DMA; bits 8, 11, 15, 16, 18, 21 are the ones used | established (layout), software expectation (use) |
| 0x6c | serial EEPROM control | clock bit 24, chip select bit 25, data to the EEPROM bit 26, data from it bit 27; the driver also sets the low nibble to 0xc | established (bits); the nibble's purpose unknown |

Bit 15 of the interrupt register is the local interrupt input. Frame events and DMA completion both reach the host through it: the driver enables the DMA interrupt only towards the 9060's local output and looks for the channel's bit 21 only after bit 15, so the output is inferred to be wired back to the local input, as the 9060 sheet suggests. The board's frame event drives the same input (inferred).

## Expansion ROM route: DMA channel 0

| Offset | Name | Rating |
|---|---|---|
| 0x100 | DMA channel 0 mode (`0x7c3`: 32-bit local bus, chaining, done interrupt enable) | established (offsets, 9060 Tables 47, 51, 57 and 9054 Tables 11-76, 11-80, 11-86); the route through the expansion ROM is a software expectation |
| 0x110 | descriptor pointer | |
| 0x128 | command and status | |

The board's DMA use, descriptor layout and byte order are in [xserver-decode.md](xserver-decode.md#dma).

## BAR2: framebuffer and board registers

| Offset | Name | Rating |
|---|---|---|
| 0x000000 to 0x7fffff | framebuffer, 32-bit pixels | software expectation |
| 0x800000 | base of an additional board-register area | unknown (a pointer is built here; nothing found uses it) |
| 0x900000, 0x910000 | RAMDAC index low and high byte | inferred |
| 0x920000 | RAMDAC data, single cycle, index auto-increments | inferred |
| 0x930000 | RAMDAC data, multi cycle | inferred |
| 0xa00000, 0xa01000, 0xa03000 | horizontal timing banks | software expectation (use); depth and bit meanings unknown |
| 0xa02000 | pointer built but never written by the loader | unknown |
| 0xb00000 | vertical timing bank | software expectation (use); depth and bit meanings unknown |
| 0xc00000, 0xe00000 | pointers built, function not found | unknown |
| 0xd00000 | pixel write mask | software expectation (use); which bit reaches which plane is unknown |
| 0xf00000 | board control and status | software expectation (use); physical effect unknown |

Port numbering of the four RAMDAC ports in address order matches the RGB561's index low, index high, data and multi-cycle ports, which is inferred from how the driver uses them. They take the low eight bits of a store.

### Board control

Bit 5 (0x20) is cleared while the driver programs a mode and set afterwards, and its interrupt handler tests it (software expectation). Bit 1 (0x02) asks for an interrupt at the next frame: the driver sets it, with a 400 ms fallback timer, when a palette or cursor update has to wait for the frame, its handler clears it when the frame arrives, and it clears it around every DMA transfer because during a transfer the handler services only DMA completion (software expectation). That the board raises a frame event only while bit 1 is set follows from that last point and is inferred. Whether the status in bit 5 is gated by bit 1 or only the interrupt is: unknown. A scan of the standalone server and `rad4d` finds no instruction loading the offset of this register as a constant, so they appear not to poll it; a scan misses offsets computed from a base.

### Framebuffer pixel and plane mask

A pixel is a 32-bit word. The X server's depth-24 TrueColor and DirectColor visuals are defined with red, green and blue masks `0x00ff0000`, `0x0000ff00` and `0x000000ff` and shifts 16, 8 and 0, read directly from the server's data (established). The RAMDAC configuration the driver writes selects 24-bit true colour from frame buffer A with no lookup, which reads the low 24 bits as direct colour (established from the RGB561 window attribute table field layout; the RGB561 input format alone does not say how CPU word bits reach the RAMDAC pins). The top byte holds the overlay and window ID: the server's four-plane overlay visual draws into it with plane mask `0x0f000000` (software expectation); wiring the RAMDAC's window-ID inputs to that byte is inferred.

The server programs the write mask before almost every drawing operation: `0x00ffffff` for ordinary colour and `0x0f000000` for the overlay. A store therefore merges as `new = (old & ~mask) | (value & mask)`: that is the generic plane-mask convention, inferred, and the board's own bit-to-plane mapping is unknown.

One software quirk matters for anyone building a model: the X server draws Motif's greyed menu labels with a tiled fill that stores raw 4-bit tile values unshifted under the `0x0f000000` mask, while all its other overlay drawing shifts the index to bit 24. With a plain plane mask those labels leave the overlay transparent and the window behind shows through. Whether a real card does the same is unknown; a photograph of a 4Dwm menu on one would settle it.

## RAMDAC registers the software uses

The RGB561 is reached through the four BAR2 ports as an indexed register file. The RAMDAC's own registers are the public specification's; the ones the software touches are:

| Index | Use | Rating |
|---|---|---|
| 0x20 | sync control: the mode routine writes 1, or 0x23 when the EEPROM selector field is 2 | established (register), software expectation (values) |
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

Initialisation values the driver writes (general initialisation, decoded with the public specification): configuration 1 `0x2c` (4:1 basic serializer, eight overlay bits, eight window-ID bits), configuration 2 `0x19` (on-chip PLL and RGB outputs on, reference clock input, cursor location latching), configuration 3 `0x41` (non-interlaced RGB order, serial clock on, synchronous cursor and scissor updates), configuration 4 `0x45` (split window IDs, eight frame-buffer window-ID bits, upper-bit auxiliary table addressing), frame-buffer window table entry `0x36` (24 or 30-bit true colour, buffer A, opaque), auxiliary frame-buffer table entry zero (gamma enabled) and cursor control `0x60` (cursor and cross-hair disabled). Rating: established that the driver writes these values (software expectation); the meaning of each is the public specification's (established for the RGB561 part, inferred for the board). Which RGB561 revision is fitted and how the board wires the RAMDAC's pixel and window-ID pins: unknown.

The multi-cycle port loads every table with more than one byte per entry: two cycles for a window attribute or gamma entry (bits 9 to 2, then bits 1 to 0 in bits 7 to 6) and three for a colour or cursor table entry. The index advances once per complete entry, and writing either index register restarts a partial entry (established, RGB561 specification pages 1 and 4).

## RAD4-KM controller

Under device `0x105` the driver also initialises a keyboard and mouse controller, exposed as `/dev/rad4_kbd` and `/dev/rad4_pntr`, separate from the system's own devices. The sixteen registers the driver uses match the SCN2681/SCC68681 dual UART index for index; that the card carries that part or a compatible one is inferred, and the 64 KiB stride between registers is inferred to be the card's address decode. Channel A carries the keyboard and channel B the mouse (software expectation). The driver resets each channel with the PS/2 reset command and assigns keyboard or mouse from the reply. The connector type, the controller part and the board-level interrupt enable register the driver also writes (address unknown) are unknown. [COVERAGE.md](../../COVERAGE.md) records the register map as not yet in defs form.

## Limits

- Revision, class code, subsystem IDs and BAR sizes of a real card: unknown. Reset behaviour of the board-local registers, and cold, warm and PCI reset: unknown.
- Timing word bit meanings, timing bank depths and the board's frame rate: unknown.
- The mailbox's producer and power-on value on a real card: unknown.
- More than one card in a machine: not examined in the driver.
