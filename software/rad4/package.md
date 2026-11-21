# PsiTech RAD4 release 1.3k package for IRIX 6.5

What the vendor package contains and how its parts fit together. The register-level and request-level findings are in [devices/rad4/xserver-decode.md](../../devices/rad4/xserver-decode.md); this page is the map. Ratings are as defined in [devices/rad4/README.md](../../devices/rad4/README.md).

| Part | Role | Rating |
|---|---|---|
| Kernel driver object | ELF64 big-endian MIPS IV object for the Origin 200 and Octane-class kernels. Attaches to `12d1:0104` and `12d1:0105`, maps BAR0, BAR2 and the expansion ROM, reads the mode record from the EEPROM, programs the mode and RAMDAC, and serves the request interface | established (read from the binary) |
| Standalone X server | ELF32 big-endian MIPS II. Opens `/dev/rad4` or `/dev/rad4.N`, maps the framebuffer, runs the 32-bit framebuffer code with its own window-copy callback and cursor requests | established |
| Buffered X server | variant selected with the `rad4X_buffered_server` chkconfig flag; renders into a host-memory shadow and moves it with DMA through `/dev/rad4_b` | inferred; not audited beyond its DMA use |
| `rad4setres` | command-line mode tool: sets the mode word through the mode-change request | established |
| `rad4d` | refresh daemon | inferred; only its absence of board-control polling was checked |
| ROM programming image | initialiser that sets up the board and writes a nonzero mailbox marker; not a board dump | inferred; stays out of the repository |

Device nodes (owner's guide, established): `/dev/rad4` for the board, `/dev/rad4_kbd` and `/dev/rad4_pntr` for the RAD4-KM keyboard and mouse, apart from the system's own input devices.

Open questions about the package are in [questions/open-questions.md](../../questions/open-questions.md).
