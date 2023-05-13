.PHONY: all,burn,clean

all: build build/swaw_app.bin

build:
	cmake -DCMAKE_TOOLCHAIN_FILE:FILEPATH=/home/kaplunow/working/sem_8/swaw/projekt/git/bsp/nucleo-f103rb/toolchain.cmake -B build -G "Ninja"
	cmake --build build -t all

build/swaw_app.bin: build build/swaw_app.elf
	arm-none-eabi-objcopy -O binary build/swaw_app.elf build/swaw_app.bin

burn: build/swaw_app.bin
	st-flash write build/swaw_app.bin 0x08000000

clean:
	rm -r build/
