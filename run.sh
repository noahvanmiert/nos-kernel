set +xe

nasm -f bin Boot/boot.asm -o Build/boot.bin
qemu-system-x86_64 Build/boot.bin