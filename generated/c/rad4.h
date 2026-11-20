/* generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source */
/* SPDX-License-Identifier: BSD-3-Clause */
/* defs-gen 2 */
/* input sha256 93b0ddd09dc551607b6d636875bca6ee0e31cbf5a4d2bbdb6c4612238c3328c1 */
/* RAD4 graphics head registers */
#ifndef RAD4_GEN_H
#define RAD4_GEN_H

#include <stdint.h>


/*
 * Expansion ROM remap register. Software expectation: the driver writes it once at attach, with the top byte 0xe1. Nothing reads it back.
 */
/* rom_remap: rw32, space bar0, reset unknown; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_ROM_REMAP_OFFSET                        0x14u /* established */

/*
 * Local bus region descriptor. Software expectation: the driver writes 0xf84303c3 at attach, which selects a 32-bit local bus.
 */
/* bus_region_descriptor: rw32, space bar0, reset unknown; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_BUS_REGION_DESCRIPTOR_OFFSET            0x18u /* established */

/*
 * Mailbox 0. Software expectation: the driver reads it at attach and skips its own mode and RAMDAC setup when it is nonzero, because it takes that to mean a firmware initialiser has run, and writes zero to it at the end of every attach. What a real card holds here after power-on is unknown.
 */
/* mailbox: rw32, space bar0, reset unknown; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_MAILBOX_OFFSET                          0x40u /* established */

/*
 * Interrupt control and status, with the bits the driver uses. The driver ORs 0x50900 into it at attach whether or not pixel DMA is enabled.
 */
/* intcsr: rw32, space bar0, reset 0x10100; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_INTCSR_OFFSET                           0x68u /* established */
#define RAD4_INTCSR_DMA0_INT_ACTIVE_SHIFT            21 /* established */
#define RAD4_INTCSR_DMA0_INT_ACTIVE_MASK             0x1u
#define RAD4_INTCSR_DMA0_INT_ACTIVE_INPLACE          (RAD4_INTCSR_DMA0_INT_ACTIVE_MASK << RAD4_INTCSR_DMA0_INT_ACTIVE_SHIFT)
#define RAD4_INTCSR_DMA0_INT_ENABLE_SHIFT            18 /* established */
#define RAD4_INTCSR_DMA0_INT_ENABLE_MASK             0x1u
#define RAD4_INTCSR_DMA0_INT_ENABLE_INPLACE          (RAD4_INTCSR_DMA0_INT_ENABLE_MASK << RAD4_INTCSR_DMA0_INT_ENABLE_SHIFT)
#define RAD4_INTCSR_LOCAL_INT_OUTPUT_ENABLE_SHIFT    16 /* established */
#define RAD4_INTCSR_LOCAL_INT_OUTPUT_ENABLE_MASK     0x1u
#define RAD4_INTCSR_LOCAL_INT_OUTPUT_ENABLE_INPLACE  (RAD4_INTCSR_LOCAL_INT_OUTPUT_ENABLE_MASK << RAD4_INTCSR_LOCAL_INT_OUTPUT_ENABLE_SHIFT)
#define RAD4_INTCSR_LOCAL_INT_INPUT_ACTIVE_SHIFT     15 /* established */
#define RAD4_INTCSR_LOCAL_INT_INPUT_ACTIVE_MASK      0x1u
#define RAD4_INTCSR_LOCAL_INT_INPUT_ACTIVE_INPLACE   (RAD4_INTCSR_LOCAL_INT_INPUT_ACTIVE_MASK << RAD4_INTCSR_LOCAL_INT_INPUT_ACTIVE_SHIFT)
#define RAD4_INTCSR_PCI_LOCAL_INT_ENABLE_SHIFT       11 /* established */
#define RAD4_INTCSR_PCI_LOCAL_INT_ENABLE_MASK        0x1u
#define RAD4_INTCSR_PCI_LOCAL_INT_ENABLE_INPLACE     (RAD4_INTCSR_PCI_LOCAL_INT_ENABLE_MASK << RAD4_INTCSR_PCI_LOCAL_INT_ENABLE_SHIFT)
#define RAD4_INTCSR_PCI_INT_ENABLE_SHIFT             8 /* established */
#define RAD4_INTCSR_PCI_INT_ENABLE_MASK              0x1u
#define RAD4_INTCSR_PCI_INT_ENABLE_INPLACE           (RAD4_INTCSR_PCI_INT_ENABLE_MASK << RAD4_INTCSR_PCI_INT_ENABLE_SHIFT)

