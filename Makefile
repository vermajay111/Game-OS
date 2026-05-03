CC = gcc
LD = ld
AS = nasm

CFLAGS = -m32 -ffreestanding -fno-pic -fno-stack-protector -Iinclude
LDFLAGS = -m elf_i386 -T scripts/linker.ld --oformat binary

all: bin/game_os.img


build/boot.bin: src/boot/boot.asm
	mkdir -p build bin
	$(AS) -f bin $< -o $@


build/entry.o: src/kernel/entry.asm
	mkdir -p build
	$(AS) -f elf32 $< -o $@


build/kernel.o: src/kernel/kernel.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/vga.o: src/drivers/vga/vga.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@


build/kernel.bin: build/entry.o build/kernel.o build/vga.o
	$(LD) $(LDFLAGS) $^ -o $@

bin/game_os.img: build/boot.bin build/kernel.bin
	cat $^ > $@

run: all
	qemu-system-x86_64 -drive format=raw,file=bin/game_os.img

clean:
	rm -rf build bin