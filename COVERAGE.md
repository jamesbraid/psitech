# psitech coverage map

The areas of PsiTech's graphics boards for SGI systems and where each stands. There is no measured inventory yet: `retools/tools/inventory.py` needs the vendor package unpacked under `root/` and an inventory configuration, and neither exists in this workspace until the binaries are catalogued. Until then the rows below are the tally, graded as in [AGENTS.md](AGENTS.md).

## RAD4 (PCI 12d1:0104)

| Area | State | Where |
|---|---|---|
| PCI identity and board parts | IDs, host systems, IRIX releases, patches and how O2 and Origin firmware list the card established; flash and keyboard controller located; parts partly inferred; class, revision and BAR sizes as the shipped RAD4-KM serial EEPROM image declares them, subsystem IDs unknown | [devices/rad4/README.md](devices/rad4/README.md) |
| Bus interface registers (BAR0) | defined in TOML: mailbox, interrupt control, EEPROM control (with the DMA read command nibble) and two stored registers; interrupt handler read in full | [devices/rad4/registers.toml](devices/rad4/registers.toml) |
| DMA channel 0 (expansion ROM route) | defined in TOML with the descriptor next-pointer word; behaviour written up | [devices/rad4/xserver-decode.md](devices/rad4/xserver-decode.md#dma) |
| Board registers (BAR2): RAMDAC ports, timing banks, mask, board control | defined in TOML; timing word bits named from the loaders and VESA timings (inferred), physical effects, bank depths and the mask-to-plane wiring unknown | [devices/rad4/registers.toml](devices/rad4/registers.toml) |
| RAMDAC indexed registers | the sync, PLL and cursor registers the software uses are defined; window attribute, gamma, colour and cursor tables and the initialisation registers are described in prose only, because the definition format has no way to express tables with a per-entry index step | [devices/rad4/README.md](devices/rad4/README.md#ramdac-registers-the-software-uses) |
| Display modes and EEPROM | 13 modes established; clock arithmetic reproduces all 13; timing words' bit rules established and their fields named; option fields unknown electrically | [devices/rad4/modes.md](devices/rad4/modes.md) |
| X server and driver requests | request table, call sites, window types, buffered and multi-head paths, scripts and daemon read; `rad4_X_knp` event loop not | [software/rad4/xserver-paths.md](software/rad4/xserver-paths.md), [devices/rad4/xserver-decode.md](devices/rad4/xserver-decode.md) |
| Binary inventory (functions, MMIO, ioctls) | all 40 ioctl handlers and the driver's 179 functions listed by role; no inventory configuration yet | [software/rad4/kernel-driver.md](software/rad4/kernel-driver.md) |
| Driver function-by-function readings | attach, interrupt, DMA, ioctls, RAMDAC and keyboard controller initialisation, flash, early textport, region descriptor bits, key translation and the terminal's escape table read; the individual escape handlers beyond three not | [software/rad4/kernel-driver.md](software/rad4/kernel-driver.md) |
| Option ROM, PROM image, kernel patches | PsiTech PROM image, option ROM, textport and keyboard patches surveyed; the ROM's initialiser, mode routine, timing loaders, paint helper, console draw and keyboard read are read in [software/firmware/rad4-option-rom.md](software/firmware/rad4-option-rom.md) | [software/rad4/proms-and-kernel.md](software/rad4/proms-and-kernel.md) |
| Open questions | 23 recorded across the RAD4, RAD1 and firmware work | [questions/open-questions.md](questions/open-questions.md) |

## RAD1 (Permedia 2 board)

| Area | State | Where |
|---|---|---|
| Board identity | product, bundle, display and memory established from the sheet; chip family inferred; the PROM's PCI row, the kernel's two registrations and the PROM's subsystem pair `12d1:0101` read; revision, class, BAR sizes, part numbers unknown | [devices/rad1/README.md](devices/rad1/README.md) |
| Machines and releases | IP27 kernel family; driver in 6.5.30 media, absent from the June 1998 6.5 media; console code in PROM 6.156, absent from 6.11; first release not pinned | [devices/rad1/README.md](devices/rad1/README.md#where-it-runs) |
| Registers (Region Zero and the RAMDAC's indexed registers) | 167 registers defined in TOML for both chips; every offset the stock software uses confirmed in the objects; bit fields only for the interrupt bits and video enable | [devices/rad1/registers.toml](devices/rad1/registers.toml) |
| Display modes and flash settings | three kernel modes, the IO6 PROM's eight and the 33-row partial-product table read in full; clock arithmetic; mode word layout | [devices/rad1/modes.md](devices/rad1/modes.md) |
| Kernel driver | registration, attach front half, interrupt handler, request jump table, chip initialiser, flash programming read in full; DMA sequences, per-request behaviour, start-up fill, detach and read, write and map traced but unverified | [software/rad1/kernel-driver.md](software/rad1/kernel-driver.md) |
| Textport and early console | PROM install and board bring-up read in full; kernel early-console registration read in full; PROM drawing functions and cursor inferred from the kernel's | [software/rad1/textport.md](software/rad1/textport.md) |
| X server and DDX | not held: PsiTech's Graphics Server for the RAD1 is not in the Library; the RAD4 server's request set is a subset of what the RAD1 driver serves | [software/rad1/package.md](software/rad1/package.md) |
| TI TVP4020 manual cross-check | not done: bit meanings beyond the public driver headers are unread | [questions/open-questions.md](questions/open-questions.md) |

## Firmware and early console (all PsiTech boards)

| Area | State | Where |
|---|---|---|
| Which firmware recognises which board | every held IO6, IP27, IP35, IP30, IP32 and IO4 PROM, `sash`, `ide`, `fx` and the 6.5.30 kernels scanned; the RAD4 family only in PsiTech's own IP27 PROM 5.30, the RAD1 in IO6 and IP27 6.27 onward | [software/firmware/which-firmware.md](software/firmware/which-firmware.md) |
| PsiTech IP27 PROM 5.30 | PCI table, install routine and output path read in full; the boot stage's ROM copy is in the RAD4 survey and agrees with the entry address | [software/firmware/psitech-ip27-prom.md](software/firmware/psitech-ip27-prom.md) |
| RAD4 and RAD4-KM expansion ROM | initialiser, mode routine, both timing loaders, paint helper, character draw, font, cursor, scroll, EEPROM read and keyboard read read in full | [software/firmware/rad4-option-rom.md](software/firmware/rad4-option-rom.md) |
| RAD1 console in SGI PROMs | release history, PCI table row and start-up mode record read; drawing functions are in the RAD1 pages | [software/firmware/sgi-prom-rad1.md](software/firmware/sgi-prom-rad1.md) |
| Other firmware | negative results with what was searched; the Origin 300 PROM only names the board, by a lookup not traced | [software/firmware/other-firmware.md](software/firmware/other-firmware.md) |
| `console=g` and the kernel's textport hooks | PROM selection, environment hand-over and the kernel's early-init hooks read; the RAD4 driver's hand-over and the keyboard patch not read | [software/firmware/console-selection.md](software/firmware/console-selection.md) |
| What a model must present | per firmware; the PsiTech PROM loads the ROM itself | [software/firmware/model-needs.md](software/firmware/model-needs.md) |

## Other PsiTech boards

| Board | State |
|---|---|
| RAD4-KM (`12d1:0105`) | controller at BAR2 + 0xe00000, registers in defs form (inferred from the SCC68681 correspondence and the driver's use); initialisation, transmit, receive and interrupt read; see [devices/rad4/km-controller.md](devices/rad4/km-controller.md) |
| `12d1:0100` | named only by the PsiTech IP27 PROM's PCI table; no document, driver or software |
| RAD4C-KM | a 1999 product sheet only: 8 MB VRAM, 200 MHz RAMDAC, overlay, gamma and two PS/2-style connectors. No PCI IDs, no registers, no software |
| RAD1 | covered in the section above |

## Missing evidence

Software evidence: the release package and the emulator runs of it are all that is held. The 13 timing-count sets, the mode-change request details and the overlay drawing paths of the X server are in. A configuration-space dump, a board photograph or a parts list of any PsiTech card would settle the identity rows; nothing in the shipped software can.
