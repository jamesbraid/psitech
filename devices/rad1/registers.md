<!-- generated from devices/rad1/registers.toml by defs-gen - do not edit, change the source -->
<!-- SPDX-License-Identifier: BSD-3-Clause -->
<!-- defs-gen 2 -->
<!-- input sha256 6d6effab60d3ecf0befbc61265bbab43ca515e793be20c3bb700c2f97c1a0b10 -->

# RAD1 graphics head registers

Registers of the PsiTech RAD1 PCI graphics board as the stock IRIX 6.5 kernel driver and the IO6 PROM textport use them. The board's chip is a TI TVP4020 (Permedia 2) or a 3Dlabs Permedia 2V, so every register here is a chip register: Region Zero (the 128 KiB register region) and the RAMDAC registers the chip holds behind its index ports. Names come from public X.Org and Linux drivers for those chips; the offsets are confirmed against the shipped objects. Grades here are the three the definition format allows: established covers what a public source or the shipped binaries state outright (the doc says which), inferred covers inferences and model approximations. The finer ratings are in devices/rad1/README.md.

Unit `rad1`, macro prefix `RAD1`.

Every item has a grade: established, inferred or unknown. A grade says how the item was derived from its source; it does not claim the item was measured on silicon.

## Address spaces

| Space | Offset unit | Description |
|---|---|---|
| rz | byte |  |
| rz_p2 | byte |  |
| rz_p2v | byte |  |
| p2dac | byte |  |
| p2vdac | byte |  |

## Registers

