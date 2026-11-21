# Shipped binaries

The files of PsiTech's RAD4 release 1.3k for IRIX 6.5 that the notes were read from, by role and SHA-256. Nothing here is a copy. [irix-files.md](irix-files.md) says how to lay them out.

| File | Size (bytes) | SHA-256 |
|---|--:|---|
| the release archive (`rad4x_65_13k.tar.gz`) | | `ebf9d26aa117a6c3ecd0abb0fe6b0512e8cc4e86d343c0dcf7fdebf464ddf55b` |
| kernel driver object, decoded from the archive (Origin 200 and Octane-class build) | | `e95edb231a6f51b212e91ee6747508bdf086038dc935b54ae2e64716d7e87834` |
| standalone X server, decoded from the archive | 3,904,468 | `c2da6ab19e28fac91d5c0d149263e76ceb7fd992988eb753e8658042f3178599` |
| `/usr/bin/rad4setres` | 13,932 | `56464ddcd6867548b0b9b61c32257ff9c55fb19a174c01dc8ad76c475d9c3d94` |
| `/var/rad4/Xradsgi` (server copy from an installed system; differs from the standalone server) | | `f8142ac73464f3b3c5902fbd421a666d32cfd592ed80fa6c90b4c3de5a4c7f5e` |
| `/var/rad4/rad4d` | | `4491a9e10db51c437e7f1162e1b55ce6dfdb4c10e42d56503edc56625d4a5afe` |

The driver and server are stored compressed in the archive and were decoded in memory; the hashes are of the decoded objects. Sizes left blank were not recorded.

