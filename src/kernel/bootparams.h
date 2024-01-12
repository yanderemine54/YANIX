// Copyright (C) 2024 Yanderemine54
// 
// This file is part of YANIX.
// 
// YANIX is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// YANIX is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with YANIX.  If not, see <http://www.gnu.org/licenses/>.

#ifndef YANIX_KERNEL_BOOTPARAMS_H
#define YANIX_KERNEL_BOOTPARAMS_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    unsigned int*  address;
    unsigned int   width;
    unsigned int   height;
    unsigned int   pitch;
} framebuffer_t;

typedef struct {
    int            argc;
    char**         argv;
    framebuffer_t* framebuffer;
} boot_parameters_t;
#ifdef __cplusplus
}
#endif
#endif