/*
 * Serial EEPROM control. Bits 24 to 27 drive the configuration EEPROM. Bits 3 to 0 are the PCI read command the DMA engines use (public datasheet): the driver replaces them at attach with its DMA read command setting, 0xc by default, and the only values it accepts are 0x6, 0xc and 0xe; request 126 changes them later.
 */
/* eeprom_ctl: rw32, space bar0, reset unknown; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_EEPROM_CTL_OFFSET                       0x6cu /* established */
#define RAD4_EEPROM_CTL_DATA_FROM_EEPROM_SHIFT       27 /* established */
#define RAD4_EEPROM_CTL_DATA_FROM_EEPROM_MASK        0x1u
#define RAD4_EEPROM_CTL_DATA_FROM_EEPROM_INPLACE     (RAD4_EEPROM_CTL_DATA_FROM_EEPROM_MASK << RAD4_EEPROM_CTL_DATA_FROM_EEPROM_SHIFT)
#define RAD4_EEPROM_CTL_DATA_TO_EEPROM_SHIFT         26 /* established */
#define RAD4_EEPROM_CTL_DATA_TO_EEPROM_MASK          0x1u
#define RAD4_EEPROM_CTL_DATA_TO_EEPROM_INPLACE       (RAD4_EEPROM_CTL_DATA_TO_EEPROM_MASK << RAD4_EEPROM_CTL_DATA_TO_EEPROM_SHIFT)
#define RAD4_EEPROM_CTL_CHIP_SELECT_SHIFT            25 /* established */
#define RAD4_EEPROM_CTL_CHIP_SELECT_MASK             0x1u
#define RAD4_EEPROM_CTL_CHIP_SELECT_INPLACE          (RAD4_EEPROM_CTL_CHIP_SELECT_MASK << RAD4_EEPROM_CTL_CHIP_SELECT_SHIFT)
#define RAD4_EEPROM_CTL_CLOCK_SHIFT                  24 /* established */
#define RAD4_EEPROM_CTL_CLOCK_MASK                   0x1u
#define RAD4_EEPROM_CTL_CLOCK_INPLACE                (RAD4_EEPROM_CTL_CLOCK_MASK << RAD4_EEPROM_CTL_CLOCK_SHIFT)
#define RAD4_EEPROM_CTL_DMA_READ_COMMAND_SHIFT       0 /* established */
#define RAD4_EEPROM_CTL_DMA_READ_COMMAND_MASK        0xfu
#define RAD4_EEPROM_CTL_DMA_READ_COMMAND_INPLACE     (RAD4_EEPROM_CTL_DMA_READ_COMMAND_MASK << RAD4_EEPROM_CTL_DMA_READ_COMMAND_SHIFT)

/*
 * Parallel flash, 64 KiB in 128-byte sectors. Software expectation: the driver switches the bus region descriptor to 0xf84003c0, uses byte accesses at the address with its two low bits inverted, programs a sector with the usual three-byte unlock sequence (0xaa, 0x55, 0xa0; addresses in the kernel driver page), writes 128 bytes and polls the last one. The part is not identified; an AT29C512-compatible page-write flash fits the geometry (inferred).
 */
/* flash: rw8, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver (flash sector requests) */
#define RAD4_FLASH_OFFSET                            0x800000u /* inferred */
#define RAD4_FLASH_COUNT                             65536
#define RAD4_FLASH_STRIDE                            1

/*
 * RAMDAC index, low byte, in the low eight bits of a 32-bit store. The identification with the RGB561 index-low port is inferred from the driver's use of it.
 */
/* rgb561_index_lo: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 */
#define RAD4_RGB561_INDEX_LO_OFFSET                  0x900000u /* inferred */
#define RAD4_RGB561_INDEX_LO_VALUE_SHIFT             0 /* inferred */
#define RAD4_RGB561_INDEX_LO_VALUE_MASK              0xffu
#define RAD4_RGB561_INDEX_LO_VALUE_INPLACE           (RAD4_RGB561_INDEX_LO_VALUE_MASK << RAD4_RGB561_INDEX_LO_VALUE_SHIFT)

