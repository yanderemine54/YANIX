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

#include "print.h"
#include "string.h"
#include "fonts/font8x8.h"
#include "bootparams.h"
#include <stddef.h>

int line = 0;
int column = 0;

void putpixel(int x, int y, int color, framebuffer_t* framebuffer) {
    unsigned int* framebuffer_pointer = framebuffer->address;
    unsigned int position = x + y * (framebuffer->pitch / 4);
    framebuffer_pointer[position] = color;
}


void putchar(char c, int x, int y, int foreground_color, int background_color, framebuffer_t* framebuffer) {
    int j, i;
    char* glyph = font8x8_basic[c];
    for (j = 0; j < 8; j++) { /* Line by line */
        for (i = 0; i < 8; i++) { /* Pixel by pixel*/
            putpixel(x + i, y + j, glyph[j] & (1 << i) ? foreground_color : background_color, framebuffer);
        }
    }
}

void kprint(const char* string, framebuffer_t* framebuffer) {
    for (size_t index = 0; index < strlen(string); index++) {
        column++;
        if (string[index] == '\n') {
            line++;
            column = 0;
        }
        putchar(string[index], column*8, line*8, 0x808080, 0x000000, framebuffer);
    }
}

