#===================================================================================================
# Import statements.
#===================================================================================================
import os
import subprocess
import sys


#===================================================================================================
# Main program entry-point.
#===================================================================================================
def main() -> None:
    # ATmega328p memory specifications.
    FLASH_SIZE_BYTES = 0x8000
    RAM_SIZE_BYTES   = 0x800

    # Get path to directory of running script.
    current_dir = os.path.dirname(__file__)

    # Get relative path to build directory.
    build_dir = os.path.join(current_dir, '..', 'build')

    # Search build directory for .hex & .map files.
    result = subprocess.run(['ls', f'{build_dir}'], stdout=subprocess.PIPE, text=True)
    files = result.stdout.split('\n')
    map_files = [file for file in files if file[-3:] == 'map']
    hex_files = [file for file in files if file[-3:] == 'hex']

    # Verify that there is only one .hex file present in directory.
    if len(hex_files) > 1:
        print('Found too many .hex files:')
        for hex_file in hex_files:
            print(f'{hex_file}')
        sys.exit(-1)
    elif len(hex_files) == 0:
        print(f'No .hex files found.')
        sys.exit(-1)
    else:
        print(f'Found .hex file: {hex_files[0]}')

    # Print size of hex file.
    result = subprocess.run(['wc', '-c', f'{build_dir}/{hex_files[0]}'], stdout=subprocess.PIPE, text=True)
    print(f'Size of hex file: {result.stdout.split()[0]} bytes.')

    # Verify that there is only one .map file present in directory.
    if len(map_files) > 1:
        print(f'Found too many .map files: {map_files}')
        sys.exit(-1)
    elif len(map_files) == 0:
        print(f'No .map files found.')
        sys.exit(-1)
    else:
        print(f'Found .map file: {map_files[0]}')

    # Find and print variables in .map-file.
    with open(f'{build_dir}/{map_files[0]}', mode='r') as istream:
        line_num = 1
        for line in istream:
            if line_num == 140:
                tag, start, size = line.split()
                print(int(size, base=16))
            line_num += 1


        # parser_state = ParserState.READ
        # line_print_cnt = 0
        # for line in istream:
        #     state_change = False
        #     line_data = line.split()
        #     with contextlib.suppress(IndexError):
        #         if line_data[0] == '.data' and line_data[2] != '0x0' and len(line_data) == 4:
        #             line_print_cnt = 2
        #             parser_state = ParserState.PRINT
        #             state_change = True
        #         if parser_state == ParserState.PRINT and not state_change:
        #             try:
        #                 address, symbol = line_data
        #                 print(f"Address: {address}  Symbol: {symbol}")
        #             except ValueError:
        #                 print(line_data)
        #             line_print_cnt -= 1
        #             if line_print_cnt == 0:
        #                 parser_state = ParserState.READ
    
    # Exit program gracefully.
    sys.exit(0)


# Protection from script from being run during import.
if __name__ == '__main__':
    main()