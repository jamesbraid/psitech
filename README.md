# psitech

Notes on PsiTech's graphics boards for SGI systems, starting with the RAD4: a PCI card for the Origin 200 (and, as
the RAD4-KM with keyboard and mouse connectors, the Origin 2000) with an 8 MB framebuffer, a PLX PCI 9060-compatible
bus interface and an IBM RGB561-compatible RAMDAC. PsiTech was a third-party vendor, and the board's own software
is the only thing that says how it is driven: a kernel driver, a standalone X server and two small tools, shipped as
release 1.3k for IRIX 6.5.

No manual for the board's registers was ever published. What is here comes from reading that software, the
PLX and IBM datasheets for the two parts the board is built around, and PsiTech's owner's guide and product sheets.
Every fact notes where it came from and how firmly: established, observed, software expectation, inferred,
approximation or unknown.

## What's covered

- **Identity and placement:** PCI IDs, base address regions, the expansion ROM resource the driver uses for DMA, and
  what is known and unknown about the board's parts.
- **Registers:** the bus interface, the board's own control, mask and timing registers, and the RAMDAC registers the
  software touches.
- **Display modes:** the driver's 13 modes, the clock arithmetic that reproduces all of them, and how the
  configuration EEPROM selects one.
- **X server and driver:** how the standalone server draws, which driver requests it makes, and what each does.

Chip pages are under [devices/](devices/README.md), the software side under [software/](software/README.md).
The RAD1 (a Permedia 2 board) and the RAD4-KM and RAD4C-KM variants are listed in [COVERAGE.md](COVERAGE.md) with
what is still missing.

## Using it

The headers and the crate live in [generated/](generated/). Don't edit them; they're built from the
`registers.toml` next to each device page.

To run the checks yourself:

```sh
git clone https://github.com/jamesbraid/psitech && cd psitech
tools/setup-clone.sh
retools/tools/re-run retools/tools/defs/ci-check
```

You'll need Podman, git and python3. The PsiTech release is not included. [references/irix-files.md](references/irix-files.md)
says which files the notes were read from.

## How far along

The register map and the mode table are settled as far as the software goes. The board's own parts, reset behaviour,
the timing words and the RAD4-KM controller are open. [COVERAGE.md](COVERAGE.md) has the areas and
[questions/](questions/README.md) the open questions.
If you spot a mistake or have a manual, a board photograph or a configuration dump we don't, [open an issue](https://github.com/jamesbraid/psitech/issues).

## License

[BSD 3-Clause](LICENSE). The `retools/` scripts started life as gr4's and keep its notice. No PsiTech, SGI or
IBM material in here; bring your own.

## Credits

James Braid, plus a lot of Claude reading MIPS disassembly so I didn't have to.

Thanks to -

* Dominik Behr ([@techomancer](https://github.com/techomancer)) for [gr2](https://github.com/techomancer/gr2)
  and [gr4](https://github.com/techomancer/gr4), where the layout and working style come from
* PLX Technology and IBM for publishing the datasheets of the parts the board is built around
* Everyone keeping SGI manuals, PsiTech's guides and period software online
