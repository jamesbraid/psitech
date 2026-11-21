# RAD4 in firmware images and kernel objects

Which firmware images and IRIX kernel objects know the PsiTech RAD4 (`12d1:0104`) and RAD4-KM (`12d1:0105`), how PsiTech's own PROM and kernel objects find and start the board, and what they change against the stock IRIX 6.5 files. Ratings are as defined in [devices/rad4/README.md](../../devices/rad4/README.md). Package overview: [package.md](package.md). Driver internals: [kernel-driver.md](kernel-driver.md).

Method. Every image was searched for the vendor halfword `0x12d1` as an instruction immediate, for `0x3d3d` (3Dlabs, the RAD1's Permedia 2), and for the strings "psitech", "rad", "pciid" and "UNKNOWN". Hits were then read as functions in a decompiler and checked against disassembly at the branch points quoted. Addresses below are offsets into the PROM payload (the file minus its 4096-byte header); the code runs at `0xffffffffbfc00000` plus the offset and reads its own data at `0xc00000001fc00000` plus the offset.

## Files and hashes

| File | Size | SHA-256 (prefix) |
|---|---|---|
| `var/rad4/ip27prom.img` | 885,184 | `627e53673dc8` |
| its payload (bytes from 0x1000) | 881,088 | `4b0b0c90ab26` |
| `var/rad4/rad4_rom` | 98,296 | `d9420b62f741` |
| `var/rad4/36500202` | 494 | `9caa82c0b753` |
| `var/rad4/rad4_prog` | 13,808 | `f56da07bb4a6` |
| `var/sysgen/boot/ioc3_pckm.o` | 33,240 | `da83ab5b334d` |
| `var/sysgen/boot/tport.a` (one member, `tport.o`, 26,996 bytes) | 27,284 | `be6521e4b075` (member `207a2cbdcc26`) |
| stock IRIX 6.5 base media, `IP27boot/ioc3_pckm.o` | 33,040 | `5c7b97a37968` |
| stock IRIX 6.5 base media, `IP27boot/tport.a` member `tport.o` | 24,260 | `9b743cb7ecfd` |
| stock IRIX 6.5.30 `IP27boot/tport.a` member `tport.o` | 23,620 | `12e8b895c97f` |
| stock IRIX 6.5.22 `IP27boot/tport.a` member `tport.o` | | `10a7d1c2415a` |
| stock IRIX 6.5.22 `IP27boot/ioc3_pckm.o` / 6.5.30 | 35,840 | `b406416cf889` / `159a1304d5d8` |
| stock PROM payloads, Origin 200/2000: 6.5 base (version 6.11) / 6.5.30 (6.156) | 892,416 / 908,752 | `14e0d0a77b92` / `c2c69bf33c37` |

## 1. Which firmware images know the RAD4

| Image (version, hash prefix) | RAD4/PsiTech awareness | Evidence | Rating |
|---|---|---|---|
| **PsiTech `ip27prom.img`** (IP27 PROM "5.30 PSITECH", `627e53673dc8`) | **Yes.** PCI IDs `0x010412d1` and `0x010512d1` are recognised in the slot scan, the board's expansion ROM is mapped, validated, copied into node memory and relocated | section 2 | established |
| IP27 PROM 6.5 base (6.11, `14e0d0a77b92`) | None | no `0x12d1` or `0x3d3d` immediate in code; no "psitech" string; its slot-configuration function (payload 0x4c3dc, read in full) handles only QLogic `0x10201077` and SGI `0x000310a9` | established |
| IP27 PROM 6.5.30 (6.156, `c2c69bf33c37`) and an Origin 2000 flash dump of the same version | RAD1 only. Name table holds "PSITECH" (payload 0x72be8); slot function at 0x3eebc handles ID `0x00093d3d` (3Dlabs Permedia 2, the RAD1's chip) | decompile of 0x3eebc and 0x406bc; no `0x12d1` immediate | established that RAD4 IDs are absent; RAD1 identification is inferred from the ID and the RAD1 strings in the Base-IO PROM below |
| Base-IO PROM (`io6prom`) 6.5.30, `bf341a718215` | RAD1 only. A function at file offset 0x16434 checks PCI subsystem vendor `0x12d1` with subsystem ID `0x0101` (either halfword order); strings "Psitech-RAD1", "Installing RAD1 Graphics Console...", "rad1 resolution unknown mode" | disassembly of the check; strings | established (check read to its return); the rest of the RAD1 console code was not read |
| Base-IO PROM 6.5 base, `da2ed5de42f2` | None. Has the generic graphics-install framework ("kl_graphics_install", "gfxpipe") but no PsiTech string or `0x12d1` | scan | established |
| Origin 300/3000 PROM (IP35) 6.210, `554924380189`, and the patch-7208 image `25f60c7f0bae`; the larger 16 MiB IP34 image | RAD1 name strings "PSITECH_RAD1", "PSITECH" (6.5.30 image at 0x84b80, 0x881f0). No `0x12d1`/`0x0104`/`0x0105` compare. 0x3d3d appears as an immediate (0x42704, 0x42758), so a RAD1/Permedia check is likely | string and immediate scan only | name strings established; absence of RAD4 established for compares; Permedia handling not read, **Unverified.** |
| Octane PROM (IP30) 6.5 base `73bf108723ea`, 6.5.30 `ee4722ca6f9b` | None found | no "psitech" or "rad" string; the only `0x12d1` hit (6.5 base, 0x1e5cc) is a branch word, not an immediate load | inferred (string and immediate scan, code not read) |
| O2 PROM (IP32) 6.5 base `820585bed598`, 6.5.30 `11230c353cb1`, the 512 KiB seed image `8c1898c1a228` | None found. Strings include `pci_register: registering vendor 0x%x device 0x%x`, so the PCI layer is present as plain text, but no `0x12d1` immediate and no table word with `d1 12` | scan | inferred; the image may carry compressed segments the scan cannot see, **Unverified.** |
| Other images scanned: `io4prom`, `io7prom` (6.5.30), IP22, IP24, IP28 PROMs | None for RAD4. The IO7 image carries only the "PSITECH_RAD1"/"PSITECH" name strings | scan | inferred |

The Owner's Guide (software revision 1.3, 15 November 1997) says the boot message on an Origin 200/2000 reads "PCI slot x pei 010412d1 UNKNOWN" (slot 5, 6 or 7 on the Origin 200), which is the stock PROM printing the combined ID `0x010412d1` with the name UNKNOWN (the guide's text layer reads "pei" for the PROM's "pciid" in the "PCI slot %d pciid %08x %8s" format string). This matches the absence of RAD4 in the stock PROM tables above (established as a published statement).

## 2. PsiTech's `ip27prom.img`

### Format and version

- Container: the same SN0 flash container as the stock images. A 4096-byte header, then a flat big-endian MIPS64 payload mapped at physical `0x1fc00000` (reset vector at payload 0, a table of jump-and-nop pairs). Header bytes `0x38..0x7f`: a 64-bit field, the 8-byte magic `JFKSWCSM`, a 64-bit field, then the image length `0xd81c0` (equal to the file size). The two fields hold `0x1e` / `5` here, `0x0b` / `6` in the 6.5 base image (version 6.11) and `0x9c` / `6` in the 6.5.30 image (version 6.156), so they read as minor and major version. Established for the header layout; the field meaning is inferred from the three images.
- Version string at payload 0xcad50: "SGI Version 5.30 PSITECH built 01:18:52 PM Oct 21, 1998" (established). The stock 6.5 images are 6.11 (April 1998) and 6.156 (November 2003). PsiTech's image is therefore a **5.x-line PROM rebuilt with a PsiTech tag**, older in code lineage than the stock 6.5-base PROM, not a patch of it. A byte-level diff against the stock payloads is meaningless (different builds, addresses move); the comparison below is by function.
- The stock 5.30 PROM it was derived from is not among the files examined, so changed regions are identified by what PsiTech's code has that both stock 6.x images lack. Any further PsiTech edit that is not visible as an ID or string difference is **Unverified.**

### What differs from the stock PROMs

Three PsiTech-only items, all in the PCI scan of the Base-IO board; the strings "Initializing PsiTech card", "signature bytes were 0x%x" and "done." exist in no stock image (payload 0xd17b0, 0xd17d8, 0xd17f8).

1. **Scan loop** (payload 0x4c4e0, read in full). For each of the eight slots of a Bridge it reads the config ID (`device << 16 | vendor`) and switches on it. PsiTech's cases are `0x010012d1`, `0x010112d1`, `0x010412d1`, `0x010512d1` (vendor `12d1`, devices `0100`, `0101`, `0104`, `0105`) and `0x00093d3d` (3Dlabs Permedia 2). Established that these five reach one handler; device `0100`/`0101` and the Permedia 2 ID are most likely the RAD1 (inferred; no RAD1 hardware fact is read here). The handler (label at 0x4c6ac) prints the slot line with the name "PSITECH" when verbose, then, only if the word at payload 0xb95a4 is still nonzero (initial value `1`, established from the image bytes), calls the board setup below; if that leaves the word zero, it registers the slot through the common device-registration helper (0x35c70) with type code 7. Because success zeroes the word, **only the first PsiTech board per boot is set up**; later PsiTech slots are skipped without registration (established from the control flow). Other cases: QLogic `0x10201077` calls the slot function and a SCSI helper; the Adaptec Fibre Channel ID `0x11609004` and others are named; the SGI IOC3 ID `0x000310a9` takes the stock path.
2. **Slot configuration function** (payload 0x4603c, read in full; the stock counterpart is payload 0x4c3dc in 6.5 base, read in full). The stock function sets command bits 1 and 2 (memory space, bus master), programs the bridge device-window register, writes BAR0 (and for the QLogic part BAR1), and for IOC3 starts two diagnostics. PsiTech adds one branch for the five IDs above. In order:
   - print "Initializing PsiTech card" and then "." (progress dots);
   - write the local hub's IO translation table entry 0 (hub register offset `0x400160`, the first entry in the public SN0 header's `IIO_ITTE_BASE` block) with value `widget << 8 | 2`, where *widget* is the Bridge's Crosstalk widget number (bits 24..27 of its address) and the node number comes from a helper at 0x5794c. This opens a big window onto the Bridge's PCI space at physical `0x20000000` of the node. Established for the write; the "big window" reading is inferred from the public Linux SN0 headers;
   - write BAR2 (config offset `0x18`) all ones, read it back to size it; assign BAR0 (`0x10`) the slot base address `((widget << 4) + (slot < 3 ? 2*slot + 2 : slot + 4)) << 20` (established from helper 0x46014); set BAR2 to the BAR0 value masked to BAR2's size plus one BAR2 size, so BAR2 sits in the block after the one that holds BAR0. BAR2 (the 8 MiB framebuffer, by the existing register notes) is therefore placed by the PROM, not by the stock assignment;
   - write the expansion ROM BAR (`0x30`) all ones, read it back, round the end of BAR2 up to 16 MiB, enable the ROM at that address;
   - read the first word of the mapped ROM through the big window; it must equal `0xaa55` (the PCI ROM signature as a little-endian word, so the window returns words byte-swapped). If not, print "signature bytes were 0x%x", set the failure word to 1, clear BAR0, BAR2 and ROM BAR, and give up;
   - walk the PCI expansion ROM images: image N matches when the ID dword at image offset `0x20` (`vendor | device << 16` of its PCIR block) equals the slot's config ID; a non-matching image is skipped by its length (halfword at offset `0x2e` of the swapped view, 512-byte units); a non-matching image whose last-image bit is set aborts. The matching image must have code type byte `0x7f` (the PCIR code-type field of `rad4_rom`, a value the PCI firmware specification does not define; PsiTech's private marker);
   - copy the image into node memory at physical `0x01800100` (offset 24 MiB + 256, inside the 24..26 MiB "Graphics PROM" region of the public Linux SN0 memory map), reordering bytes within each 32-bit word. The image bytes land verbatim at `0x01800104`;
   - relocate seven 64-bit slots at image offsets `0x3c..0x73` by adding `0x01800100 - 0xb0`. A slot's value minus `0xb4` is the function's image offset (for example slot value `0x19e0` is the RAMDAC initialiser at `0x192c`); the sum with the load address `0x01800104` equals the relocated value. The table ends at `0x01800178`, which is image offset `0x74`, the ROM's entry dispatcher;
   - clear the failure word and print "done.".
   The copy, relocation, ROM BAR placement and the Bridge window are established from the decompile and disassembly; the identification of the slot table as a PIC global offset table (entry in `t9`, `gp` = entry + `0x7fb0`) is inferred from how the ROM's code reaches its table.
