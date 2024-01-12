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

#ifndef YANIX_BOOT_ELF_H
#define YANIX_BOOT_ELF_H
#ifdef __cplusplus
extern "C" {
#endif
#include <uefi/uefi.h>
/** ELF constants and headers **/
#define ELF_MAGIC_NUMBER             "\177ELF"
#define ELF_MAGIC_NUMBER_SIZE        4
#define ARCHITECTURE_WORD_SIZE_INDEX 4         /* 4 because we count from 0 */
#define ENDIANNESS_INDEX             5         /* Again, we count from 0 */
#define WORD_SIZE                    2         /* 64-bit; 1 = 32-bit, 2 = 64-bit */
#define ENDIANNESS                   1         /* Little endian; 1 = little endian, 2 = big endian */
#define FILE_TYPE_EXECUTABLE         2         
#define LAODABLE_SEGMENT             1
#ifdef __x86_64__
#define ARCHITECTURE                 0x3E      /* x86_64 architecture */
#endif
#ifdef __aarch64__
#define ARCHITECTURE                 0xB7      /* 64-bit ARM architecture */
#endif
#ifdef __riscv64__
#define ARCHTIECTURE                 0xF3      /* RISC-V architecture */
#endif

typedef struct {
    uint8_t  ELF_identification[16];           /* Magic number and file information */
    uint16_t ELF_file_type;                    /* Object file type (e.g. executable) */
    uint16_t ELF_machine;                      /* Machine architecture (e.g. aarch64) */
    uint32_t ELF_version;                      /* ELF version, should be 1 */
    uint64_t ELF_entry_point;                  /* Program entry point's virtual address */
    uint64_t ELF_program_header_offset;        /* Program header offset */
    uint64_t ELF_section_header_offset;        /* Section header offset (We don't use it here.) */
    uint32_t ELF_flags;                        /* Processor-specific flags */
    uint16_t ELF_ELF_header_size;              /* ELF header size in bytes */
    uint16_t ELF_program_header_entry_size;    /* Program header table entry size */
    uint16_t ELF_program_header_entry_count;   /* Program header table entry count */
    uint16_t ELF_section_header_entry_size;    /* Section header table entry size */
    uint16_t ELF_section_header_entry_count;   /* Section header table entry count */
    uint16_t ELF_section_header_string_index;  /* Section header string table index */
} ELF64_ELF_header_t;

typedef struct {
    uint32_t program_type;                     /* Segment type */
    uint32_t program_flags;                    /* Segment flags */
    uint64_t program_offset;                   /* Segment file offset */
    uint64_t program_virtual_address;          /* Segment virtual address */
    uint64_t program_physical_address;         /* Segment physical address */
    uint64_t program_file_size;                /* Segment size in file */
    uint64_t program_memory_size;              /* Segment size in memory */
    uint64_t program_alignment;                /* Segment alignment */
} ELF64_program_header_t;
#ifdef __cplusplus
}
#endif
#endif