/*
 * RAMDAC index, high byte.
 */
/* rgb561_index_hi: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 */
#define RAD4_RGB561_INDEX_HI_OFFSET                  0x910000u /* inferred */
#define RAD4_RGB561_INDEX_HI_VALUE_SHIFT             0 /* inferred */
#define RAD4_RGB561_INDEX_HI_VALUE_MASK              0xffu
#define RAD4_RGB561_INDEX_HI_VALUE_INPLACE           (RAD4_RGB561_INDEX_HI_VALUE_MASK << RAD4_RGB561_INDEX_HI_VALUE_SHIFT)

/*
 * RAMDAC single-cycle data port. The index advances after each access.
 */
/* rgb561_data: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 27 */
#define RAD4_RGB561_DATA_OFFSET                      0x920000u /* inferred */
#define RAD4_RGB561_DATA_VALUE_SHIFT                 0 /* inferred */
#define RAD4_RGB561_DATA_VALUE_MASK                  0xffu
#define RAD4_RGB561_DATA_VALUE_INPLACE               (RAD4_RGB561_DATA_VALUE_MASK << RAD4_RGB561_DATA_VALUE_SHIFT)

/*
 * RAMDAC multi-cycle data port for tables whose entries are wider than a byte: two cycles per window attribute or gamma entry, three per colour or cursor table entry. The index advances once per complete entry.
 */
/* rgb561_data_multi: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; IBM RGB561 Architecture, preliminary revision 1.1, pp. 1, 4 */
#define RAD4_RGB561_DATA_MULTI_OFFSET                0x930000u /* inferred */
#define RAD4_RGB561_DATA_MULTI_VALUE_SHIFT           0 /* inferred */
#define RAD4_RGB561_DATA_MULTI_VALUE_MASK            0xffu
#define RAD4_RGB561_DATA_MULTI_VALUE_INPLACE         (RAD4_RGB561_DATA_MULTI_VALUE_MASK << RAD4_RGB561_DATA_MULTI_VALUE_SHIFT)

/*
 * Horizontal timing bank 0. Software expectation: the mode loader writes one word per four-pixel group of the horizontal total. The bank depth is not known, 1024 words is the room between banks, and the bit meanings are unknown.
 */
/* timing_h0: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver */
#define RAD4_TIMING_H0_OFFSET                        0xa00000u /* inferred */
#define RAD4_TIMING_H0_COUNT                         1024
#define RAD4_TIMING_H0_STRIDE                        4

/*
 * Horizontal timing bank 1. Same use and limits as bank 0.
 */
/* timing_h1: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver */
#define RAD4_TIMING_H1_OFFSET                        0xa01000u /* inferred */
#define RAD4_TIMING_H1_COUNT                         1024
#define RAD4_TIMING_H1_STRIDE                        4

/*
 * Horizontal timing bank 3. Same use and limits as bank 0. The loader holds a pointer to a bank between 1 and 3 and never writes it.
 */
/* timing_h3: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver */
#define RAD4_TIMING_H3_OFFSET                        0xa03000u /* inferred */
#define RAD4_TIMING_H3_COUNT                         1024
#define RAD4_TIMING_H3_STRIDE                        4

/*
 * Vertical timing bank. Software expectation: one word per line of the vertical total, at most 1656 for the driver's modes. The depth is not known and the bit meanings are unknown.
 */
/* timing_v: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver */
#define RAD4_TIMING_V_OFFSET                         0xb00000u /* inferred */
#define RAD4_TIMING_V_COUNT                          2048
#define RAD4_TIMING_V_STRIDE                         4

/*
 * Pixel write mask. Software expectation: the driver and X server program 0xffffffff, 0x00ffffff for colour drawing and 0x0f000000 for the overlay planes before stores, then restore the full mask. That a store merges as old under the inverse mask or value under the mask is the generic plane-mask convention. Which mask bit reaches which board plane is unknown.
 */
/* plane_mask: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver and standalone X server */
#define RAD4_PLANE_MASK_OFFSET                       0xd00000u /* inferred */

/*
 * Channel A mode register: the first write after a command-register mode-pointer reset goes to mode register 1, the next to mode register 2. The driver writes 0x07 twice at initialisation, and 0x47 then 0x07 after finding a mouse. Low eight bits of the store.
 */
