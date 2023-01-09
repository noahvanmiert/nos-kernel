# Made by Noah Van Miert
# 12/12/2022
# 
# NOS-KERNEL
#

# Automatic Variables
# $@ -> Target Name
# $^ -> Dependencies


BOOT   = boot
BUILD  = build
KERNEL = kernel


KERNEL_VERSION = 0.1.0
KERNEL_MACROS = -D _KERNEL_VERBOSE_MODE


# NASM
ASM       = nasm
ASM_FLAGS = -f bin


# GCC
CC       = /usr/local/i386elfgcc/bin/i386-elf-gcc
CC_FLAGS = -ffreestanding -m32 -g -Wall -Wextra -Werror -pedantic -std=c11 $(KERNEL_MACROS)


# LD
LD       = /usr/local/i386elfgcc/bin/i386-elf-ld 
LD_FLAGS = --oformat binary


# All the source and object file of the kernel
SOURCES = $(wildcard $(KERNEL)/*.c $(KERNEL)/**/*.c $(KERNEL)/**/**/*.c $(KERNEL)/**/**/**/*.c)
OBJECTS = $(SOURCES:.c=.o)


# Qemu Variables
QEMU_MEMORY_SIZE = 512M


X86_INTERRUPTS = $(KERNEL)/arch/x86/interrupts


KERNEL_OBJ_FILES = $(BUILD)/kernel.o $(BUILD)/isra.o $(BUILD)/isr.o $(BUILD)/vga_driver.o  $(BUILD)/string.o $(BUILD)/stdio.o $(BUILD)/kpanic.o $(BUILD)/idt.o $(BUILD)/idta.o


all: $(BUILD) $(KERNEL_OBJ_FILES) $(BUILD)/boot.bin


$(BUILD)/kernel.o: $(KERNEL)/kernel.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/isra.o: $(X86_INTERRUPTS)/isr.asm
	$(ASM) -felf $^ -o $@


$(BUILD)/isr.o: $(X86_INTERRUPTS)/isr.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/vga_driver.o: $(KERNEL)/drivers/vga/vga_driver.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/string.o: $(KERNEL)/lib/string.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/stdio.o: $(KERNEL)/lib/stdio.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/kpanic.o: $(KERNEL)/kpanic.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/idt.o: $(X86_INTERRUPTS)/idt.c
	$(CC) $(CC_FLAGS) -c $^ -o $@


$(BUILD)/idta.o: $(X86_INTERRUPTS)/idt.asm
	$(ASM) -felf $^ -o $@


$(BUILD)/boot.bin: $(BOOT)/boot.asm $(BOOT)/kernel_entry.asm $(OBJECTS)
	$(ASM) -felf $(BOOT)/kernel_entry.asm -o $(BUILD)/kernel_entry.o
	$(LD) -o $(BUILD)/nos_kernel.bin -Ttext 0x1000 $(BUILD)/kernel_entry.o $(KERNEL_OBJ_FILES) $(LD_FLAGS)
	$(ASM) $(ASM_FLAGS) $(BOOT)/boot.asm -o $@

	cat $@ $(BUILD)/nos_kernel.bin > $(BUILD)/nos_tmp.bin
	cat $(BUILD)/nos_tmp.bin $(BOOT)/zero.bin > $(BUILD)/nos.bin


$(BUILD):
	mkdir -p $(BUILD)


help:
	@echo "make                   -    Compiles the kernel into a binary"
	@echo "make run               -    Launch Qemu with the compiled kernel"
	@echo "make clean             -    Remove all the build files"
	@echo "make version           -    Prints the kernel version"
	@echo ""
	@echo "make install-debian    -    Install all the dependencies on debian-based platforms"
	@echo "make install-arch      -    Install all the dependencies on arch-based platforms"


version:
	@echo "nos-kernel version $(KERNEL_VERSION)"


install-debian:
	utils/debian_dependencies.sh


install-arch:
	utils/arch_dependencies.sh


run:
	qemu-system-x86_64 -drive format=raw,file="$(BUILD)/nos.bin",index=0,if=floppy, -m $(QEMU_MEMORY_SIZE)


clean:
	rm -rf $(BUILD)
	rm -f $(KERNEL)/*.o
	rm -f $(KERNEL)/lib/*.o
	rm -f $(KERNEL)/drivers/vga/*.o
	rm -f $(KERNEL)/arch/x86/interrupts/*.o
