/* generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source */
/* SPDX-License-Identifier: BSD-3-Clause */
/* defs-gen 2 */
/* input sha256 5c01288c2f4002a51f89eb170adbcd593b1c1683e9feab87f5d24880adb81c28 */
/* RAD4 graphics head registers */
/* Names are RAD4_BOARD_*; name source: ours. */
#ifndef HW_SGI_GPU_RAD4_BOARD_REGS_H
#define HW_SGI_GPU_RAD4_BOARD_REGS_H

#include "hw/core/registerfields.h"

REG32(RAD4_BOARD_ROM_REMAP, 0x14) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */

REG32(RAD4_BOARD_BUS_REGION_DESCRIPTOR, 0x18) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */

REG32(RAD4_BOARD_MAILBOX, 0x40) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */

REG32(RAD4_BOARD_INTCSR, 0x68) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */
FIELD(RAD4_BOARD_INTCSR, DMA0_INT_ACTIVE, 21, 1) /* established */
FIELD(RAD4_BOARD_INTCSR, DMA0_INT_ENABLE, 18, 1) /* established */
FIELD(RAD4_BOARD_INTCSR, LOCAL_INT_OUTPUT_ENABLE, 16, 1) /* established */
FIELD(RAD4_BOARD_INTCSR, LOCAL_INT_INPUT_ACTIVE, 15, 1) /* established */
FIELD(RAD4_BOARD_INTCSR, PCI_LOCAL_INT_ENABLE, 11, 1) /* established */
FIELD(RAD4_BOARD_INTCSR, PCI_INT_ENABLE, 8, 1) /* established */

REG32(RAD4_BOARD_EEPROM_CTL, 0x6c) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */
FIELD(RAD4_BOARD_EEPROM_CTL, DATA_FROM_EEPROM, 27, 1) /* established */
FIELD(RAD4_BOARD_EEPROM_CTL, DATA_TO_EEPROM, 26, 1) /* established */
FIELD(RAD4_BOARD_EEPROM_CTL, CHIP_SELECT, 25, 1) /* established */
FIELD(RAD4_BOARD_EEPROM_CTL, CLOCK, 24, 1) /* established */
FIELD(RAD4_BOARD_EEPROM_CTL, DMA_READ_COMMAND, 0, 4) /* established */

REG8(RAD4_BOARD_FLASH, 0x800000) /* inferred */
#define RAD4_BOARD_FLASH_COUNT 65536
#define RAD4_BOARD_FLASH_STRIDE 0x1

REG32(RAD4_BOARD_RGB561_INDEX_LO, 0x900000) /* inferred */
FIELD(RAD4_BOARD_RGB561_INDEX_LO, VALUE, 0, 8) /* inferred */

REG32(RAD4_BOARD_RGB561_INDEX_HI, 0x910000) /* inferred */
FIELD(RAD4_BOARD_RGB561_INDEX_HI, VALUE, 0, 8) /* inferred */

REG32(RAD4_BOARD_RGB561_DATA, 0x920000) /* inferred */
FIELD(RAD4_BOARD_RGB561_DATA, VALUE, 0, 8) /* inferred */

REG32(RAD4_BOARD_RGB561_DATA_MULTI, 0x930000) /* inferred */
FIELD(RAD4_BOARD_RGB561_DATA_MULTI, VALUE, 0, 8) /* inferred */

REG32(RAD4_BOARD_TIMING_H0, 0xa00000) /* inferred */
#define RAD4_BOARD_TIMING_H0_COUNT 1024
#define RAD4_BOARD_TIMING_H0_STRIDE 0x4

REG32(RAD4_BOARD_TIMING_H1, 0xa01000) /* inferred */
#define RAD4_BOARD_TIMING_H1_COUNT 1024
#define RAD4_BOARD_TIMING_H1_STRIDE 0x4

REG32(RAD4_BOARD_TIMING_H3, 0xa03000) /* inferred */
#define RAD4_BOARD_TIMING_H3_COUNT 1024
#define RAD4_BOARD_TIMING_H3_STRIDE 0x4

REG32(RAD4_BOARD_TIMING_V, 0xb00000) /* inferred */
#define RAD4_BOARD_TIMING_V_COUNT 2048
#define RAD4_BOARD_TIMING_V_STRIDE 0x4

REG32(RAD4_BOARD_PLANE_MASK, 0xd00000) /* inferred */

REG32(RAD4_BOARD_KM_MR, 0xe00000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_SR_CSR_A, 0xe10000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_CR_A, 0xe20000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_DATA_A, 0xe30000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_ACR, 0xe40000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_ISR_IMR, 0xe50000) /* inferred; name source: public (Philips SCC68681 product data) */
FIELD(RAD4_BOARD_KM_ISR_IMR, RX_READY_B, 5, 1) /* inferred */
FIELD(RAD4_BOARD_KM_ISR_IMR, RX_READY_A, 1, 1) /* inferred */