| Register | Offset | Access | Width | Count | Space | Reset | Grade | Source |
|---|---|---|---|---|---|---|---|---|
| `rd_cursor_control` | 0x6 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_color_mode` | 0x18 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_mode_control` | 0x19 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_misc_control` | 0x1e | rw | 8 |  | p2dac | unknown | established |  |
| `rd_pixel_clock_c1` | 0x26 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_pixel_clock_c2` | 0x27 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_pixel_clock_c3` | 0x28 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_pixel_clock_status` | 0x29 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_memory_clock_1` | 0x30 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_memory_clock_2` | 0x31 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_memory_clock_3` | 0x32 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_memory_clock_status` | 0x33 | rw | 8 |  | p2dac | unknown | established |  |
| `rd_misc_control_2v` | 0x0 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_sync_control_2v` | 0x1 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_dac_control_2v` | 0x2 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_pixel_size_2v` | 0x3 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_color_format_2v` | 0x4 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_mode_2v` | 0x5 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_control_2v` | 0x6 | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_cursor_x_low_2v` | 0x7 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_x_high_2v` | 0x8 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_y_low_2v` | 0x9 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_y_high_2v` | 0xa | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_hot_spot_x_2v` | 0xb | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_hot_spot_y_2v` | 0xc | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_overlay_key_2v` | 0xd | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_pan_2v` | 0xe | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_dclk_control_2v` | 0x200 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_dclk2_prescale_2v` | 0x207 | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_dclk2_feedback_scale_2v` | 0x208 | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_dclk2_postscale_2v` | 0x209 | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_dclk3_prescale_2v` | 0x20a | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_dclk3_feedback_scale_2v` | 0x20b | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_dclk3_postscale_2v` | 0x20c | rw | 8 |  | p2vdac | unknown | inferred |  |
| `rd_mclk_control_2v` | 0x20d | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_mclk_prescale_2v` | 0x20e | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_mclk_feedback_scale_2v` | 0x20f | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_mclk_postscale_2v` | 0x210 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_palette_2v` | 0x303 | rw | 8 |  | p2vdac | unknown | established |  |
| `rd_cursor_pattern_2v` | 0x400 | rw | 8 |  | p2vdac | unknown | established |  |
| `reset_status` | 0x0 | rw | 32 |  | rz | unknown | established |  |
| `int_enable` | 0x8 | rw | 32 |  | rz | unknown | established |  |
| `int_flags` | 0x10 | rw | 32 |  | rz | unknown | established |  |
| `in_fifo_space` | 0x18 | r | 32 |  | rz | unknown | established |  |
| `out_fifo_words` | 0x20 | r | 32 |  | rz | unknown | established |  |
| `error_flags` | 0x38 | rw | 32 |  | rz | unknown | established |  |
| `vclk_ctl` | 0x40 | rw | 32 |  | rz | unknown | established |  |
| `aperture_one` | 0x50 | rw | 32 |  | rz | unknown | established |  |
| `aperture_two` | 0x58 | rw | 32 |  | rz | unknown | established |  |
| `dma_control` | 0x60 | rw | 32 |  | rz | unknown | established |  |
| `chip_config` | 0x70 | rw | 32 |  | rz | unknown | established |  |
| `out_dma_address` | 0x80 | rw | 32 |  | rz | unknown | established |  |
| `out_dma_count` | 0x88 | rw | 32 |  | rz | unknown | established |  |
| `by_dma_address` | 0xa0 | rw | 32 |  | rz | unknown | established |  |
| `by_dma_stride` | 0xb8 | rw | 32 |  | rz | unknown | established |  |
| `by_dma_mem_address` | 0xc0 | rw | 32 |  | rz | unknown | established |  |
| `by_dma_size` | 0xc8 | rw | 32 |  | rz | unknown | established |  |
| `by_dma_byte_mask` | 0xd0 | rw | 32 |  | rz | unknown | established |  |
| `by_dma_control` | 0xd8 | rw | 32 |  | rz | unknown | established |  |
| `mem_control` | 0x1040 | rw | 32 |  | rz | unknown | established |  |
| `boot_address` | 0x1080 | rw | 32 |  | rz | unknown | established |  |
| `mem_config` | 0x10c0 | rw | 32 |  | rz | unknown | established |  |
| `bypass_write_mask` | 0x1100 | rw | 32 |  | rz | unknown | established |  |
| `out_fifo` | 0x2000 | r | 32 |  | rz | unknown | established |  |
| `screen_base` | 0x3000 | rw | 32 |  | rz | unknown | established |  |
| `screen_stride` | 0x3008 | rw | 32 |  | rz | unknown | established |  |
| `h_total` | 0x3010 | rw | 32 |  | rz | unknown | established |  |
| `hg_end` | 0x3018 | rw | 32 |  | rz | unknown | established |  |
| `hb_end` | 0x3020 | rw | 32 |  | rz | unknown | established |  |
| `hs_start` | 0x3028 | rw | 32 |  | rz | unknown | established |  |
| `hs_end` | 0x3030 | rw | 32 |  | rz | unknown | established |  |
| `v_total` | 0x3038 | rw | 32 |  | rz | unknown | established |  |
| `vb_end` | 0x3040 | rw | 32 |  | rz | unknown | established |  |
| `vs_start` | 0x3048 | rw | 32 |  | rz | unknown | established |  |
| `vs_end` | 0x3050 | rw | 32 |  | rz | unknown | established |  |
| `video_control` | 0x3058 | rw | 32 |  | rz | unknown | established |  |
| `fifo_control` | 0x3078 | rw | 32 |  | rz | unknown | established |  |
| `screen_base_right` | 0x3080 | rw | 32 |  | rz | unknown | established |  |
| `rd_palette_write_address` | 0x4000 | rw | 32 |  | rz | unknown | established |  |
| `rd_palette_data` | 0x4008 | rw | 32 |  | rz | unknown | established |  |
| `rd_pixel_mask` | 0x4010 | rw | 32 |  | rz | unknown | established |  |
| `rd_palette_read_address` | 0x4018 | rw | 32 |  | rz | unknown | established |  |
| `vga_control` | 0x63c4 | rw | 32 |  | rz | unknown | inferred |  |
| `start_x_dom` | 0x8000 | rw | 32 |  | rz | unknown | established |  |
| `d_x_dom` | 0x8008 | rw | 32 |  | rz | unknown | established |  |
| `start_x_sub` | 0x8010 | rw | 32 |  | rz | unknown | established |  |
| `d_x_sub` | 0x8018 | rw | 32 |  | rz | unknown | established |  |
| `start_y` | 0x8020 | rw | 32 |  | rz | unknown | established |  |
| `d_y` | 0x8028 | rw | 32 |  | rz | unknown | established |  |
| `count` | 0x8030 | rw | 32 |  | rz | unknown | established |  |
| `render` | 0x8038 | rw | 32 |  | rz | unknown | established |  |
| `wait_for_completion` | 0x8088 | rw | 32 |  | rz | unknown | established |  |
| `rasterizer_mode` | 0x80a0 | rw | 32 |  | rz | unknown | established |  |
| `rectangle_origin` | 0x80d0 | rw | 32 |  | rz | unknown | established |  |
| `rectangle_size` | 0x80d8 | rw | 32 |  | rz | unknown | established |  |
| `packed_data_limits` | 0x8150 | rw | 32 |  | rz | unknown | established |  |
| `scissor_mode` | 0x8180 | rw | 32 |  | rz | unknown | established |  |
| `screen_size` | 0x8198 | rw | 32 |  | rz | unknown | established |  |
| `area_stipple_mode` | 0x81a0 | rw | 32 |  | rz | unknown | established |  |
| `window_origin` | 0x81c8 | rw | 32 |  | rz | unknown | established |  |
| `texture_address_mode` | 0x8380 | rw | 32 |  | rz | unknown | established |  |
| `s_start` | 0x8388 | rw | 32 |  | rz | unknown | established |  |
| `d_s_dx` | 0x8390 | rw | 32 |  | rz | unknown | established |  |
| `d_s_dy_dom` | 0x8398 | rw | 32 |  | rz | unknown | established |  |
| `t_start` | 0x83a0 | rw | 32 |  | rz | unknown | established |  |
| `d_t_dx` | 0x83a8 | rw | 32 |  | rz | unknown | established |  |
| `d_t_dy_dom` | 0x83b0 | rw | 32 |  | rz | unknown | established |  |
| `texel_lut_index` | 0x84c0 | rw | 32 |  | rz | unknown | established |  |
| `texel_lut_data` | 0x84c8 | rw | 32 |  | rz | unknown | established |  |
| `texel_lut_address` | 0x84d0 | rw | 32 |  | rz | unknown | established |  |
| `texture_base_address` | 0x8580 | rw | 32 |  | rz | unknown | established |  |
| `texture_map_format` | 0x8588 | rw | 32 |  | rz | unknown | established |  |
| `texture_data_format` | 0x8590 | rw | 32 |  | rz | unknown | established |  |
| `texel0` | 0x8600 | rw | 32 |  | rz | unknown | established |  |
| `texture_read_mode` | 0x8670 | rw | 32 |  | rz | unknown | established |  |
| `texel_lut_mode` | 0x8678 | rw | 32 |  | rz | unknown | established |  |
| `texture_color_mode` | 0x8680 | rw | 32 |  | rz | unknown | established |  |
| `fog_mode` | 0x8690 | rw | 32 |  | rz | unknown | established |  |
| `r_start` | 0x8780 | rw | 32 |  | rz | unknown | established |  |
| `d_r_dx` | 0x8788 | rw | 32 |  | rz | unknown | established |  |
| `d_r_dy_dom` | 0x8790 | rw | 32 |  | rz | unknown | established |  |
| `g_start` | 0x8798 | rw | 32 |  | rz | unknown | established |  |
| `d_g_dx` | 0x87a0 | rw | 32 |  | rz | unknown | established |  |
| `d_g_dy_dom` | 0x87a8 | rw | 32 |  | rz | unknown | established |  |
| `b_start` | 0x87b0 | rw | 32 |  | rz | unknown | established |  |
| `d_b_dx` | 0x87b8 | rw | 32 |  | rz | unknown | established |  |
| `d_b_dy_dom` | 0x87c0 | rw | 32 |  | rz | unknown | established |  |
| `a_start` | 0x87c8 | rw | 32 |  | rz | unknown | established |  |
| `color_dda_mode` | 0x87e0 | rw | 32 |  | rz | unknown | established |  |
| `alpha_blend_mode` | 0x8810 | rw | 32 |  | rz | unknown | established |  |
| `dither_mode` | 0x8818 | rw | 32 |  | rz | unknown | established |  |
| `fb_software_write_mask` | 0x8820 | rw | 32 |  | rz | unknown | established |  |
| `logical_op_mode` | 0x8828 | rw | 32 |  | rz | unknown | established |  |
| `fb_write_data` | 0x8830 | rw | 32 |  | rz | unknown | established |  |
| `lb_read_mode` | 0x8880 | rw | 32 |  | rz | unknown | established |  |
| `lb_window_base` | 0x88b8 | rw | 32 |  | rz | unknown | established |  |
| `lb_write_mode` | 0x88c0 | rw | 32 |  | rz | unknown | established |  |
| `lb_write_format` | 0x88c8 | rw | 32 |  | rz | unknown | established |  |
| `window` | 0x8980 | rw | 32 |  | rz | unknown | established |  |
| `stencil_mode` | 0x8988 | rw | 32 |  | rz | unknown | established |  |
| `depth_mode` | 0x89a0 | rw | 32 |  | rz | unknown | established |  |
| `fb_read_mode` | 0x8a80 | rw | 32 |  | rz | unknown | established |  |
| `fb_pixel_offset` | 0x8a90 | rw | 32 |  | rz | unknown | established |  |
| `fb_window_base` | 0x8ab0 | rw | 32 |  | rz | unknown | established |  |
| `fb_write_mode` | 0x8ab8 | rw | 32 |  | rz | unknown | established |  |
| `fb_hard_write_mask` | 0x8ac0 | rw | 32 |  | rz | unknown | established |  |
| `fb_block_color` | 0x8ac8 | rw | 32 |  | rz | unknown | established |  |
| `fb_read_pixel` | 0x8ad0 | rw | 32 |  | rz | unknown | established |  |
| `filter_mode` | 0x8c00 | rw | 32 |  | rz | unknown | established |  |
| `statistic_mode` | 0x8c08 | rw | 32 |  | rz | unknown | established |  |
| `sync` | 0x8c40 | rw | 32 |  | rz | unknown | established |  |
| `fb_source_base` | 0x8d80 | rw | 32 |  | rz | unknown | established |  |
| `fb_source_delta` | 0x8d88 | rw | 32 |  | rz | unknown | established |  |
| `yuv_mode` | 0x8f00 | rw | 32 |  | rz | unknown | established |  |
| `delta_mode` | 0x9300 | rw | 32 |  | rz | unknown | established |  |
| `rd_cursor_color_address` | 0x4020 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_cursor_color_data` | 0x4028 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_indexed_data` | 0x4050 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_cursor_ram_data` | 0x4058 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_cursor_x_low` | 0x4060 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_cursor_x_high` | 0x4068 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_cursor_y_low` | 0x4070 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_cursor_y_high` | 0x4078 | rw | 32 |  | rz_p2 | unknown | established |  |
| `rd_index_low_2v` | 0x4020 | rw | 32 |  | rz_p2v | unknown | established |  |
| `rd_index_high_2v` | 0x4028 | rw | 32 |  | rz_p2v | unknown | established |  |
| `rd_indexed_data_2v` | 0x4030 | rw | 32 |  | rz_p2v | unknown | established |  |
| `rd_index_control_2v` | 0x4038 | rw | 32 |  | rz_p2v | unknown | established |  |

