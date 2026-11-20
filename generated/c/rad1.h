/* generated from devices/rad1/registers.toml by defs-gen - do not edit, change the source */
/* SPDX-License-Identifier: BSD-3-Clause */
/* defs-gen 2 */
/* input sha256 6d6effab60d3ecf0befbc61265bbab43ca515e793be20c3bb700c2f97c1a0b10 */
/* RAD1 graphics head registers */
#ifndef RAD1_GEN_H
#define RAD1_GEN_H

#include <stdint.h>


/*
 * Cursor control: 64x64 size and the cursor mode. Software expectation.
 */
/* rd_cursor_control: rw8, space p2dac, reset unknown */
#define RAD1_RD_CURSOR_CONTROL_OFFSET                0x6u /* established */

/*
 * Colour mode: 8888 pixel format with GUI, RGB and true colour set at init.
 */
/* rd_color_mode: rw8, space p2dac, reset unknown */
#define RAD1_RD_COLOR_MODE_OFFSET                    0x18u /* established */

/*
 * Mode control. Written 0.
 */
/* rd_mode_control: rw8, space p2dac, reset unknown */
#define RAD1_RD_MODE_CONTROL_OFFSET                  0x19u /* established */

/*
 * Misc control: 8-bit palette, sync polarities and sync on green.
 */
/* rd_misc_control: rw8, space p2dac, reset unknown */
#define RAD1_RD_MISC_CONTROL_OFFSET                  0x1eu /* established */

/*
 * Pixel clock C, feedback (M).
 */
/* rd_pixel_clock_c1: rw8, space p2dac, reset unknown */
#define RAD1_RD_PIXEL_CLOCK_C1_OFFSET                0x26u /* established */

/*
 * Pixel clock C, prescale (N).
 */
/* rd_pixel_clock_c2: rw8, space p2dac, reset unknown */
#define RAD1_RD_PIXEL_CLOCK_C2_OFFSET                0x27u /* established */

/*
 * Pixel clock C, postscale (P) with the enable bit (bit 3). Written 0 first to stop the PLL.
 */
/* rd_pixel_clock_c3: rw8, space p2dac, reset unknown */
#define RAD1_RD_PIXEL_CLOCK_C3_OFFSET                0x28u /* established */

/*
 * Pixel clock status; bit 4 is the lock flag.
 */
/* rd_pixel_clock_status: rw8, space p2dac, reset unknown */
#define RAD1_RD_PIXEL_CLOCK_STATUS_OFFSET            0x29u /* established */

/*
 * Memory clock, feedback (M).
 */
/* rd_memory_clock_1: rw8, space p2dac, reset unknown */
#define RAD1_RD_MEMORY_CLOCK_1_OFFSET                0x30u /* established */

/*
 * Memory clock, prescale (N).
 */
/* rd_memory_clock_2: rw8, space p2dac, reset unknown */
#define RAD1_RD_MEMORY_CLOCK_2_OFFSET                0x31u /* established */

/*
 * Memory clock, postscale (P) with the enable bit. Written 6 first to stop the PLL.
 */
/* rd_memory_clock_3: rw8, space p2dac, reset unknown */
#define RAD1_RD_MEMORY_CLOCK_3_OFFSET                0x32u /* established */

/*
 * Memory clock status; bit 4 is the lock flag.
 */
/* rd_memory_clock_status: rw8, space p2dac, reset unknown */
#define RAD1_RD_MEMORY_CLOCK_STATUS_OFFSET           0x33u /* established */

/*
 * Misc control: high colour resolution, direct colour and overlay set at init.
 */
/* rd_misc_control_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_MISC_CONTROL_2V_OFFSET               0x0u /* established */

/*
 * Sync control: horizontal and vertical polarity at the pin. Software expectation.
 */
/* rd_sync_control_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_SYNC_CONTROL_2V_OFFSET               0x1u /* established */

/*
 * DAC control: blank pedestal at init; the textport blank sets and clears the low-power bit.
 */
/* rd_dac_control_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DAC_CONTROL_2V_OFFSET                0x2u /* established */

/*
 * Pixel size: 2 (32 bits) at init.
 */
/* rd_pixel_size_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_PIXEL_SIZE_2V_OFFSET                 0x3u /* established */

/*
 * Colour format: RGB and 8888 at init.
 */
/* rd_color_format_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_COLOR_FORMAT_2V_OFFSET               0x4u /* established */

/*
 * Cursor mode: format (64x64), type and enable. The kernel driver turns the cursor on and off through this register.
 */
/* rd_cursor_mode_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_MODE_2V_OFFSET                0x5u /* established */

/*
 * Cursor control. Written 0 at init.
 */
/* rd_cursor_control_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_CONTROL_2V_OFFSET             0x6u /* inferred */

/*
 * Cursor X, low byte.
 */
/* rd_cursor_x_low_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_X_LOW_2V_OFFSET               0x7u /* established */

/*
 * Cursor X, high byte.
 */
/* rd_cursor_x_high_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_X_HIGH_2V_OFFSET              0x8u /* established */

/*
 * Cursor Y, low byte.
 */
/* rd_cursor_y_low_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_Y_LOW_2V_OFFSET               0x9u /* established */

