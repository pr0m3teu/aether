CC=x86_64-elf-gcc
LD=x86_64-elf-ld
ASM=nasm

BUILD=build/

CFLAGS=-Wall -Wextra -Werror
CFLAGS +=-std=c11 -O2 -ffreestanding -fno-PIE -m32
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
	  $(BUILD)vga.o           \
	  $(BUILD)util.o 		  \
	  $(BUILD)serial.o 		  \
	  $(BUILD)kassert.o       \
	  $(BUILD)pic.o			  \
	  $(BUILD)trap.o		  \
	  $(BUILD)kbd.o		      \
	  $(BUILD)driver.o		  \

$(BUILD)aether.img: $(BUILD)boot.bin $(BUILD)kernel.out
	# Create a 16MB blank disk image
	dd if=/dev/zero of=build/aether.img bs=1M count=16
	dd if=build/boot.bin of=build/aether.img conv=notrunc
	dd if=build/kernel.out of=build/aether.img bs=512 seek=1 conv=notrunc


$(BUILD)boot.bin: boot/boot.asm 
	# Assemble your boot sector (NASM) and write it to sector 0
	$(ASM) -f bin boot/boot.asm -o build/boot.bin

$(BUILD)kernel.out: kernel/kernel.ld $(OBJS)
	 $(LD) $(LFLAGS) -o build/kernel.out $(OBJS)
	 
$(BUILD)kernel.o: kernel/kernel.c
	 $(CC) $(CFLAGS) -c kernel/kernel.c -o $(BUILD)kernel.o

$(BUILD)interrupts.o: kernel/interrupts.c kernel/interrupts.h
	$(CC) $(CFLAGS) -c  -o $(BUILD)interrupts.o kernel/interrupts.c 

$(BUILD)interruptsasm.o: kernel/interrupts.s
	$(ASM) -f elf -o $(BUILD)interruptsasm.o kernel/interrupts.s

$(BUILD)vga.o: drivers/vga.c drivers/vga.h
	$(CC) $(CFLAGS) -c -o $(BUILD)vga.o drivers/vga.c

$(BUILD)util.o: common/util.c common/util.h
	$(CC) $(CFLAGS) -c -o $(BUILD)util.o common/util.c


$(BUILD)serial.o: drivers/serial.c drivers/serial.h
	$(CC) $(CFLAGS) -c -o $(BUILD)serial.o drivers/serial.c

$(BUILD)kassert.o: common/kassert.c common/kassert.h
	$(CC) $(CFLAGS) -c -o $(BUILD)kassert.o common/kassert.c

$(BUILD)pic.o: kernel/pic.c kernel/pic.h
	$(CC) $(CFLAGS) -c -o $(BUILD)pic.o kernel/pic.c

$(BUILD)trap.o: kernel/trap.c kernel/interrupts.h
	$(CC) $(CFLAGS) -c -o $(BUILD)trap.o kernel/trap.c

$(BUILD)kbd.o: drivers/kbd.c drivers/kbd.h
	$(CC) $(CFLAGS) -c -o $(BUILD)kbd.o drivers/kbd.c

$(BUILD)driver.o: drivers/driver.c drivers/driver.h
	$(CC) $(CFLAGS) -c -o $(BUILD)driver.o drivers/driver.c


.PHONY: qemu
qemu: $(BUILD)aether.img
	clear
	qemu-system-x86_64 $(QEMU_FLAGS)



.PHONY: clean
clean:
	rm -f build/*.*
