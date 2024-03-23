import serial
import struct
import time


def main() -> None:
    UART_CFG = {
        "port": "COM3",
        "baudrate": 9600,
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
        msg_list = [0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]
        msg = struct.pack("<8B", 0, 5, 0, 0, 0, 0, 0, 0)
        for byte in msg:
            print(f"Byte: {hex(byte)}")
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