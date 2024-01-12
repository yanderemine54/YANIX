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

MODULES = kernel boot
SUBDIRS = $(addprefix src/,$(MODULES))

CC = x86_64-elf-gcc
CFLAGS = -Wall -Wextra -ffreestanding -fno-PIE -fno-stack-protector -fno-stack-check -mno-red-zone -nostdlib

export CC
export CFLAGS

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

.PHONY: all