/*
 * Cursor Y, high byte.
 */
/* rd_cursor_y_high_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_Y_HIGH_2V_OFFSET              0xau /* established */

/*
 * Cursor hot spot X, 6 bits.
 */
/* rd_cursor_hot_spot_x_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_HOT_SPOT_X_2V_OFFSET          0xbu /* established */

/*
 * Cursor hot spot Y, 6 bits.
 */
/* rd_cursor_hot_spot_y_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_HOT_SPOT_Y_2V_OFFSET          0xcu /* established */

/*
 * Overlay key. Written 0 at init.
 */
/* rd_overlay_key_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_OVERLAY_KEY_2V_OFFSET                0xdu /* established */

/*
 * Pan. Written 0 at init.
 */
/* rd_pan_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_PAN_2V_OFFSET                        0xeu /* established */

/*
 * Pixel clock PLL control: bit 0 enable, bit 1 locked.
 */
/* rd_dclk_control_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK_CONTROL_2V_OFFSET               0x200u /* established */

/*
 * Pixel clock set 2 prescale (N). The mode loader programs sets 2 and 3 alike; the clock select picks set C.
 */
/* rd_dclk2_prescale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK2_PRESCALE_2V_OFFSET             0x207u /* inferred */

/*
 * Pixel clock set 2 feedback (M).
 */
/* rd_dclk2_feedback_scale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK2_FEEDBACK_SCALE_2V_OFFSET       0x208u /* inferred */

/*
 * Pixel clock set 2 postscale (P).
 */
/* rd_dclk2_postscale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK2_POSTSCALE_2V_OFFSET            0x209u /* inferred */

/*
 * Pixel clock set 3 prescale (N).
 */
/* rd_dclk3_prescale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK3_PRESCALE_2V_OFFSET             0x20au /* inferred */

/*
 * Pixel clock set 3 feedback (M).
 */
/* rd_dclk3_feedback_scale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK3_FEEDBACK_SCALE_2V_OFFSET       0x20bu /* inferred */

/*
 * Pixel clock set 3 postscale (P).
 */
/* rd_dclk3_postscale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_DCLK3_POSTSCALE_2V_OFFSET            0x20cu /* inferred */

/*
 * Memory clock PLL control: bit 0 enable, bit 1 locked.
 */
/* rd_mclk_control_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_MCLK_CONTROL_2V_OFFSET               0x20du /* established */

/*
 * Memory clock prescale (N): 11.
 */
/* rd_mclk_prescale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_MCLK_PRESCALE_2V_OFFSET              0x20eu /* established */

/*
 * Memory clock feedback (M): 128.
 */
/* rd_mclk_feedback_scale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_MCLK_FEEDBACK_SCALE_2V_OFFSET        0x20fu /* established */

/*
 * Memory clock postscale (P): 1.
 */
/* rd_mclk_postscale_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_MCLK_POSTSCALE_2V_OFFSET             0x210u /* established */

/*
 * Cursor palette: colours stored in consecutive stores.
 */
/* rd_cursor_palette_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_PALETTE_2V_OFFSET             0x303u /* established */

/*
 * Cursor pattern RAM: 64x64 at two bits a pixel, 1 KiB.
 */
/* rd_cursor_pattern_2v: rw8, space p2vdac, reset unknown */
#define RAD1_RD_CURSOR_PATTERN_2V_OFFSET             0x400u /* established */

/*
 * Soft reset. Software expectation: board start-up writes 0 and polls bit 31 until it clears, before programming anything else.
 */
/* reset_status: rw32, space rz, reset unknown */
#define RAD1_RESET_STATUS_OFFSET                     0x0u /* established */

/*
 * Interrupt enable. Software expectation: the kernel driver writes 0x83 once at attach, enabling the GP-DMA, sync and bypass-DMA interrupts (bits 0, 1 and 7), and its interrupt handler writes 0 on entry and restores 0x83 on exit. The textport library writes 0.
 */
/* int_enable: rw32, space rz, reset unknown */
#define RAD1_INT_ENABLE_OFFSET                       0x8u /* established */
#define RAD1_INT_ENABLE_BYPASS_DMA_SHIFT             7 /* established */
#define RAD1_INT_ENABLE_BYPASS_DMA_MASK              0x1u
#define RAD1_INT_ENABLE_BYPASS_DMA_INPLACE           (RAD1_INT_ENABLE_BYPASS_DMA_MASK << RAD1_INT_ENABLE_BYPASS_DMA_SHIFT)
#define RAD1_INT_ENABLE_SYNC_SHIFT                   1 /* established */
#define RAD1_INT_ENABLE_SYNC_MASK                    0x1u
#define RAD1_INT_ENABLE_SYNC_INPLACE                 (RAD1_INT_ENABLE_SYNC_MASK << RAD1_INT_ENABLE_SYNC_SHIFT)
#define RAD1_INT_ENABLE_DMA_SHIFT                    0 /* established */
#define RAD1_INT_ENABLE_DMA_MASK                     0x1u
#define RAD1_INT_ENABLE_DMA_INPLACE                  (RAD1_INT_ENABLE_DMA_MASK << RAD1_INT_ENABLE_DMA_SHIFT)