3. **Name table** (payload 0xd3258): the string "PSITECH" sits beside "UNIVME", "SGI_LINC", "UNKNOWN". Present in 6.5.30 too, absent in 6.5 base (established).

The boot stage does not call the ROM. The call is made by the ELF stage's install routine, which reads BAR0, BAR2 and the expansion ROM base, checks the first word is `0xaa55` and calls node memory `0x01800178` (the load address plus entry offset `0x74`) with arguments (0, ROM, BAR2, BAR0); console character output then calls command 1 (established in [../firmware/psitech-ip27-prom.md](../firmware/psitech-ip27-prom.md), read in full there; the copy loop above agrees: `0x01800104 + 0x74 = 0x01800178`). Consistent with the existing note that the ROM writes a nonzero marker to a mailbox (section 3), but the PROM itself does not read it.

### Registers and ordering the PROM touches on the card

In order: config command (`0x04`) |= 6; BAR0 `0x10`; BAR2 `0x18` (all ones, readback, final value); ROM BAR `0x30` (all ones, readback, final value, enable bit set); then ROM reads through the window. It writes nothing else to the card; the RAMDAC, timing and framebuffer registers are touched only by the ROM code. The PROM does not draw anything itself.

## 3. `rad4_rom`, `36500202` and `rad4_prog`

