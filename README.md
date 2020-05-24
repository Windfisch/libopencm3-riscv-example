playing around with libopencm3 on an inexpensive gd32 riscv board

Any GCC-based RISC-V toolchain should work. This has been tested with:

- `riscv-sifive-elf-gcc`: just works™
- `riscv64-elf-gcc`: you must add `export PREFIX:=riscv64-elf-` to the Makefile (or specify that variable in the environment)
