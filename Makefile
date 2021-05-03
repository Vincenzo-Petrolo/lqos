all: build run

build:
	nasm -felf32 boot.asm -o boot.o
	~/opt/cross/bin/i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	~/opt/cross/bin/i686-elf-gcc -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	./utils/verify_multiboot
	./utils/bake_iso
run:
	qemu-system-x86_64 -cdrom lqos.iso