### `rad4_rom`: S-record text holding a two-image PCI expansion ROM

- Format: Motorola S-records in CRLF text, one `S1` (16-bit address) record per 32 bytes, a final `S9`; 1296 `S1` records and one `S9`, all checksums valid (parsed). Data spans `0x0000..0xa203` (41,476 bytes) with four short holes (`0x4543`, `0x4598..0x45ff`, `0x896a..0x896b`, `0xa193`). The loader zero-fills unspecified bytes (see below), so the holes read as zero.
- Contents: **two back-to-back PCI ROM images**, parsed from their `0x55aa` headers and PCIR blocks. Image 1 at `0x0000`: vendor `12d1`, device `0104`, class `038000`, length 35 units (17,920 bytes), code type `0x7f`, last-image bit clear. Image 2 at `0x4600`: device `0105`, length 47 units (24,064 bytes), last-image bit set. The PROM above picks the image whose PCIR ID equals the board's own, so one ROM file serves both RAD4 and RAD4-KM (established).
- Target: big-endian **MIPS64** code (`daddiu`/`sd`/`ld`, 64-bit stack frames), position independent through a seven-entry table placed in the header at image offset `0x3c`, entry at image offset `0x74`. This is the host CPU's instruction set, not an on-card processor; the PROM runs it on the node's R10000 (established: instruction decoding plus the PROM's relocation of the table). The table values are `0, 0x10000, 0x19e0, 0x2110, 0x2308, 0x24a4, 0x2d00` for image 1 (established); their role (rebased base pointers for a global-pointer-relative program) is inferred.
- Entry function (image 1, offsets `0x74..0x1c0`, read in full): `entry(command, arg1, arg2)`. Command 0 calls an initialiser with `arg1` = the framebuffer window pointer and `arg2` = the register window pointer; commands 1 and 2 also run. Every call brackets its work by writing `0xf84303c3` to register-window offset `0x18` on entry and `0xf84003c0` on exit (established from the stores). Offset `0x18` is the local-bus region descriptor in the PLX 9060 register map, so this probably switches local bus timing around the operation (inferred from the register map, not from this ROM).
- Command 0 initialiser (offset `0x1c4`, read to about `0x590`, rest skimmed): stores the two window pointers; derives sub-block pointers from the framebuffer window pointer (`+0x000000`, `+0x100000`, `+0x110000`, `+0x120000`, `+0x130000`, `+0x200000..0x203000` in 4 KiB steps, `+0x300000`, `+0x400000`, `+0x500000`, `+0x600000`, `+0x700000`) and the 8 MiB end (`+0x800000`); what each block is was not identified; sets bit 25 of the register at offset `0x6c` (the PLX CNTRL register, where the serial EPROM clock and data bits live in the 9060 map), clocks out an opcode byte `0xac` and reads **40 bytes** back bit by bit, matching the kernel driver's `seprom_read(..., 0x58, 0x28, ...)` of the mode record; then runs mode, palette and console setup (not read, **Unverified.**). It ends by printing text and writing the constant `0x424f4f21` (ASCII "BOO!") to register offset `0x40` (the first PLX mailbox in the 9060 map): the nonzero marker the existing notes describe (established as a store at offset `0x938`; the ASCII reading is mine).
- Console routines (established for the dispatch, inferred for the drawing): command 1 prints a NUL-terminated string through a character routine at `0x9e0` that handles CR, LF, form feed, backspace, tab (eight spaces) and printable ASCII 32..127; each character first erases and then redraws a cursor (helper `0x15a0`). Glyphs come from a table indexed `char << 4` (16 rows per glyph, tested with `< 15`) and are stored as 32-bit pixels (index shifted left by 2), so the console is a bitmap font on a 32-bit-per-pixel linear framebuffer. The firmware pages read it in full: the font is 8x15 (glyph stride 15, 128 glyphs at image offset `0x3104`), cells 80x34, centred, white on black, drawn as 32-bit CPU pixel writes ([../firmware/rad4-option-rom.md](../firmware/rad4-option-rom.md)); an earlier 16-row reading here was wrong. Command 2 is a stub that returns `-1`.

### `36500202`: the serial EPROM image

Data I/O-style S-records (header record text "DATA I/O", `S1` records of 16 bytes with LF-CR line ends and NUL padding), 128 bytes at `0x00..0x7f`, `S9` trailer (established). Content: `05 01 d1 12 80 03 02 00 00 00 00 01 ...`, which reads as device `0x0105`, vendor `0x12d1`, then class and revision words, in the PLX 9060 serial-EEPROM word order; the rest are PLX local-space values with bytes `0x30..0x7f` all zero. So this image is for the **RAD4-KM** configuration (the device word is `0105`), and its last 40 bytes (`0x58..0x7f`, the mode-record window the driver reads) are blank (established for the bytes; the PLX field decoding is inferred from the PLX 9060 data sheet and is not walked field by field here). No `0104` serial EPROM image ships.

Decoded against the long EEPROM load table of the PLX PCI 9060 data sheet, version 1.2 (section 3.3.2, pages 11 and 12; registers in tables 27 to 29, pages 42 and 43), reading the file as little-endian halfwords in the table's order (established for the image, inferred for a card that carries it):

| Table field | Value in the image | Meaning |
|---|---|---|
| device and vendor ID | `0x0105`, `0x12d1` | the RAD4-KM |
| class code and revision | `0x0380`, `0x0002` | class `0x038000`, revision 2 |
| interrupt pin and line routing | `0x0100` | |
| mailboxes 0 and 1 | all zero | |
| PCI to local space 0, range | `0xff00` and `0x0000` | a 16 MiB window |
| PCI to local space 0, local base (re-map) | `0x0000` and `0x0001` | local address 0, space enabled |
| PCI to local expansion ROM, range | `0xff80` and `0x0000` | an 8 MiB window |
| PCI to local expansion ROM, local base (re-map) | `0x0080` and `0x0000` | local address `0x800000` |
| bus region descriptors | `0xf940` and `0x02c0` | `0xf94002c0`: 8-bit space 0 and 8-bit expansion ROM space, ready inputs on, prefetch off for the ROM space, bursts on for space 0 |

Everything from table offset 0x30 on is zero. This settles several rows that were unknown. The local base of the expansion ROM re-map, `0x800000`, is the local address of the 64 KiB flash (the flash sits at BAR2 plus 0x800000 and space 0 is re-mapped to local 0), so the expansion ROM base register decodes the flash, which is where the package's programming tool writes the ROM image (inferred from the two register values and the driver's flash window; the part number stays unknown). The driver then re-points the same re-map register at a different local address (`0xe1000000`) at attach, in the way the sheet's note on reaching the DMA registers through the expansion ROM space describes (Method II, page 32), so once the driver has attached the ROM window no longer shows the flash: the firmware reads the image before the driver loads, which agrees with the PROM-first order of the package. The two window sizes are the sizes the image asks the part to claim, a 16 MiB BAR2 and an 8 MiB expansion ROM, which fits a driver that maps 8 MiB of framebuffer and registers up to 0xf00000 and asks for an 8 MiB ROM window. The mailbox the image loads is zero. A card whose serial EEPROM carries a different image, or none, would differ.