/* km_mr: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_MR_OFFSET                            0xe00000u /* inferred */

/*
 * Channel A: reads give the status register (bit 0 receiver ready, bit 2 transmitter ready, the two the driver tests); writes set the clock select, which the driver sets to 0xff.
 */
/* km_sr_csr_a: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_SR_CSR_A_OFFSET                      0xe10000u /* inferred */

/*
 * Channel A command register, written only. Values used: 0x1a, 0x20, 0x30, 0x40, 0x50 (resets, with 0x1a disabling receiver and transmitter), 0x05 (enable both), 0x01 and 0x20 around a transmit.
 */
/* km_cr_a: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_CR_A_OFFSET                          0xe20000u /* inferred */

/*
 * Channel A receive and transmit data, low eight bits.
 */
/* km_data_a: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_DATA_A_OFFSET                        0xe30000u /* inferred */

/*
 * Auxiliary control register, written zero at initialisation.
 */
/* km_acr: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_ACR_OFFSET                           0xe40000u /* inferred */

/*
 * Reads give interrupt status, writes set the interrupt mask. The driver uses bit 1 (channel A receiver ready) and bit 5 (channel B receiver ready), and ANDs the saved mask with the status in its handler. The saved mask is also what drives board control bit 7.
 */
/* km_isr_imr: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_ISR_IMR_OFFSET                       0xe50000u /* inferred */
#define RAD4_KM_ISR_IMR_RX_READY_B_SHIFT             5 /* inferred */
#define RAD4_KM_ISR_IMR_RX_READY_B_MASK              0x1u
#define RAD4_KM_ISR_IMR_RX_READY_B_INPLACE           (RAD4_KM_ISR_IMR_RX_READY_B_MASK << RAD4_KM_ISR_IMR_RX_READY_B_SHIFT)
#define RAD4_KM_ISR_IMR_RX_READY_A_SHIFT             1 /* inferred */
#define RAD4_KM_ISR_IMR_RX_READY_A_MASK              0x1u
#define RAD4_KM_ISR_IMR_RX_READY_A_INPLACE           (RAD4_KM_ISR_IMR_RX_READY_A_MASK << RAD4_KM_ISR_IMR_RX_READY_A_SHIFT)

/*
 * Channel B mode register, used as register km_mr is for channel A.
 */
/* km_mr_b: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_MR_B_OFFSET                          0xe80000u /* inferred */

/*
 * Channel B status on read and clock select on write, as for channel A.
 */
/* km_sr_csr_b: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_SR_CSR_B_OFFSET                      0xe90000u /* inferred */

/*
 * Channel B command register, written only.
 */
/* km_cr_b: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_CR_B_OFFSET                          0xea0000u /* inferred */

/*
 * Channel B receive and transmit data, low eight bits.
 */
/* km_data_b: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_DATA_B_OFFSET                        0xeb0000u /* inferred */

/*
 * Output port configuration, written zero at initialisation, which makes the output port bits plain outputs.
 */
/* km_opcr: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_OPCR_OFFSET                          0xed0000u /* inferred */

/*
 * Set output port bits. The driver uses bits 2 and 6 around a channel A transmit and bits 3 and 7 around a channel B transmit. Their wiring (inferred: open-collector drives of the PS/2 clock and data lines) is not documented.
 */
/* km_opr_set: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_OPR_SET_OFFSET                       0xee0000u /* inferred */

/*
 * Reset output port bits, same bits as km_opr_set. Written 0xff at initialisation.
 */
/* km_opr_reset: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver; Philips SCC68681 product data, 6 April 2004 */
#define RAD4_KM_OPR_RESET_OFFSET                     0xef0000u /* inferred */

/*
 * Board control and status. Software expectation: the driver clears bit 5 while it programs a mode and sets it afterwards, sets bit 1 to ask for an interrupt at the next frame and clears it around DMA transfers, and its interrupt handler tests bit 5. That bit 5 reports a frame event only while bit 1 is set is inferred. Bit 7 is set whenever the keyboard and mouse controller has any interrupt enabled and cleared when none is. The status in bit 5 is read only by the interrupt handler, through a stored pointer, and bit 1 is cleared there when it is set. The physical effects are unknown.
 */