REG32(RAD4_BOARD_KM_MR_B, 0xe80000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_SR_CSR_B, 0xe90000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_CR_B, 0xea0000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_DATA_B, 0xeb0000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_OPCR, 0xed0000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_OPR_SET, 0xee0000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_KM_OPR_RESET, 0xef0000) /* inferred; name source: public (Philips SCC68681 product data) */

REG32(RAD4_BOARD_BOARD_CONTROL, 0xf00000) /* inferred */
FIELD(RAD4_BOARD_BOARD_CONTROL, KM_INTERRUPT_GATE, 7, 1) /* inferred */
FIELD(RAD4_BOARD_BOARD_CONTROL, MODE_GATE_FRAME_STATUS, 5, 1) /* inferred */
FIELD(RAD4_BOARD_BOARD_CONTROL, FRAME_REQUEST, 1, 1) /* inferred */

REG8(RAD4_BOARD_RGB561_SYNC_CTL, 0x20) /* established */

REG8(RAD4_BOARD_RGB561_PLL_VCO, 0x21) /* established */
FIELD(RAD4_BOARD_RGB561_PLL_VCO, RANGE_CODE, 6, 2) /* inferred */
FIELD(RAD4_BOARD_RGB561_PLL_VCO, M_MINUS_65, 0, 6) /* established */

REG8(RAD4_BOARD_RGB561_PLL_REF, 0x22) /* established */
FIELD(RAD4_BOARD_RGB561_PLL_REF, N, 0, 5) /* established */

REG8(RAD4_BOARD_RGB561_CURSOR_CTL, 0x30) /* established */
FIELD(RAD4_BOARD_RGB561_CURSOR_CTL, ENABLE, 0, 1) /* established */

REG8(RAD4_BOARD_RGB561_CURSOR_HOT_X, 0x34) /* established */
FIELD(RAD4_BOARD_RGB561_CURSOR_HOT_X, X, 0, 6) /* established */

REG8(RAD4_BOARD_RGB561_CURSOR_HOT_Y, 0x35) /* established */
FIELD(RAD4_BOARD_RGB561_CURSOR_HOT_Y, Y, 0, 6) /* established */

REG32(RAD4_BOARD_DMAMODE0, 0x100) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */
FIELD(RAD4_BOARD_DMAMODE0, DONE_INT_ENABLE, 10, 1) /* established */
FIELD(RAD4_BOARD_DMAMODE0, CHAINING, 9, 1) /* established */

REG32(RAD4_BOARD_DMADPR0, 0x110) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */

REG32(RAD4_BOARD_DMACSR0, 0x128) /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2) */
FIELD(RAD4_BOARD_DMACSR0, USER, 5, 3) /* established */
FIELD(RAD4_BOARD_DMACSR0, DONE, 4, 1) /* established */
FIELD(RAD4_BOARD_DMACSR0, CLEAR_INT, 3, 1) /* established */
FIELD(RAD4_BOARD_DMACSR0, ABORT, 2, 1) /* established */
FIELD(RAD4_BOARD_DMACSR0, START, 1, 1) /* established */
FIELD(RAD4_BOARD_DMACSR0, ENABLE, 0, 1) /* established */

#define RAD4_BOARD_DMA_DESC_NEXT_WIDTH 32 /* established; name source: public (PLX PCI 9060 Data Sheet, version 1.2); word */
FIELD(RAD4_BOARD_DMA_DESC_NEXT, NEXT, 4, 28) /* established */
FIELD(RAD4_BOARD_DMA_DESC_NEXT, LOCAL_TO_PCI, 3, 1) /* established */
FIELD(RAD4_BOARD_DMA_DESC_NEXT, INT_ON_COMPLETE, 2, 1) /* established */
FIELD(RAD4_BOARD_DMA_DESC_NEXT, END_OF_CHAIN, 1, 1) /* established */

#define RAD4_BOARD_DMA_COUNT_BITS 0x17u /* established */
#define RAD4_BOARD_DMA_DESC_BYTES 0x10u /* established */
#define RAD4_BOARD_EEPROM_RECORD_ADDR 0x58u /* established */
#define RAD4_BOARD_EEPROM_RECORD_LEN 0x28u /* established */
#define RAD4_BOARD_FB_SIZE 0x800000u /* established */
#define RAD4_BOARD_MODE_COUNT 0xdu /* established */
#define RAD4_BOARD_REFERENCE_CLOCK_HZ 0x1f78a40u /* inferred */

#endif /* HW_SGI_GPU_RAD4_BOARD_REGS_H */
