# rad4: the RAD4-KM keyboard and mouse controller

How the kernel driver of release 1.3k drives the keyboard and mouse controller of the RAD4-KM (`12d1:0105`). Ratings are as defined in [README.md](README.md). The register definitions are in [registers.toml](registers.toml) (the `km_` registers); the rest of the driver is in [../../software/rad4/kernel-driver.md](../../software/rad4/kernel-driver.md).

## Where it is

The controller is in BAR2 of the board, not in a separate region: its register block starts at BAR2 plus 0xe00000, and register `n` of the sixteen is at that base plus `n * 0x10000` (established: the driver builds the pointer in its register block at attach, and every access to the controller goes through it). The earlier notes placed it in a BAR3 and listed 0xe00000 as a pointer with no found use; both are corrected here. The driver accesses it with aligned 32-bit loads and stores and uses only the low eight bits.

## The part

The register layout and every use match the SCN2681/SCC68681 dual UART index for index: mode registers at 0 and 8, status and clock select at 1 and 9, command at 2 and 10, data at 3 and 11, auxiliary control at 4, interrupt status and mask at 5, the output port configuration at 13 and the output-port set and reset at 14 and 15 (software expectation for the use; inferred that the part is that UART or a compatible one, since nothing names it). The status bits the driver tests are receiver ready (bit 0) and transmitter ready (bit 2). The controller is clocked as 0xff in both clock-select registers, the "external clock, 1x" code of the public part, so the PS/2 clock line is inferred to drive the receiver and transmitter clocks.

The counter and timer registers (6, 7, 12 and the start and stop reads at 14 and 15) are unused. The board's control register has bit 7 set whenever the saved interrupt mask is nonzero (see [registers.toml](registers.toml), `board_control`).

## Initialisation (`init_duart`, established)

Run at attach when the mailbox is zero and the device is `0x105`. In order:

1. Interrupt mask (register 5) written 0; saved mask 0.
2. Both channels: command 0x1a (reset mode pointer, disable receiver and transmitter), 0x20, 0x30, 0x40, 0x50 (reset receiver, reset transmitter, reset errors, reset break change).
3. Both mode registers written 0x07 twice.
4. Auxiliary control 0, both clock selects 0xff, output port configuration 0, output port reset 0xff.
5. Both channels: command 0x05 (enable receiver and transmitter).
6. For each channel, detect the attached device: send 0xff (the PS/2 reset command, see below) and read the reply. A first reply byte of 0xaa followed by 0x00 marks a mouse (code 2); 0xaa followed by anything else marks a keyboard (code 1); no reply leaves the code 0. For a mouse, the channel is then reconfigured: command 0x1a, mode register 0x47, mode register 0x07, command 0x05. The codes are stored in the board state; in the same order the driver treats channel A first, channel B second.

When the mailbox is nonzero the driver does not run this: it takes the codes from mailbox words 1 and 2 instead (BAR0 offsets 0x44 and 0x48), which means a firmware initialiser that ran first stored them there (software expectation).

## Transmit and receive

- **Transmit** (`write_serial_A`, `write_serial_B`): wait up to 5000 polls for transmitter ready, set output port bit 2 (channel A) or 3 (channel B), write the byte, pause 60 ms, then with the interrupt lock held reset the transmitter (command 0x20), mask the channel's interrupt, enable the transmitter (command 0x01), and toggle output bits 6 and 2 (or 7 and 3) in a set-and-reset sequence with short busy delays. It then reads a byte and expects the byte it sent, followed by 0xfa (the PS/2 acknowledge) or 0xf4, and retries up to five times, logging an error when all fail (established). The role of the output port bits is inferred: they gate the PS/2 clock and data lines open-collector style so the controller can send a byte to the device, which the plain UART transmitter cannot do for a clocked protocol.
- **Receive** (`read_serial_A`, `read_serial_B`): wait up to 500,000 polls for receiver ready and return the byte, or 6 on timeout.
- **Interrupt** (`duart_interrupt`): reads the interrupt status and ANDs it with the saved mask; bit 1 drains channel A's receive FIFO and bit 5 channel B's into a 1,024-byte ring buffer per device (the ring's capacity is one less than its size), then signals the reading process. The driver assigns the ring by what the channel carries: keyboard bytes go to the keyboard ring and mouse bytes to the pointer ring, whichever channel they came in on (established).
- **Enable and disable** (`duart_interrupt_control`): per device, set or clear the channel's mask bit (2 for A, 0x20 for B) in the saved mask, write it to register 5, and set or clear board-control bit 7 accordingly. DMA and mode programming drop both enables for their duration (established, see the kernel driver page).

Everything above the receive ring (scan code translation for the terminal, key handler, keyboard LEDs through the kernel's keyboard helper, queueing and the `/dev/rad4_kbd` and `/dev/rad4_pntr` read paths) was not decoded: Unverified.

## PS/2 correspondence (inferred)

The command 0xff is the PS/2 "reset" command, 0xaa the self-test pass reply and 0xfa the acknowledge; 0xf4 is the PS/2 "enable data reporting" command, so the driver evidently accepts its echo as well as the acknowledge; an 0xaa reply followed by a device ID of 0x00 is a PS/2 mouse. The driver's detection logic matches that and the connector is described by the owner's guide as keyboard and mouse ports. The RAD4C-KM product sheet's two 9-pin DIN connectors are a different, later board.

## Not known

The controller part number, the board wiring of its output port bits, the interrupt routing from the UART to the PLX local interrupt input (the board-control register's bit 7 is the only board-level control the driver touches) and whether the RAD4-KM has a separate crystal.
