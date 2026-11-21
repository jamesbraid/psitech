# PsiTech Reverse Engineering Project

This project reverse-engineers PsiTech's graphics boards for SGI systems, starting with the **RAD4** (PCI `12d1:0104`) and its keyboard-and-mouse variant the **RAD4-KM** (`12d1:0105`), and the way PsiTech's release 1.3k for IRIX 6.5 drives them. The goal is to document the boards as register definitions and notes that emulator authors, FPGA builders and the vintage SGI community can work from. Layout and working style follow techomancer's [gr2](https://github.com/techomancer/gr2) and [gr4](https://github.com/techomancer/gr4). Where this file is silent, do what gr4 does.

## 1. Board overview

The RAD4 is a third-party PCI card. The software that drives it is one vendor package: a kernel driver, a standalone X server, the `rad4setres` mode tool and the `rad4d` refresh daemon. The board is built around a PLX PCI 9060-compatible bus interface and an IBM RGB561-compatible RAMDAC, with board-local framebuffer, timing and control logic whose chips are not identified. A later RAD4C-KM and an earlier RAD1 (a Permedia 2 board) exist; only the RAD4 is covered so far.

Facts are labelled with one of three ratings. **established**: read in full from a shipped binary (the whole function, table or code path), a published document, or a public driver, cited with the release, function, page or file. **inferred**: a reasoned reading, with the reasoning. A reading built from call lists, store summaries, a name, a sibling chip or a partial read is inferred, and so is any approximation, with its limit stated. An emulator run is inferred, never established: it shows model behaviour, not hardware. **unknown**: nothing published or shipped decides it. Anything unlabelled is unknown. Do not fill gaps from memory, other graphics boards or other emulators. The register definitions in `registers.toml` carry the three grades the format allows; each doc text says which source the entry rests on.

## 2. Binaries

Proprietary PsiTech binaries are not tracked. Copy the files [references/irix-files.md](references/irix-files.md) lists from your own release 1.3k package into the ignored `root/`. Disassembly, decompiled C, headers and notes derived from them are committed as findings in your own words; instruction listings and firmware images are not. [references/binaries.md](references/binaries.md) names each file by SHA-256.

Public documents are indexed in [references/documents/INDEX.md](references/documents/INDEX.md) by title and URL. No code submodules are pinned yet; add them under `references/code/` when a public source is cited.

## 3. Deliverables

Register and word layouts live in `devices/<unit>/registers.toml`, one file per unit, with a grade on every item. `generated/` (C, Rust, Python, JSON, genxml, QEMU) and `devices/<unit>/registers.md` are written from it by `retools/tools/defs/defs-gen` and never edited by hand. To change a layout, edit the TOML, run `defs-gen`, then `retools/tools/defs/defs-check --build`, and commit both. Everything else goes in pages under `devices/` and `software/`, in your own words, each finding labelled with its rating and derivation.

## 4. Toolchain

The host needs Podman, git and python3; everything else runs in the container built from [retools/tools/Containerfile](retools/tools/Containerfile) via `retools/tools/re-run COMMAND`. [tools/setup-clone.sh](tools/setup-clone.sh) prepares a fresh clone. Run shared tools by their submodule path from the repository root (`retools/tools/<name>`). A change to a tool is made in retools and the pin here moves with a commit. `tools/` keeps only the setup script and `tools/config/`. The shared tools descend from gr4's and carry its BSD-3 notice ([retools/tools/LICENSE-gr4](retools/tools/LICENSE-gr4)).

## 5. Evidence: software only, any source

No hardware is available. Do not plan, request or wait for measurements. Every question is answered from software and published material, and a row is not finished while either still has something to read. Readers may open every file of the vendor package, the public specifications of the PLX and IBM parts, public drivers and emulators, manuals and man pages, and published output from real machines (`hinv`, X logs, screenshots in posts and archives).