/* board_control: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver */
#define RAD4_BOARD_CONTROL_OFFSET                    0xf00000u /* inferred */
#define RAD4_BOARD_CONTROL_KM_INTERRUPT_GATE_SHIFT   7 /* inferred */
#define RAD4_BOARD_CONTROL_KM_INTERRUPT_GATE_MASK    0x1u
#define RAD4_BOARD_CONTROL_KM_INTERRUPT_GATE_INPLACE (RAD4_BOARD_CONTROL_KM_INTERRUPT_GATE_MASK << RAD4_BOARD_CONTROL_KM_INTERRUPT_GATE_SHIFT)
#define RAD4_BOARD_CONTROL_MODE_GATE_FRAME_STATUS_SHIFT 5 /* inferred */
#define RAD4_BOARD_CONTROL_MODE_GATE_FRAME_STATUS_MASK 0x1u
#define RAD4_BOARD_CONTROL_MODE_GATE_FRAME_STATUS_INPLACE (RAD4_BOARD_CONTROL_MODE_GATE_FRAME_STATUS_MASK << RAD4_BOARD_CONTROL_MODE_GATE_FRAME_STATUS_SHIFT)
#define RAD4_BOARD_CONTROL_FRAME_REQUEST_SHIFT       1 /* inferred */
#define RAD4_BOARD_CONTROL_FRAME_REQUEST_MASK        0x1u
#define RAD4_BOARD_CONTROL_FRAME_REQUEST_INPLACE     (RAD4_BOARD_CONTROL_FRAME_REQUEST_MASK << RAD4_BOARD_CONTROL_FRAME_REQUEST_SHIFT)

/*
 * Sync control. The mode routine writes 1, or 0x23 when the EEPROM selector field equals 2.
 */
/* rgb561_sync_ctl: rw8, space rgb561, reset unknown; IBM RGB561 Architecture, preliminary revision 1.1, p. 27 */
#define RAD4_RGB561_SYNC_CTL_OFFSET                  0x20u /* established */

/*
 * PLL VCO divider. M is bits 5 to 0 plus 65. Bits 7 to 6 hold the range code; that position is inferred, since it reproduces the clock field of all 13 driver modes to the hertz.
 */
/* rgb561_pll_vco: rw8, space rgb561, reset unknown; IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 */
#define RAD4_RGB561_PLL_VCO_OFFSET                   0x21u /* established */
#define RAD4_RGB561_PLL_VCO_RANGE_CODE_SHIFT         6 /* inferred */
#define RAD4_RGB561_PLL_VCO_RANGE_CODE_MASK          0x3u
#define RAD4_RGB561_PLL_VCO_RANGE_CODE_INPLACE       (RAD4_RGB561_PLL_VCO_RANGE_CODE_MASK << RAD4_RGB561_PLL_VCO_RANGE_CODE_SHIFT)
#define RAD4_RGB561_PLL_VCO_M_MINUS_65_SHIFT         0 /* established */
#define RAD4_RGB561_PLL_VCO_M_MINUS_65_MASK          0x3fu
#define RAD4_RGB561_PLL_VCO_M_MINUS_65_INPLACE       (RAD4_RGB561_PLL_VCO_M_MINUS_65_MASK << RAD4_RGB561_PLL_VCO_M_MINUS_65_SHIFT)

/*
 * PLL reference divider N, bits 4 to 0.
 */
/* rgb561_pll_ref: rw8, space rgb561, reset unknown; IBM RGB561 Architecture, preliminary revision 1.1, pp. 27, 36 */
#define RAD4_RGB561_PLL_REF_OFFSET                   0x22u /* established */
#define RAD4_RGB561_PLL_REF_N_SHIFT                  0 /* established */
#define RAD4_RGB561_PLL_REF_N_MASK                   0x1fu
#define RAD4_RGB561_PLL_REF_N_INPLACE                (RAD4_RGB561_PLL_REF_N_MASK << RAD4_RGB561_PLL_REF_N_SHIFT)

/*
 * Cursor control. Bit 0 enables the 64 by 64 two-bit cursor.
 */