### `rad4_prog`: the programming tool

ELF32 big-endian MIPS, dynamically linked, `main` at `0x10000dc8` (read in full). Usage text: `rad4_prog [-d<device>] -f<S-record file> [-seprom] [-v]`; default device `/dev/rad4`.

- Opens the device, issues `ioctl(fd, 0x806, 0)` once (purpose **unknown**), parses the S-record file line by line (address widths of two, three and four bytes, that is `S1` to `S3`; checksum is the complemented byte sum; "Error in S record input" and "Checksum error" otherwise), zero-fills a 64 KiB buffer first. Addresses are rejected above `0x10000` for the EEPROM ("Address too large for EEPROM") and above `0x80` for the serial EPROM.
- **Flash (EEPROM) path** (default): writes the whole 64 KiB buffer in 128-byte sectors with `ioctl 129` (argument: sector offset and buffer pointer), then verifies by reading each sector back with `ioctl 130` and comparing byte by byte ("Verifying EEPROM...", "EEPROM read error @ 0x%x, was 0x%x, expected 0x%x"). Established; this matches the sector requests 129/130 the user noted in the driver header.
- **Serial EPROM path** (`-seprom`): `ioctl 131` writes 128 bytes (offset 0, length 128), `ioctl 132` reads them back for the same comparison. The driver contains `seprom_write`/`seprom_read` for these; which ioctl case calls them was not traced (**Unverified.**).
- `-v` skips the write and only verifies.

