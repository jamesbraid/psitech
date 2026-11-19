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

## Other PsiTech boards

| Board | State |
|---|---|
| RAD4-KM (`12d1:0105`) | controller registers match the SCC68681 dual UART index for index (inferred); not yet in defs form because the layout rests on one datasheet correspondence and the driver's use, with the board-level interrupt register's address unknown |
| RAD4C-KM | a 1999 product sheet only: 8 MB VRAM, 200 MHz RAMDAC, overlay, gamma and two PS/2-style connectors. No PCI IDs, no registers, no software |
| RAD1 | not started. A Permedia 2 board; product sheet only |

## Missing evidence

Software evidence: the release package and the emulator runs of it are all that is held. The 13 timing-count sets, the mode-change request details and the overlay drawing paths of the X server are in. A configuration-space dump, a board photograph or a parts list of any PsiTech card would settle the identity rows; nothing in the shipped software can.
