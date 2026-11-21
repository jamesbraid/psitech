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
