# PsiTech's IP27 PROM, version 5.30

The RAD4 package, release 1.3k, carries a modified Origin 200 and Origin 2000 node-board PROM, installed as `var/rad4/ip27prom.img` in the `rad4x.sw.prom` subsystem. It is the only firmware examined that recognises the RAD4 and RAD4-KM. This page reads it. The ROM code it calls is in [rad4-option-rom.md](rad4-option-rom.md); how `console=g` reaches it is in [console-selection.md](console-selection.md). Ratings are as in [which-firmware.md](which-firmware.md).

## The image

| Item | Value | Rating |
|---|---|---|
| Container | 885,184-byte PROM image: a 4 KiB header, the boot stage, one gzip stream holding a big-endian MIPS64 ELF (753,694 bytes after decompression), a small code blob and a symbol-name table | established |
| Banner | "SGI Version 5.30 PSITECH built 01:18:52 PM Oct 21, 1998" (the ELF embeds a second banner, built 01:17:34 PM the same day) | established |
| SHA-256 of the image | `627e53673dc8d39ae4a66ff0c345aeb503a443c4fb0e84326f21b7b501756cca` | established |
| Relation to SGI's PROMs | built from SGI's 5.x branch (after 5.28, 24 Sep 1998); it has none of the RAD1 code of PROM 6.27 and later | inferred from the version sequence and string scan |

## What it adds

Compared with the SGI IP27 PROMs, the image adds, in its ELF stage (established, read in full): a PCI table with PsiTech rows, an install routine that runs code from the board's expansion ROM, and a console output path that sends every character to that code. Its flat boot stage adds the slot scan that copies the ROM into memory (see below and [../rad4/proms-and-kernel.md](../rad4/proms-and-kernel.md)).

### The PCI table

The PROM keeps a table of PCI functions it can build a graphics console on: 24-byte rows holding a device word, a vendor word, a flags word (0xa), zero and the address of an install routine. The PsiTech image's rows for this purpose, read from the table in the image:

| Vendor | Device | Board | Install routine |
|---|---|---|---|
| `12d1` | `0105` | RAD4-KM | PsiTech install routine |
| `12d1` | `0104` | RAD4 | same |
| `12d1` | `0100` | a PsiTech board that no document, driver or other firmware here names | same |
| `12d1` | `0101` | RAD1 | same |
| `3d3d` | `0009` | a raw Permedia 2V, which is what a RAD1 carries as its primary identity | same |

Besides the rows, the console selection routine compares the first configuration word of each PCI function directly against the same five identity words (`0x010412d1`, `0x010512d1`, `0x010012d1`, `0x010112d1`, `0x00093d3d`). A match sets the environment variables `psitech` and `nodbgmon` to `1` (see [console-selection.md](console-selection.md)). That the routine matches `3d3d:0009` for any board, not only a PsiTech one, is established; it means a stock Permedia 2V card also triggers it.

This image stores the device word first. SGI's PROMs do the same up to 6.119 and store the vendor first from 6.129; the lookup is by the (vendor, device) pair either way (established, tables of both read).

### The install routine

Read in full. It runs once per matching PCI function when the PROM installs its device drivers:

1. Look up the environment variable `psitech`. Absent, return; present and the console already installed, republish the entry address and return.
2. Print "Installing Graphics Console...".
3. Read the function's configuration space through the Bridge window: base register 0 (offset 0x10, low four bits masked), base register 2 (offset 0x18, low four bits masked) and the expansion ROM base register (offset 0x30, low two bits masked), each turned into an uncached address in the node's PCI window.
4. Read the first word of the expansion ROM. If it is not `0xaa55`, fall back: set `ConsoleIn` to the path another routine returns (the serial console, inferred) and return. The word is read as a 32-bit big-endian load, so the ROM's first two bytes `55 aa` arrive as `0x0000aa55` after the bridge's byte swap (inferred; the swap itself is the one the RAD1 notes record).
5. Compute the console entry point as the node's physical address `0x01800100` plus `0x78`, in the cached address window of the board's own node. The code there was copied by the boot stage (below).
6. Call that entry with command 0 and three arguments: the expansion ROM address, the base 2 address and the base 0 address. A nonzero return prints "PSITECH INIT FAILED" and gives up.
7. Print the banner "Origin200 / PsiTech Graphics Console" through the entry, one character at a time with command 1.
8. Mark the console installed, set `gfx` to `alive` and store the entry address, as `0x%llx`, in `psitech`.

The helper called before each jump only loads the entry address into `t9` (the register the MIPS position-independent code convention uses to find itself); it does nothing else.

### Output

The PROM's character output routine tests `psitech`. If the variable is set it parses it as a hexadecimal address once, remembers it, and sends each character to the entry with command 1. A line feed is preceded by a carriage return. The path is output only: no PROM routine calls command 2, so keyboard input stays with the IOC3 PS/2 port or the serial console (established: no other routine in the decompiled image touches the entry variable).

## Where the called code comes from

The code is put in node memory by the PROM's earlier stage, not by the install routine. The image has two stages: a flat boot stage mapped at `0x1fc00000` that runs first and carries the PCI slot scan, and the ELF read above, which runs later. The boot stage's slot configuration is read in [../rad4/proms-and-kernel.md](../rad4/proms-and-kernel.md#2-psitechs-ip27promimg); in short it assigns the board's base registers and expansion ROM, requires the ROM's first word to be `0xaa55`, picks the ROM image whose PCI data structure carries the board's identity and the code type `0x7f`, copies it to node memory at `0x01800100` with the bytes of each word reordered, and relocates a table of seven base pointers in the image's header. The image's bytes therefore land at `0x01800104`.

That agrees with the call above. The ROM's dispatcher is at image offset `0x74`, and `0x01800104 + 0x74 = 0x01800178`, the address the install routine computes as `0x01800100 + 0x78` (established, by arithmetic over the two readings). The five identity words the boot stage switches on are the five the console selection routine and the PCI table use. I confirmed in the boot stage's bytes that it builds `0x01800100` in two places; I did not re-read its copy loop.

The RAD4 survey records that nothing in the boot stage calls the ROM. The call is made by the ELF stage's install routine and character output described above (established), which closes that gap.

`nodbgmon` is set together with `psitech`. The IRIX kernel carries a debug monitor loader and the ROM's memory is the PROM's reserved region at 24 MiB, so the variable suggests the monitor must not be loaded over it (inferred; no reader of `nodbgmon` was found in the PROM, the stock kernel or the PsiTech kernel objects).

## The other boards in the table

The same routine serves `12d1:0100` and `12d1:0101`, so a RAD1 and the unnamed `0100` board were expected to carry an expansion ROM of the same kind (inferred). Nothing in the PsiTech package carries ROM images for them.
