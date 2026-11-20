# psitech coverage map

The areas of PsiTech's graphics boards for SGI systems and where each stands. There is no measured inventory yet: `retools/tools/inventory.py` needs the vendor package unpacked under `root/` and an inventory configuration, and neither exists in this workspace until the binaries are catalogued. Until then the rows below are the tally, graded as in [AGENTS.md](AGENTS.md).

## RAD4 (PCI 12d1:0104)

| Area | State | Where |
|---|---|---|
| PCI identity and board parts | IDs established; parts partly inferred; revision, class, BAR sizes unknown | [devices/rad4/README.md](devices/rad4/README.md) |
| Bus interface registers (BAR0) | defined in TOML: mailbox, interrupt control, EEPROM control and two stored registers | [devices/rad4/registers.toml](devices/rad4/registers.toml) |
| DMA channel 0 (expansion ROM route) | defined in TOML with the descriptor next-pointer word; behaviour written up | [devices/rad4/xserver-decode.md](devices/rad4/xserver-decode.md#dma) |
| Board registers (BAR2): RAMDAC ports, timing banks, mask, board control | defined in TOML; physical effects and bit meanings of timing words unknown | [devices/rad4/registers.toml](devices/rad4/registers.toml) |
| RAMDAC indexed registers | the sync, PLL and cursor registers the software uses are defined; window attribute, gamma, colour and cursor tables and the initialisation registers are described in prose only, because the definition format has no way to express tables with a per-entry index step | [devices/rad4/README.md](devices/rad4/README.md#ramdac-registers-the-software-uses) |
| Display modes and EEPROM | 13 modes established; clock arithmetic reproduces all 13; option fields unknown electrically | [devices/rad4/modes.md](devices/rad4/modes.md) |
| X server and driver requests | request table, no-DMA path, overlay drawing paths and the greyed-label quirk read; buffered and multi-device paths not audited | [devices/rad4/xserver-decode.md](devices/rad4/xserver-decode.md) |
| Binary inventory (functions, MMIO, ioctls) | not started: no inventory configuration or `root/` yet | |
| Driver function-by-function readings | not started | |
| Open questions | 11 recorded | [questions/open-questions.md](questions/open-questions.md) |

## RAD1 (Permedia 2 board)

| Area | State | Where |
|---|---|---|
| Board identity | product, bundle, display and memory established from the sheet; chip family inferred; the PROM's PCI row, the kernel's two registrations and the PROM's subsystem pair `12d1:0101` read; revision, class, BAR sizes, part numbers unknown | [devices/rad1/README.md](devices/rad1/README.md) |
| Machines and releases | IP27 kernel family; driver in 6.5.30 media, absent from the June 1998 6.5 media; console code in PROM 6.156, absent from 6.11; first release not pinned | [devices/rad1/README.md](devices/rad1/README.md#where-it-runs) |
| Registers (Region Zero and the RAMDAC's indexed registers) | 167 registers defined in TOML for both chips; every offset the stock software uses confirmed in the objects; bit fields only for the interrupt bits and video enable | [devices/rad1/registers.toml](devices/rad1/registers.toml) |
| Display modes and flash settings | three modes and the 33-row partial-product table read in full; clock arithmetic; mode word layout | [devices/rad1/modes.md](devices/rad1/modes.md) |
| Kernel driver | registration, attach front half, interrupt handler, request jump table, chip initialiser, flash programming read in full; DMA sequences, per-request behaviour, start-up fill, detach and read, write and map traced but unverified | [software/rad1/kernel-driver.md](software/rad1/kernel-driver.md) |
| Textport and early console | PROM install and board bring-up read in full; kernel early-console registration read in full; PROM drawing functions and cursor inferred from the kernel's | [software/rad1/textport.md](software/rad1/textport.md) |
| X server and DDX | not held: PsiTech's Graphics Server for the RAD1 is not in the Library; the RAD4 server's request set is a subset of what the RAD1 driver serves | [software/rad1/package.md](software/rad1/package.md) |
| TI TVP4020 manual cross-check | not done: bit meanings beyond the public driver headers are unread | [questions/open-questions.md](questions/open-questions.md) |

## Other PsiTech boards

| Board | State |
|---|---|
| RAD4-KM (`12d1:0105`) | controller registers match the SCC68681 dual UART index for index (inferred); not yet in defs form because the layout rests on one datasheet correspondence and the driver's use, with the board-level interrupt register's address unknown |
| RAD4C-KM | a 1999 product sheet only: 8 MB VRAM, 200 MHz RAMDAC, overlay, gamma and two PS/2-style connectors. No PCI IDs, no registers, no software |
| RAD1 | covered in the section above |

## Missing evidence

Software evidence: the release package and the emulator runs of it are all that is held. The 13 timing-count sets, the mode-change request details and the overlay drawing paths of the X server are in. A configuration-space dump, a board photograph or a parts list of any PsiTech card would settle the identity rows; nothing in the shipped software can.
