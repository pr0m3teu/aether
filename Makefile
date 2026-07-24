CC=x86_64-elf-gcc
LD=x86_64-elf-ld
ASM=nasm

BUILD=build/

CFLAGS=-Wall -Wextra -std=c11 -O2 -ffreestanding -fno-PIE -m32
CFLAGS +=-I.
CFLAGS +=-nostdinc
# Because of no SSE availability yet
CFLAGS +=-mno-sse -mno-sse2 -mno-mmx -mno-80387

LFLAGS=-T kernel/kernel.ld --oformat binary -m elf_i386
QEMU_FLAGS=-drive format=raw,file=build/aether.img -m 128M \
		   	-cpu qemu64 \
			-no-reboot -no-shutdown \
			-serial stdio \
			-d int,cpu_reset,in_asm \
			-D $(BUILD)qemu.log

OBJS= $(BUILD)kernel.o        \
	  $(BUILD)interrupts.o    \
	  $(BUILD)interruptsasm.o \
	  $(BUILD)vga_driver.o    \




$(BUILD)boot.bin: boot.asm build/kernel.out
	# Create a 16MB blank disk image
	dd if=/dev/zero of=build/aether.img bs=1M count=16

	# Assemble your boot sector (NASM) and write it to sector 0
	$(ASM) -f bin boot.asm -o build/boot.bin
	dd if=build/boot.bin of=build/aether.img conv=notrunc
	dd if=build/kernel.out of=build/aether.img bs=512 seek=1 conv=notrunc


$(BUILD)kernel.out: kernel/kernel.ld $(OBJS)
	 $(LD) $(LFLAGS) -o build/kernel.out $(OBJS)
	 

$(BUILD)kernel.o: kernel/kernel.c
	 $(CC) $(CFLAGS) -c kernel/kernel.c -o $(BUILD)kernel.o


$(BUILD)interrupts.o: kernel/interrupts.c kernel/interrupts.h
	$(CC) $(CFLAGS) -c  -o $(BUILD)interrupts.o kernel/interrupts.c 


$(BUILD)interruptsasm.o: kernel/interrupts.s
	$(ASM) -f elf kernel/interrupts.s -o $(BUILD)interruptsasm.o 


$(BUILD)vga_driver.o: drivers/vga_driver.c drivers/vga_driver.h
	$(CC) $(CFLAGS) -c drivers/vga_driver.c -o build/vga_driver.o


.PHONY: qemu
qemu: build/boot.bin build/kernel.out
	qemu-system-x86_64 $(QEMU_FLAGS)


.PHONY: clean
clean:
	rm -f build/*.*
