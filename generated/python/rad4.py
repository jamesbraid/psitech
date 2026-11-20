"""generated from devices/rad4/registers.toml by defs-gen - do not edit, change the source
SPDX-License-Identifier: BSD-3-Clause
defs-gen 2
input sha256 93b0ddd09dc551607b6d636875bca6ee0e31cbf5a4d2bbdb6c4612238c3328c1
RAD4 graphics head registers"""

UNIT = 'rad4'
REGISTERS = {'rom_remap': {'offset': 20, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar0', 'reset': 'unknown', 'grade': 'established'}, 'bus_region_descriptor': {'offset': 24, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar0', 'reset': 'unknown', 'grade': 'established'}, 'mailbox': {'offset': 64, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar0', 'reset': 'unknown', 'grade': 'established'}, 'intcsr': {'offset': 104, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar0', 'reset': 65792, 'grade': 'established'}, 'eeprom_ctl': {'offset': 108, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar0', 'reset': 'unknown', 'grade': 'established'}, 'flash': {'offset': 8388608, 'access': 'rw', 'width': 8, 'count': 65536, 'stride': 1, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'rgb561_index_lo': {'offset': 9437184, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'rgb561_index_hi': {'offset': 9502720, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'rgb561_data': {'offset': 9568256, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'rgb561_data_multi': {'offset': 9633792, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'timing_h0': {'offset': 10485760, 'access': 'rw', 'width': 32, 'count': 1024, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'timing_h1': {'offset': 10489856, 'access': 'rw', 'width': 32, 'count': 1024, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'timing_h3': {'offset': 10498048, 'access': 'rw', 'width': 32, 'count': 1024, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'timing_v': {'offset': 11534336, 'access': 'rw', 'width': 32, 'count': 2048, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'plane_mask': {'offset': 13631488, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_mr': {'offset': 14680064, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_sr_csr_a': {'offset': 14745600, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_cr_a': {'offset': 14811136, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_data_a': {'offset': 14876672, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_acr': {'offset': 14942208, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_isr_imr': {'offset': 15007744, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_mr_b': {'offset': 15204352, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_sr_csr_b': {'offset': 15269888, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_cr_b': {'offset': 15335424, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_data_b': {'offset': 15400960, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_opcr': {'offset': 15532032, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_opr_set': {'offset': 15597568, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'km_opr_reset': {'offset': 15663104, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'board_control': {'offset': 15728640, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'bar2', 'reset': 'unknown', 'grade': 'inferred'}, 'rgb561_sync_ctl': {'offset': 32, 'access': 'rw', 'width': 8, 'count': 1, 'stride': 1, 'space': 'rgb561', 'reset': 'unknown', 'grade': 'established'}, 'rgb561_pll_vco': {'offset': 33, 'access': 'rw', 'width': 8, 'count': 1, 'stride': 1, 'space': 'rgb561', 'reset': 'unknown', 'grade': 'established'}, 'rgb561_pll_ref': {'offset': 34, 'access': 'rw', 'width': 8, 'count': 1, 'stride': 1, 'space': 'rgb561', 'reset': 'unknown', 'grade': 'established'}, 'rgb561_cursor_ctl': {'offset': 48, 'access': 'rw', 'width': 8, 'count': 1, 'stride': 1, 'space': 'rgb561', 'reset': 'unknown', 'grade': 'established'}, 'rgb561_cursor_hot_x': {'offset': 52, 'access': 'rw', 'width': 8, 'count': 1, 'stride': 1, 'space': 'rgb561', 'reset': 'unknown', 'grade': 'established'}, 'rgb561_cursor_hot_y': {'offset': 53, 'access': 'rw', 'width': 8, 'count': 1, 'stride': 1, 'space': 'rgb561', 'reset': 'unknown', 'grade': 'established'}, 'dmamode0': {'offset': 256, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'rom', 'reset': 'unknown', 'grade': 'established'}, 'dmadpr0': {'offset': 272, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'rom', 'reset': 'unknown', 'grade': 'established'}, 'dmacsr0': {'offset': 296, 'access': 'rw', 'width': 32, 'count': 1, 'stride': 4, 'space': 'rom', 'reset': 4112, 'grade': 'established'}}
WORDS = {'DMA_DESC_NEXT': {'width': 32, 'grade': 'established'}}
FIELDS = {'rom_remap': {}, 'bus_region_descriptor': {}, 'mailbox': {}, 'intcsr': {'dma0_int_active': (21, 21), 'dma0_int_enable': (18, 18), 'local_int_output_enable': (16, 16), 'local_int_input_active': (15, 15), 'pci_local_int_enable': (11, 11), 'pci_int_enable': (8, 8)}, 'eeprom_ctl': {'data_from_eeprom': (27, 27), 'data_to_eeprom': (26, 26), 'chip_select': (25, 25), 'clock': (24, 24), 'dma_read_command': (3, 0)}, 'flash': {}, 'rgb561_index_lo': {'value': (7, 0)}, 'rgb561_index_hi': {'value': (7, 0)}, 'rgb561_data': {'value': (7, 0)}, 'rgb561_data_multi': {'value': (7, 0)}, 'timing_h0': {}, 'timing_h1': {}, 'timing_h3': {}, 'timing_v': {}, 'plane_mask': {}, 'km_mr': {}, 'km_sr_csr_a': {}, 'km_cr_a': {}, 'km_data_a': {}, 'km_acr': {}, 'km_isr_imr': {'rx_ready_b': (5, 5), 'rx_ready_a': (1, 1)}, 'km_mr_b': {}, 'km_sr_csr_b': {}, 'km_cr_b': {}, 'km_data_b': {}, 'km_opcr': {}, 'km_opr_set': {}, 'km_opr_reset': {}, 'board_control': {'km_interrupt_gate': (7, 7), 'mode_gate_frame_status': (5, 5), 'frame_request': (1, 1)}, 'rgb561_sync_ctl': {}, 'rgb561_pll_vco': {'range_code': (7, 6), 'm_minus_65': (5, 0)}, 'rgb561_pll_ref': {'n': (4, 0)}, 'rgb561_cursor_ctl': {'enable': (0, 0)}, 'rgb561_cursor_hot_x': {'x': (5, 0)}, 'rgb561_cursor_hot_y': {'y': (5, 0)}, 'dmamode0': {'done_int_enable': (10, 10), 'chaining': (9, 9)}, 'dmadpr0': {}, 'dmacsr0': {'user': (7, 5), 'done': (4, 4), 'clear_int': (3, 3), 'abort': (2, 2), 'start': (1, 1), 'enable': (0, 0)}, 'DMA_DESC_NEXT': {'next': (31, 4), 'local_to_pci': (3, 3), 'int_on_complete': (2, 2), 'end_of_chain': (1, 1)}}
ENUMS = {}
FIELD_ENUM = {}
CONSTANTS = {'DMA_COUNT_BITS': {'value': 23, 'count': 1, 'stride': 1}, 'DMA_DESC_BYTES': {'value': 16, 'count': 1, 'stride': 1}, 'EEPROM_RECORD_ADDR': {'value': 88, 'count': 1, 'stride': 1}, 'EEPROM_RECORD_LEN': {'value': 40, 'count': 1, 'stride': 1}, 'FB_SIZE': {'value': 8388608, 'count': 1, 'stride': 1}, 'MODE_COUNT': {'value': 13, 'count': 1, 'stride': 1}, 'REFERENCE_CLOCK_HZ': {'value': 33000000, 'count': 1, 'stride': 1}}
TESTS = []


def decode(name, value):
    """Field name -> value for a register or word."""
    return {f: (value >> lo) & ((1 << (hi - lo + 1)) - 1) for f, (hi, lo) in FIELDS[name].items()}


def encode(name, **fields):
    v = 0
    for f, x in fields.items():
        hi, lo = FIELDS[name][f]
        if x >> (hi - lo + 1):
            raise ValueError('%s.%s: %d does not fit' % (name, f, x))
        v |= x << lo
    return v


def describe(name, value):
    """decode, with enum labels where the field has an enum."""
    out = {}
    for f, x in decode(name, value).items():
        e = ENUMS.get(FIELD_ENUM.get('%s.%s' % (name, f)))
        out[f] = e.get(x, x) if e else x
    return out


def selftest():
    for name, value, expect in TESTS:
        got = decode(name, value)
        for f, want in expect.items():
            assert got[f] == want, (name, hex(value), f, got[f], want)
    return len(TESTS)


if __name__ == '__main__':
    print('%s: %d vectors ok' % (UNIT, selftest()))