/*
 * Interrupt status, cleared by writing the bits back. Software expectation: the handler reads it, writes the value back, and wakes one waiter for each of bits 1 (sync), 0 (GP output DMA) and 7 (bypass DMA). No other bit is tested.
 */
/* int_flags: rw32, space rz, reset unknown */
#define RAD1_INT_FLAGS_OFFSET                        0x10u /* established */
#define RAD1_INT_FLAGS_BYPASS_DMA_SHIFT              7 /* established */
#define RAD1_INT_FLAGS_BYPASS_DMA_MASK               0x1u
#define RAD1_INT_FLAGS_BYPASS_DMA_INPLACE            (RAD1_INT_FLAGS_BYPASS_DMA_MASK << RAD1_INT_FLAGS_BYPASS_DMA_SHIFT)
#define RAD1_INT_FLAGS_SYNC_SHIFT                    1 /* established */
#define RAD1_INT_FLAGS_SYNC_MASK                     0x1u
#define RAD1_INT_FLAGS_SYNC_INPLACE                  (RAD1_INT_FLAGS_SYNC_MASK << RAD1_INT_FLAGS_SYNC_SHIFT)
#define RAD1_INT_FLAGS_DMA_SHIFT                     0 /* established */
#define RAD1_INT_FLAGS_DMA_MASK                      0x1u
#define RAD1_INT_FLAGS_DMA_INPLACE                   (RAD1_INT_FLAGS_DMA_MASK << RAD1_INT_FLAGS_DMA_SHIFT)

/*
 * Free entries in the input FIFO. Software expectation: every batch of GP register writes is preceded by a poll until the value reaches the batch size; the thresholds used are 2, 3, 6, 9, 14, 20, 32, 40 and 100.
 */
/* in_fifo_space: r32, space rz, reset unknown */
#define RAD1_IN_FIFO_SPACE_OFFSET                    0x18u /* established */

/*
 * Words waiting in the output FIFO. Software expectation: polled until nonzero after a sync or a read-back, and drained to empty after a timeout.
 */
/* out_fifo_words: r32, space rz, reset unknown */
#define RAD1_OUT_FIFO_WORDS_OFFSET                   0x20u /* established */

/*
 * Error status. Software expectation: read before a read-back DMA and written back to clear it, and again after the transfer.
 */
/* error_flags: rw32, space rz, reset unknown */
#define RAD1_ERROR_FLAGS_OFFSET                      0x38u /* established */

/*
 * Video clock control. Software expectation: the driver reads it at attach and treats a nonzero value as the console already having initialised the chip, which skips the clock, memory and screen-clear steps; a zero value means a full initialisation. Start-up writes it with clock source 2 and a recovery time derived from the pixel clock.
 */
/* vclk_ctl: rw32, space rz, reset unknown */
#define RAD1_VCLK_CTL_OFFSET                         0x40u /* established */

/*
 * Aperture one control. Software expectation: written 0 at init.
 */
/* aperture_one: rw32, space rz, reset unknown */
#define RAD1_APERTURE_ONE_OFFSET                     0x50u /* established */

/*
 * Aperture two control. Software expectation: written at init with bit 9 (ROM access) set and nothing else, which is what exposes the board's flash for the settings sector.
 */
/* aperture_two: rw32, space rz, reset unknown */
#define RAD1_APERTURE_TWO_OFFSET                     0x58u /* established */

/*
 * DMA control. Software expectation: written 0x8 at init.
 */
/* dma_control: rw32, space rz, reset unknown */
#define RAD1_DMA_CONTROL_OFFSET                      0x60u /* established */

/*
 * Chip configuration. Software expectation: only read, by a diagnostic dump routine.
 */
/* chip_config: rw32, space rz, reset unknown */
#define RAD1_CHIP_CONFIG_OFFSET                      0x70u /* established */

/*
 * Output DMA address: the host (PCI) address a read-back is written to. Software expectation: set per chunk before the count.
 */
/* out_dma_address: rw32, space rz, reset unknown */
#define RAD1_OUT_DMA_ADDRESS_OFFSET                  0x80u /* established */

/*
 * Output DMA count in words; writing it starts the transfer. Software expectation: at most 0xffff words per write.
 */
/* out_dma_count: rw32, space rz, reset unknown */
#define RAD1_OUT_DMA_COUNT_OFFSET                    0x88u /* established */

/*
 * Bypass DMA host address. Software expectation: the source of a host-to-framebuffer transfer.
 */
/* by_dma_address: rw32, space rz, reset unknown */
#define RAD1_BY_DMA_ADDRESS_OFFSET                   0xa0u /* established */

/*
 * Bypass DMA source stride in bytes.
 */
/* by_dma_stride: rw32, space rz, reset unknown */
#define RAD1_BY_DMA_STRIDE_OFFSET                    0xb8u /* established */

/*
 * Bypass DMA destination in local memory, in pixels (or in pixel units of the format).
 */
/* by_dma_mem_address: rw32, space rz, reset unknown */
#define RAD1_BY_DMA_MEM_ADDRESS_OFFSET               0xc0u /* established */

