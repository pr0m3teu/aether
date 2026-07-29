# Aether

This project is a small hobbyist operating system intended for my own learning.
It is currently working only inside QEMU with full hardware support as a future prospect.

## Requirements
 
- An `elf`-targeting cross-compiler toolchain (GCC + binutils) capable of building 32-bit freestanding binaries, plus `ld`
- [NASM](https://www.nasm.us/) for assembling the bootloader and low-level interrupt stubs
- [QEMU](https://www.qemu.org/) (`qemu-system-x86_64`) for running the OS
- GNU Make

## Building

First, install the following dependencies:

```bash
sudo apt update
sudo apt install qemu build-essential nasm qemu-system-x86
```

Then make sure to choose the correct cross-compiler on your system:

```makefile
# Comment this out if you don't have a cross-compiler
TOOLPREFIX=x86_64-elf-
# Uncomment for no cross-compiler
# TOOLPREFIX= 
```

Finally, simply run:
```bash
make qemu
```

This assembles the bootloader, compiles and links the kernel, writes both into a raw disk image (`build/aether.img`), 
and boots it in QEMU with serial output mirrored to stdio.
 
```bash
make clean   # remove build artifacts
```

On a successful boot you should see something like:
 
```
Welcome to project Aether!
Hello from Protected Mode!
>
```
 
Typing at that point echoes characters to the screen through the keyboard IRQ → console pipeline.

## Features
It's a small operating system built from scratch with a custom MBR single-stage bootloader,
kernel and a few drivers.

### Echo OS
For now the project is just a simple kernel that mimics and echo server. 
It can only read some input from the keyboard (not all keys and key combinations have been mapped yet)
and display it to VGA. 

## Roadmap

The following goals should be reached in order to reach a v0.1.0 release:
- [ ] Switch to Long Mode
- [ ] Gather CPU feature information at boot (CPUID)
- [ ] Add virtual memory support (paging, virtual-to-physical translation)
- [ ] Expand hardware driver coverage (APIC, PIT, more of PS/2, etc.) 
- [ ] Implement processes. (Kernel process data structure, process creation, etc.)
- [ ] Implement a Round-Robin scheduler.
- [ ] Implement a proper Kernel debugging console. 
- [ ] Add ELF file format support.
- [ ] Add UEFI bootloader, or make OS UEFI compliant.
- [ ] Add the first `init` user-level process.


This is the bare minimum for a "stable" version, not an exhaustive list.
 
## References
 
`references.md` holds links to the documentation and tutorial sites used to learn the foundational concepts behind this code.
