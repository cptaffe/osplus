
# cross compiler
#CXX = clang -target i686-pc-none-elf
CXX = i686-elf-g++
FLAGS = -nostdlib -O2 -Wall -Wextra
CXXFLAGS = --std=c++11 $(FLAGS) -ffreestanding -fno-builtin -nostdinc -fno-exceptions -fno-rtti
LNKFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib #-lgcc

SRC = main.cc \
	driver/vga.cc \
	io.cc \
	bsod.cc \
	boot.s \
	buffer.cc \
	kernel.cc \
	standard.cc \
	interrupts.cc \
	task.cc \
	proc.s
OBJ_S = $(SRC:.cc=.o)
OBJ = $(OBJ_S:.s=.o)
BIN = kernel

CRTBEGIN:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND:=$(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.s
	$(CXX) $(CXXFLAGS) -c $< -o $@

# NOTE: these must be linked in this order
# crti.o defines the beginning of the .init and .fini
# functions, and ctrn.o defines the ends of each,
# the autogenerated crtbegin.o and crtend.o contain
# some of the body of these functions, and each object
# contains them for static objects and whatnot.
$(BIN): crti.o $(CRTBEGIN) $(OBJ) $(CRTEND) crtn.o
	$(CXX) $(LNKFLAGS) $^ -o $(BIN)

clean:
	$(RM) $(OBJ) $(BIN)