/*
 * Bypass DMA size: width in bits 11 to 0, height from bit 16. Software expectation.
 */
/* by_dma_size: rw32, space rz, reset unknown */
#define RAD1_BY_DMA_SIZE_OFFSET                      0xc8u /* established */

/*
 * Bypass DMA byte mask. Software expectation: always written 0x000f000f (all lanes at both edges).
 */
/* by_dma_byte_mask: rw32, space rz, reset unknown */
#define RAD1_BY_DMA_BYTE_MASK_OFFSET                 0xd0u /* established */

/*
 * Bypass DMA control; the write starts the transfer. Software expectation: implicit mode, no patching, 32-, 16- or 8-bit source format, the pixel-partial-product fields of the current screen width, and GP restart.
 */
/* by_dma_control: rw32, space rz, reset unknown */
#define RAD1_BY_DMA_CONTROL_OFFSET                   0xd8u /* established */

/*
 * Memory type. Software expectation: written 0 (SGRAM).
 */
/* mem_control: rw32, space rz, reset unknown */
#define RAD1_MEM_CONTROL_OFFSET                      0x1040u /* established */

/*
 * Memory boot address (the SGRAM mode word). Software expectation: 0x20 for the 104c:3d07 chip and 0x30 for the 3d3d:0009 chip, written after the memory type.
 */
/* boot_address: rw32, space rz, reset unknown */
#define RAD1_BOOT_ADDRESS_OFFSET                     0x1080u /* established */

/*
 * Memory timing. Software expectation: 0xe6002021 for the 104c:3d07 chip and 0xe6012021 for the 3d3d:0009 chip, both with four banks.
 */
/* mem_config: rw32, space rz, reset unknown */
#define RAD1_MEM_CONFIG_OFFSET                       0x10c0u /* established */

/*
 * Plane write mask for bypass (host and DMA) writes. Software expectation: 0x00ffffff at init; the mask ioctl, rectangle writes and the screen clear change it and restore it.
 */
/* bypass_write_mask: rw32, space rz, reset unknown */
#define RAD1_BYPASS_WRITE_MASK_OFFSET                0x1100u /* established */

/*
 * Output FIFO read port. Software expectation: read to drain sync tags and read-back words.
 */
/* out_fifo: r32, space rz, reset unknown */
#define RAD1_OUT_FIFO_OFFSET                         0x2000u /* established */

/*
 * Screen base, in 64-bit units. Software expectation: 0.
 */
/* screen_base: rw32, space rz, reset unknown */
#define RAD1_SCREEN_BASE_OFFSET                      0x3000u /* established */

/*
 * Screen stride in 64-bit units: 640 for the two 1280-wide modes and 512 for 1024 wide.
 */
/* screen_stride: rw32, space rz, reset unknown */
#define RAD1_SCREEN_STRIDE_OFFSET                    0x3008u /* established */

/*
 * Horizontal total in 64-bit units, from the mode table's count halved.
 */
/* h_total: rw32, space rz, reset unknown */
#define RAD1_H_TOTAL_OFFSET                          0x3010u /* established */

/*
 * Horizontal gate end, 64-bit units.
 */
/* hg_end: rw32, space rz, reset unknown */
#define RAD1_HG_END_OFFSET                           0x3018u /* established */

/*
 * Horizontal blank end, 64-bit units.
 */
/* hb_end: rw32, space rz, reset unknown */
#define RAD1_HB_END_OFFSET                           0x3020u /* established */

/*
 * Horizontal sync start, 64-bit units.
 */
/* hs_start: rw32, space rz, reset unknown */
#define RAD1_HS_START_OFFSET                         0x3028u /* established */

/*
 * Horizontal sync end, 64-bit units.
 */
/* hs_end: rw32, space rz, reset unknown */
#define RAD1_HS_END_OFFSET                           0x3030u /* established */

/*
 * Vertical total in lines.
 */
/* v_total: rw32, space rz, reset unknown */
#define RAD1_V_TOTAL_OFFSET                          0x3038u /* established */

/*
 * Vertical blank end in lines.
 */
/* vb_end: rw32, space rz, reset unknown */
#define RAD1_VB_END_OFFSET                           0x3040u /* established */

/*
 * Vertical sync start in lines.
 */
/* vs_start: rw32, space rz, reset unknown */
#define RAD1_VS_START_OFFSET                         0x3048u /* established */

/*
 * Vertical sync end in lines.
 */
/* vs_end: rw32, space rz, reset unknown */
#define RAD1_VS_END_OFFSET                           0x3050u /* established */

/*
 * Video control. Software expectation: bit 0 enables refresh; the mode loader also sets blank, 64-bit data and active-high sync fields, then turns refresh off and on around the mode change.
 */
/* video_control: rw32, space rz, reset unknown */
#define RAD1_VIDEO_CONTROL_OFFSET                    0x3058u /* established */
#define RAD1_VIDEO_CONTROL_ENABLE_SHIFT              0 /* established */
#define RAD1_VIDEO_CONTROL_ENABLE_MASK               0x1u
#define RAD1_VIDEO_CONTROL_ENABLE_INPLACE            (RAD1_VIDEO_CONTROL_ENABLE_MASK << RAD1_VIDEO_CONTROL_ENABLE_SHIFT)

