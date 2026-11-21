# PsiTech boards in SGI firmware and standalone programs

Which SGI and PsiTech firmware images know a PsiTech board, how each one finds it and what it draws. Ratings follow [AGENTS.md](../../AGENTS.md): **established** (a table or function body read in full from a shipped binary), **inferred** (a reasoned reading, or one from a partial read) and **unknown**. Everything here comes from the shipped images; no manual covers a PsiTech board's registers. Names such as `rad4_earlyinit` are symbols the shipped objects carry.

## Pages

| Page | What it holds |
|---|---|
| [psitech-ip27-prom.md](psitech-ip27-prom.md) | PsiTech's own IP27 PROM, version 5.30: the only firmware that recognises the RAD4, RAD4-KM and `12d1:0100`. The boot stage's slot scan and ROM copy are in [../rad4/proms-and-kernel.md](../rad4/proms-and-kernel.md) |
| [rad4-option-rom.md](rad4-option-rom.md) | The expansion ROM image PsiTech ships for the RAD4 and RAD4-KM: the console code the PsiTech PROM runs |
| [sgi-prom-rad1.md](sgi-prom-rad1.md) | The RAD1 console in SGI's IO6 and IP27 PROMs, release by release |
| [other-firmware.md](other-firmware.md) | Images that do not drive a PsiTech board: the Octane, O2 and Origin 300 PROMs, `sash`, `ide`, `fx` and the kernels |
| [console-selection.md](console-selection.md) | How `console=g` picks the board, the environment variables that carry the result and the kernel's textport hooks |
| [model-needs.md](model-needs.md) | What a board model must present for each PROM to find the board and print on it |

The RAD1's registers and its PROM drawing functions are in [../rad1/textport.md](../rad1/textport.md); this section adds the release history and the PCI table that picks the board.

## Which firmware knows which board

Images are named by the banner they print. Every version listed was searched for the board names, the `12d1` identity words and the console messages (established, string and table scan of each image, including its compressed parts).

| Firmware | RAD1 (`12d1:0101`, Permedia 2) | RAD4 (`12d1:0104`), RAD4-KM (`12d1:0105`) | Where |
|---|---|---|---|
| IP27 PROM "SGI Version 5.30 PSITECH", 21 Oct 1998, shipped in the PsiTech 1.3k package | row present, same install routine as the RAD4 | rows present: console through the board's own ROM code | [psitech-ip27-prom.md](psitech-ip27-prom.md) |
| IO6 (base I/O) PROM 6.27 to 6.156 | console code present from 6.27 (18 Mar 1999) | no | [sgi-prom-rad1.md](sgi-prom-rad1.md) |
| IP27 PROM 6.27 to 6.48 | console code and table row present | no | [sgi-prom-rad1.md](sgi-prom-rad1.md) |
| IP27 PROM 6.57 to 6.156 | initialisation code left in the image; no table row and no install message, so unreachable (inferred) | no | [sgi-prom-rad1.md](sgi-prom-rad1.md) |
| IO6 PROM 4.9 to 6.25; IP27 PROM 4.9 to 6.25 | no | no | [sgi-prom-rad1.md](sgi-prom-rad1.md) |
| IP35 (Origin 300) PROM 6.37 to 6.211 | the name `PSITECH_RAD1` in diagnostic name tables only; no console code | name `PSITECH` only | [other-firmware.md](other-firmware.md) |
| IP30 (Octane) PROM 2.15 to 4.17; IP32 (O2) PROM 2.3 to 4.18; IO4 PROMs | no | no | [other-firmware.md](other-firmware.md) |
| `sash64`, `sashARCS`, `fx.64`, `ide` of IRIX 6.5.30 | no (`ide` has an unrelated SGI audio chip test named RAD) | no | [other-firmware.md](other-firmware.md) |
| IRIX 6.5.30 kernels | textport hooks `rad1_earlyinit` and `rad4_earlyinit` in the IP27 kernel only | hook present, driver comes from PsiTech's package | [console-selection.md](console-selection.md) |

## Method and what was not read

Each image was unpacked (the IP27 and IO6 images carry a gzip stream holding a MIPS64 ELF), searched, and the matching routines were read in a Ghidra export checked against `mips64-linux-gnuabi64-objdump` output, both run in the toolchain containers. The PsiTech package's ROM image is stored as Motorola S-records; it was converted to a flat image first. No IRIX source was read for these pages.

Not held: PROM images for the IP28 (Indigo2 Impact), the IP22, IP24 and IP26 families were not searched for the board names; none of them is a platform PsiTech sold for. `symmon` and `dbgmon` were not found as separate files.