### Register `rd_cursor_control`

Cursor control: 64x64 size and the cursor mode. Software expectation.

### Register `rd_color_mode`

Colour mode: 8888 pixel format with GUI, RGB and true colour set at init.

### Register `rd_mode_control`

Mode control. Written 0.

### Register `rd_misc_control`

Misc control: 8-bit palette, sync polarities and sync on green.

### Register `rd_pixel_clock_c1`

Pixel clock C, feedback (M).

### Register `rd_pixel_clock_c2`

Pixel clock C, prescale (N).

### Register `rd_pixel_clock_c3`

Pixel clock C, postscale (P) with the enable bit (bit 3). Written 0 first to stop the PLL.

### Register `rd_pixel_clock_status`

Pixel clock status; bit 4 is the lock flag.

### Register `rd_memory_clock_1`

Memory clock, feedback (M).

### Register `rd_memory_clock_2`

Memory clock, prescale (N).

### Register `rd_memory_clock_3`

Memory clock, postscale (P) with the enable bit. Written 6 first to stop the PLL.

### Register `rd_memory_clock_status`

Memory clock status; bit 4 is the lock flag.

### Register `rd_misc_control_2v`

Misc control: high colour resolution, direct colour and overlay set at init.

### Register `rd_sync_control_2v`

Sync control: horizontal and vertical polarity at the pin. Software expectation.