So `rad4_rom` is the flash image for the option ROM, and `36500202` the PLX serial EPROM image; both are programmed through the running kernel driver, not from the PROM.

## 4. `ioc3_pckm.o` and `tport.a` against stock IRIX 6.5

### `tport.a` (textport)

The archive holds one member, `tport.o`, built from the same source as stock 6.5 with the compiler's no-optimisation setting (MIPSpro 7.2.1, 64-bit MIPS IV, `-O0`), against the stock objects built at `-O3`. This is why every function is larger. Against the 6.5 base member (`9b743cb7ecfd`):

- Same 22 function names and same data: the `.data` bytes (`tp_tab` 112 bytes, `tpinfo`, tunables) are byte-identical (checked by hash) with the same relocation targets.
- The only symbol-level difference is two new **weak** undefined references, `rad1_earlyinit` and `rad4_earlyinit`.
- The only function whose logic differs, of those read, is `gfx_earlyinit` (read in full in all three versions). Stock 6.5 base (36 bytes): call `mgras_earlyinit`, then `kona_earlyinit`. PsiTech (88 bytes): if `rad1_earlyinit` is linked call it, else if `rad4_earlyinit` is linked call it; then call `mgras_earlyinit` and `kona_earlyinit`; no return values are tested. Stock 6.5.22 and 6.5.30 (108 bytes) contain the same weak references with a different order and a return-value chain: `mgras`, then `kona` (a nonzero return from either ends the chain), then `rad1` if linked (a nonzero return ends it), then `rad4` if linked.
- The other 21 functions were not instruction-compared; the matching sizes pattern (every function scaled by the optimisation level) and identical data make a behavioural change unlikely, which is only **inferred**. `tp_init`, read in full in PsiTech's build and in the 6.5.30 build, has the same structure: gated on two boot variables (the relocations name them `arg_console`, which must start with `g` or `G` when specified, and `arg_gfx`, which must start with `a`); it then loops over `tp_tab` calling each entry's init until one returns nonzero (established).