Running the shipped software under an emulator shows the model's behaviour and the driver's expectations. It is never hardware evidence; label it that way. Write findings in your own words. Never paste vendor source, firmware or binaries; the programming image and any option ROM stay in `root/`, so describe their format and cite offsets.

Use "established" only for what you read in full: the whole function body or table, or the passage in a document. A reading built from call lists, register-store summaries, a sibling chip or a name is "inferred". Never reword an entry to change its grade. An entry written quickly and not yet checked ends with "Unverified." and grades at most inferred. The PLX and IBM datasheets describe the parts; they are cross-checks for the board. A fact about what the board does, or about its wiring, needs the vendor software or a PsiTech document.

When every route is exhausted, label the fact "unknown: no shipped software or published source depends on it" and list the routes tried; an emulator author then chooses a value and documents it. Never write "needs capture". An open question is not a stopping point: record it in `questions/open-questions.md` with the routes tried and the next one, and carry on. When it is answered, move it into the owning page and delete the entry.

## Evidence order

For a register or behaviour fact, take it from the highest source that states it and grade it by that source:

1. Public documents for the parts on the board (PLX, IBM, the EEPROM and UART datasheets) and PsiTech's own guides and product sheets: write the fact in your own words and cite document, revision and page. A fact one of them defines is `established` for that part.
2. Shipped binaries: confirm what the software does, graded established where read in full, and note which release.
3. Public Linux, OpenBSD and NetBSD headers and drivers for the same parts: `established` once a document or binary confirms them. No public driver for the RAD4 itself exists.
4. Notes from other projects (other projects' datasheets, manual pages and emulator code): may confirm or contradict, never supply a fact. A fact resting only on one stays `unknown`, with the note named.

Reset values: `established` when a datasheet states a power-on default; `inferred` when the software depends on a value before its first write; a read after firmware initialisation is not a reset value and can only rule values out; otherwise `unknown`. A physical hardware read is a last resort, needs the repository owner's approval, and counts as a reset value only for a register firmware provably never writes. Emulator runs are model behaviour, never hardware evidence.

Full text and the checks that enforce it: `retools/tools/README-analysis.md#evidence-order`.

## 6. When work is finished

A coverage row is done when every item in its area is `established` or labelled as having no software dependency, each with a derivation (release, binary, install path under `root/`, offset, callee) in the same entry. Hand off only when your area meets that definition or the session ends; then say in `questions/open-questions.md` where you stopped.

## 7. Rules

- Software-only reverse engineering from public sources and the shipped package. Nothing else is an input.
- Name no emulator projects, private tooling, hosts, people or local storage paths in committed files, and do not record where your copy of the files came from. Give no capture, trace or machine a nickname. Do not quote internal documents. Quote only public sources, briefly, with title and URL in `references/documents/INDEX.md`. `retools/tools/leakcheck.py` enforces this (allow-list `tools/config/leak-allow.txt`) and refuses commit trailers.
- Update `COVERAGE.md` in the same commit as the finding. Commit disassembly and traces you produce as data; keep the proprietary binaries in `root/`.
- No trailers in commit messages: no attribution, sign-off or generated-with lines.
- Commit small and often, straight to `main`. Subjects are lowercase, component-prefixed imperatives (`devices/rad4: record the mode clock formula`); bodies say why. Write everything for a stranger.

## Where new work goes

There is no `evidence/` directory. File each page by what it is about:

- `devices/<board>/`, `platforms/<board>/`, `formats/<name>/`, `software/<area>/`: a note about one device, platform, format or software component.
- `references/`: what we hold and cite: binary lists with checksums, scope lists, source lists. Code submodules stay under `references/code/`.
- `generated/`: tool output that is regenerated and never hand-edited (register output; inventory tables once a root exists).
- `COVERAGE.md` at the root: progress tallies and the areas still open.
- `questions/`: open questions.

`retools/tools/defs/ci-check` fails when an `evidence/` directory comes back.