### Register `rd_dac_control_2v`

DAC control: blank pedestal at init; the textport blank sets and clears the low-power bit.

### Register `rd_pixel_size_2v`

Pixel size: 2 (32 bits) at init.

### Register `rd_color_format_2v`

Colour format: RGB and 8888 at init.

### Register `rd_cursor_mode_2v`

Cursor mode: format (64x64), type and enable. The kernel driver turns the cursor on and off through this register.

### Register `rd_cursor_control_2v`

Cursor control. Written 0 at init.

### Register `rd_cursor_x_low_2v`

Cursor X, low byte.

### Register `rd_cursor_x_high_2v`

Cursor X, high byte.

### Register `rd_cursor_y_low_2v`

Cursor Y, low byte.

### Register `rd_cursor_y_high_2v`

Cursor Y, high byte.

### Register `rd_cursor_hot_spot_x_2v`

Cursor hot spot X, 6 bits.

### Register `rd_cursor_hot_spot_y_2v`

Cursor hot spot Y, 6 bits.

### Register `rd_overlay_key_2v`

Overlay key. Written 0 at init.

### Register `rd_pan_2v`

Pan. Written 0 at init.

### Register `rd_dclk_control_2v`

Pixel clock PLL control: bit 0 enable, bit 1 locked.

### Register `rd_dclk2_prescale_2v`

