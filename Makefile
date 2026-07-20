QEMU_FLAGS= -drive format=raw,file=build/aether.img  -m 128M -cpu qemu64 -no-reboot -no-shutdown -serial stdio -d int,cpu_reset -D build/qemu.log

boot: boot.asm
	# Create a 16MB blank disk image
	dd if=/dev/zero of=build/aether.img bs=1M count=16
	# Assemble your boot sector (NASM) and write it to sector 0
	nasm -f bin boot.asm -o build/boot.bin
	dd if=build/boot.bin of=build/aether.img conv=notrunc

qemu: boot
	qemu-system-x86_64 $(QEMU_FLAGS)


.PHONY: clean
clean:
	rm -f build/*.bin
	rm -f build/*.img