The stock tport objects for the **Octane (IP30), O2 (IP32) and Origin 300 (IP35)** have no `rad1`/`rad4` reference at all (established by symbol list). The weak hooks exist only in the IP27 build. PsiTech ships no tport archive for IP32, so the IP32 driver's `rad4_earlyinit` has no caller in the shipped files (inferred).

### `ioc3_pckm.o` (keyboard and mouse driver)

Same 35 symbols as the stock 6.5 base object, same exports (`pckm_setleds`, `pckm_bell`, `pckm_kbdexists`, `du_keyboard_port`, `early_pckminit`, `gl_setporthandler`). Only one function differs in size: `pckm_wput`, 488 bytes stock, 540 bytes PsiTech (all others are identical in size; the compiler build differs slightly: 7.2.1 build `1274714010` against `1274555410`). Read in full side by side: for a data message written to the keyboard port, the PsiTech version looks at each byte before the stock handling. Byte `0xfc` skips one following byte. Byte `0xfa` issues six keyboard commands through `pckm_pollcmd`: `0xfa`, `0xfc 0x14`, `0xfc 0x76`, `0xf4`. In PS/2 scancode set 3 those are "all keys make/break/typematic", "set key type make/break" for Caps Lock (`0x14`) and Num Lock (`0x76`), and "enable" (the PS/2 meanings are from public keyboard documentation, so the intent is inferred). The effect is a pass-through control path the RAD4 driver's `write_keyboard` can use to put the lock keys into make/break mode. Whether the RAD4 driver sends `0xfa` here is not traced (**Unverified.**).

