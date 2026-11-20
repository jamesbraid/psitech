// generated from devices/rad1/registers.toml by defs-gen - do not edit, change the source
// SPDX-License-Identifier: BSD-3-Clause
// defs-gen 2
// input sha256 6d6effab60d3ecf0befbc61265bbab43ca515e793be20c3bb700c2f97c1a0b10
// RAD1 graphics head registers
#![allow(dead_code)]

/// Cursor control: 64x64 size and the cursor mode. Software expectation. (established)
pub mod rd_cursor_control {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x6;
}
/// Colour mode: 8888 pixel format with GUI, RGB and true colour set at init. (established)
pub mod rd_color_mode {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x18;
}
/// Mode control. Written 0. (established)
pub mod rd_mode_control {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x19;
}
/// Misc control: 8-bit palette, sync polarities and sync on green. (established)
pub mod rd_misc_control {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x1e;
}
/// Pixel clock C, feedback (M). (established)
pub mod rd_pixel_clock_c1 {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x26;
}
/// Pixel clock C, prescale (N). (established)
pub mod rd_pixel_clock_c2 {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x27;
}
/// Pixel clock C, postscale (P) with the enable bit (bit 3). Written 0 first to stop the PLL. (established)
pub mod rd_pixel_clock_c3 {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x28;
}
/// Pixel clock status; bit 4 is the lock flag. (established)
pub mod rd_pixel_clock_status {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x29;
}
/// Memory clock, feedback (M). (established)
pub mod rd_memory_clock_1 {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x30;
}
/// Memory clock, prescale (N). (established)
pub mod rd_memory_clock_2 {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x31;
}
/// Memory clock, postscale (P) with the enable bit. Written 6 first to stop the PLL. (established)
pub mod rd_memory_clock_3 {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x32;
}
/// Memory clock status; bit 4 is the lock flag. (established)
pub mod rd_memory_clock_status {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x33;
}
/// Misc control: high colour resolution, direct colour and overlay set at init. (established)
pub mod rd_misc_control_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x0;
}
/// Sync control: horizontal and vertical polarity at the pin. Software expectation. (established)
pub mod rd_sync_control_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x1;
}
/// DAC control: blank pedestal at init; the textport blank sets and clears the low-power bit. (established)
pub mod rd_dac_control_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x2;
}
/// Pixel size: 2 (32 bits) at init. (established)
pub mod rd_pixel_size_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x3;
}
/// Colour format: RGB and 8888 at init. (established)
pub mod rd_color_format_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x4;
}
/// Cursor mode: format (64x64), type and enable. The kernel driver turns the cursor on and off through this register. (established)
pub mod rd_cursor_mode_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x5;
}
/// Cursor control. Written 0 at init. (inferred)
pub mod rd_cursor_control_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x6;
}
/// Cursor X, low byte. (established)
pub mod rd_cursor_x_low_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x7;
}
/// Cursor X, high byte. (established)
pub mod rd_cursor_x_high_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x8;
}
/// Cursor Y, low byte. (established)
pub mod rd_cursor_y_low_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x9;
}
/// Cursor Y, high byte. (established)
pub mod rd_cursor_y_high_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0xa;
}
/// Cursor hot spot X, 6 bits. (established)
pub mod rd_cursor_hot_spot_x_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0xb;
}
/// Cursor hot spot Y, 6 bits. (established)
pub mod rd_cursor_hot_spot_y_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0xc;
}
/// Overlay key. Written 0 at init. (established)
pub mod rd_overlay_key_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0xd;
}
/// Pan. Written 0 at init. (established)
pub mod rd_pan_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0xe;
}
/// Pixel clock PLL control: bit 0 enable, bit 1 locked. (established)
pub mod rd_dclk_control_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x200;
}
/// Pixel clock set 2 prescale (N). The mode loader programs sets 2 and 3 alike; the clock select picks set C. (inferred)
pub mod rd_dclk2_prescale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x207;
}
/// Pixel clock set 2 feedback (M). (inferred)
pub mod rd_dclk2_feedback_scale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x208;
}
/// Pixel clock set 2 postscale (P). (inferred)
pub mod rd_dclk2_postscale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x209;
}
/// Pixel clock set 3 prescale (N). (inferred)
pub mod rd_dclk3_prescale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20a;
}
/// Pixel clock set 3 feedback (M). (inferred)
pub mod rd_dclk3_feedback_scale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20b;
}
/// Pixel clock set 3 postscale (P). (inferred)
pub mod rd_dclk3_postscale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20c;
}
/// Memory clock PLL control: bit 0 enable, bit 1 locked. (established)
pub mod rd_mclk_control_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20d;
}
/// Memory clock prescale (N): 11. (established)
pub mod rd_mclk_prescale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20e;
}
/// Memory clock feedback (M): 128. (established)
pub mod rd_mclk_feedback_scale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x20f;
}
/// Memory clock postscale (P): 1. (established)
pub mod rd_mclk_postscale_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x210;
}
/// Cursor palette: colours stored in consecutive stores. (established)
pub mod rd_cursor_palette_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x303;
}
/// Cursor pattern RAM: 64x64 at two bits a pixel, 1 KiB. (established)
pub mod rd_cursor_pattern_2v {
    pub const WIDTH: u32 = 8;
    pub const OFFSET: u64 = 0x400;
}
/// Soft reset. Software expectation: board start-up writes 0 and polls bit 31 until it clears, before programming anything else. (established)
pub mod reset_status {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x0;
}
/// Interrupt enable. Software expectation: the kernel driver writes 0x83 once at attach, enabling the GP-DMA, sync and bypass-DMA interrupts (bits 0, 1 a (established)
pub mod int_enable {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8;
    pub mod bypass_dma { // bits 7:7, established
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod sync { // bits 1:1, established
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dma { // bits 0:0, established
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
/// Interrupt status, cleared by writing the bits back. Software expectation: the handler reads it, writes the value back, and wakes one waiter for each o (established)
pub mod int_flags {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x10;
    pub mod bypass_dma { // bits 7:7, established
        pub const SHIFT: u32 = 7;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod sync { // bits 1:1, established
        pub const SHIFT: u32 = 1;
        pub const MASK: u32 = 0x1;
        pub const fn get(v: u32) -> u32 {
            (v >> SHIFT) & MASK
        }
        pub const fn set(v: u32, x: u32) -> u32 {
            (v & !(MASK << SHIFT)) | ((x & MASK) << SHIFT)
        }
    }
    pub mod dma { // bits 0:0, established
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
/// Free entries in the input FIFO. Software expectation: every batch of GP register writes is preceded by a poll until the value reaches the batch size;  (established)
pub mod in_fifo_space {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x18;
}
/// Words waiting in the output FIFO. Software expectation: polled until nonzero after a sync or a read-back, and drained to empty after a timeout. (established)
pub mod out_fifo_words {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x20;
}
/// Error status. Software expectation: read before a read-back DMA and written back to clear it, and again after the transfer. (established)
pub mod error_flags {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x38;
}
/// Video clock control. Software expectation: the driver reads it at attach and treats a nonzero value as the console already having initialised the chip (established)
pub mod vclk_ctl {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x40;
}
/// Aperture one control. Software expectation: written 0 at init. (established)
pub mod aperture_one {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x50;
}
/// Aperture two control. Software expectation: written at init with bit 9 (ROM access) set and nothing else, which is what exposes the board's flash for  (established)
pub mod aperture_two {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x58;
}
/// DMA control. Software expectation: written 0x8 at init. (established)
pub mod dma_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x60;
}
/// Chip configuration. Software expectation: only read, by a diagnostic dump routine. (established)
pub mod chip_config {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x70;
}
/// Output DMA address: the host (PCI) address a read-back is written to. Software expectation: set per chunk before the count. (established)
pub mod out_dma_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x80;
}
/// Output DMA count in words; writing it starts the transfer. Software expectation: at most 0xffff words per write. (established)
pub mod out_dma_count {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x88;
}
/// Bypass DMA host address. Software expectation: the source of a host-to-framebuffer transfer. (established)
pub mod by_dma_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xa0;
}
/// Bypass DMA source stride in bytes. (established)
pub mod by_dma_stride {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xb8;
}
/// Bypass DMA destination in local memory, in pixels (or in pixel units of the format). (established)
pub mod by_dma_mem_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xc0;
}
/// Bypass DMA size: width in bits 11 to 0, height from bit 16. Software expectation. (established)
pub mod by_dma_size {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xc8;
}
/// Bypass DMA byte mask. Software expectation: always written 0x000f000f (all lanes at both edges). (established)
pub mod by_dma_byte_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xd0;
}
/// Bypass DMA control; the write starts the transfer. Software expectation: implicit mode, no patching, 32-, 16- or 8-bit source format, the pixel-partia (established)
pub mod by_dma_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0xd8;
}
/// Memory type. Software expectation: written 0 (SGRAM). (established)
pub mod mem_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1040;
}
/// Memory boot address (the SGRAM mode word). Software expectation: 0x20 for the 104c:3d07 chip and 0x30 for the 3d3d:0009 chip, written after the memory (established)
pub mod boot_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1080;
}
/// Memory timing. Software expectation: 0xe6002021 for the 104c:3d07 chip and 0xe6012021 for the 3d3d:0009 chip, both with four banks. (established)
pub mod mem_config {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x10c0;
}
/// Plane write mask for bypass (host and DMA) writes. Software expectation: 0x00ffffff at init; the mask ioctl, rectangle writes and the screen clear cha (established)
pub mod bypass_write_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x1100;
}
/// Output FIFO read port. Software expectation: read to drain sync tags and read-back words. (established)
pub mod out_fifo {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x2000;
}
/// Screen base, in 64-bit units. Software expectation: 0. (established)
pub mod screen_base {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3000;
}
/// Screen stride in 64-bit units: 640 for the two 1280-wide modes and 512 for 1024 wide. (established)
pub mod screen_stride {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3008;
}
/// Horizontal total in 64-bit units, from the mode table's count halved. (established)
pub mod h_total {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3010;
}
/// Horizontal gate end, 64-bit units. (established)
pub mod hg_end {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3018;
}
/// Horizontal blank end, 64-bit units. (established)
pub mod hb_end {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3020;
}
/// Horizontal sync start, 64-bit units. (established)
pub mod hs_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3028;
}
/// Horizontal sync end, 64-bit units. (established)
pub mod hs_end {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3030;
}
/// Vertical total in lines. (established)
pub mod v_total {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3038;
}
/// Vertical blank end in lines. (established)
pub mod vb_end {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3040;
}
/// Vertical sync start in lines. (established)
pub mod vs_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3048;
}
/// Vertical sync end in lines. (established)
pub mod vs_end {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3050;
}
/// Video control. Software expectation: bit 0 enables refresh; the mode loader also sets blank, 64-bit data and active-high sync fields, then turns refre (established)
pub mod video_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3058;
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
/// Video FIFO control. Software expectation: written 0x0b07. (established)
pub mod fifo_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3078;
}
/// Right-eye screen base. Software expectation: written 0. (established)
pub mod screen_base_right {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x3080;
}
/// Palette write address; also the index port of the Permedia 2 indexed registers. Software expectation: the palette load writes 0 here, then red, green  (established)
pub mod rd_palette_write_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4000;
}
/// Palette data. Software expectation: three consecutive byte stores per entry. (established)
pub mod rd_palette_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4008;
}
/// Pixel read mask. Software expectation: written 0xff. (established)
pub mod rd_pixel_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4010;
}
/// Palette read address. Software expectation: written 0 before a palette load. (established)
pub mod rd_palette_read_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4018;
}
/// SVGA control (name ours). Software expectation: written 0x40 before the mode is set, to turn the legacy VGA core off. (inferred)
pub mod vga_control {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x63c4;
}
/// Start X of the dominant edge, 16.16 signed; also the X of a point. (established)
pub mod start_x_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8000;
}
/// Dominant edge X step, 16.16 signed. Written 0. (established)
pub mod d_x_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8008;
}
/// Start X of the subordinate edge, 16.16 signed; the screen clear sets it to the width. (established)
pub mod start_x_sub {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8010;
}
/// Subordinate edge X step, 16.16 signed. Written 0. (established)
pub mod d_x_sub {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8018;
}
/// Start Y, 16.16 signed; also the Y of a point. (established)
pub mod start_y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8020;
}
/// Y step, 16.16 signed. Written 0x10000 at init. (established)
pub mod d_y {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8028;
}
/// Scanline count of a trapezoid. The screen clear writes the mode height. (established)
pub mod count {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8030;
}
/// Render command; the write starts the operation. Software expectation: primitive in bits 7 to 6 (trapezoid, point, rectangle), fast fill bit 3, texture (established)
pub mod render {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8038;
}
/// Wait for completion; written 0 after a render that the driver must see finished. (established)
pub mod wait_for_completion {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8088;
}
/// Rasterizer mode. Written 0. (established)
pub mod rasterizer_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x80a0;
}
/// Rectangle origin: X in the low 12 bits, Y from bit 16. (established)
pub mod rectangle_origin {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x80d0;
}
/// Rectangle size: width in the low bits, height from bit 16. (established)
pub mod rectangle_size {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x80d8;
}
/// Packed data limits; the X end is set to width minus one. (established)
pub mod packed_data_limits {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8150;
}
/// Scissor mode. Written 0. (established)
pub mod scissor_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8180;
}
/// Screen size: width in bits 10 to 0, height from bit 16. (established)
pub mod screen_size {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8198;
}
/// Area stipple mode. Written 0. (established)
pub mod area_stipple_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x81a0;
}
/// Window origin. Written 0. (established)
pub mod window_origin {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x81c8;
}
/// Texture address mode. Written 1 (enable) for the format-converting copy and 0 otherwise. (established)
pub mod texture_address_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8380;
}
/// Texture S start. (established)
pub mod s_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8388;
}
/// Texture S step per pixel; written 1.0 in 12.18 fixed point at init. (established)
pub mod d_s_dx {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8390;
}
/// Texture S step per scanline. (established)
pub mod d_s_dy_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8398;
}
/// Texture T start. (established)
pub mod t_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x83a0;
}
/// Texture T step per pixel. (established)
pub mod d_t_dx {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x83a8;
}
/// Texture T step per scanline; 1.0 in the format-converting copy. (established)
pub mod d_t_dy_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x83b0;
}
/// Texel look-up table index; written 0 before a table load. (established)
pub mod texel_lut_index {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x84c0;
}
/// Texel look-up table data, one 32-bit colour per store. (established)
pub mod texel_lut_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x84c8;
}
/// Texel look-up table address in local memory; set to 256 words below the end of the 8 MiB memory. (established)
pub mod texel_lut_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x84d0;
}
/// Texture base address: where the format-converting copy reads its source, in local memory. (established)
pub mod texture_base_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8580;
}
/// Texture map format: texel size and the width partial products. (established)
pub mod texture_map_format {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8588;
}
/// Texture data format. Written 0 at init. (established)
pub mod texture_data_format {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8590;
}
/// Texel 0. Written 0 at init. (established)
pub mod texel0 {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8600;
}
/// Texture read mode. (established)
pub mod texture_read_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8670;
}
/// Texel look-up table mode; 1 enables it for 8-bit colour-index copies. (established)
pub mod texel_lut_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8678;
}
/// Texture colour mode. (established)
pub mod texture_color_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8680;
}
/// Fog mode. Written 0. (established)
pub mod fog_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8690;
}
/// Colour DDA red start; used only by the start-up screen fill. (established)
pub mod r_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8780;
}
/// Colour DDA red step per pixel. (established)
pub mod d_r_dx {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8788;
}
/// Colour DDA red step per scanline. (established)
pub mod d_r_dy_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8790;
}
/// Colour DDA green start. (established)
pub mod g_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8798;
}
/// Colour DDA green step per pixel. (established)
pub mod d_g_dx {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87a0;
}
/// Colour DDA green step per scanline. (established)
pub mod d_g_dy_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87a8;
}
/// Colour DDA blue start. (established)
pub mod b_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87b0;
}
/// Colour DDA blue step per pixel. (established)
pub mod d_b_dx {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87b8;
}
/// Colour DDA blue step per scanline. (established)
pub mod d_b_dy_dom {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87c0;
}
/// Colour DDA alpha start. (established)
pub mod a_start {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87c8;
}
/// Colour DDA mode; enabled with Gouraud shading only for the start-up screen fill. (established)
pub mod color_dda_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x87e0;
}
/// Alpha blend mode. Written 0 at init and set to the format operation for a read-back. (established)
pub mod alpha_blend_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8810;
}
/// Dither mode. Written with the unit enable bit set at init. (established)
pub mod dither_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8818;
}
/// Framebuffer software write mask. Written all ones at init; the rectangle fill and copy paths put the caller's mask here. (established)
pub mod fb_software_write_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8820;
}
/// Logical operation mode: enable, operation, and the constant-write-data bit that makes fills use the write-data register. Software expectation. (established)
pub mod logical_op_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8828;
}
/// Constant framebuffer write data: the colour of a fill or a textport pixel. (established)
pub mod fb_write_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8830;
}
/// Local buffer read mode. Written 0 at init. (established)
pub mod lb_read_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8880;
}
/// Local buffer window base. Written 0. (established)
pub mod lb_window_base {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x88b8;
}
/// Local buffer write mode. Written 0. (established)
pub mod lb_write_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x88c0;
}
/// Local buffer write format. Written 0. (established)
pub mod lb_write_format {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x88c8;
}
/// Window: the local buffer update fields. Written with the update disabled. (established)
pub mod window {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8980;
}
/// Stencil mode. Written 0. (established)
pub mod stencil_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8988;
}
/// Depth mode. Written 0. (established)
pub mod depth_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x89a0;
}
/// Framebuffer read mode: source and destination read enables, packed data, relative offset and the screen-width partial products. (established)
pub mod fb_read_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8a80;
}
/// Framebuffer pixel offset. Written 0. (established)
pub mod fb_pixel_offset {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8a90;
}
/// Framebuffer window base. Written 0. (established)
pub mod fb_window_base {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8ab0;
}
/// Framebuffer write mode: write enable, and the upload-to-host bit for a read-back. (established)
pub mod fb_write_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8ab8;
}
/// Framebuffer hardware write mask. Written all ones at init and 0x00ffffff afterwards. (established)
pub mod fb_hard_write_mask {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8ac0;
}
/// Block colour for a fast fill. (established)
pub mod fb_block_color {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8ac8;
}
/// Framebuffer read pixel size. Written 2 (32 bits). (established)
pub mod fb_read_pixel {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8ad0;
}
/// Filter mode: which output tags reach the host. Synchronisation data for a sync, colour data for a read-back. (established)
pub mod filter_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8c00;
}
/// Statistic mode. Written 0 at init. (established)
pub mod statistic_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8c08;
}
/// Sync: writing a tag with bit 31 set raises the sync interrupt when the pipeline reaches it, and the tag appears in the output FIFO. (established)
pub mod sync {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8c40;
}
/// Framebuffer source base. Written 0 at init. (established)
pub mod fb_source_base {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8d80;
}
/// Framebuffer source delta: the Y and X offset of a screen-to-screen copy's source, negated. (established)
pub mod fb_source_delta {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8d88;
}
/// YUV mode. Written 0 at init. (established)
pub mod yuv_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x8f00;
}
/// Delta mode. Written 0 at init. (established)
pub mod delta_mode {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x9300;
}
/// Cursor colour address. Software expectation: written 1 before the cursor colours. (established)
pub mod rd_cursor_color_address {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4020;
}
/// Cursor colour data: three bytes background then three bytes foreground. (established)
pub mod rd_cursor_color_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4028;
}
/// Data port of the indexed registers, selected through the palette write address. Software expectation: read to poll the PLL lock bits. (established)
pub mod rd_indexed_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4050;
}
/// Cursor pattern RAM data port. (established)
pub mod rd_cursor_ram_data {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4058;
}
/// Cursor X, low byte. (established)
pub mod rd_cursor_x_low {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4060;
}
/// Cursor X, high byte. (established)
pub mod rd_cursor_x_high {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4068;
}
/// Cursor Y, low byte. (established)
pub mod rd_cursor_y_low {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4070;
}
/// Cursor Y, high byte. (established)
pub mod rd_cursor_y_high {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4078;
}
/// Index, low byte. Software expectation: written before each access to an indexed register. (established)
pub mod rd_index_low_2v {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4020;
}
/// Index, high byte. (established)
pub mod rd_index_high_2v {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4028;
}
/// Indexed data port. Software expectation: after a cursor palette or pattern index is set, consecutive stores fill the table, so the index auto-incremen (established)
pub mod rd_indexed_data_2v {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4030;
}
/// Index control. Software expectation: written 1 at init to turn auto-increment on. (established)
pub mod rd_index_control_2v {
    pub const WIDTH: u32 = 32;
    pub const OFFSET: u64 = 0x4038;
}
