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

Public documents are listed in [documents/INDEX.md](documents/INDEX.md).
