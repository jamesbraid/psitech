// generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source
// SPDX-License-Identifier: BSD-3-Clause
// defs-gen 2
// input sha256 610c8d4ccc0b111742935107dabbda7f5141463a0b9e88789b53045ae90f2724
// RAD4 graphics head registers
#![allow(dead_code)]

/// Expansion ROM remap register. Software expectation: the driver writes it once at attach, with the top byte 0xe1. Nothing reads it back. (established)
pub mod rom_remap {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x14;
}
/// Local bus region descriptor. Software expectation: the driver writes 0xf84303c3 at attach, which selects a 32-bit local bus. (established)
pub mod bus_region_descriptor {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x18;
}
/// Mailbox. Software expectation: the driver reads it at attach and skips its own mode and RAMDAC setup when it is nonzero, because it takes that to mean (established)
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
/// Serial EEPROM control. Bits 24 to 27 drive the configuration EEPROM. The driver also replaces the low nibble with 0xc at attach, a use the datasheet r (established)
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
/// Horizontal timing bank 0. Software expectation: the mode loader writes one word per four-pixel group of the horizontal total. The bank depth is not kn (inferred)
pub mod timing_h0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa00000;
    pub const COUNT: u32 = 1024;
    pub const STRIDE: u64 = 4;
}
/// Horizontal timing bank 1. Same use and limits as bank 0. (inferred)
pub mod timing_h1 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa01000;
    pub const COUNT: u32 = 1024;
    pub const STRIDE: u64 = 4;
}
/// Horizontal timing bank 3. Same use and limits as bank 0. The loader holds a pointer to a bank between 1 and 3 and never writes it. (inferred)
pub mod timing_h3 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa03000;
    pub const COUNT: u32 = 1024;
    pub const STRIDE: u64 = 4;
}
/// Vertical timing bank. Software expectation: one word per line of the vertical total, at most 1656 for the driver's modes. The depth is not known and t (inferred)
pub mod timing_v {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xb00000;
    pub const COUNT: u32 = 2048;
    pub const STRIDE: u64 = 4;
}
/// Pixel write mask. Software expectation: the driver and X server program 0xffffffff, 0x00ffffff for colour drawing and 0x0f000000 for the overlay plane (inferred)
pub mod plane_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xd00000;
}
/// Board control and status. Software expectation: the driver clears bit 5 while it programs a mode and sets it afterwards, sets bit 1 to ask for an inte (inferred)
pub mod board_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xf00000;
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
/// DMA channel 0 mode. Software expectation: the driver reaches the DMA registers through the expansion ROM resource, writes 0x7c3 here (32-bit local bus (established)
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
