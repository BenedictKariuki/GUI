CFLAGS = -fno-stack-protector -fno-pie -O0 -Wall -std=gnu23 -m16 -ffreestanding -I include -nostdlib
LDFLAGS = -m elf_i386 --nmagic --script=gui.ld
OBJECTS = main.o shapes.o bmp.o
BOBJECTS = bgfx.o
NASMENV = -i include/asm/
export NASMENV

.PHONY: clean  # A phony target is a target that does not refer to files but are just actions.
# However, a phony target can have prerequisites.

all: gui.com

gui.com: $(OBJECTS) $(BOBJECTS)
	ld $(LDFLAGS) $^ -o $@ 		# $^ refers to all dependencies $@ refers to the target

main.o: main.c include/gui.h include/assembly.h include/shapes.h
	cc $(CFLAGS) -c $<

shapes.o: shapes.c include/gui.h include/assembly.h include/shapes.h
	cc $(CFLAGS) -c $<

bmp.o: bmp.c include/gui.h include/bmp.h include/images.h
	cc $(CFLAGS) -c $<

bgfx.o: bgfx.asm include/asm/bgfx.h
	nasm -f elf32 $< -o $@

clean:
	rm -f *.o *.com