Pixel clock set 2 prescale (N). The mode loader programs sets 2 and 3 alike; the clock select picks set C.

### Register `rd_dclk2_feedback_scale_2v`

Pixel clock set 2 feedback (M).

### Register `rd_dclk2_postscale_2v`

Pixel clock set 2 postscale (P).

### Register `rd_dclk3_prescale_2v`

Pixel clock set 3 prescale (N).

### Register `rd_dclk3_feedback_scale_2v`

Pixel clock set 3 feedback (M).

### Register `rd_dclk3_postscale_2v`

Pixel clock set 3 postscale (P).

### Register `rd_mclk_control_2v`

Memory clock PLL control: bit 0 enable, bit 1 locked.

### Register `rd_mclk_prescale_2v`

Memory clock prescale (N): 11.

### Register `rd_mclk_feedback_scale_2v`

Memory clock feedback (M): 128.

### Register `rd_mclk_postscale_2v`

Memory clock postscale (P): 1.

### Register `rd_cursor_palette_2v`

Cursor palette: colours stored in consecutive stores.

### Register `rd_cursor_pattern_2v`

Cursor pattern RAM: 64x64 at two bits a pixel, 1 KiB.

### Register `reset_status`

Soft reset. Software expectation: board start-up writes 0 and polls bit 31 until it clears, before programming anything else.

### Register `int_enable`

Interrupt enable. Software expectation: the kernel driver writes 0x83 once at attach, enabling the GP-DMA, sync and bypass-DMA interrupts (bits 0, 1 and 7), and its interrupt handler writes 0 on entry and restores 0x83 on exit. The textport library writes 0.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `bypass_dma` | established |  |  |  |
| 1 | `sync` | established |  |  |  |
| 0 | `dma` | established |  |  |  |

### Register `int_flags`

Interrupt status, cleared by writing the bits back. Software expectation: the handler reads it, writes the value back, and wakes one waiter for each of bits 1 (sync), 0 (GP output DMA) and 7 (bypass DMA). No other bit is tested.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 7 | `bypass_dma` | established |  |  |  |
| 1 | `sync` | established |  |  |  |
| 0 | `dma` | established |  |  |  |

