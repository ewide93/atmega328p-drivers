import serial
import struct
import time

def calc_lrc(data: list) -> int:
    lrc = 0
    for byte in data:
        lrc = (lrc + byte) & 0xFF
    return (((0xFF - lrc) & 0xFF) + 1) & 0xFF


def assemble_pdu(func_code: int, payload: list) -> bytearray:
    msg = bytearray([0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
    msg[0] = func_code & 0xFF
    for i, byte in enumerate(payload):
        msg[1 + i] = byte & 0xFF
    msg[7] = calc_lrc(msg[0:7])
    return msg


def main() -> None:
    UART_CFG = {
        "port": "COM3",
        "baudrate": 115200,
        "data_bits": 8,
        "parity": "N",
        "stop_bits": 1,
        "timeout": None,
    }

    ACK_RESPONSE = 0x55
    NACK_RESPONSE = 0xAA

    uart = serial.Serial(UART_CFG["port"], UART_CFG["baudrate"],
                         UART_CFG["data_bits"], UART_CFG["parity"],
                         UART_CFG["stop_bits"], UART_CFG["timeout"])

    for _ in range(8):
        msg = assemble_pdu(0, [5])
        print(f"Transmitting PDU: {[hex(x) for x in msg]}")
        uart.write(msg)
        raw_response = uart.read()
        response = struct.unpack("<B", raw_response)[0]
        if response == ACK_RESPONSE:
            print(f"ACK recieved: {hex(response)}")
        elif response == NACK_RESPONSE:
            print(f"NACK recieved: {hex(response)}")
        else:
            print(f"Invalid response recived: {hex(response)}")
        time.sleep(0.75)

    uart.close()


if __name__ == "__main__":
    main()