The stock 6.5.22 and 6.5.30 `ioc3_pckm.o` are a later design: the globals above are static `ioc3_`-prefixed functions registered through `pckm_console_register`, and `pckm_setleds` and friends are not exported from that object. The RAD4 driver imports `pckm_setleds` and `gl_setporthandler`, so PsiTech's older object (and the 6.5 base kernel's exported names, `nm` of the base kernel shows all four) is the one it links against. Against a 6.5.22 or newer relink with the stock object the import would not resolve (inferred from symbols; not tried).

### How the kernel textport selects the RAD4 as console

1. `gfx_earlyinit` (in the kernel's textport object) runs at boot, before any PCI attach, and calls `rad4_earlyinit` if the driver object is linked in (section above).
2. `rad4_earlyinit` (read in full, 104 bytes) runs once: allocates 8 MiB plus a small allowance of zeroed kernel memory, stores it in `rad4_earlyinit_base`, and calls `htp_register_board(&rad4_info_pointer, RAD4_htp_fncs, 1280, 1024)`; it returns 1 always.
3. `htp_register_board` is in the stock `htport.o` (6.5 base, 6.5.22 and 6.5.30; read for the first fifty instructions). It records one board's function table and info pointer, and the 1280x1024 size, in file-static state; the textport's `htp_init` then calls function 0 of that table. Every kernel image examined has `htp_register_board` and `htp_init`; only the 6.5.30 IP27 kernel carries a complete built-in RAD1 driver (`rad1pci`, `rad1_earlyinit`, `RAD1_htp_fncs`), and none carries RAD4 code.
4. `RAD4_htp_fncs` (nine function pointers at data offset `0x1790`, read): initialise (finds the board slot through `RAD4_baseindex`, runs `RAD4InitBoard`, which only sets a flag, then clears the screen), set a palette entry (`(r << 16) | (g << 8) | b` into a table), select the current colour, fill a rectangle, and so on. None of these touches a register. They draw 32-bit pixels into either the early buffer (before attach) or the board's mapped framebuffer after it, in a 1280x1024 frame.
5. At attach, the driver calls `RAD4BoardTPInit(info, index)` for the first board (stores the info pointer in `RAD4Boards[index]`, at most four boards), then, if the early buffer exists, copies it pixel by pixel into the board's framebuffer (info offset `0x38`) using the width and height in the info block, frees the 8 MiB, and from then on draws directly into the framebuffer. This is the whole early-textport path (established, read in `rad4pciattach` at `0x2020..0x2170`).
6. `tp_init` (above) selects the registered board only if the console boot variable begins with `g`/`G`. So the textport is selected as a normal graphics console by the same boot variable as any other head; there is no RAD4-specific selection variable (established). Its model of the board is just "a linear 32-bit framebuffer plus a mode set by the driver", with the PROM ROM (section 3) as an alternative, earlier console that the kernel does not use.

## 5. Releases and machines

- PsiTech's package: README states "release 1.3", "RAD4 drivers for IRIX 6.3 & 6.4", installation notes for O2 (merged server needs SGI patch 2009), Octane ("not officially supported, call PsiTech") and Origin 200/2000 ("SGI patch 2082 is recommended"). The Owner's Guide (software revision 1.3, 15 November 1997) agrees on 6.3 and 6.4, requires "IRIX 6.4 02121744 or newer with patch SGO001887 PCI Rollup patch" for the Origin 200/2000, gives the boot message quoted above, and appendix D names SGI patches 2009 (O2 and Octane merged server) and 2082 ("fixes six second launch delay", Origin 200/2000). Public document: *RAD4 Owner's Guide*, PsiTech, software revision 1.3 (archive copy, with the RAD4C-KM 10-99 product sheet). No IRIX release note or patch README in the public Library roots searched (techpubs, irix-mirrors, irix-artifacts, irix-extracts, by "RAD4", "PsiTech", "12d1") mentions the RAD4 or its PROM; the guide is the only hit family. The guide's text past appendix E was not read.
- The shipped **kernel objects are built for IRIX 6.5**, not 6.3/6.4 (established): the IP27 build line carries `-DIRIX65 -DIP27 -DR10000 ... -DSN0 -DMAPPED_KERNEL` with MIPSpro 7.2.1; build-directory strings name `rad4-sgi/6.5.IP27` and `rad4-sgi/6.5.IP32`; the version string is `1.101`; build dates are Feb 16 1999 (IP27) and Feb 18 1999 (IP32). The README text therefore predates the objects. The PROM image is dated October 1998 and carries PROM version 5.30; the driver is dated four months later.
- Driver registration (`rad4pciinit`, read in full): `pciio_driver_register` for vendor `0x12d1`, device `0x0104` and device `0x0105` (established). `master.d/rad4pci.IP27`: flags `cs` (character device, software-registered), prefix `rad4pci`, major `63`, `3` devices, no dependencies; tunables `rad4pci_use_userbuffer=1`, `rad4pci_max_dma_area=204800`, `rad4pci_no_dma=0`, `rad4pci_default_resolution=0x201`, `rad4pci_dma_read_cmd=0xc`, `rad4pci_enable_prefetch=1`, `rad4pci_latency_override=256`. `system/rad4pci.sm.IP27`: `USE: rad4pci`, `VECTOR: bustype=PCI module=rad4pci`. **No `.IP32` master or system file ships**; the O2 object relies on the IP27 ones or on the O2 installer's own, which is not in the package (**Unverified.**).

### IP27 and IP32 drivers

| | IP27 object | IP32 object |
|---|---|---|
| Container | ELF64, MIPS IV, `r10000`, 64-bit ABI (`-64`) | ELF32 n32, MIPS III, `r5000`, `-TARG:t5_ll_sc_bug=on` |
| `.text` size | `0x13a64` | `0x13aec` |
| Global/function symbols | 155 | 155 |
| Undefined symbols | same set | same set |

The two objects export **the identical set of 155 symbols and import the identical set**, including `rad4_earlyinit`, `RAD4BoardTPInit` and `RAD4_htp_fncs` in both (established by `nm`). So there is no function present in only one; the IP32 build differs in ABI and compiler options only, plus string table order. The textport hook symbols are present on IP32 but, as shown above, nothing in the stock IP32 kernel's textport calls them.

## Not covered / unknown

- **Caller of the relocated ROM.** Answered: the PROM's ELF-stage install routine, see item 2 and the firmware pages.
- **Whether a stock-PROM Origin boots with this ROM at all, and how a stock PROM treats the board.** The guide's UNKNOWN boot message says the PROM ignores it; whether PsiTech's PROM was ever required for the console role is not stated in any shipped file.
- **Differences from the stock 5.30 PROM.** The base PROM is not available, so every PsiTech edit that is not an ID or string addition is invisible. Settle by finding an IRIX 6.4-era `ip27prom` image (5.30) and diffing by function.
- **`ioctl 0x806`** in `rad4_prog` and the driver's handler for it. Settle by reading the driver's ioctl jump table against the command numbers 128..132, 2054.
- **Remaining ROM behaviour**: the mode routine, the two timing loaders and the paint helper are now read and agree with the driver ([../firmware/rad4-option-rom.md](../firmware/rad4-option-rom.md)); the meaning of table entry 1 (`0x10000`) is still open, and so is the scan-code helper behind the keyboard command.
- **`pckm_wput` marker bytes**: whether the RAD4 driver ever writes `0xfa`/`0xfc`. Settle by tracing `write_keyboard` and the keyboard queue code in the driver.
- **IP35, IP32 and IP30 images**: Permedia/RAD1 handling in IP35, and compressed segments in the IP32 PROM, were scanned, not read. Settle by decompiling the IP35 function near its `0x3d3d` immediates and by unpacking the IP32 sections before rescanning.
- **No `.IP32` master/system file; IRIX 6.3/6.4 objects.** No 6.3/6.4 object ships, so the README claim and the 6.5 build date cannot be reconciled from files; settle with an earlier PsiTech release package.
- **Retention of PSITECH names in IP35 and IO7**: the strings exist; which code uses them was not traced.
- **Material not opened under the hard rule**: no restricted IRIX source tree, vendor source or restricted-root Library hit was opened. The only Library results were the public owner's guide family and an unrelated Cray-user-group proceedings file, which was not opened.
