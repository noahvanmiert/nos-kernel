# Made by Noah Van Miert
# 12/12/2022
#
# I know this is a mess.
# 
# NOS-KERNEL

BOOT = Boot
BUILD = Build
KERNEL = Kernel

# NASM
ASM = nasm
ASM_FLAGS = -f bin

# GCC
CC = i386-elf-gcc
CC_FLAGS = -ffreestanding -m32 -g -pedantic -Wall -Wextra

# LD
LD = i386-elf-ld 
LD_FLAGS = --oformat binary

SOURCES = $(wildcard $(KERNEL)/*.c $(KERNEL)/**/*.c $(KERNEL)/**/**/*.c)
OBJECTS = $(SOURCES:.c=.o)


all: $(BUILD) $(BUILD)/kernel.o $(BUILD)/vga_driver.o  $(BUILD)/string.o $(BUILD)/stdio.o $(BUILD)/kpanic.o $(BUILD)/boot.bin


$(BUILD)/kernel.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c Kernel/kernel.c -o $(BUILD)/kernel.o


$(BUILD)/vga_driver.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c Kernel/Drivers/Vga/vga_driver.c -o $(BUILD)/vga_driver.o


$(BUILD)/string.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c Kernel/Lib/string.c -o $(BUILD)/string.o


$(BUILD)/stdio.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c Kernel/Lib/stdio.c -o $(BUILD)/stdio.o


$(BUILD)/kpanic.o: $(KERNEL_FILES)
	$(CC) $(CC_FLAGS) -c Kernel/kpanic.c -o $(BUILD)/kpanic.o


$(BUILD)/boot.bin: $(BOOT)/boot.asm $(BOOT)/kernel_entry.asm $(OBJECTS)
	$(ASM) -felf $(BOOT)/kernel_entry.asm -o $(BUILD)/kernel_entry.o
	$(LD) -o $(BUILD)/nos_kernel.bin -Ttext 0x1000 $(BUILD)/kernel_entry.o $(BUILD)/kernel.o $(BUILD)/vga_driver.o $(BUILD)/string.o $(BUILD)/stdio.o $(BUILD)/kpanic.o $(LD_FLAGS)
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
	rm $(KERNEL)/Lib/*.o
	rm $(KERNEL)/Drivers/Vga/*.o
