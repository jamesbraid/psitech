<!-- generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source -->
<!-- SPDX-License-Identifier: BSD-3-Clause -->
<!-- defs-gen 2 -->
<!-- input sha256 610c8d4ccc0b111742935107dabbda7f5141463a0b9e88789b53045ae90f2724 -->

# RAD4 graphics head registers

Registers of the PsiTech RAD4 PCI graphics board (PCI 12d1:0104) as the vendor's IRIX 6.5 driver and X server use them: a PLX PCI 9060-compatible bus interface, board-local framebuffer, timing and control registers, and the RAMDAC's indexed registers. Grades here are the three the definition format allows. established covers what a public datasheet or the shipped binaries state outright, including driver expectations, and each doc says which. inferred covers inferences and model approximations. The finer ratings are in devices/rad4/README.md.

Unit `rad4`, macro prefix `RAD4`.
Default source: PLX PCI 9060 Data Sheet, version 1.2.

Every item has a grade: established, inferred or unknown. A grade says how the item was derived from its source; it does not claim the item was measured on silicon.

## Address spaces

| Space | Offset unit | Description |
|---|---|---|
| bar0 | byte |  |
| rom | byte |  |
| bar2 | byte |  |
| rgb561 | byte |  |

## Registers

| Register | Offset | Access | Width | Count | Space | Reset | Grade | Source |
|---|---|---|---|---|---|---|---|---|
| `rom_remap` | 0x14 | rw | 32 |  | bar0 | unknown | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `bus_region_descriptor` | 0x18 | rw | 32 |  | bar0 | unknown | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `mailbox` | 0x40 | rw | 32 |  | bar0 | unknown | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `intcsr` | 0x68 | rw | 32 |  | bar0 | 0x10100 (established; PLX PCI 9060 Data Sheet, version 1.2, Table 45 (bits 8 and 16 reset set)) | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `eeprom_ctl` | 0x6c | rw | 32 |  | bar0 | unknown | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `rgb561_index_lo` | 0x900000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |
| `rgb561_index_hi` | 0x910000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |
| `rgb561_data` | 0x920000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |
| `rgb561_data_multi` | 0x930000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 4 |
| `timing_h0` | 0xa00000 | rw | 32 | 1024 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `timing_h1` | 0xa01000 | rw | 32 | 1024 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `timing_h3` | 0xa03000 | rw | 32 | 1024 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `timing_v` | 0xb00000 | rw | 32 | 2048 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `plane_mask` | 0xd00000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver and standalone X server |
| `board_control` | 0xf00000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `rgb561_sync_ctl` | 0x20 | rw | 8 |  | rgb561 | unknown | established | IBM RGB561 Architecture, preliminary revision 1.1, p. 27 |
| `rgb561_pll_vco` | 0x21 | rw | 8 |  | rgb561 | unknown | established | IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 |
| `rgb561_pll_ref` | 0x22 | rw | 8 |  | rgb561 | unknown | established | IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 |
| `rgb561_cursor_ctl` | 0x30 | rw | 8 |  | rgb561 | unknown | established | IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 37 |
| `rgb561_cursor_hot_x` | 0x34 | rw | 8 |  | rgb561 | unknown | established | IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 38 |
| `rgb561_cursor_hot_y` | 0x35 | rw | 8 |  | rgb561 | unknown | established | IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 38 |
| `dmamode0` | 0x100 | rw | 32 |  | rom | unknown | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `dmadpr0` | 0x110 | rw | 32 |  | rom | unknown | established | PLX PCI 9060 Data Sheet, version 1.2 |
| `dmacsr0` | 0x128 | rw | 32 |  | rom | 0x1010 (established; PLX PCI 9060 Data Sheet, version 1.2, Table 57 (both channels' Done set)) | established | PLX PCI 9060 Data Sheet, version 1.2 |

### Register `rom_remap`

Expansion ROM remap register. Software expectation: the driver writes it once at attach, with the top byte 0xe1. Nothing reads it back.

### Register `bus_region_descriptor`

Local bus region descriptor. Software expectation: the driver writes 0xf84303c3 at attach, which selects a 32-bit local bus.

### Register `mailbox`

Mailbox. Software expectation: the driver reads it at attach and skips its own mode and RAMDAC setup when it is nonzero, because it takes that to mean a firmware initialiser has run. What a real card holds here after power-on is unknown.

### Register `intcsr`

Interrupt control and status, with the bits the driver uses. The driver ORs 0x50900 into it at attach whether or not pixel DMA is enabled.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 21 | `dma0_int_active` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 18 | `dma0_int_enable` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 16 | `local_int_output_enable` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 15 | `local_int_input_active` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 11 | `pci_local_int_enable` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 8 | `pci_int_enable` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |

### Register `eeprom_ctl`

Serial EEPROM control. Bits 24 to 27 drive the configuration EEPROM. The driver also replaces the low nibble with 0xc at attach, a use the datasheet reading here does not explain.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 27 | `data_from_eeprom` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 26 | `data_to_eeprom` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 25 | `chip_select` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 24 | `clock` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |

### Register `rgb561_index_lo`

RAMDAC index, low byte, in the low eight bits of a 32-bit store. The identification with the RGB561 index-low port is inferred from the driver's use of it.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7:0 | `value` | inferred |  | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |  |

### Register `rgb561_index_hi`

RAMDAC index, high byte.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7:0 | `value` | inferred |  | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |  |

### Register `rgb561_data`

RAMDAC single-cycle data port. The index advances after each access.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7:0 | `value` | inferred |  | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |  |

### Register `rgb561_data_multi`

RAMDAC multi-cycle data port for tables whose entries are wider than a byte: two cycles per window attribute or gamma entry, three per colour or cursor table entry. The index advances once per complete entry.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7:0 | `value` | inferred |  | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 4 |  |

### Register `timing_h0`

Horizontal timing bank 0. Software expectation: the mode loader writes one word per four-pixel group of the horizontal total. The bank depth is not known, 1024 words is the room between banks, and the bit meanings are unknown.

Array of 1024 registers, stride 4.

### Register `timing_h1`

Horizontal timing bank 1. Same use and limits as bank 0.

Array of 1024 registers, stride 4.

### Register `timing_h3`

Horizontal timing bank 3. Same use and limits as bank 0. The loader holds a pointer to a bank between 1 and 3 and never writes it.

Array of 1024 registers, stride 4.

### Register `timing_v`

Vertical timing bank. Software expectation: one word per line of the vertical total, at most 1656 for the driver's modes. The depth is not known and the bit meanings are unknown.

Array of 2048 registers, stride 4.

### Register `plane_mask`

Pixel write mask. Software expectation: the driver and X server program 0xffffffff, 0x00ffffff for colour drawing and 0x0f000000 for the overlay planes before stores, then restore the full mask. That a store merges as old under the inverse mask or value under the mask is the generic plane-mask convention. Which mask bit reaches which board plane is unknown.

### Register `board_control`

Board control and status. Software expectation: the driver clears bit 5 while it programs a mode and sets it afterwards, sets bit 1 to ask for an interrupt at the next frame and clears it around DMA transfers, and its interrupt handler tests bit 5. That bit 5 reports a frame event only while bit 1 is set is inferred. The physical effects are unknown.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 5 | `mode_gate_frame_status` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 1 | `frame_request` | inferred |  | PsiTech RAD4 release 1.3k driver |  |

### Register `rgb561_sync_ctl`

Sync control. The mode routine writes 1, or 0x23 when the EEPROM selector field equals 2.

### Register `rgb561_pll_vco`

PLL VCO divider. M is bits 5 to 0 plus 65. Bits 7 to 6 hold the range code; that position is inferred, since it reproduces the clock field of all 13 driver modes to the hertz.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7:6 | `range_code` | inferred |  | IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 |  |
| 5:0 | `m_minus_65` | established |  | IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 |  |

### Register `rgb561_pll_ref`

PLL reference divider N, bits 4 to 0.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 4:0 | `n` | established |  | IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 |  |

### Register `rgb561_cursor_ctl`

Cursor control. Bit 0 enables the 64 by 64 two-bit cursor.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 0 | `enable` | established |  | IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 37 |  |

### Register `rgb561_cursor_hot_x`

Cursor hot spot, horizontal, six bits.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 5:0 | `x` | established |  | IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 38 |  |

### Register `rgb561_cursor_hot_y`

Cursor hot spot, vertical, six bits.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 5:0 | `y` | established |  | IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 38 |  |

### Register `dmamode0`

DMA channel 0 mode. Software expectation: the driver reaches the DMA registers through the expansion ROM resource, writes 0x7c3 here (32-bit local bus, chaining, done interrupt enabled) and clears the done-interrupt bit when a transfer times out.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 10 | `done_int_enable` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 9 | `chaining` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |

### Register `dmadpr0`

DMA channel 0 descriptor pointer. Loaded from each descriptor's next-pointer word. The driver starts it at the top of the board's 8 MiB local memory.

### Register `dmacsr0`

DMA command and status, channel 0 in bits 7 to 0. The driver starts a transfer by writing 3 (enable and start) and aborts one with 4 after a timeout, then polls Done.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7:5 | `user` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 4 | `done` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 3 | `clear_int` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 2 | `abort` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 1 | `start` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 0 | `enable` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |

## Words

| Word | Width | Grade | Source |
|---|---|---|---|
| `DMA_DESC_NEXT` | 32 | established | PLX PCI 9060 Data Sheet, version 1.2, Table 51 |

### Word `DMA_DESC_NEXT`

Fourth word of a 16-byte chain descriptor (PCI address, local address, byte count, next pointer). It is loaded into the descriptor pointer register, and its low bits describe the descriptor's own transfer.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 31:4 | `next` | established |  | PLX PCI 9060 Data Sheet, version 1.2, Table 51 |  |
| 3 | `local_to_pci` | established |  | PLX PCI 9060 Data Sheet, version 1.2, Table 51 |  |
| 2 | `int_on_complete` | established |  | PLX PCI 9060 Data Sheet, version 1.2, Table 51 |  |
| 1 | `end_of_chain` | established |  | PLX PCI 9060 Data Sheet, version 1.2, Table 51 |  |

## Constants

| Constant | Value | Grade | Source | Description |
|---|---|---|---|---|
| `DMA_COUNT_BITS` | 0x17 | established | PLX PCI 9060 Data Sheet, version 1.2 | Width of the descriptor byte count. |
| `DMA_DESC_BYTES` | 0x10 | established | PLX PCI 9060 Data Sheet, version 1.2, section 3.6.2 | Size of a chain descriptor. |
| `EEPROM_RECORD_ADDR` | 0x58 | established | PsiTech RAD4 release 1.3k driver | Byte address of the 40-byte configuration record the driver reads at attach. |
| `EEPROM_RECORD_LEN` | 0x28 | established | PsiTech RAD4 release 1.3k driver | Length of that record. |
| `FB_SIZE` | 0x800000 | established | PsiTech RAD4 release 1.3k driver (the mapping it requests) | Framebuffer mapping the driver requests, 8 MiB. The physical memory population is not established. |
| `MODE_COUNT` | 0xd | established | PsiTech RAD4 release 1.3k driver (mode table) | Display modes the driver carries. |
| `REFERENCE_CLOCK_HZ` | 0x1f78a40 | inferred | IBM RGB561 Architecture, preliminary revision 1.1, p. 36; PsiTech RAD4 release 1.3k driver | Board reference clock. The RAMDAC PLL formula with this value reproduces the pixel clock field of every one of the driver's 13 mode records to the hertz. |
