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
#include "bootparams.h"
#include <stddef.h>

void _start(boot_parameters_t* args) {
    kprint("Welcome to YANIX 0.1.0!\n\n# ", args->framebuffer);
}