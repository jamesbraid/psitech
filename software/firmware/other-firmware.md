# Firmware and standalone programs that do not drive a PsiTech board

The negative results, with what was searched, so nobody repeats it. Ratings as in [which-firmware.md](which-firmware.md). "Searched" means the whole image was scanned, compressed parts included, for the board names (`PsiTech`, `RAD1`, `RAD4`, `Permedia`), the identity words `12d1` and `3d3d`, and the console messages of [sgi-prom-rad1.md](sgi-prom-rad1.md) and [psitech-ip27-prom.md](psitech-ip27-prom.md).

## Origin 300 and later (IP35) PROMs

Searched: every image from 6.37-test (27 Sep 1999) to 6.211 (25 Jan 2008), 31 builds. All carry the name `PSITECH` and, from 6.81 (5 Jun 2001), `PSITECH_RAD1` (established). None carries the identity words, the install message, a mode-record message or code that calls a board ROM.

The two names sit in diagnostic text: a table of PCI device type names printed by the I/O configuration test ("Device %d Type %s", with `SGI_RAD`, `UNIVERSE_VME`, `FIBERCHANNEL` and `QLOGIC_FIBER2` among them) and a second table of eight-character names printed in a "PCI slot %d pciid %08x" listing next to `RAD`, `UNIVME`, `USB` and `IEEE1394`. Both are lists for naming devices in a report. The routine that maps a PCI identity to a name, and so which identity prints as `PSITECH`, was not traced: the strings are not referenced from any routine the decompiler recognised (unknown; the route is the listing routine reached from the "I/O console probing" message in the image). The nested base I/O image inside the 6.210 payload carries the same strings and no more.

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
