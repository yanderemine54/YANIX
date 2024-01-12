# Copyright (C) 2024 Yanderemine54
# 
# This file is part of YANIX.
# 
# YANIX is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# YANIX is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with YANIX.  If not, see <http://www.gnu.org/licenses/>.

LD = x86_64-elf-ld
LDFLAGS +=-T kernel.ld -nostdlib

export CFLAGS

all: ../../bin/kernel.elf
../../bin/kernel.elf: kernel.o print.o strlen.o io.o
	$(LD) $(LDFLAGS) -o ../../bin/kernel.elf kernel.o print.o strlen.o io.o

print.o: print.c
	$(CC) $(CFLAGS) -c -o print.o print.c

strlen.o: strlen.c
	$(CC) $(CFLAGS) -c -o strlen.o strlen.c

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c -o kernel.o kernel.c

io.o: io.c
	$(CC) $(CFLAGS) -c -o io.o io.c

.PHONY: all
