# Firmware and standalone programs that do not drive a PsiTech board

The negative results, with what was searched, so nobody repeats it. Ratings as in [which-firmware.md](which-firmware.md). "Searched" means the whole image was scanned, compressed parts included, for the board names (`PsiTech`, `RAD1`, `RAD4`, `Permedia`), the identity words `12d1` and `3d3d`, and the console messages of [sgi-prom-rad1.md](sgi-prom-rad1.md) and [psitech-ip27-prom.md](psitech-ip27-prom.md).

## Origin 300 and later (IP35) PROMs

Searched: every image from 6.37-test (27 Sep 1999) to 6.211 (25 Jan 2008), 31 builds. All carry the name `PSITECH` and, from 6.81 (5 Jun 2001), `PSITECH_RAD1` (established). None carries the identity words, the install message, a mode-record message or code that calls a board ROM.

The two names sit in diagnostic text: a table of PCI device type names printed by the I/O configuration test ("Device %d Type %s", with `SGI_RAD`, `UNIVERSE_VME`, `FIBERCHANNEL` and `QLOGIC_FIBER2` among them) and a second table of eight-character names printed in a "PCI slot %d pciid %08x" listing next to `RAD`, `UNIVME`, `USB` and `IEEE1394`. Both are lists for naming devices in a report.

**Which identity prints as the name (established, both routines read in full in the 6.210 CPU image, `554924380189`).** Each routine reads configuration word 0 of every function on a PCI bus and sorts it with a compiled range-and-equality search on the whole word, vendor in the low half. The word `0x00093d3d` (vendor `3d3d`, device `0009`, the Permedia 2V) selects `PSITECH_RAD1` in the type-name routine (image offset 0x42478 onward, string at 0x84b80) and `PSITECH` in the listing routine (offset 0x47fe8 onward, string at 0x881f0). Neither routine reads the subsystem pair, so any `3d3d:0009` board prints as a PsiTech device, whoever made it. No case in either routine matches `104c:3d07` (the other chip the kernel driver accepts) or the PsiTech vendor `12d1`, so a RAD4 or RAD4-KM prints as an unknown device. Past the match the routines only choose a name and a counter; no console code follows (inferred from the two routines' remaining paths, which were read to their returns).

Why earlier searches found no reference: the routines never address the strings directly. They load a pointer from the image's global-pointer table (`gp` minus 29008 and minus 29016 hold pointers to the string areas; the table is inside the image, near its end) and add constant displacements, so a scan for string addresses or for `lui` and `addiu` pairs misses them. The same method resolves every other name in the two tables. The nested base I/O image carries the same strings; its routines were not read again (inferred to match).

So an Origin 300 PROM can name a PsiTech board in a configuration report but cannot use it as a console (inferred from the absence of console code).

## Octane (IP30), O2 (IP32) and Challenge/Onyx (IO4) PROMs

Searched: IP30 2.15 to 4.17 (21 builds, 1997 to 2004), IP32 2.3 to 4.18 (18 builds), IO4 1.0 to 2.1 (13 builds). No hit of any kind (established). PsiTech's package installs `rad4pci.o` for the Octane and O2 kernels and a server for the O2, so the boards were meant to run there as a second head under the system's own console, never as the console (inferred; the owner's guide says the same for the O2, see [../rad4/package.md](../rad4/package.md)).

## Standalone programs

Searched in the IRIX 6.5.30 boot directory:

| Program | Result |
|---|---|
| `sash64`, `sashARCS` (the 64-bit and ARCS loaders) | no hit |
| `fx.64` (disk formatter) | no hit |
| `ide.IP30` (diagnostic monitor) | no PsiTech or Permedia name. It does carry three tests named `rad_regs`, `rad_dma` and `rad_ram` ("RAD Reset", "RAD Status DMA", "PCI Shoe Box Tests") and a scripted call to `rad_regs` in its report routine. These test SGI's RAD digital audio chip, not a graphics board: the messages talk about a status DMA and RAM, and the chip's kernel driver object has no graphics code (inferred from the text; the identity the tests use was not read) |

`symmon` and `dbgmon` are not held as separate files; the stock IP27 kernel carries a debug monitor loader (see the `nodbgmon` note in [psitech-ip27-prom.md](psitech-ip27-prom.md)).

## Kernels

- IRIX 6.5.30 IP27 kernel: contains the RAD1 driver (`rad1pci`, with its textport hooks) and the weak references `rad1_earlyinit` and `rad4_earlyinit` in its textport object; no RAD4 driver ([console-selection.md](console-selection.md)). The kernel image has no `psitech` or `nodbgmon` string.
- IRIX 6.5.30 IP35 kernel: one hit, `PSITECH, INC.`, in a long sorted list of company names that is the IEEE registry of Ethernet address assignments. It is not board support (inferred from the surrounding names, which are all company names).

## Not searched

PROM images for the IP28 (Indigo2 Impact), IP22, IP24, IP26, IP12, IP17, IP20, IP5, IP6 and IP7/IP9 families. PsiTech sold for the Origin, Octane and O2 only, so these are low value; they are in the same PROM catalogue and could be scanned the same way.

## Review note

Independent review, 2026-11-21 (not the author). Re-read in the 6.210 CPU payload (extracted from the packaged image at offset 0x1000; SHA-256 matches [../../references/binaries.md](../../references/binaries.md)): the word 0x00093d3d is built in both routines (the `lui 9; ori 0x3d3d` pairs at 0x42704, 0x42758 and 0x480cc), and `PSITECH_RAD1` and `PSITECH` sit at 0x84b80 and 0x881f0. The path from the equality test to the name pointer through the global-pointer table was not retraced, so that link stays as the author graded it on the strength of the other reading.