/*
 * Video FIFO control. Software expectation: written 0x0b07.
 */
/* fifo_control: rw32, space rz, reset unknown */
#define RAD1_FIFO_CONTROL_OFFSET                     0x3078u /* established */

/*
 * Right-eye screen base. Software expectation: written 0.
 */
/* screen_base_right: rw32, space rz, reset unknown */
#define RAD1_SCREEN_BASE_RIGHT_OFFSET                0x3080u /* established */

/*
 * Palette write address; also the index port of the Permedia 2 indexed registers. Software expectation: the palette load writes 0 here, then red, green and blue in turn to the data port for each of 256 entries.
 */
/* rd_palette_write_address: rw32, space rz, reset unknown */
#define RAD1_RD_PALETTE_WRITE_ADDRESS_OFFSET         0x4000u /* established */

/*
 * Palette data. Software expectation: three consecutive byte stores per entry.
 */
/* rd_palette_data: rw32, space rz, reset unknown */
#define RAD1_RD_PALETTE_DATA_OFFSET                  0x4008u /* established */

/*
 * Pixel read mask. Software expectation: written 0xff.
 */
/* rd_pixel_mask: rw32, space rz, reset unknown */
#define RAD1_RD_PIXEL_MASK_OFFSET                    0x4010u /* established */

/*
 * Palette read address. Software expectation: written 0 before a palette load.
 */
/* rd_palette_read_address: rw32, space rz, reset unknown */
#define RAD1_RD_PALETTE_READ_ADDRESS_OFFSET          0x4018u /* established */

/*
 * SVGA control (name ours). Software expectation: written 0x40 before the mode is set, to turn the legacy VGA core off.
 */
/* vga_control: rw32, space rz, reset unknown */
#define RAD1_VGA_CONTROL_OFFSET                      0x63c4u /* inferred */

/*
 * Start X of the dominant edge, 16.16 signed; also the X of a point.
 */
/* start_x_dom: rw32, space rz, reset unknown */
#define RAD1_START_X_DOM_OFFSET                      0x8000u /* established */

/*
 * Dominant edge X step, 16.16 signed. Written 0.
 */
/* d_x_dom: rw32, space rz, reset unknown */
#define RAD1_D_X_DOM_OFFSET                          0x8008u /* established */

/*
 * Start X of the subordinate edge, 16.16 signed; the screen clear sets it to the width.
 */
/* start_x_sub: rw32, space rz, reset unknown */
#define RAD1_START_X_SUB_OFFSET                      0x8010u /* established */

/*
 * Subordinate edge X step, 16.16 signed. Written 0.
 */
/* d_x_sub: rw32, space rz, reset unknown */
#define RAD1_D_X_SUB_OFFSET                          0x8018u /* established */

/*
 * Start Y, 16.16 signed; also the Y of a point.
 */
/* start_y: rw32, space rz, reset unknown */
#define RAD1_START_Y_OFFSET                          0x8020u /* established */

/*
 * Y step, 16.16 signed. Written 0x10000 at init.
 */
/* d_y: rw32, space rz, reset unknown */
#define RAD1_D_Y_OFFSET                              0x8028u /* established */

/*
 * Scanline count of a trapezoid. The screen clear writes the mode height.
 */
/* count: rw32, space rz, reset unknown */
#define RAD1_COUNT_OFFSET                            0x8030u /* established */

/*
 * Render command; the write starts the operation. Software expectation: primitive in bits 7 to 6 (trapezoid, point, rectangle), fast fill bit 3, texture enable bit 13, increase X bit 21 and increase Y bit 22 are the bits used.
 */
/* render: rw32, space rz, reset unknown */
#define RAD1_RENDER_OFFSET                           0x8038u /* established */

/*
 * Wait for completion; written 0 after a render that the driver must see finished.
 */
/* wait_for_completion: rw32, space rz, reset unknown */
#define RAD1_WAIT_FOR_COMPLETION_OFFSET              0x8088u /* established */

/*
 * Rasterizer mode. Written 0.
 */
/* rasterizer_mode: rw32, space rz, reset unknown */
#define RAD1_RASTERIZER_MODE_OFFSET                  0x80a0u /* established */

/*
 * Rectangle origin: X in the low 12 bits, Y from bit 16.
 */
/* rectangle_origin: rw32, space rz, reset unknown */
#define RAD1_RECTANGLE_ORIGIN_OFFSET                 0x80d0u /* established */

/*
 * Rectangle size: width in the low bits, height from bit 16.
 */
/* rectangle_size: rw32, space rz, reset unknown */
#define RAD1_RECTANGLE_SIZE_OFFSET                   0x80d8u /* established */

/*
 * Packed data limits; the X end is set to width minus one.
 */
/* packed_data_limits: rw32, space rz, reset unknown */
#define RAD1_PACKED_DATA_LIMITS_OFFSET               0x8150u /* established */

/*
 * Scissor mode. Written 0.
 */
/* scissor_mode: rw32, space rz, reset unknown */
#define RAD1_SCISSOR_MODE_OFFSET                     0x8180u /* established */

