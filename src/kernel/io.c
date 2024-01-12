/**
 * Copyright (C) 2024 Yanderemine54
 * 
 * This file is part of YANIX.
 * 
 * YANIX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * YANIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with YANIX.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "io.h"

static inline void outb(uint16_t port, uint8_t value) {
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port) {
    uint8_t return_value;
    asm volatile ( "inb %1, %0"
                   : "=a"(return_value)
                   : "Nd"(port)
                   : "memory");
    return return_value;
}