The release archive, unpacked and its members decoded (each is stored compressed in the archive's software image), gives these hashes (SHA-256 of the decoded files):

| File | Size (bytes) | SHA-256 |
|---|--:|---|
| kernel driver object, Origin 200 and Octane-class build (`var/sysgen/boot/rad4pci.o`) | 188,640 | `e95edb231a6f51b212e91ee6747508bdf086038dc935b54ae2e64716d7e87834` (matches the row above) |
| standalone X server (`var/rad4/Xradsgi`) | 3,904,468 | `c2da6ab19e28fac91d5c0d149263e76ceb7fd992988eb753e8658042f3178599` (matches the row above) |
| `usr/bin/rad4setres` | 13,932 | `2c24f92877325c0ce520bd28e6594a9cfb483b7dedfba54e53c52e3191da6c53` (same size as the row above, different hash; which of the two the notes were read from is not recorded) |
| `var/rad4/rad4d` (the IP32 build the archive carries) | 9,488 | `5f5c5d7f1af6b0f2a26cc0658b19b2efcd962aef07e2305d81679127672519d4` (not the installed-system copy above) |
| `var/rad4/rad4_prog` | 13,808 | `f56da07bb4a64c3ee2b91c3a5e92e7c3145e7d2ab7734f6ed66ce0223c3b0202` |
| `var/rad4/rad4_rom` | 98,296 | `d9420b62f7411024f5a3279f80bc6620d40df0cf8bd488b8cea943c2931b9e14` |
| `usr/lib/X11/dyDDX/psitech.so` | 1,761,568 | `b5fb66dec98082d5c7f904195716766d141b83794a9509219a0134ad339c0b8f` |
| `usr/include/rad4pci.h` | 4,225 | `5d92aad7fb7cbd87402a675d114db10ff2ca664430bded0d20b5f3dd3b7469ee` |

Public documents are listed in [documents/INDEX.md](documents/INDEX.md).

## RAD1 kernel driver, by IRIX release

SGI's stock driver archive `rad1pci.a` (five members: `rad1drv.o`, `rad1_init.o`, `rad1_tpinit.o`, `rad1_tport.o`, `rad1data.o`) as installed under the IP27 kernel object directory by the base operating system overlay, SHA-256 of the extracted file. The overlay's machine-dependent ("m") and full ("f") products carry separate copies from 6.5.4 to 6.5.21; the date is the build date the object carries as a string. Absent from the held media of 6.5 (June 1998), the 6.5 beta, 6.5.2 and 6.5.3.

| Release | Build date | Bytes | SHA-256 |
|---|---|--:|---|
| 6.5.4 (m) | 13 Apr 1999 | 99,156 | `66f4ad21b39cb6c529a8dff06b58c4e303c00280c8fc8752e78b7977d2a8ebc2` |
| 6.5.4 (f) | 13 Apr 1999 | 99,156 | `47b0398f5f04bc7cf64b466f72adcb32abf236cb61b8d4b7e4c84deecf86e319` |
| 6.5.10 (m) | 11 Oct 2000 | 99,844 | `298fdfe9e90c9b8ac78ee726bbab4b21f52cfe68c15a4731979eb97e67c6ff04` |
| 6.5.11 (m) | 8 Jan 2001 | 93,844 | `eb702715e4eb232a000c8c13f1b9c239e97c8416f0fe1745d32cd9a5a8bc292c` |
| 6.5.14 (f) | 9 Oct 2001 | 93,828 | `21c3f5969c38c21ccfbf5d8fe91ac59a3d79560d204ac5f6998105b33f0b131e` |
| 6.5.22 (m) | 6 Oct 2003 | 93,828 | `07d04647c65bf1f43b63ba8c8b81324d25f56f9ee2d81d261a23646c777de81e` |
| 6.5.30 (m) | 20 Jul 2006 | 93,828 | `43b86a8e6d29b8b29796604e0f6fc626fdf17c6532e3e43df944531eb8096f2b` |

Members of the 6.5.4 (m) archive (the 6.5.30 members are in [../software/rad1/package.md](../software/rad1/package.md#files-read)):

| Member | Bytes | SHA-256 |
|---|--:|---|
| `rad1drv.o` | 57844 | `0db1ae61eb6d5859769d953c74ce2d7027d576afdb378a977bcb1886e9b5fc75` |
| `rad1_init.o` | 12164 | `f281855e4562f2764d56f54ab44cb94e980bf3eefc0cc7c80063a02c0774d0a7` |
| `rad1_tpinit.o` | 10388 | `7bf7759d2f7daf7aec373e0ca19ef29ac1d58e4b7b01b7fc70ba72bb20495b5f` |
| `rad1_tport.o` | 12884 | `1b3ddd285841cc0329a8c9d32b7a9f2a2bac42ae7585f4ea7635bb20fd876cb0` |
| `rad1data.o` | 4724 | `9b700a65af858cff804b76f6cd4583262c8f55cdbefea076346b5b0dd75a738f` |

Copies of the archive also exist for every release not listed above, namely 6.5.5 (11 Jul 1999), 6.5.6 (1 Oct 1999), 6.5.7 (20 Jan 2000), 6.5.8 (11 Apr 2000), 6.5.9 (11 Jul 2000), 6.5.12 (6 Apr 2001), 6.5.13 (5 to 6 Jul 2001), 6.5.15 (8 Jan 2002), 6.5.16 (4 Apr 2002), 6.5.17 (28 Jun 2002), 6.5.18 (10 Oct 2002), 6.5.19 (10 Jan 2003), 6.5.20 (9 Apr 2003), 6.5.21 (7 Jul 2003), 6.5.23 (7 Jan 2004), 6.5.24 (7 Apr 2004), 6.5.25 (7 Jul 2004), 6.5.26 (6 Oct 2004), 6.5.27 (6 Jan 2005), 6.5.28 (1 Jul 2005) and 6.5.29 (9 Jan 2006); only the rows above were read.

## Origin 300 (IP35) PROM image read for the PCI name routines

| File | Bytes | SHA-256 |
|---|--:|---|
| CPU PROM payload, IRIX 6.5.30 installation tools (release 6.210) | 1,476,264 | `554924380189a03a512156af2faa38344902f251b49fd5c80c253c23ecaff27b` |
| packaged `ip35prom.img` | 1,480,360 | `d74b4b7ef9c11c66692019db9af698104595be7a0573a86feae8a83441921318` |
| `io7prom.bin` (carries the same name strings; not re-read) | 1,468,990 | `f903b3ce33b86c286f168ba43395f36a0073c24b1d4e703adce240f683b8c2d7` |
