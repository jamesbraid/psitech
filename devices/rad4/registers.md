<!-- generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source -->
<!-- SPDX-License-Identifier: BSD-3-Clause -->
<!-- defs-gen 2 -->
<!-- input sha256 41966f1bd72c1959f7ae6ad7fe24ed136ae73f0c96d4b97155353c46d9c3d511 -->

# RAD4 graphics head registers

Registers of the PsiTech RAD4 PCI graphics board (PCI 12d1:0104) as the vendor's IRIX 6.5 driver and X server use them: a PLX PCI 9060-compatible bus interface, board-local framebuffer, timing and control registers, and the RAMDAC's indexed registers. Grades here are the three the definition format allows. established covers what a public datasheet or the shipped binaries state outright, including what the driver does, and each doc says which. inferred covers inferences and approximations, with the limit stated in the doc.

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
| `flash` | 0x800000 | rw | 8 | 65536 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver (flash sector requests) |
| `rgb561_index_lo` | 0x900000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |
| `rgb561_index_hi` | 0x910000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |
| `rgb561_data` | 0x920000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 |
| `rgb561_data_multi` | 0x930000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 4 |
| `timing_h0` | 0xa00000 | rw | 32 | 1024 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `timing_h1` | 0xa01000 | rw | 32 | 1024 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `timing_h3` | 0xa03000 | rw | 32 | 1024 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `timing_v` | 0xb00000 | rw | 32 | 2048 | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver |
| `plane_mask` | 0xd00000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver and standalone X server |
| `km_mr` | 0xe00000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_sr_csr_a` | 0xe10000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_cr_a` | 0xe20000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_data_a` | 0xe30000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_acr` | 0xe40000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_isr_imr` | 0xe50000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_mr_b` | 0xe80000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_sr_csr_b` | 0xe90000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_cr_b` | 0xea0000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_data_b` | 0xeb0000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_opcr` | 0xed0000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_opr_set` | 0xee0000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
| `km_opr_reset` | 0xef0000 | rw | 32 |  | bar2 | unknown | inferred | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |
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

Expansion ROM remap register. Software use: the driver writes it once at attach, with the top byte 0xe1. Nothing reads it back.

### Register `bus_region_descriptor`

Local bus region descriptor. Software use: the driver writes 0xf84303c3 at attach, which selects a 32-bit local bus.

### Register `mailbox`

Mailbox 0. Software use: the driver reads it at attach and skips its own mode and RAMDAC setup when it is nonzero, because it takes that to mean a firmware initialiser has run, and writes zero to it at the end of every attach. What a real card holds here after power-on is unknown.

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

Serial EEPROM control. Bits 24 to 27 drive the configuration EEPROM. Bits 3 to 0 are the PCI read command the DMA engines use (public datasheet): the driver replaces them at attach with its DMA read command setting, 0xc by default, and the only values it accepts are 0x6, 0xc and 0xe; request 126 changes them later.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 27 | `data_from_eeprom` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 26 | `data_to_eeprom` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 25 | `chip_select` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 24 | `clock` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |
| 3:0 | `dma_read_command` | established |  | PLX PCI 9060 Data Sheet, version 1.2 |  |

### Register `flash`

Parallel flash, 64 KiB in 128-byte sectors. Software use: the driver switches the bus region descriptor to 0xf84003c0, uses byte accesses at the address with its two low bits inverted, programs a sector with the usual three-byte unlock sequence (0xaa, 0x55, 0xa0; addresses in the kernel driver page), writes 128 bytes and polls the last one. The part is not identified; an AT29C512-compatible page-write flash fits the geometry (inferred).

Array of 65536 registers, stride 1.

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

Horizontal timing bank 0. Software use: the mode loader writes one word per four-pixel group of the horizontal total (at most 781 words in the driver's modes). The words are computed from the mode record by the loader, read in full, and bank 1 and the vertical bank are written the same way; the field names below are the loader's structure read against VESA-style timings (modes.md, timing words), not a hardware statement. The bank depth is not known: 1024 words is the room before the next bank.

Array of 1024 registers, stride 4.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `sync_level` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 6 | `sync_window` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 3 | `display_enable` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 2 | `line_end_b` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 1 | `fetch_enable` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 0 | `line_end_a` | inferred |  | PsiTech RAD4 release 1.3k driver |  |

### Register `timing_h1`

Horizontal timing bank 1. Same use and limits as bank 0, but the loader sets only the line-end, sync-window and sync-level bits, never the two enable bits.

Array of 1024 registers, stride 4.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `sync_level` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 6 | `sync_window` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 2 | `line_end_b` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 0 | `line_end_a` | inferred |  | PsiTech RAD4 release 1.3k driver |  |

### Register `timing_h3`

Horizontal timing bank 3. Same use and limits as bank 1, with the sync-window bit inverted relative to banks 0 and 1 and the sync-level bit equal to theirs for separate sync (sync type 0) and inverted for composite sync and sync on green. The loader also holds a pointer to the slot between banks 1 and 3 and never writes it.

Array of 1024 registers, stride 4.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `sync_level` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 6 | `sync_window` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 2 | `line_end_b` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 0 | `line_end_a` | inferred |  | PsiTech RAD4 release 1.3k driver |  |

### Register `timing_v`

Vertical timing bank. Software use: one word per line of the vertical total, at most 1656 for the driver's modes, computed by the loader from the record. The depth is not known; 1656 is the largest count any shipped mode needs. The field names are the loader's structure read against VESA-style timings (modes.md, timing words).

Array of 2048 registers, stride 4.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `sync_level` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 6 | `blank` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 1 | `sync_marker` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
| 0 | `frame_end` | inferred |  | PsiTech RAD4 release 1.3k driver |  |

### Register `plane_mask`

Pixel write mask. Software use: the driver programs 0xffffffff at attach and around its DMA descriptor stores; the X server programs 0x0fffffff at screen start, then 0x00ffffff for colour drawing and 0x0f000000 for the overlay nibble before stores, and paints the window-type nibble under 0xf0000000 through the rectangle-fill request. The driver's buffered path sets the mask to the request mask before a DMA upload and restores the previous one after the transfer has finished, which is how the mask is kept live for DMA data (inferred). That a store merges as old under the inverse mask or value under the mask is the generic plane-mask convention. Which mask bit reaches which board plane is unknown: the software only treats bits 23 to 0 as colour, 27 to 24 as overlay and 31 to 28 as window type.

### Register `km_mr`

Channel A mode register: the first write after a command-register mode-pointer reset goes to mode register 1, the next to mode register 2. The driver writes 0x07 twice at initialisation, and 0x47 then 0x07 after finding a mouse. Low eight bits of the store.

### Register `km_sr_csr_a`

Channel A: reads give the status register (bit 0 receiver ready, bit 2 transmitter ready, the two the driver tests); writes set the clock select, which the driver sets to 0xff.

### Register `km_cr_a`

Channel A command register, written only. Values used: 0x1a, 0x20, 0x30, 0x40, 0x50 (resets, with 0x1a disabling receiver and transmitter), 0x05 (enable both), 0x01 and 0x20 around a transmit.

### Register `km_data_a`

Channel A receive and transmit data, low eight bits.

### Register `km_acr`

Auxiliary control register, written zero at initialisation.

### Register `km_isr_imr`

Reads give interrupt status, writes set the interrupt mask. The driver uses bit 1 (channel A receiver ready) and bit 5 (channel B receiver ready), and ANDs the saved mask with the status in its handler. The saved mask is also what drives board control bit 7.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 5 | `rx_ready_b` | inferred |  | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |  |
| 1 | `rx_ready_a` | inferred |  | PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 |  |

### Register `km_mr_b`

Channel B mode register, used as register km_mr is for channel A.

### Register `km_sr_csr_b`

Channel B status on read and clock select on write, as for channel A.

### Register `km_cr_b`

Channel B command register, written only.

### Register `km_data_b`

Channel B receive and transmit data, low eight bits.

### Register `km_opcr`

Output port configuration, written zero at initialisation, which makes the output port bits plain outputs.

### Register `km_opr_set`

Set output port bits. The driver uses bits 2 and 6 around a channel A transmit and bits 3 and 7 around a channel B transmit. Their wiring (inferred: open-collector drives of the PS/2 clock and data lines) is not documented.

### Register `km_opr_reset`

Reset output port bits, same bits as km_opr_set. Written 0xff at initialisation.

### Register `board_control`

Board control and status. Software use: the driver clears bit 5 while it programs a mode and sets it afterwards, sets bit 1 to ask for an interrupt at the next frame and clears it around DMA transfers, and its interrupt handler tests bit 5. That bit 5 reports a frame event only while bit 1 is set is inferred. Bit 7 is set whenever the keyboard and mouse controller has any interrupt enabled and cleared when none is. The status in bit 5 is read only by the interrupt handler, through a stored pointer, and bit 1 is cleared there when it is set. The physical effects are unknown.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `km_interrupt_gate` | inferred |  | PsiTech RAD4 release 1.3k driver |  |
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

DMA channel 0 mode. Software use: the driver reaches the DMA registers through the expansion ROM resource, writes 0x7c3 here (32-bit local bus, chaining, done interrupt enabled) and clears the done-interrupt bit when a transfer times out.

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
