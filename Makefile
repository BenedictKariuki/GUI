CFLAGS = -fno-stack-protector -fno-pie -O0 -Wall -fno-pie -std=gnu23 -m32 -ffreestanding -I include
LDFLAGS = -m elf_i386 --nmagic --script=gui.ld
OBJECTS = main.o
BOBJECTS = bgfx.o
NASMENV = -i include/asm/
export NASMENV

.PHONY: clean  # a phony target is a target that does not refer to files but are just actions.
			   # However, a phony target can have prerequisites.

all: gui.com

gui.com: $(OBJECTS) $(BOBJECTS)
	ld $(LDFLAGS) $^ -o $@ 		# $^ refers to the first dep. $@ refers to the target

main.o: main.c
	cc $(CFLAGS) -c $^

bgfx.o: bgfx.asm
	nasm -f elf32 $^ -o $@

clean:
	rm -f *.o *.com