/*
 * Screen size: width in bits 10 to 0, height from bit 16.
 */
/* screen_size: rw32, space rz, reset unknown */
#define RAD1_SCREEN_SIZE_OFFSET                      0x8198u /* established */

/*
 * Area stipple mode. Written 0.
 */
/* area_stipple_mode: rw32, space rz, reset unknown */
#define RAD1_AREA_STIPPLE_MODE_OFFSET                0x81a0u /* established */

/*
 * Window origin. Written 0.
 */
/* window_origin: rw32, space rz, reset unknown */
#define RAD1_WINDOW_ORIGIN_OFFSET                    0x81c8u /* established */

/*
 * Texture address mode. Written 1 (enable) for the format-converting copy and 0 otherwise.
 */
/* texture_address_mode: rw32, space rz, reset unknown */
#define RAD1_TEXTURE_ADDRESS_MODE_OFFSET             0x8380u /* established */

/*
 * Texture S start.
 */
/* s_start: rw32, space rz, reset unknown */
#define RAD1_S_START_OFFSET                          0x8388u /* established */

/*
 * Texture S step per pixel; written 1.0 in 12.18 fixed point at init.
 */
/* d_s_dx: rw32, space rz, reset unknown */
#define RAD1_D_S_DX_OFFSET                           0x8390u /* established */

/*
 * Texture S step per scanline.
 */
/* d_s_dy_dom: rw32, space rz, reset unknown */
#define RAD1_D_S_DY_DOM_OFFSET                       0x8398u /* established */

/*
 * Texture T start.
 */
/* t_start: rw32, space rz, reset unknown */
#define RAD1_T_START_OFFSET                          0x83a0u /* established */

/*
 * Texture T step per pixel.
 */
/* d_t_dx: rw32, space rz, reset unknown */
#define RAD1_D_T_DX_OFFSET                           0x83a8u /* established */

/*
 * Texture T step per scanline; 1.0 in the format-converting copy.
 */
/* d_t_dy_dom: rw32, space rz, reset unknown */
#define RAD1_D_T_DY_DOM_OFFSET                       0x83b0u /* established */

/*
 * Texel look-up table index; written 0 before a table load.
 */
/* texel_lut_index: rw32, space rz, reset unknown */
#define RAD1_TEXEL_LUT_INDEX_OFFSET                  0x84c0u /* established */

/*
 * Texel look-up table data, one 32-bit colour per store.
 */
/* texel_lut_data: rw32, space rz, reset unknown */
#define RAD1_TEXEL_LUT_DATA_OFFSET                   0x84c8u /* established */

/*
 * Texel look-up table address in local memory; set to 256 words below the end of the 8 MiB memory.
 */
/* texel_lut_address: rw32, space rz, reset unknown */
#define RAD1_TEXEL_LUT_ADDRESS_OFFSET                0x84d0u /* established */

/*
 * Texture base address: where the format-converting copy reads its source, in local memory.
 */
/* texture_base_address: rw32, space rz, reset unknown */
#define RAD1_TEXTURE_BASE_ADDRESS_OFFSET             0x8580u /* established */

/*
 * Texture map format: texel size and the width partial products.
 */
/* texture_map_format: rw32, space rz, reset unknown */
#define RAD1_TEXTURE_MAP_FORMAT_OFFSET               0x8588u /* established */

/*
 * Texture data format. Written 0 at init.
 */
/* texture_data_format: rw32, space rz, reset unknown */
#define RAD1_TEXTURE_DATA_FORMAT_OFFSET              0x8590u /* established */

/*
 * Texel 0. Written 0 at init.
 */
/* texel0: rw32, space rz, reset unknown */
#define RAD1_TEXEL0_OFFSET                           0x8600u /* established */

/*
 * Texture read mode.
 */
/* texture_read_mode: rw32, space rz, reset unknown */
#define RAD1_TEXTURE_READ_MODE_OFFSET                0x8670u /* established */

/*
 * Texel look-up table mode; 1 enables it for 8-bit colour-index copies.
 */
/* texel_lut_mode: rw32, space rz, reset unknown */
#define RAD1_TEXEL_LUT_MODE_OFFSET                   0x8678u /* established */

/*
 * Texture colour mode.
 */
/* texture_color_mode: rw32, space rz, reset unknown */
#define RAD1_TEXTURE_COLOR_MODE_OFFSET               0x8680u /* established */

/*
 * Fog mode. Written 0.
 */
/* fog_mode: rw32, space rz, reset unknown */
#define RAD1_FOG_MODE_OFFSET                         0x8690u /* established */

/*
 * Colour DDA red start; used only by the start-up screen fill.
 */
/* r_start: rw32, space rz, reset unknown */
#define RAD1_R_START_OFFSET                          0x8780u /* established */

/*
 * Colour DDA red step per pixel.
 */
/* d_r_dx: rw32, space rz, reset unknown */
#define RAD1_D_R_DX_OFFSET                           0x8788u /* established */

/*
 * Colour DDA red step per scanline.
 */
/* d_r_dy_dom: rw32, space rz, reset unknown */
#define RAD1_D_R_DY_DOM_OFFSET                       0x8790u /* established */

