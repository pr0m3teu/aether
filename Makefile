CC=x86_64-elf-gcc
LD=x86_64-elf-ld
ASM=nasm

BUILD=build/
$(shell mkdir -p $(BUILD))

CFLAGS=-Wall -Wextra -Werror -nostdinc -I.
CFLAGS +=-std=c11 -O2 -ffreestanding -fno-PIE -m32
CFLAGS +=-MMD -MP
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
	  $(BUILD)console.o       \

VPATH=common:drivers:kernel

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
	 

$(BUILD)%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<


$(BUILD)interruptsasm.o: interrupts.s
	$(ASM) -f elf -o $@ $<


-include $(OBJS:.o=.d)

.PHONY: qemu
qemu: $(BUILD)aether.img
	clear
	qemu-system-x86_64 $(QEMU_FLAGS)



.PHONY: clean
clean:
	rm -f build/*.*
