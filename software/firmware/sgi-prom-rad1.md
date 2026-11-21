# The RAD1 console in SGI's PROMs

SGI's base I/O (IO6) and node (IP27) PROMs for the Origin 200 and Origin 2000 carry a console driver for the RAD1, a Permedia 2 board that presents PsiTech's identity as its PCI subsystem. The IO6 PROM 6.156 reading, the board bring-up, the drawing functions and the kernel's early console are in [../rad1/textport.md](../rad1/textport.md). This page adds what that page does not have: the release in which the code first appears and when it stopped being reachable, how the PCI table is laid out, and the start-up mode record. Ratings as in [which-firmware.md](which-firmware.md).

## Release history

Every IO6 image from 4.9 to 6.156 and every IP27 image from 4.9 to 6.156 held was searched, compressed parts included, for the strings "Psitech-RAD1", "Installing RAD1 Graphics Console" and "rad1 resolution unknown mode" and for the table row. The match is by build, not by IRIX release; the banners are the ones the images print.

| Image | Build date | RAD1 console code | Table row for `3d3d:0009` | Mode-record message |
|---|---|---|---|---|
| IO6 4.9 to 5.28, 6.10 to 6.25 | to 13 Jan 1999 | no | no | no |
| IO6 6.27 | 18 Mar 1999 | yes | yes | no |
| IO6 6.31 | 11 Jun 1999 | yes | yes | no |
| IO6 6.36 to 6.156 | 9 Sep 1999 to 18 Nov 2003 | yes | yes | yes |
| IP27 4.9 to 6.25 | to 13 Jan 1999 | no | no | no |
| IP27 6.27 to 6.48 | 18 Mar to 22 Dec 1999 | yes | yes | from 6.36 |
| IP27 6.57 to 6.156 | 12 Apr 2000 to 18 Nov 2003 | initialisation code only: the name and the mode-record message are in the image, the install message is not | no (6.156 read: three rows, none for the RAD1) | yes |

All rows established as string and table presence. The first IO6 and IP27 images with the code are both 6.27, built the same day (established); the IRIX release that first shipped one is not pinned here. The early 5.x patch builds (5.26 to 5.28) have none. The 6.156 IP27 image keeps the initialisation code (two routines reference its strings) but the table has rows only for the IOC3 on the base I/O board, the QLogic SCSI controller and a do-nothing fallback, so the RAD1 install routine cannot be reached (inferred from the table). On an Origin 200 the console therefore comes up from the IO6 PROM, which is the image that holds the board's console install in every later release.

## The PCI table

The PROM builds a node for every function it finds on the Bridge and looks the (vendor, device) pair up in a table of 24-byte rows: two identity words, a flags word (always 0xa), zero and the install routine's address. In the IO6 PROM 6.156 the rows are, in order: `10a9:0003` (the IOC3), `1077:1020` (a QLogic SCSI controller), `3d3d:0009` (the RAD1 install routine) and a last row with a placeholder identity `fafb:0300` whose routine returns zero. Each image up to 6.119 stores the device word first and each from 6.129 the vendor word first; the lookup is the same (established).

The RAD1 row names the raw Permedia 2V, not PsiTech. The install routine then requires the PsiTech subsystem identity `12d1:0101` before it accepts the board ([../rad1/textport.md](../rad1/textport.md#prom-finding-the-card)). A RAD1 presenting only the TI TVP4020 identity `104c:3d07` matches no row: the pair is nowhere in the 6.156 image (established, searched as words and halfwords).

## The start-up mode record

The initialiser reads a 128-byte record from offset 0xff00 of the window the PROM maps through the expansion ROM base register, and reads it twice, copying it byte-swapped (each byte at index xor 3) into the board state (established, read in full). From the first word:

| Field | Bits |
|---|---|
| Mode index | 6:0 |
| Option fields | bit 8, bit 10 and bits 13:12, handed to the mode routine as three arguments |

An index of 8 or more prints "rad1 resolution unknown mode 0x%x set to 0" and uses mode 0 with the three options cleared. The mode table in the 6.156 image holds eight records, indexes 0 to 7 (established, table read):

| Index | Width by height | Refresh label (Hz) |
|--:|---|--:|
| 0 | 1280 x 1024 | 60 |
| 1 | 800 x 600 | 75 |
| 2 | 1280 x 1024 | 72 |
| 3 | 640 x 480 | 72 |
| 4 | 800 x 600 | 56 |
| 5 | 1024 x 768 | 60 |
| 6 | 1024 x 768 | 70 |
| 7 | 1024 x 1024 | 60 |

Each record is 17 words (68 bytes): width, height, label, horizontal total less one, and the remaining timing fields. A 33-row table of three small fields and a product is searched for the row whose product equals the record's width (32 up to 2048, with a fallback row); it is the partial-product table the RAD1 pages describe. The PROM's table, with eight records and a limit of 8, is its own: the kernel's table has three records, and the earlier count of three for the PROM's limit came from reading the kernel's table. The limit is a data word at the end of the last record's 17th word and the start-up routine compares the index against it (established, compare read in the image's decompilation); the records and the comparison with the kernel's table are in [../../devices/rad1/modes.md](../../devices/rad1/modes.md#the-proms-own-table).

The initialiser's two chip paths differ by identity word: for `9` (Permedia 2V) it programs the clock through the indexed registers at 0x4020, 0x4028 and 0x4030, for `0x3d07` through 0x4000 and 0x4050. The install routine always stores the identity `9`, so the `0x3d07` path is dead in this PROM (inferred, install routine read in full).

## What the PROM does not do

No RAD1 code reads or writes the PLX-style registers of the RAD4 family, and none calls code in the board's ROM: the RAD1 console is drawn by the PROM's own render-command sequences ([../rad1/textport.md](../rad1/textport.md#the-textport-functions)). This is a different mechanism from the PsiTech PROM's ([psitech-ip27-prom.md](psitech-ip27-prom.md)).
