# rad1: PsiTech RAD1 board identity and register map

The RAD1 is PsiTech's low-cost PCI graphics card for the Origin 200: 8 MB of SGRAM, an HD-15 connector and a TI or 3Dlabs Permedia 2 family chip that carries its own RAMDAC. It has no bus bridge and no separate RAMDAC, which is the main difference from the [RAD4](../rad4/README.md). This page is the board's identity, address map and register summary. The register definitions are [registers.toml](registers.toml) and the generated table [registers.md](registers.md). The display modes and the settings sector are in [modes.md](modes.md). The software that drives the board is in [../../software/rad1/](../../software/rad1/package.md).

Every fact carries one of three ratings: **established** (a published document, or a shipped binary or driver read in full, cited), **inferred** (a reasoned reading: what the software assumes about the board where the read was partial, approximations, and emulator runs, which show model behaviour and not hardware) and **unknown** (nothing published or shipped decides it). `registers.toml` uses the same three grades, and each entry's doc text names its source.

## Sources

- PsiTech, *RAD1 Graphics Head* product sheet, publication RAD1-DS-1099 (1999): size, memory, display and bundle claims. The text of the sheet does not name the chip.
- X.Org `xf86-video-glint` and Linux `pm2fb`, for the public names of the chip's registers and PCI identities.
- The stock IRIX 6.5.30 kernel driver object `rad1pci.a` (members `rad1drv.o`, `rad1_init.o`, `rad1_tpinit.o`, `rad1_tport.o`, `rad1data.o`), the IO6 PROM 6.156 and the IRIX 6.5.30 system and master files, read as binaries or files. Hashes are in [../../software/rad1/package.md](../../software/rad1/package.md#files-read).
- IRIX 6.5.30 release notes (one fixed-bug entry) and four Usenet messages, listed in [../../references/documents/INDEX.md](../../references/documents/INDEX.md).

No manual for the board was published, and no board photograph, schematic, parts list, configuration-space dump or flash dump has been found. The board's own software is a PsiTech driver and graphics server on a CD; none of it is held. What is held is SGI's later stock driver for the card, which ships with IRIX.

## Identity

| Fact | Value | Rating | Source |
|---|---|---|---|
| Product | RAD1 Graphics Head, "low cost console/graphics head for SGI Origin200 systems" | established | product sheet |
| Card | short universal PCI card, 32-bit bus, 12 W | established | product sheet |
| Memory | 8 MB SGRAM | established | product sheet; the kernel driver maps an 8 MiB framebuffer window (established) |
| Display | HD-15; 3 by 8-bit DAC; 8-bit overlay; programmable resolution with 1280 by 1024, 1024 by 768 and 1024 by 1024 listed; separate, composite and sync-on-green | established | product sheet |
| Price and life | list price cut to $295 on 1 September 1999; "no longer for sale" and "replaced by the RAD4C-KM" by July 2002 | established for the press release text; inferred for the end of sale (one poster's statement) | Usenet, 1999 and 2002 |
| Bundle | PCI card, users manual, CD-ROM, registration card; supplied with the PsiTech Graphics Server and PsiTech PCI drivers for IRIX 6.5 | established | product sheet |
| Chip family | TI TVP4020 (Permedia 2) or 3Dlabs Permedia 2V | inferred, high confidence | the stock driver registers both PCI identities below, and every register it touches matches the public maps for those chips |
| Chip PCI identities the stock kernel driver accepts | `104c:3d07` (TVP4020) and `3d3d:0009` (Permedia 2V) | established | the driver registers both, read in `rad1drv.o` |
| Chip PCI identity the stock PROM accepts | `3d3d:0009` only | established | the PROM's table of PCI devices it can install a console on holds one row for this pair; the install routine then stores the Permedia 2V identity into the board state whatever it found |
| PsiTech subsystem identity | vendor `12d1`, device `0101` | established | the PROM install routine reads configuration offsets 0x2c and 0x2e and accepts the pair in either halfword order; the kernel driver never reads it |
| Which chip a shipped RAD1 carried | unknown | unknown | the PROM only accepts the Permedia 2V pair, so a RAD1 that could be the console carried that chip (inferred); nothing says a `104c:3d07` board was ever sold |
| PCI revision, class code, BAR sizes as declared | | unknown | the kernel driver reads the revision and logs it; no captured value exists |
| Part numbers (PsiTech, SGI) | | unknown | the 1999 thread asks for the SGI part number and the reply held does not give it |
| Board reference clock | 14.31818 MHz | inferred | every clock formula in the software uses 14318180 Hz, see [modes.md](modes.md) |
| Flash | 64 KiB, byte-wide, JEDEC-style program sequence | established (size, sequence); inferred (the part) | the driver's own request size and unlock bytes |

The chip register names are those of the public Permedia 2 documentation; the TI TVP4020 programmer's manual was not read for this page, so register meanings the public drivers and the shipped software do not show are unknown rather than filled from the manual.

## Where it runs

- **Machines.** The kernel driver is in the IP27 kernel object directory of IRIX 6.5.30, which is the Origin 200, Origin 2000 and Onyx2 kernel family (established). The product is sold for the Origin 200 only (sheet). The IO6 base I/O PROM carries a console driver for it in release 6.156 (established, binary read). Whether an Origin 2000 or Onyx2 ever ran one is unknown.
- **Releases.** The driver object `rad1pci.a` is on the held IRIX 6.5.4 media (built 13 April 1999) and on every held later release to 6.5.30 (built 20 July 2006), always in the IP27 kernel object directory and never in the IP30, IP32 or IP35 ones; the 6.5.30 object is the one the pages were read from (established: file listings of the held overlay discs, one object per disc, each carrying its build date as a string). It is absent from the first 6.5 release's media (June 1998), from the 6.5 beta, from 6.5.2 and from 6.5.3, so 6.5.4 is the first held release with the driver (established for the held media). The first-release disc of 6.5.1 is not held, only its second overlay disc, which has no kernel objects, so 6.5.1 is unknown. The 6.5.4 and 6.5.30 builds differ in compiler and code layout but register the same two PCI identities, map the same four resources by the same selectors and sizes, make the same sequence of kernel calls in the attach routine, and carry byte-identical mode and parameter tables; the distinct immediate constants of the chip initialiser match apart from stack offsets (inferred: the two builds' attach and initialiser were compared by call and constant lists, not read line by line). Release history and hashes: [../../references/binaries.md](../../references/binaries.md). The June 1998 IO6 PROM, 6.11, contains no RAD1 console strings (established: the string is absent from the decompressed image); the first PROMs with the console code are 6.27 of March 1999 (see [../../software/firmware/sgi-prom-rad1.md](../../software/firmware/sgi-prom-rad1.md#release-history)), so the console code and the kernel driver arrived together, a month apart in build date (inferred from the build dates). The IRIX 6.5.30 release notes list a fixed bug, "Psitech RAD1 card conflict with QLogic SCSI PCI card", which shows 6.5.30 still carried and maintained the driver (one note).
- **Later releases.** One owner reported in 2004 that PsiTech's own drivers stopped working somewhere between IRIX 6.5.12 and 6.5.19 and that PsiTech would not rewrite them. That is a participant's report, not a specification; it says the vendor's driver and the stock one are different software (inferred).

## Relationship to the RAD4

Different board, same author lineage. The RAD1 has no PLX bus interface or external RAMDAC and a different PCI identity (`12d1:0104` and `12d1:0105` belong to the RAD4 and RAD4-KM), so the two boards' register contracts must not be merged. The stock RAD1 kernel driver was written from the RAD4 driver: it serves the same request numbers 101 to 141 with the same argument layouts, and its textport and mode code descend from it (the request numbers and argument layouts are established from the code; the lineage is inferred; see [../../software/rad1/kernel-driver.md](../../software/rad1/kernel-driver.md#requests)). The RAD4's request interface is therefore a guide to what a RAD1 client may send, and the RAD1 driver ignores the requests that need RAD4 hardware.

## Resources the stock software maps

The kernel driver names its resources by the Bridge-family window numbers: window 0, window 1 and window 2 (established). The PROM works from configuration space directly.

| Resource | Kernel driver | PROM | Rating |
|---|---|---|---|
| Registers: Region Zero of the chip | window 0, 128 KiB requested | the first base address register, masked to 128 KiB | established; the layout is the chip's, established from the public maps |
| Framebuffer | window 1, 8 MiB requested (a plain translation first, a mapped window if that fails) | not mapped; the PROM draws through the chip's render commands | established. Which BAR carries it is inferred (the second, as in the public Linux driver for the chip) |
| Flash | window 2, 64 KiB requested | the expansion ROM base register, masked to 64 KiB | established. The two drivers name the same 64 KiB flash in different ways; which BAR the kernel's window 2 is, is unknown |
| Configuration space | 256 bytes, read for vendor, device and revision | read at 0x10, 0x2c, 0x2e and 0x30 | established |

The kernel driver only reads configuration space (vendor at offset 0, device at 2, revision at 8, through the kernel's configuration-read call) and never writes it: no call to a configuration-write routine exists in any of the five members of the 6.5.4 and 6.5.30 builds (established, undefined-symbol lists), so the command register and base address registers are set by the platform's PCI code before attach. The window numbers are the kernel's resource selectors 8, 9 and 10; selector 7 is configuration space. That window n is base address register n follows the kernel's naming convention and was not checked against a header this round (inferred).

Every access either driver makes to Region Zero is an aligned 32-bit load or store (established); the flash is accessed a byte at a time.

## Region Zero

The chip's register region follows the public Permedia 2 layout. Blocks the software touches:

| Offset range | Block | Use by the stock software |
|---|---|---|
| 0x0000 to 0x00ff | control and status, interrupts, FIFOs, DMA | reset, interrupt flags and enable, FIFO space polling, bypass and output DMA |
| 0x1000 to 0x1fff | memory control | memory type, boot address, timing word, bypass write mask |
| 0x2000 | output FIFO | sync tags and read-back words |
| 0x3000 to 0x3080 | video timing | screen base, stride, horizontal and vertical counts, video control |
| 0x4000 to 0x407f | RAMDAC ports | palette, indexed-register ports, cursor ports; the two chips lay these out differently |
| 0x63c4 | SVGA | one write that turns the legacy VGA core off |
| 0x8000 to 0x93ff | graphics processor registers | the rectangle, point and trapezoid fills, copy, texture-copy and read-back setup |

The software never touches the video-stream block, the reserved block or the byte-swapped alias of the graphics registers (established). Every offset the stock software uses appears in the shipped objects as a load or store offset or an index immediate; the one exception is the vertical-interrupt line register, which the shipped objects never access (inferred: the code that would use it is not built).

## What is not known

See [../../questions/open-questions.md](../../questions/open-questions.md) for the routes tried. In short: the PCI configuration of a real card, which chip the card carried, the part numbers, the flash part and its BAR, reset values, and any PsiTech software other than the stock driver.

## Review note

Independent review, 2026-11-21 (not the author). The ratings converted from the retired six-rating scheme were sampled (see [../../AGENTS.md](../../AGENTS.md)); the sampled rows in this page read consistently with their evidence. The 6.5.4 first-release claim rests on media listings this review could not re-open (only the 6.5.22 discs and the 6.5.30 first disc are on hand), so it is carried as written; the 6.5.30 archive hash and size in `references/binaries.md` were re-checked.
