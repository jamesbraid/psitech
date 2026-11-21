# The software that drives a RAD1

What runs on, and in front of, a RAD1: the parts that ship with IRIX, the parts that came from PsiTech and are not held, and what a client such as an X server can ask of the board. Ratings are as defined in [../../devices/rad1/README.md](../../devices/rad1/README.md).

## What ships with IRIX

| Part | Role | Rating |
|---|---|---|
| IP27 kernel object `rad1pci.a`, installed under the IP27 kernel object directory with the base operating system overlay | the kernel driver: attach, interrupts, DMA, device nodes, requests, flash. Five members: the driver, the chip and mode initialiser, the textport board bring-up, the textport drawing functions and the mode table. See [kernel-driver.md](kernel-driver.md) | established |
| Master file `rad1pci` and a `USE: rad1pci` line in the shipped system file | selects the driver for the IP27 kernel family and sets four tunables | established |
| IO6 PROM 6.156, a console driver for the card | finds the card, initialises it and draws the textport. See [textport.md](textport.md) | established |
| IRIX 6.5.30 release notes | one fixed-bug line: "Psitech RAD1 card conflict with QLogic SCSI PCI card" | established (the line); what the conflict was is unknown |

No other stock IRIX file names the driver or the board: a search of the held 6.5 June 1998 media and the 6.5.30 media for the driver's name, its node names and the PsiTech name finds only the files above (established for the held file trees only; the held media may be incomplete). No stock X server module, library, manual page or diagnostic mentions the RAD1.

## What came from PsiTech and is not held

The product sheet says the card was supplied with the PsiTech Graphics Server (an X server that it describes as protocol-compatible with the X Window System and with SGI OpenGL) and PsiTech PCI drivers for IRIX 6.5, on a CD (established, the sheet). None of that software is held, and no installed copy, manual, patch or archive of it has been found. A 2004 Usenet report says PsiTech's drivers worked up to roughly IRIX 6.5.12 and failed on 6.5.19, and that PsiTech declined to rework them (a participant's report, inferred to mean that the vendor's driver and the stock driver are separate software).

So for the RAD1, the X server and DDX are unknown: no request paths, mode-set sequence, cursor, colour-map, overlay or DMA use of a RAD1 X server can be read, because the server is not available. The routes tried and the next ones are in [../../questions/open-questions.md](../../questions/open-questions.md).

## What a client can ask: the request interface

The stock driver serves a fixed set of requests on `rad1` and, for board 0, the buffered node `rad1_b` (the list and what each does are in [kernel-driver.md](kernel-driver.md#requests)). These are the numbers and argument shapes of the RAD4 driver: the RAD4 X server, `rad4setres` and `rad4d` use requests 113 to 123, 135 and 140 (see [../../devices/rad4/xserver-decode.md](../../devices/rad4/xserver-decode.md#driver-request-interface)), and the stock RAD1 driver serves every one of them. The RAD4's tools open `/dev/rad4` where the RAD1 driver publishes `rad1`. So a client written for the RAD4 interface could draw and set the mode on a RAD1 through the same calls with a different node name (inferred: the request numbers and argument shapes match; nothing was run). That the PsiTech Graphics Server for the RAD1 is the RAD4 server with a different node name is a guess and is not recorded as a finding.

What differs for a client:

- The two palette requests (101, 102) do nothing on a board with the `104c:3d07` chip.
- Request 141 loads the texel table used for 8-bit writes; it has no RAD4 counterpart in the list above.
- The RAD4's depth, gamma, serial-ROM and overlay-start requests (103 to 112, 127, 131 to 134) are accepted and ignored. The RAD1 has no overlay-plane or window-ID request: the sheet's 8-bit overlay has no request in the stock driver.
- The mode word (request 114) selects one of three modes in the stock kernel's table (the IO6 PROM carries eight), not the RAD4's thirteen.

## Files read

The kernel driver, from the IRIX 6.5.30 base operating system overlay (SHA-256 is of the file as extracted):

| File | Bytes | SHA-256 |
|---|--:|---|
| `rad1pci.a` | 93,828 | `43b86a8e6d29b8b29796604e0f6fc626fdf17c6532e3e43df944531eb8096f2b` |
| member `rad1drv.o` | | `f7b98b61a9f2c7359bd50983a330fae2ee69aaf95f7495ad2485b5e4ba387918` |
| member `rad1_init.o` | | `a4e33971869e4d95bdb125df313cc2419766a6ad0ec46fb63f24e3fe1d5e6f10` |
| member `rad1_tpinit.o` | | `529aa6cc5d8c4551359687e418931bd617f4bde892ace5a1eb4bed573105751c` |
| member `rad1_tport.o` | | `543761b5ba2f66d0bb78cd3b368d9cee0b64bcc8d4264855fb864786b8f94dc9` |
| member `rad1data.o` | | `8c867bb214d7952904e9bb8c6d7bf5df99565305207ce5e74f0b1cc32096d32c` |
| master file `rad1pci` | 426 | `9a6996cf174be25b7ca05e791870096193bf536e4ed3b47a1a9ea48966fc2937` |
| system file `irix.sm` | | `db30e005e5329d85d8fc81067a4c1dac0f1f65f1513cdf2ef1b7c206094e26f4` |

The PROM, IRIX 6.5.30 Installation Tools and Overlays, IO6 PROM 6.156:

| File | Bytes | SHA-256 |
|---|--:|---|
| `io6prom.img` as shipped | 365,328 | `024d2f28b526933e8f00d964fefdfcd9b0e873d504a43d9307099579e2b59ae9` |
| decompressed image (the PROM's own loader format, gzip, unpacked) | 773,406 | `bf341a71821541233cb96459f6b99f6f4ecd2cf90f7e9321d918686ee6c25047` |

Where to put them for the checks: [../../references/irix-files.md](../../references/irix-files.md) says how `root/` is laid out; copy these files under `root/` from your own IRIX 6.5.30 media. Nothing here is a copy. The PROM version 6.11 from the June 1998 6.5 media was also scanned and contains no RAD1 console code.

## Not covered

PsiTech's own RAD1 software (above), any IRIX release between 6.5.0 and 6.5.30 other than the PROM at 6.11, the PROM images between 6.11 and 6.156, and 64-bit userland that talks to the driver.