/*
 * Colour DDA green start.
 */
/* g_start: rw32, space rz, reset unknown */
#define RAD1_G_START_OFFSET                          0x8798u /* established */

/*
 * Colour DDA green step per pixel.
 */
/* d_g_dx: rw32, space rz, reset unknown */
#define RAD1_D_G_DX_OFFSET                           0x87a0u /* established */

/*
 * Colour DDA green step per scanline.
 */
/* d_g_dy_dom: rw32, space rz, reset unknown */
#define RAD1_D_G_DY_DOM_OFFSET                       0x87a8u /* established */

/*
 * Colour DDA blue start.
 */
/* b_start: rw32, space rz, reset unknown */
#define RAD1_B_START_OFFSET                          0x87b0u /* established */

/*
 * Colour DDA blue step per pixel.
 */
/* d_b_dx: rw32, space rz, reset unknown */
#define RAD1_D_B_DX_OFFSET                           0x87b8u /* established */

/*
 * Colour DDA blue step per scanline.
 */
/* d_b_dy_dom: rw32, space rz, reset unknown */
#define RAD1_D_B_DY_DOM_OFFSET                       0x87c0u /* established */

/*
 * Colour DDA alpha start.
 */
/* a_start: rw32, space rz, reset unknown */
#define RAD1_A_START_OFFSET                          0x87c8u /* established */

/*
 * Colour DDA mode; enabled with Gouraud shading only for the start-up screen fill.
 */
/* color_dda_mode: rw32, space rz, reset unknown */
#define RAD1_COLOR_DDA_MODE_OFFSET                   0x87e0u /* established */

/*
 * Alpha blend mode. Written 0 at init and set to the format operation for a read-back.
 */
/* alpha_blend_mode: rw32, space rz, reset unknown */
#define RAD1_ALPHA_BLEND_MODE_OFFSET                 0x8810u /* established */

/*
 * Dither mode. Written with the unit enable bit set at init.
 */
/* dither_mode: rw32, space rz, reset unknown */
#define RAD1_DITHER_MODE_OFFSET                      0x8818u /* established */

/*
 * Framebuffer software write mask. Written all ones at init; the rectangle fill and copy paths put the caller's mask here.
 */
/* fb_software_write_mask: rw32, space rz, reset unknown */
#define RAD1_FB_SOFTWARE_WRITE_MASK_OFFSET           0x8820u /* established */

/*
 * Logical operation mode: enable, operation, and the constant-write-data bit that makes fills use the write-data register. Software expectation.
 */
/* logical_op_mode: rw32, space rz, reset unknown */
#define RAD1_LOGICAL_OP_MODE_OFFSET                  0x8828u /* established */

/*
 * Constant framebuffer write data: the colour of a fill or a textport pixel.
 */
/* fb_write_data: rw32, space rz, reset unknown */
#define RAD1_FB_WRITE_DATA_OFFSET                    0x8830u /* established */

/*
 * Local buffer read mode. Written 0 at init.
 */
/* lb_read_mode: rw32, space rz, reset unknown */
#define RAD1_LB_READ_MODE_OFFSET                     0x8880u /* established */

/*
 * Local buffer window base. Written 0.
 */
/* lb_window_base: rw32, space rz, reset unknown */
#define RAD1_LB_WINDOW_BASE_OFFSET                   0x88b8u /* established */

/*
 * Local buffer write mode. Written 0.
 */
/* lb_write_mode: rw32, space rz, reset unknown */
#define RAD1_LB_WRITE_MODE_OFFSET                    0x88c0u /* established */

/*
 * Local buffer write format. Written 0.
 */
/* lb_write_format: rw32, space rz, reset unknown */
#define RAD1_LB_WRITE_FORMAT_OFFSET                  0x88c8u /* established */

/*
 * Window: the local buffer update fields. Written with the update disabled.
 */
/* window: rw32, space rz, reset unknown */
#define RAD1_WINDOW_OFFSET                           0x8980u /* established */

/*
 * Stencil mode. Written 0.
 */
/* stencil_mode: rw32, space rz, reset unknown */
#define RAD1_STENCIL_MODE_OFFSET                     0x8988u /* established */

/*
 * Depth mode. Written 0.
 */
/* depth_mode: rw32, space rz, reset unknown */
#define RAD1_DEPTH_MODE_OFFSET                       0x89a0u /* established */

/*
 * Framebuffer read mode: source and destination read enables, packed data, relative offset and the screen-width partial products.
 */
/* fb_read_mode: rw32, space rz, reset unknown */
#define RAD1_FB_READ_MODE_OFFSET                     0x8a80u /* established */

/*
 * Framebuffer pixel offset. Written 0.
 */
/* fb_pixel_offset: rw32, space rz, reset unknown */
#define RAD1_FB_PIXEL_OFFSET_OFFSET                  0x8a90u /* established */

/*
 * Framebuffer window base. Written 0.
 */
/* fb_window_base: rw32, space rz, reset unknown */
#define RAD1_FB_WINDOW_BASE_OFFSET                   0x8ab0u /* established */

/*
 * Framebuffer write mode: write enable, and the upload-to-host bit for a read-back.
 */
