# Made by Noah Van Miert
# 12/12/2022
# 
# NOS-KERNEL

BOOT = Boot
BUILD = Build
ASM = nasm
ASM_FLAGS = -f bin


all: $(BUILD) $(BUILD)/boot.bin


$(BUILD)/boot.bin: $(BOOT)/boot.asm
	$(ASM) $(ASM_FLAGS) $^ -o $@


$(BUILD):
	mkdir -p $(BUILD)


run:
	qemu-system-x86_64 $(BUILD)/boot.bin


clean:
	rm -rf $(BUILD)
