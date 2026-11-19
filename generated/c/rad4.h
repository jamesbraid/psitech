/* generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source */
/* SPDX-License-Identifier: BSD-3-Clause */
/* defs-gen 2 */
/* input sha256 610c8d4ccc0b111742935107dabbda7f5141463a0b9e88789b53045ae90f2724 */
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
 * Mailbox. Software expectation: the driver reads it at attach and skips its own mode and RAMDAC setup when it is nonzero, because it takes that to mean a firmware initialiser has run. What a real card holds here after power-on is unknown.
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
 * Serial EEPROM control. Bits 24 to 27 drive the configuration EEPROM. The driver also replaces the low nibble with 0xc at attach, a use the datasheet reading here does not explain.
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
 * Board control and status. Software expectation: the driver clears bit 5 while it programs a mode and sets it afterwards, sets bit 1 to ask for an interrupt at the next frame and clears it around DMA transfers, and its interrupt handler tests bit 5. That bit 5 reports a frame event only while bit 1 is set is inferred. The physical effects are unknown.
 */
/* board_control: rw32, space bar2, reset unknown; PsiTech RAD4 release 1.3k driver */
#define RAD4_BOARD_CONTROL_OFFSET                    0xf00000u /* inferred */
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