/* fb_write_mode: rw32, space rz, reset unknown */
#define RAD1_FB_WRITE_MODE_OFFSET                    0x8ab8u /* established */

/*
 * Framebuffer hardware write mask. Written all ones at init and 0x00ffffff afterwards.
 */
/* fb_hard_write_mask: rw32, space rz, reset unknown */
#define RAD1_FB_HARD_WRITE_MASK_OFFSET               0x8ac0u /* established */

/*
 * Block colour for a fast fill.
 */
/* fb_block_color: rw32, space rz, reset unknown */
#define RAD1_FB_BLOCK_COLOR_OFFSET                   0x8ac8u /* established */

/*
 * Framebuffer read pixel size. Written 2 (32 bits).
 */
/* fb_read_pixel: rw32, space rz, reset unknown */
#define RAD1_FB_READ_PIXEL_OFFSET                    0x8ad0u /* established */

/*
 * Filter mode: which output tags reach the host. Synchronisation data for a sync, colour data for a read-back.
 */
/* filter_mode: rw32, space rz, reset unknown */
#define RAD1_FILTER_MODE_OFFSET                      0x8c00u /* established */

/*
 * Statistic mode. Written 0 at init.
 */
/* statistic_mode: rw32, space rz, reset unknown */
#define RAD1_STATISTIC_MODE_OFFSET                   0x8c08u /* established */

/*
 * Sync: writing a tag with bit 31 set raises the sync interrupt when the pipeline reaches it, and the tag appears in the output FIFO.
 */
/* sync: rw32, space rz, reset unknown */
#define RAD1_SYNC_OFFSET                             0x8c40u /* established */

/*
 * Framebuffer source base. Written 0 at init.
 */
/* fb_source_base: rw32, space rz, reset unknown */
#define RAD1_FB_SOURCE_BASE_OFFSET                   0x8d80u /* established */

/*
 * Framebuffer source delta: the Y and X offset of a screen-to-screen copy's source, negated.
 */
/* fb_source_delta: rw32, space rz, reset unknown */
#define RAD1_FB_SOURCE_DELTA_OFFSET                  0x8d88u /* established */

/*
 * YUV mode. Written 0 at init.
 */
/* yuv_mode: rw32, space rz, reset unknown */
#define RAD1_YUV_MODE_OFFSET                         0x8f00u /* established */

/*
 * Delta mode. Written 0 at init.
 */
/* delta_mode: rw32, space rz, reset unknown */
#define RAD1_DELTA_MODE_OFFSET                       0x9300u /* established */

/*
 * Cursor colour address. Software expectation: written 1 before the cursor colours.
 */
/* rd_cursor_color_address: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_COLOR_ADDRESS_OFFSET          0x4020u /* established */

/*
 * Cursor colour data: three bytes background then three bytes foreground.
 */
/* rd_cursor_color_data: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_COLOR_DATA_OFFSET             0x4028u /* established */

/*
 * Data port of the indexed registers, selected through the palette write address. Software expectation: read to poll the PLL lock bits.
 */
/* rd_indexed_data: rw32, space rz_p2, reset unknown */
#define RAD1_RD_INDEXED_DATA_OFFSET                  0x4050u /* established */

/*
 * Cursor pattern RAM data port.
 */
/* rd_cursor_ram_data: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_RAM_DATA_OFFSET               0x4058u /* established */

/*
 * Cursor X, low byte.
 */
/* rd_cursor_x_low: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_X_LOW_OFFSET                  0x4060u /* established */

/*
 * Cursor X, high byte.
 */
/* rd_cursor_x_high: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_X_HIGH_OFFSET                 0x4068u /* established */

/*
 * Cursor Y, low byte.
 */
/* rd_cursor_y_low: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_Y_LOW_OFFSET                  0x4070u /* established */

/*
 * Cursor Y, high byte.
 */
/* rd_cursor_y_high: rw32, space rz_p2, reset unknown */
#define RAD1_RD_CURSOR_Y_HIGH_OFFSET                 0x4078u /* established */

/*
 * Index, low byte. Software expectation: written before each access to an indexed register.
 */
/* rd_index_low_2v: rw32, space rz_p2v, reset unknown */
#define RAD1_RD_INDEX_LOW_2V_OFFSET                  0x4020u /* established */

/*
 * Index, high byte.
 */
/* rd_index_high_2v: rw32, space rz_p2v, reset unknown */
#define RAD1_RD_INDEX_HIGH_2V_OFFSET                 0x4028u /* established */

/*
 * Indexed data port. Software expectation: after a cursor palette or pattern index is set, consecutive stores fill the table, so the index auto-increments.
 */
/* rd_indexed_data_2v: rw32, space rz_p2v, reset unknown */
#define RAD1_RD_INDEXED_DATA_2V_OFFSET               0x4030u /* established */

/*
 * Index control. Software expectation: written 1 at init to turn auto-increment on.
 */
/* rd_index_control_2v: rw32, space rz_p2v, reset unknown */
#define RAD1_RD_INDEX_CONTROL_2V_OFFSET              0x4038u /* established */

#endif /* RAD1_GEN_H */