### Register `in_fifo_space`

Free entries in the input FIFO. Software expectation: every batch of GP register writes is preceded by a poll until the value reaches the batch size; the thresholds used are 2, 3, 6, 9, 14, 20, 32, 40 and 100.

### Register `out_fifo_words`

Words waiting in the output FIFO. Software expectation: polled until nonzero after a sync or a read-back, and drained to empty after a timeout.

### Register `error_flags`

Error status. Software expectation: read before a read-back DMA and written back to clear it, and again after the transfer.

### Register `vclk_ctl`

Video clock control. Software expectation: the driver reads it at attach and treats a nonzero value as the console already having initialised the chip, which skips the clock, memory and screen-clear steps; a zero value means a full initialisation. Start-up writes it with clock source 2 and a recovery time derived from the pixel clock.

### Register `aperture_one`

Aperture one control. Software expectation: written 0 at init.

### Register `aperture_two`

Aperture two control. Software expectation: written at init with bit 9 (ROM access) set and nothing else, which is what exposes the board's flash for the settings sector.

### Register `dma_control`

DMA control. Software expectation: written 0x8 at init.

### Register `chip_config`

Chip configuration. Software expectation: only read, by a diagnostic dump routine.

### Register `out_dma_address`

Output DMA address: the host (PCI) address a read-back is written to. Software expectation: set per chunk before the count.

### Register `out_dma_count`

Output DMA count in words; writing it starts the transfer. Software expectation: at most 0xffff words per write.

### Register `by_dma_address`

Bypass DMA host address. Software expectation: the source of a host-to-framebuffer transfer.

### Register `by_dma_stride`

Bypass DMA source stride in bytes.

### Register `by_dma_mem_address`

Bypass DMA destination in local memory, in pixels (or in pixel units of the format).

### Register `by_dma_size`

Bypass DMA size: width in bits 11 to 0, height from bit 16. Software expectation.

### Register `by_dma_byte_mask`

Bypass DMA byte mask. Software expectation: always written 0x000f000f (all lanes at both edges).

### Register `by_dma_control`

Bypass DMA control; the write starts the transfer. Software expectation: implicit mode, no patching, 32-, 16- or 8-bit source format, the pixel-partial-product fields of the current screen width, and GP restart.

### Register `mem_control`

Memory type. Software expectation: written 0 (SGRAM).

### Register `boot_address`

Memory boot address (the SGRAM mode word). Software expectation: 0x20 for the 104c:3d07 chip and 0x30 for the 3d3d:0009 chip, written after the memory type.

### Register `mem_config`

Memory timing. Software expectation: 0xe6002021 for the 104c:3d07 chip and 0xe6012021 for the 3d3d:0009 chip, both with four banks.

### Register `bypass_write_mask`

Plane write mask for bypass (host and DMA) writes. Software expectation: 0x00ffffff at init; the mask ioctl, rectangle writes and the screen clear change it and restore it.

### Register `out_fifo`

Output FIFO read port. Software expectation: read to drain sync tags and read-back words.

### Register `screen_base`

Screen base, in 64-bit units. Software expectation: 0.

### Register `screen_stride`

Screen stride in 64-bit units: 640 for the two 1280-wide modes and 512 for 1024 wide.

### Register `h_total`

Horizontal total in 64-bit units, from the mode table's count halved.

### Register `hg_end`

Horizontal gate end, 64-bit units.

### Register `hb_end`

Horizontal blank end, 64-bit units.

### Register `hs_start`

Horizontal sync start, 64-bit units.

### Register `hs_end`

Horizontal sync end, 64-bit units.

### Register `v_total`

Vertical total in lines.

### Register `vb_end`

Vertical blank end in lines.

### Register `vs_start`

Vertical sync start in lines.

### Register `vs_end`

Vertical sync end in lines.

### Register `video_control`

Video control. Software expectation: bit 0 enables refresh; the mode loader also sets blank, 64-bit data and active-high sync fields, then turns refresh off and on around the mode change.

