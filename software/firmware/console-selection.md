# How `console=g` reaches a PsiTech board

The `console` variable, the environment variables the PROMs set from it and the kernel hooks that take over after boot. Covers the PsiTech IP27 PROM, SGI's IO6 PROM and the IRIX 6.5.30 IP27 kernel with the PsiTech kernel patch. Ratings as in [which-firmware.md](which-firmware.md). Only console-specific material is here; the drivers are in [../rad4/package.md](../rad4/package.md) and [../rad1/kernel-driver.md](../rad1/kernel-driver.md).

## PsiTech IP27 PROM (5.30)

The selection routine (read in full):

1. Read `console`. Unset, or a first character other than `g` or `G`: leave the serial console alone and return.
2. A capital `G` sets `sgilogo` to `n` (no logo) and resets `console` to `g`.
3. The character after the `g` is a graphics pipe number. A digit above 7 resets `console` to `g0`; a pipe that the node's configuration data cannot supply also resets it to `g0`. This is SGI's own pipe-selection code and applies to the InfiniteReality pipes of an Origin 2000, not to a PCI board.
4. If `gConsoleOut` is set, use it (with `/gfxpipe/0` appended) as `ConsoleOut` and mark the first pipe's configuration entry; this is the standard path for a pipe on a Hub board.
5. Otherwise, with `console` starting `g` (lowercase), walk the PCI functions of the node's Bridge and read the first configuration word of each. If it equals `0x010412d1`, `0x010512d1`, `0x010012d1`, `0x010112d1` or `0x00093d3d` (RAD4, RAD4-KM, `12d1:0100`, RAD1, a raw Permedia 2V), set `psitech` and `nodbgmon` to `1` and return.
6. If any slot in the PROM's console probe table is filled, check `ConsoleIn` and `ConsoleOut`: one that names a device that cannot be found prints a warning and reverts to the default.

Then the PROM installs its device drivers, which runs the PsiTech install routine for the matching function ([psitech-ip27-prom.md](psitech-ip27-prom.md)). That routine sets `gfx=alive` and the `psitech` entry address; from then on the PROM's character output goes to the board ROM's code. The PROM's input stays on the IOC3 keyboard port or serial: no code path asks the ROM for a key.

If the board's ROM does not start with `0xaa55`, `psitech` stays at `1` and the install routine falls back to a non-graphics `ConsoleIn`; the PROM continues on its previous output (inferred from the fall-back path, not exercised).

## SGI's IO6 PROM (RAD1)

For the RAD1 the same `console` variable decides: a value starting with `d` (or `D`) is serial; any other value lets the install routine run, which prints "Installing RAD1 Graphics Console...", sets the console output path to the board's node under `/hw/module/%M/slot/MotherBoard/node/xtalk/%d/pci/%d` and on success sets `gfx=alive`; on failure it sets `console` to `d` and reverts to serial ([../rad1/textport.md](../rad1/textport.md#prom-finding-the-card), [sgi-prom-rad1.md](sgi-prom-rad1.md)). The path names the motherboard slot, so a RAD1 behind a PCI shoebox or on an I/O module that is not the base I/O gets no PROM console (inferred from the path format, read in the install routine).

## Hand-over to the kernel

Both PROMs leave `gfx=alive` (established for the PsiTech PROM and the IO6 PROM). The stock IRIX 6.5.30 IP27 kernel and the PsiTech patch to it (`tport.a` in the package, whose symbols match the stock 6.5.30 object, see below) use it this way (read in full):

- The kernel's textport start-up requires `console` to start with `g` or `G` (defaulting to `g` when unset) and the `gfx` variable to start with `a`. Anything else leaves no textport.
- It then calls the init entry of each head in the kernel's textport table until one reports success, passing whether `console` was a capital `G`, the `monitor` argument (a built-in default when unset) and the sync-on-green argument (default yes).
- Before that, `gfx_earlyinit` registers the board-specific early consoles: if the object `rad1_earlyinit` is linked in it calls that and not `rad4_earlyinit`; otherwise, if `rad4_earlyinit` is linked in, it calls that; then the MGRAS and KONA hooks. Both PsiTech hooks are weak references, so a kernel without the driver object skips them.

`rad4_earlyinit`, defined in PsiTech's `rad4pci.o` (read in full): once only, allocate 8 MiB of zeroed kernel memory (`kmem_zalloc`, flags `0x8800`) and register a hardware textport board of 1280 by 1024 pixels (`htp_register_board` with width `0x500` and height `0x400`). Until the driver attaches the board, the textport draws into that memory, so early kernel messages are held until attach and then the board shows them (inferred from the RAD1 case in [../rad1/textport.md](../rad1/textport.md#kernel-early-console-and-handover); the RAD4 hand-over routine was not read).

The same object exports the textport board hooks the kernel calls, `RAD4BoardTPInit` (store a board pointer at index 0 to 3), `RAD4InitBoard` (mark it ready), `RAD4Reset` (clear the mark), `RAD4InitCursor` (does nothing) and `RAD4_baseindex` (find a pointer among four slots); all read in full and tiny. They mirror the RAD1 object's hooks of the same shape.

## The patch against stock

| Object | PsiTech package | Stock 6.5-base (June 1998) | Stock 6.5.30 |
|---|---|---|---|
| IP27 `tport.o` | built with weak references to `rad1_earlyinit` and `rad4_earlyinit` | no such references | the same two weak references |
| IP27 `ioc3_pckm.o` | PsiTech's build, which carries a `console_km` flag | not compared | not compared |

So the package's `tport.a` adds the hooks that IRIX 6.5.30 later carries in stock form (established, symbol tables of the three objects compared; the symbol lists match 6.5.30's and differ from 6.5-base's by exactly those two). The O2 and Octane boot directories of 6.5.30 and 6.5-base have no such references (established, scan).

## Items not examined

- The `ioc3_pckm.o` patch: what `console_km` changes for the RAD4-KM keyboard was not read.
- The driver's own text screen (`rad4_tty_init`, `tty_screen_init`): it uses the same 8 by 15 cell geometry as the ROM, 80 by 34 at most, centred (read in the initialiser), and serves a tty on the board; how it relates to the kernel textport was not traced.
