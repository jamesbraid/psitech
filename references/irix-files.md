# Files needed for the PsiTech RAD4 reverse engineering

This lists the proprietary files a reader copies from their own copy of PsiTech's RAD4 release 1.3k for IRIX 6.5 into a local `root/` directory. They are not tracked in source control. Paths and roles only: this repository holds no file contents.

`root/` mirrors the layout of the installed system. [binaries.md](binaries.md) gives the hash of each file so a copy can be checked.

```files
rad4x_65_13k.tar.gz
/usr/bin/rad4setres
/var/rad4/Xradsgi
/var/rad4/rad4d
```

The kernel driver object and the standalone X server are inside the release archive, stored compressed; decode them in memory and keep the results under `root/`. The ROM programming image in the same archive is not needed for the register work and must not be committed.