| Bits | Field | Grade | Values | Source | Description |
|---|---|---|---|---|---|
| 0 | `enable` | established |  |  |  |

### Register `fifo_control`

Video FIFO control. Software expectation: written 0x0b07.

### Register `screen_base_right`

Right-eye screen base. Software expectation: written 0.

### Register `rd_palette_write_address`

Palette write address; also the index port of the Permedia 2 indexed registers. Software expectation: the palette load writes 0 here, then red, green and blue in turn to the data port for each of 256 entries.

### Register `rd_palette_data`

Palette data. Software expectation: three consecutive byte stores per entry.

### Register `rd_pixel_mask`

Pixel read mask. Software expectation: written 0xff.

### Register `rd_palette_read_address`

Palette read address. Software expectation: written 0 before a palette load.

### Register `vga_control`

SVGA control (name ours). Software expectation: written 0x40 before the mode is set, to turn the legacy VGA core off.

### Register `start_x_dom`

Start X of the dominant edge, 16.16 signed; also the X of a point.

### Register `d_x_dom`

Dominant edge X step, 16.16 signed. Written 0.

### Register `start_x_sub`

Start X of the subordinate edge, 16.16 signed; the screen clear sets it to the width.

### Register `d_x_sub`

Subordinate edge X step, 16.16 signed. Written 0.

### Register `start_y`

Start Y, 16.16 signed; also the Y of a point.

### Register `d_y`

Y step, 16.16 signed. Written 0x10000 at init.

### Register `count`

Scanline count of a trapezoid. The screen clear writes the mode height.

### Register `render`

Render command; the write starts the operation. Software expectation: primitive in bits 7 to 6 (trapezoid, point, rectangle), fast fill bit 3, texture enable bit 13, increase X bit 21 and increase Y bit 22 are the bits used.

### Register `wait_for_completion`

Wait for completion; written 0 after a render that the driver must see finished.

### Register `rasterizer_mode`

Rasterizer mode. Written 0.

### Register `rectangle_origin`

Rectangle origin: X in the low 12 bits, Y from bit 16.

### Register `rectangle_size`

Rectangle size: width in the low bits, height from bit 16.

### Register `packed_data_limits`

Packed data limits; the X end is set to width minus one.

### Register `scissor_mode`

Scissor mode. Written 0.

### Register `screen_size`

Screen size: width in bits 10 to 0, height from bit 16.

### Register `area_stipple_mode`

Area stipple mode. Written 0.

### Register `window_origin`

Window origin. Written 0.

### Register `texture_address_mode`

Texture address mode. Written 1 (enable) for the format-converting copy and 0 otherwise.

### Register `s_start`

Texture S start.

### Register `d_s_dx`

Texture S step per pixel; written 1.0 in 12.18 fixed point at init.

### Register `d_s_dy_dom`

Texture S step per scanline.

### Register `t_start`

Texture T start.

### Register `d_t_dx`

Texture T step per pixel.

### Register `d_t_dy_dom`

Texture T step per scanline; 1.0 in the format-converting copy.

### Register `texel_lut_index`

Texel look-up table index; written 0 before a table load.

### Register `texel_lut_data`

Texel look-up table data, one 32-bit colour per store.

### Register `texel_lut_address`

Texel look-up table address in local memory; set to 256 words below the end of the 8 MiB memory.

### Register `texture_base_address`

Texture base address: where the format-converting copy reads its source, in local memory.

### Register `texture_map_format`

Texture map format: texel size and the width partial products.

### Register `texture_data_format`

Texture data format. Written 0 at init.

### Register `texel0`

Texel 0. Written 0 at init.

### Register `texture_read_mode`

Texture read mode.

### Register `texel_lut_mode`

Texel look-up table mode; 1 enables it for 8-bit colour-index copies.

### Register `texture_color_mode`

Texture colour mode.

### Register `fog_mode`

Fog mode. Written 0.

### Register `r_start`

Colour DDA red start; used only by the start-up screen fill.

### Register `d_r_dx`

Colour DDA red step per pixel.

### Register `d_r_dy_dom`

Colour DDA red step per scanline.