/* rgb561_cursor_ctl: rw8, space rgb561, reset unknown; IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 37 */
#define RAD4_RGB561_CURSOR_CTL_OFFSET                0x30u /* established */
#define RAD4_RGB561_CURSOR_CTL_ENABLE_SHIFT          0 /* established */
#define RAD4_RGB561_CURSOR_CTL_ENABLE_MASK           0x1u
#define RAD4_RGB561_CURSOR_CTL_ENABLE_INPLACE        (RAD4_RGB561_CURSOR_CTL_ENABLE_MASK << RAD4_RGB561_CURSOR_CTL_ENABLE_SHIFT)

/*
 * Cursor hot spot, horizontal, six bits.
 */
/* rgb561_cursor_hot_x: rw8, space rgb561, reset unknown; IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 38 */
#define RAD4_RGB561_CURSOR_HOT_X_OFFSET              0x34u /* established */
#define RAD4_RGB561_CURSOR_HOT_X_X_SHIFT             0 /* established */
#define RAD4_RGB561_CURSOR_HOT_X_X_MASK              0x3fu
#define RAD4_RGB561_CURSOR_HOT_X_X_INPLACE           (RAD4_RGB561_CURSOR_HOT_X_X_MASK << RAD4_RGB561_CURSOR_HOT_X_X_SHIFT)

/*
 * Cursor hot spot, vertical, six bits.
 */
/* rgb561_cursor_hot_y: rw8, space rgb561, reset unknown; IBM RGB561 Architecture, preliminary revision 1.1, pp. 3, 38 */
#define RAD4_RGB561_CURSOR_HOT_Y_OFFSET              0x35u /* established */
#define RAD4_RGB561_CURSOR_HOT_Y_Y_SHIFT             0 /* established */
#define RAD4_RGB561_CURSOR_HOT_Y_Y_MASK              0x3fu
#define RAD4_RGB561_CURSOR_HOT_Y_Y_INPLACE           (RAD4_RGB561_CURSOR_HOT_Y_Y_MASK << RAD4_RGB561_CURSOR_HOT_Y_Y_SHIFT)

/*
 * DMA channel 0 mode. Software expectation: the driver reaches the DMA registers through the expansion ROM resource, writes 0x7c3 here (32-bit local bus, chaining, done interrupt enabled) and clears the done-interrupt bit when a transfer times out.
 */
/* dmamode0: rw32, space rom, reset unknown; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_DMAMODE0_OFFSET                         0x100u /* established */
#define RAD4_DMAMODE0_DONE_INT_ENABLE_SHIFT          10 /* established */
#define RAD4_DMAMODE0_DONE_INT_ENABLE_MASK           0x1u
#define RAD4_DMAMODE0_DONE_INT_ENABLE_INPLACE        (RAD4_DMAMODE0_DONE_INT_ENABLE_MASK << RAD4_DMAMODE0_DONE_INT_ENABLE_SHIFT)
#define RAD4_DMAMODE0_CHAINING_SHIFT                 9 /* established */
#define RAD4_DMAMODE0_CHAINING_MASK                  0x1u
#define RAD4_DMAMODE0_CHAINING_INPLACE               (RAD4_DMAMODE0_CHAINING_MASK << RAD4_DMAMODE0_CHAINING_SHIFT)

/*
 * DMA channel 0 descriptor pointer. Loaded from each descriptor's next-pointer word. The driver starts it at the top of the board's 8 MiB local memory.
 */
/* dmadpr0: rw32, space rom, reset unknown; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_DMADPR0_OFFSET                          0x110u /* established */

/*
 * DMA command and status, channel 0 in bits 7 to 0. The driver starts a transfer by writing 3 (enable and start) and aborts one with 4 after a timeout, then polls Done.
 */
