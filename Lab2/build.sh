
rm bin/*.o bin/calculadora.elf bin/calculadora.bin

echo "Asemblando..."
arm-none-eabi-as os/root.s -o bin/root.o

echo "Compilando..."
arm-none-eabi-gcc os/os.c -o bin/os.o -c
arm-none-eabi-gcc lib/stdio.c -o bin/stdio.o -c
arm-none-eabi-gcc lib/string.c -o bin/string.o -c
arm-none-eabi-gcc app/main.c -o bin/main.o -c

echo "Linkeando..."
# arm-none-eabi-ld -T os/linker.ld bin/root.o bin/stdio.o bin/string.o bin/os.o bin/main.o -o bin/calculadora.elf
arm-none-eabi-gcc -T os/linker.ld -nostdlib bin/root.o bin/stdio.o bin/string.o bin/os.o bin/main.o -lgcc -o bin/calculadora.elf

echo "Binarizando..."
arm-none-eabi-objcopy -O binary bin/calculadora.elf bin/calculadora.bin

echo "Finalizado."