### Register `g_start`

Colour DDA green start.

### Register `d_g_dx`

Colour DDA green step per pixel.

### Register `d_g_dy_dom`

Colour DDA green step per scanline.

### Register `b_start`

Colour DDA blue start.

### Register `d_b_dx`

Colour DDA blue step per pixel.

### Register `d_b_dy_dom`

Colour DDA blue step per scanline.

### Register `a_start`

Colour DDA alpha start.

### Register `color_dda_mode`

Colour DDA mode; enabled with Gouraud shading only for the start-up screen fill.

### Register `alpha_blend_mode`

Alpha blend mode. Written 0 at init and set to the format operation for a read-back.

### Register `dither_mode`

Dither mode. Written with the unit enable bit set at init.

### Register `fb_software_write_mask`

Framebuffer software write mask. Written all ones at init; the rectangle fill and copy paths put the caller's mask here.

### Register `logical_op_mode`

Logical operation mode: enable, operation, and the constant-write-data bit that makes fills use the write-data register. Software expectation.

### Register `fb_write_data`

Constant framebuffer write data: the colour of a fill or a textport pixel.

### Register `lb_read_mode`

Local buffer read mode. Written 0 at init.

### Register `lb_window_base`

Local buffer window base. Written 0.

### Register `lb_write_mode`

Local buffer write mode. Written 0.

### Register `lb_write_format`

Local buffer write format. Written 0.

### Register `window`

Window: the local buffer update fields. Written with the update disabled.

### Register `stencil_mode`

Stencil mode. Written 0.

### Register `depth_mode`

Depth mode. Written 0.

### Register `fb_read_mode`

Framebuffer read mode: source and destination read enables, packed data, relative offset and the screen-width partial products.

### Register `fb_pixel_offset`

Framebuffer pixel offset. Written 0.

### Register `fb_window_base`

Framebuffer window base. Written 0.

### Register `fb_write_mode`

Framebuffer write mode: write enable, and the upload-to-host bit for a read-back.

### Register `fb_hard_write_mask`

Framebuffer hardware write mask. Written all ones at init and 0x00ffffff afterwards.

### Register `fb_block_color`

Block colour for a fast fill.

### Register `fb_read_pixel`

Framebuffer read pixel size. Written 2 (32 bits).

### Register `filter_mode`

Filter mode: which output tags reach the host. Synchronisation data for a sync, colour data for a read-back.

### Register `statistic_mode`

Statistic mode. Written 0 at init.

### Register `sync`

Sync: writing a tag with bit 31 set raises the sync interrupt when the pipeline reaches it, and the tag appears in the output FIFO.

### Register `fb_source_base`

Framebuffer source base. Written 0 at init.

### Register `fb_source_delta`

Framebuffer source delta: the Y and X offset of a screen-to-screen copy's source, negated.

### Register `yuv_mode`

YUV mode. Written 0 at init.

### Register `delta_mode`

Delta mode. Written 0 at init.

### Register `rd_cursor_color_address`

Cursor colour address. Software expectation: written 1 before the cursor colours.

### Register `rd_cursor_color_data`

Cursor colour data: three bytes background then three bytes foreground.

### Register `rd_indexed_data`

Data port of the indexed registers, selected through the palette write address. Software expectation: read to poll the PLL lock bits.

### Register `rd_cursor_ram_data`

Cursor pattern RAM data port.

### Register `rd_cursor_x_low`

Cursor X, low byte.

### Register `rd_cursor_x_high`

Cursor X, high byte.

### Register `rd_cursor_y_low`

Cursor Y, low byte.

### Register `rd_cursor_y_high`

Cursor Y, high byte.

### Register `rd_index_low_2v`

Index, low byte. Software expectation: written before each access to an indexed register.

### Register `rd_index_high_2v`

Index, high byte.

### Register `rd_indexed_data_2v`

Indexed data port. Software expectation: after a cursor palette or pattern index is set, consecutive stores fill the table, so the index auto-increments.

### Register `rd_index_control_2v`

Index control. Software expectation: written 1 at init to turn auto-increment on.