/* dmacsr0: rw32, space rom, reset 0x1010; PLX PCI 9060 Data Sheet, version 1.2 */
#define RAD4_DMACSR0_OFFSET                          0x128u /* established */
#define RAD4_DMACSR0_USER_SHIFT                      5 /* established */
#define RAD4_DMACSR0_USER_MASK                       0x7u
#define RAD4_DMACSR0_USER_INPLACE                    (RAD4_DMACSR0_USER_MASK << RAD4_DMACSR0_USER_SHIFT)
#define RAD4_DMACSR0_DONE_SHIFT                      4 /* established */
#define RAD4_DMACSR0_DONE_MASK                       0x1u
#define RAD4_DMACSR0_DONE_INPLACE                    (RAD4_DMACSR0_DONE_MASK << RAD4_DMACSR0_DONE_SHIFT)
#define RAD4_DMACSR0_CLEAR_INT_SHIFT                 3 /* established */
#define RAD4_DMACSR0_CLEAR_INT_MASK                  0x1u
#define RAD4_DMACSR0_CLEAR_INT_INPLACE               (RAD4_DMACSR0_CLEAR_INT_MASK << RAD4_DMACSR0_CLEAR_INT_SHIFT)
#define RAD4_DMACSR0_ABORT_SHIFT                     2 /* established */
#define RAD4_DMACSR0_ABORT_MASK                      0x1u
#define RAD4_DMACSR0_ABORT_INPLACE                   (RAD4_DMACSR0_ABORT_MASK << RAD4_DMACSR0_ABORT_SHIFT)
#define RAD4_DMACSR0_START_SHIFT                     1 /* established */
#define RAD4_DMACSR0_START_MASK                      0x1u
#define RAD4_DMACSR0_START_INPLACE                   (RAD4_DMACSR0_START_MASK << RAD4_DMACSR0_START_SHIFT)
#define RAD4_DMACSR0_ENABLE_SHIFT                    0 /* established */
#define RAD4_DMACSR0_ENABLE_MASK                     0x1u
#define RAD4_DMACSR0_ENABLE_INPLACE                  (RAD4_DMACSR0_ENABLE_MASK << RAD4_DMACSR0_ENABLE_SHIFT)

/*
 * Fourth word of a 16-byte chain descriptor (PCI address, local address, byte count, next pointer). It is loaded into the descriptor pointer register, and its low bits describe the descriptor's own transfer.
 */
/* word DMA_DESC_NEXT: 32 bits; PLX PCI 9060 Data Sheet, version 1.2, Table 51 */
#define RAD4_DMA_DESC_NEXT_WIDTH                     32 /* established */
#define RAD4_DMA_DESC_NEXT_NEXT_SHIFT                4 /* established */
#define RAD4_DMA_DESC_NEXT_NEXT_MASK                 0xfffffffu
#define RAD4_DMA_DESC_NEXT_NEXT_INPLACE              (RAD4_DMA_DESC_NEXT_NEXT_MASK << RAD4_DMA_DESC_NEXT_NEXT_SHIFT)
#define RAD4_DMA_DESC_NEXT_LOCAL_TO_PCI_SHIFT        3 /* established */
#define RAD4_DMA_DESC_NEXT_LOCAL_TO_PCI_MASK         0x1u
#define RAD4_DMA_DESC_NEXT_LOCAL_TO_PCI_INPLACE      (RAD4_DMA_DESC_NEXT_LOCAL_TO_PCI_MASK << RAD4_DMA_DESC_NEXT_LOCAL_TO_PCI_SHIFT)
#define RAD4_DMA_DESC_NEXT_INT_ON_COMPLETE_SHIFT     2 /* established */
#define RAD4_DMA_DESC_NEXT_INT_ON_COMPLETE_MASK      0x1u
#define RAD4_DMA_DESC_NEXT_INT_ON_COMPLETE_INPLACE   (RAD4_DMA_DESC_NEXT_INT_ON_COMPLETE_MASK << RAD4_DMA_DESC_NEXT_INT_ON_COMPLETE_SHIFT)
#define RAD4_DMA_DESC_NEXT_END_OF_CHAIN_SHIFT        1 /* established */
#define RAD4_DMA_DESC_NEXT_END_OF_CHAIN_MASK         0x1u
#define RAD4_DMA_DESC_NEXT_END_OF_CHAIN_INPLACE      (RAD4_DMA_DESC_NEXT_END_OF_CHAIN_MASK << RAD4_DMA_DESC_NEXT_END_OF_CHAIN_SHIFT)

#define RAD4_DMA_COUNT_BITS                          0x17u /* established */
#define RAD4_DMA_DESC_BYTES                          0x10u /* established */
#define RAD4_EEPROM_RECORD_ADDR                      0x58u /* established */
#define RAD4_EEPROM_RECORD_LEN                       0x28u /* established */
#define RAD4_FB_SIZE                                 0x800000u /* established */
#define RAD4_MODE_COUNT                              0xdu /* established */
#define RAD4_REFERENCE_CLOCK_HZ                      0x1f78a40u /* inferred */

#endif /* RAD4_GEN_H */
