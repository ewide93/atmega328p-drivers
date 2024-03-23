from serial import Serial
import serial
import struct
import time
import sys
from enum import IntEnum
from typing import NamedTuple, List


class FunctionCode(IntEnum):
    TEST = 0x00
    DIGITAL_SET_PIN = 0x10
    DIGITAL_CLEAR_PIN = 0x11
    DIGITAL_TOGGLE_PIN = 0x12


class Response(IntEnum):
    ACK = 0x55
    NACK = 0xAA


class ProtocolState(IntEnum):
    PORT_CLOSED = 0
    IDLE = 1
    TRANSMITTING = 2
    AWAITING_RESPONSE = 3


class UARTConfig(NamedTuple):
    port: str
    baudrate: int
    data_bits: int
    parity: str
    stop_bits: int
    timeout: float


class ProtocolHandler:
    RETRANSMIT_CNT_MAX = 5

    def __init__(self, uart_cfg: UARTConfig) -> None:
        self._state = ProtocolState.PORT_CLOSED
        self._port = uart_cfg.port
        self._baudrate = uart_cfg.baudrate
        self._data_bits = uart_cfg.data_bits
        self._parity = uart_cfg.parity
        self._stop_bits = uart_cfg.stop_bits
        self._timeout = uart_cfg.timeout
        self._serial = None
        self._current_pdu = None
        self._retransmit_cnt = 0
        self._retransmit_delay = 0.1

    def connect(self) -> None:
        self._serial = Serial(
            self._port,
            self._baudrate,
            self._data_bits,
            self._parity,
            self._stop_bits,
            self._timeout,
        )
        self._state = ProtocolState.IDLE

    def disconnect(self) -> None:
        self._serial.close()
        self._state = ProtocolState.PORT_CLOSED

    def _calc_lrc(self, data: bytearray) -> int:
        lrc = 0
        for byte in data:
            lrc = (lrc + byte) & 0xFF
        return (((0xFF - lrc) & 0xFF) + 1) & 0xFF

    def _assemble_pdu(self, func_code: FunctionCode, payload: List[int]) -> bytearray:
        pdu = bytearray([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
        pdu[0] = func_code & 0xFF
        for i, byte in enumerate(payload):
            pdu[1 + i] = byte & 0xFF
        pdu[7] = self._calc_lrc(pdu[0:7])
        return pdu

    def _handle_response(self, response: Response) -> None:
        match response:
            case Response.ACK:
                print("ACK Recieved")
            case Response.NACK:
                self._retransmit()
            case _:
                print(f"Invalid response recieved: {hex(response)}")

    def send(self, func_code: FunctionCode, data: List[int]) -> None:
        self._state = ProtocolState.TRANSMITTING
        pdu = self._assemble_pdu(func_code, data)
        print(f"Sending PDU: {[hex(byte) for byte in pdu]}")
        self._current_pdu = pdu
        self._serial.write(pdu)

        self._state = ProtocolState.AWAITING_RESPONSE
        response_raw = self._serial.read()
        try:
            response = struct.unpack("<B", response_raw)[0]
            self._handle_response(response)
        except struct.error:
            print(f"No response from {self._port}")
        self._state = ProtocolState.IDLE
        self._current_pdu = None

    def _retransmit(self) -> None:
        if self._retransmit_cnt < self.RETRANSMIT_CNT_MAX:
            time.sleep(self._retransmit_delay)
            self._state = ProtocolState.TRANSMITTING
            print(f"Retransmitting PDU: {[hex(byte) for byte in self._current_pdu]}")
            self._retransmit_cnt += 1
            print(f"Retransmit counter: {self._retransmit_cnt}")
            self._serial.write(self._current_pdu)

            self._state = ProtocolState.AWAITING_RESPONSE
            response_raw = self._serial.read()
            try:
                response = struct.unpack("<B", response_raw)[0]
                self._handle_response(response)
            except struct.error:
                print(f"No response from {self._port}")
            self._state = ProtocolState.IDLE
            self._current_pdu = None
        else:
            print(f"Max number of retransmissions({self.RETRANSMIT_CNT_MAX}) reached.")
            self.disconnect()
            sys.exit(-1)



def main() -> None:
    uart_cfg = UARTConfig("COM3", 115200, 8, "N", 1, 2.5)
    uart = ProtocolHandler(uart_cfg)
    uart.connect()
    uart.send(FunctionCode.TEST, [0x05])
    uart.disconnect()


if __name__ == "__main__":
    main()
