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

#!/bin/bash

# Script that creates a raw disk image for use in QEMU.
# NOTE: This needs to be run as root and WILL NOT work if you already have
# /dev/loop0 mounted.

dd if=/dev/zero of=diskimage.dd bs=512 count=2880
fdisk diskimage.dd
losetup --sizelimit $[8*512*2880] -f diskimage.dd
mkfs.vfat -F 12 -n "EFI System" /dev/loop0
mkdir iso
mount /dev/loop0 iso
mkdir -p iso/EFI/BOOT
cp bin/boot.efi iso/EFI/BOOT/BOOTX64.EFI
cp bin/kernel.elf iso
umount iso
rmdir iso
losetup -d /dev/loop0
