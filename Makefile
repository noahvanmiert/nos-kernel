# Made by Noah Van Miert
# 12/12/2022
#
# I know this is a mess.
# 
# NOS-KERNEL
#

# Automatic Variables
# $@ -> Target Name
# $^ -> Dependencies


BOOT = boot
BUILD = build
KERNEL = kernel

KERNEL_MACROS = -D _KERNEL_VERBOSE_MODE 

# NASM
ASM = nasm
ASM_FLAGS = -f bin

# GCC
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
CC_FLAGS = -ffreestanding -m32 -g -Wall -Wextra -Werror -pedantic $(KERNEL_MACROS)

# LD
LD = /usr/local/i386elfgcc/bin/i386-elf-ld 
LD_FLAGS = --oformat binary

SOURCES = $(wildcard $(KERNEL)/*.c $(KERNEL)/**/*.c $(KERNEL)/**/**/*.c $(KERNEL)/**/**/**/*.c)
OBJECTS = $(SOURCES:.c=.o)

QEMU_MEMORY_SIZE = 512M

X86_INTERRUPTS = $(KERNEL)/arch/x86/interrupts


KERNEL_OBJ_FILES = $(BUILD)/kernel.o $(BUILD)/isra.o $(BUILD)/isr.o $(BUILD)/vga_driver.o  $(BUILD)/string.o $(BUILD)/stdio.o $(BUILD)/kpanic.o $(BUILD)/idt.o $(BUILD)/idta.o


all: $(BUILD) $(KERNEL_OBJ_FILES) $(BUILD)/boot.bin


$(BUILD)/kernel.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/kernel.c -o $@


$(BUILD)/isra.o: $(KERNEL_FILES)
	$(ASM) -felf $(X86_INTERRUPTS)/isr.asm -o $@


$(BUILD)/isr.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(X86_INTERRUPTS)/isr.c -o $@


$(BUILD)/vga_driver.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/drivers/vga/vga_driver.c -o $@


$(BUILD)/string.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/lib/string.c -o $@


$(BUILD)/stdio.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/lib/stdio.c -o $@


$(BUILD)/kpanic.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/kpanic.c -o $@


$(BUILD)/idt.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(X86_INTERRUPTS)/idt.c -o $@


$(BUILD)/idta.o: $(KERNEL_FILES)
	$(ASM) -felf $(X86_INTERRUPTS)/idt.asm -o $@


$(BUILD)/boot.bin: $(BOOT)/boot.asm $(BOOT)/kernel_entry.asm $(OBJECTS)
	$(ASM) -felf $(BOOT)/kernel_entry.asm -o $(BUILD)/kernel_entry.o
	$(LD) -o $(BUILD)/nos_kernel.bin -Ttext 0x1000 $(BUILD)/kernel_entry.o $(KERNEL_OBJ_FILES) $(LD_FLAGS)
	$(ASM) $(ASM_FLAGS) $(BOOT)/boot.asm -o $@

	cat $(BUILD)/boot.bin $(BUILD)/nos_kernel.bin > $(BUILD)/nos_tmp.bin
	cat $(BUILD)/nos_tmp.bin $(BOOT)/zero.bin > $(BUILD)/nos.bin


$(BUILD):
	mkdir -p $(BUILD)


help:
	python3 utils/help.py


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
