# UETRV_Pcore

UETRV_Pcore is a RISC-V based application class SoC integrating a 5-stage pipelined processor with memory and peripherals. Currently, the core implements RV32IMAZicsr ISA based on User-level ISA Version 2.0 and Privileged Architecture Version 1.11 supporting M/S/U modes. Following are the key features of the SoC:

## Key Features
- 32-bit RISC-V ISA core that supports base integer (I) and multiplication and division (M), atomic (A) and Zicsr (Z) extensions (RV32IMAZicsr).
- Supports user, supervisor and machine mode privilege levels.
- Support for instruction / data (writeback) caches.
- Sv32 based MMU support and is capable of running Linux.
- Cache size, TLB entries etc., are configurable.
- Intergated PLIC, CLINT, uart, spi peripherals. 
- Uses RISOF framework to run architecture compatibility tests.

This branch can be used to run UETRV-Pcore on Nexys A7 FPGA. It contains a running project on Vivado 2019 and prebuilt Linux images.

## Opening project in Vivado 2019
Type in the following command to open the project in Vivado 2019
```
vivado PCore_FPGA/PCore_FPGA.xpr
```

## Generate bitstream
New bitstream can be generated with the exisitng project or you may find a working bitstream in folder ``PCore_FPGA/bitstream_working``

## Booting Linux Image
* Load the bitstream on the FPGA, your serial monitor will show message `Load File`
* Type in the following commands to load the prebuilt Linux image
  ```
  cd sdk/load_uart
  python3 serial_sendfile.py <baud_rate in MHz> <path/to/image/file>
  ```
* Baud rate of existing bitstream is ``1250000``. Sample images are saved in ``sdk/load_uart`` folder.
* If using default baud rate and default bitstream, the following command can be run
  ```
  python3 serial_sendfile.py 1.25 imem12.bin
  ```
