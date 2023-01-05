# Made by Noah Van Miert
# 12/12/2022
#
# I know this is a mess.
# 
# NOS-KERNEL

BOOT = boot
BUILD = build
KERNEL = kernel

# NASM
ASM = nasm
ASM_FLAGS = -f bin

# GCC
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
CC_FLAGS = -ffreestanding -m32 -g -Wall -Wextra -Werror

# LD
LD = /usr/local/i386elfgcc/bin/i386-elf-ld 
LD_FLAGS = --oformat binary

SOURCES = $(wildcard $(KERNEL)/*.c $(KERNEL)/**/*.c $(KERNEL)/**/**/*.c $(KERNEL)/**/**/**/*.c)
OBJECTS = $(SOURCES:.c=.o)

X86_INTERRUPTS = $(KERNEL)/arch/x86/interrupts


all: $(BUILD) $(BUILD)/kernel.o $(BUILD)/isra.o $(BUILD)/isr.o $(BUILD)/vga_driver.o  $(BUILD)/string.o $(BUILD)/stdio.o $(BUILD)/kpanic.o $(BUILD)/idt.o $(BUILD)/idta.o $(BUILD)/boot.bin

$(BUILD)/kernel.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/kernel.c -o $(BUILD)/kernel.o


$(BUILD)/isra.o: $(KERNEL_FILES)
	$(ASM) -felf $(X86_INTERRUPTS)/isr.asm -o $(BUILD)/isra.o


$(BUILD)/isr.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(X86_INTERRUPTS)/isr.c -o $(BUILD)/isr.o


$(BUILD)/vga_driver.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/drivers/vga/vga_driver.c -o $(BUILD)/vga_driver.o


$(BUILD)/string.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/lib/string.c -o $(BUILD)/string.o


$(BUILD)/stdio.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/lib/stdio.c -o $(BUILD)/stdio.o


$(BUILD)/kpanic.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(KERNEL)/kpanic.c -o $(BUILD)/kpanic.o


$(BUILD)/idt.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c $(X86_INTERRUPTS)/idt.c -o $(BUILD)/idt.o


$(BUILD)/idta.o: $(KERNEL_FILES)
	$(ASM) -felf $(X86_INTERRUPTS)/idt.asm -o $(BUILD)/idta.o

$(BUILD)/boot.bin: $(BOOT)/boot.asm $(BOOT)/kernel_entry.asm $(OBJECTS)
	$(ASM) -felf $(BOOT)/kernel_entry.asm -o $(BUILD)/kernel_entry.o
	$(LD) -o $(BUILD)/nos_kernel.bin -Ttext 0x1000 $(BUILD)/kernel_entry.o $(BUILD)/kernel.o $(BUILD)/isra.o $(BUILD)/isr.o $(BUILD)/idta.o $(BUILD)/idt.o $(BUILD)/vga_driver.o $(BUILD)/string.o $(BUILD)/stdio.o $(BUILD)/kpanic.o $(LD_FLAGS)
	$(ASM) $(ASM_FLAGS) $(BOOT)/boot.asm -o $(BUILD)/boot.bin

	cat $(BUILD)/boot.bin $(BUILD)/nos_kernel.bin > $(BUILD)/nos_tmp.bin
	cat $(BUILD)/nos_tmp.bin $(BOOT)/zero.bin > $(BUILD)/nos.bin


$(BUILD):
	mkdir -p $(BUILD)


run:
	qemu-system-x86_64 -drive format=raw,file="$(BUILD)/nos.bin",index=0,if=floppy, -m 512M


clean:
	rm -rf $(BUILD)
	rm $(KERNEL)/*.o
	rm $(KERNEL)/lib/*.o
	rm $(KERNEL)/drivers/vga/*.o
	rm $(KERNEL)/arch/x86/interrupts/*.o
