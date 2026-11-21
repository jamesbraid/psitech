// generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source
// SPDX-License-Identifier: BSD-3-Clause
// defs-gen 2
// input sha256 41966f1bd72c1959f7ae6ad7fe24ed136ae73f0c96d4b97155353c46d9c3d511
// RAD4 graphics head registers
#![allow(dead_code)]

/// Expansion ROM remap register. Software use: the driver writes it once at attach, with the top byte 0xe1. Nothing reads it back. (established)
pub mod rom_remap {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x14;
}
/// Local bus region descriptor. Software use: the driver writes 0xf84303c3 at attach, which selects a 32-bit local bus. (established)
pub mod bus_region_descriptor {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x18;
}
/// Mailbox 0. Software use: the driver reads it at attach and skips its own mode and RAMDAC setup when it is nonzero, because it takes that to mean a fir (established)
pub mod mailbox {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x40;
}
/// Interrupt control and status, with the bits the driver uses. The driver ORs 0x50900 into it at attach whether or not pixel DMA is enabled. (established)
pub mod intcsr {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x68;
    pub mod dma0_int_active { // bits 21:21, established
        pub const SHIFT: u32 = 21;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dma0_int_enable { // bits 18:18, established
        pub const SHIFT: u32 = 18;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod local_int_output_enable { // bits 16:16, established
        pub const SHIFT: u32 = 16;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod local_int_input_active { // bits 15:15, established
        pub const SHIFT: u32 = 15;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod pci_local_int_enable { // bits 11:11, established
        pub const SHIFT: u32 = 11;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod pci_int_enable { // bits 8:8, established
        pub const SHIFT: u32 = 8;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Serial EEPROM control. Bits 24 to 27 drive the configuration EEPROM. Bits 3 to 0 are the PCI read command the DMA engines use (public datasheet): the  (established)
pub mod eeprom_ctl {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x6c;
    pub mod data_from_eeprom { // bits 27:27, established
        pub const SHIFT: u32 = 27;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod data_to_eeprom { // bits 26:26, established
        pub const SHIFT: u32 = 26;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod chip_select { // bits 25:25, established
        pub const SHIFT: u32 = 25;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod clock { // bits 24:24, established
        pub const SHIFT: u32 = 24;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dma_read_command { // bits 3:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xf;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Parallel flash, 64 KiB in 128-byte sectors. Software use: the driver switches the bus region descriptor to 0xf84003c0, uses byte accesses at the addre (inferred)
pub mod flash {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x800000;
    pub const COUNT: u32 = 65536;
    pub const STRIDE: u64 = 1;
}
/// RAMDAC index, low byte, in the low eight bits of a 32-bit store. The identification with the RGB561 index-low port is inferred from the driver's use o (inferred)
pub mod rgb561_index_lo {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x900000;
    pub mod value { // bits 7:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// RAMDAC index, high byte. (inferred)
pub mod rgb561_index_hi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x910000;
    pub mod value { // bits 7:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// RAMDAC single-cycle data port. The index advances after each access. (inferred)
pub mod rgb561_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x920000;
    pub mod value { // bits 7:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// RAMDAC multi-cycle data port for tables whose entries are wider than a byte: two cycles per window attribute or gamma entry, three per colour or curso (inferred)
pub mod rgb561_data_multi {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x930000;
    pub mod value { // bits 7:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0xff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Horizontal timing bank 0. Software use: the mode loader writes one word per four-pixel group of the horizontal total (at most 781 words in the driver' (inferred)
pub mod timing_h0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa00000;
    pub const COUNT: u32 = 1024;
    pub const STRIDE: u64 = 4;
    pub mod sync_level { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod sync_window { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod display_enable { // bits 3:3, inferred
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod line_end_b { // bits 2:2, inferred
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod fetch_enable { // bits 1:1, inferred
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod line_end_a { // bits 0:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Horizontal timing bank 1. Same use and limits as bank 0, but the loader sets only the line-end, sync-window and sync-level bits, never the two enable  (inferred)
pub mod timing_h1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa01000;
    pub const COUNT: u32 = 1024;
    pub const STRIDE: u64 = 4;
    pub mod sync_level { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod sync_window { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod line_end_b { // bits 2:2, inferred
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod line_end_a { // bits 0:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Horizontal timing bank 3. Same use and limits as bank 1, with the sync-window bit inverted relative to banks 0 and 1 and the sync-level bit equal to t (inferred)
pub mod timing_h3 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa03000;
    pub const COUNT: u32 = 1024;
    pub const STRIDE: u64 = 4;
    pub mod sync_level { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod sync_window { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod line_end_b { // bits 2:2, inferred
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod line_end_a { // bits 0:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Vertical timing bank. Software use: one word per line of the vertical total, at most 1656 for the driver's modes, computed by the loader from the reco (inferred)
pub mod timing_v {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xb00000;
    pub const COUNT: u32 = 2048;
    pub const STRIDE: u64 = 4;
    pub mod sync_level { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod blank { // bits 6:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod sync_marker { // bits 1:1, inferred
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod frame_end { // bits 0:0, inferred
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Pixel write mask. Software use: the driver programs 0xffffffff at attach and around its DMA descriptor stores; the X server programs 0x0fffffff at scr (inferred)
pub mod plane_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xd00000;
}
/// Channel A mode register: the first write after a command-register mode-pointer reset goes to mode register 1, the next to mode register 2. The driver  (inferred)
pub mod km_mr {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe00000;
}
/// Channel A: reads give the status register (bit 0 receiver ready, bit 2 transmitter ready, the two the driver tests); writes set the clock select, whic (inferred)
pub mod km_sr_csr_a {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe10000;
}
/// Channel A command register, written only. Values used: 0x1a, 0x20, 0x30, 0x40, 0x50 (resets, with 0x1a disabling receiver and transmitter), 0x05 (enab (inferred)
pub mod km_cr_a {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe20000;
}
/// Channel A receive and transmit data, low eight bits. (inferred)
pub mod km_data_a {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe30000;
}
/// Auxiliary control register, written zero at initialisation. (inferred)
pub mod km_acr {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe40000;
}
/// Reads give interrupt status, writes set the interrupt mask. The driver uses bit 1 (channel A receiver ready) and bit 5 (channel B receiver ready), and (inferred)
pub mod km_isr_imr {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe50000;
    pub mod rx_ready_b { // bits 5:5, inferred
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod rx_ready_a { // bits 1:1, inferred
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Channel B mode register, used as register km_mr is for channel A. (inferred)
pub mod km_mr_b {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe80000;
}
/// Channel B status on read and clock select on write, as for channel A. (inferred)
pub mod km_sr_csr_b {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xe90000;
}
/// Channel B command register, written only. (inferred)
pub mod km_cr_b {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xea0000;
}
/// Channel B receive and transmit data, low eight bits. (inferred)
pub mod km_data_b {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xeb0000;
}
/// Output port configuration, written zero at initialisation, which makes the output port bits plain outputs. (inferred)
pub mod km_opcr {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xed0000;
}
/// Set output port bits. The driver uses bits 2 and 6 around a channel A transmit and bits 3 and 7 around a channel B transmit. Their wiring (inferred: o (inferred)
pub mod km_opr_set {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xee0000;
}
/// Reset output port bits, same bits as km_opr_set. Written 0xff at initialisation. (inferred)
pub mod km_opr_reset {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xef0000;
}
/// Board control and status. Software use: the driver clears bit 5 while it programs a mode and sets it afterwards, sets bit 1 to ask for an interrupt at (inferred)
pub mod board_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xf00000;
    pub mod km_interrupt_gate { // bits 7:7, inferred
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod mode_gate_frame_status { // bits 5:5, inferred
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod frame_request { // bits 1:1, inferred
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Sync control. The mode routine writes 1, or 0x23 when the EEPROM selector field equals 2. (established)
pub mod rgb561_sync_ctl {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20;
}
/// PLL VCO divider. M is bits 5 to 0 plus 65. Bits 7 to 6 hold the range code; that position is inferred, since it reproduces the clock field of all 13 d (established)
pub mod rgb561_pll_vco {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x21;
    pub mod range_code { // bits 7:6, inferred
        pub const SHIFT: u32 = 6;
        pub const MASK: u32 = 0x3;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod m_minus_65 { // bits 5:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x3f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// PLL reference divider N, bits 4 to 0. (established)
pub mod rgb561_pll_ref {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x22;
    pub mod n { // bits 4:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Cursor control. Bit 0 enables the 64 by 64 two-bit cursor. (established)
pub mod rgb561_cursor_ctl {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x30;
    pub mod enable { // bits 0:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Cursor hot spot, horizontal, six bits. (established)
pub mod rgb561_cursor_hot_x {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x34;
    pub mod x { // bits 5:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x3f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Cursor hot spot, vertical, six bits. (established)
pub mod rgb561_cursor_hot_y {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x35;
    pub mod y { // bits 5:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x3f;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// DMA channel 0 mode. Software use: the driver reaches the DMA registers through the expansion ROM resource, writes 0x7c3 here (32-bit local bus, chaini (established)
pub mod dmamode0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x100;
    pub mod done_int_enable { // bits 10:10, established
        pub const SHIFT: u32 = 10;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod chaining { // bits 9:9, established
        pub const SHIFT: u32 = 9;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// DMA channel 0 descriptor pointer. Loaded from each descriptor's next-pointer word. The driver starts it at the top of the board's 8 MiB local memory. (established)
pub mod dmadpr0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x110;
}
/// DMA command and status, channel 0 in bits 7 to 0. The driver starts a transfer by writing 3 (enable and start) and aborts one with 4 after a timeout,  (established)
pub mod dmacsr0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x128;
    pub mod user { // bits 7:5, established
        pub const SHIFT: u32 = 5;
        pub const MASK: u32 = 0x7;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod done { // bits 4:4, established
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod clear_int { // bits 3:3, established
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod abort { // bits 2:2, established
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod start { // bits 1:1, established
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod enable { // bits 0:0, established
        pub const SHIFT: u32 = 0;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
/// Fourth word of a 16-byte chain descriptor (PCI address, local address, byte count, next pointer). It is loaded into the descriptor pointer register, a (established)
pub mod dma_desc_next {
    pub const WIDTH: u32 = 32;
    pub mod next { // bits 31:4, established
        pub const SHIFT: u32 = 4;
        pub const MASK: u32 = 0xfffffff;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod local_to_pci { // bits 3:3, established
        pub const SHIFT: u32 = 3;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod int_on_complete { // bits 2:2, established
        pub const SHIFT: u32 = 2;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod end_of_chain { // bits 1:1, established
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
}
pub const DMA_COUNT_BITS: u32 = 0x17; // established
pub const DMA_DESC_BYTES: u32 = 0x10; // established
pub const EEPROM_RECORD_ADDR: u32 = 0x58; // established
pub const EEPROM_RECORD_LEN: u32 = 0x28; // established
pub const FB_SIZE: u32 = 0x800000; // established
pub const MODE_COUNT: u32 = 0xd; // established
pub const REFERENCE_CLOCK_HZ: u32 = 0x1f78a40; // inferred
