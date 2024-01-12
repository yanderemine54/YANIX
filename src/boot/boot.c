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

#include <uefi/uefi.h>
#include <stdbool.h>
#include "elf.h"
#include "../kernel/bootparams.h"

int main(int argc, char** argv) {
    FILE* kernel_file;
    char* buffer;
    long int size;
    ELF64_ELF_header_t *ELF_header;
    ELF64_program_header_t *program_header;
    uintptr_t entry_point;
    boot_parameters_t boot_parameters;
    framebuffer_t framebuffer;
    efi_status_t status;
    efi_guid_t GOPGUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t* GOP;
    int index;

    /* load kernel */
    if ((kernel_file = fopen("\\kernel.elf", "r"))) {
        fseek(kernel_file, 0, SEEK_END);
        size = ftell(kernel_file);
        fseek(kernel_file, 0, SEEK_SET);
        buffer = malloc(size + 1);
        if (!buffer) {
            fprintf(stderr, "Unable to allocate memory for the kernel!\n");
        }
        fread(buffer, size, 1, kernel_file);
        fclose(kernel_file);
    } else {
        fprintf(stderr, "Unable to open the kernel executable file!\n");
        return 0;
    }

    /* Set up the kernel's boot parameters */
    memset(&boot_parameters, 0, sizeof(boot_parameters_t));
    status = BS->LocateProtocol(&GOPGUID, NULL, &GOP);
    if(!EFI_ERROR(status) && GOP) {
        status = GOP->SetMode(GOP, 0);
        ST->ConOut->Reset(ST->ConOut, false);
        ST->StdErr->Reset(ST->StdErr, false);
        if (EFI_ERROR(status)) {
            fprintf(stderr, "unable to set the video mode!\n");
            return 0;
        }
        memset(&framebuffer, 0, sizeof(framebuffer_t));
        framebuffer.address = (unsigned int*)GOP->Mode->FrameBufferBase;
        framebuffer.width = GOP->Mode->Information->HorizontalResolution;
        framebuffer.height = GOP->Mode->Information->VerticalResolution;
        framebuffer.pitch = sizeof(unsigned int) * GOP->Mode->Information->PixelsPerScanLine;
        boot_parameters.framebuffer = &framebuffer;
    } else {
        fprintf(stderr, "Unable to get the graphics output protocol.\n");
        return 0;
    }
    if (argc > 1) {
        boot_parameters.argc = argc - 1;
        boot_parameters.argv = (char**)malloc(argc * sizeof(char));
        if (boot_parameters.argv) {
            for (index = 0; index < boot_parameters.argc; index++) {
                if ((boot_parameters.argv[index] = (char*)malloc(strlen(argv[index + 1]) + 1))) {
                    strcpy(boot_parameters.argv[index], argv[index + 1]);
                }
            }
        }
    }

    /* Is the ELF file compatible with our system? */
    ELF_header = (ELF64_ELF_header_t*)buffer;
    if (!memcmp(ELF_header->ELF_identification, ELF_MAGIC_NUMBER, ELF_MAGIC_NUMBER_SIZE)         && /* Is the magic number good? */
        ELF_header->ELF_identification[ARCHITECTURE_WORD_SIZE_INDEX]     == WORD_SIZE            && /* Is ihe executable 64-bit? */
        ELF_header->ELF_identification[ENDIANNESS_INDEX]                 == ENDIANNESS           && /* Is it little endian? */
        ELF_header->ELF_file_type                                        == FILE_TYPE_EXECUTABLE && /* Is it an executable? */
        ELF_header->ELF_machine                                          == ARCHITECTURE         && /* Is it for the right architecture? */
        ELF_header->ELF_program_header_entry_count                       >  0) {                    /* Does it have program headers? */
        /* Load segments */
        for (program_header = (ELF64_program_header_t*)(buffer + ELF_header->ELF_program_header_offset), index = 0;
             index < ELF_header->ELF_program_header_entry_count;
             index++, program_header = (ELF64_program_header_t*)((uint8_t*)program_header + ELF_header->ELF_program_header_entry_size)) {
            if (program_header->program_type == LAODABLE_SEGMENT) {
                memcpy((void*)program_header->program_virtual_address, buffer + program_header->program_offset, program_header->program_file_size);
                memset((void*)(program_header->program_virtual_address + program_header->program_file_size), 0,
                       program_header->program_memory_size - program_header->program_file_size);
            }
        }
        entry_point = ELF_header->ELF_entry_point;
    } else {
        fprintf(stderr, "Invalid ELF file (for this machine)!\n");
        return 0;
    }

    free(buffer);

    if (exit_bs() != 0) {
        fprintf(stderr, "Let me out! Let me out!\n");
        return 0;
    }

    /* Execute the kernel, a.k.a. the most cursed function call I've ever seen */
    (*((void(* __attribute__((sysv_abi)))(boot_parameters_t*))(entry_point)))(&boot_parameters);

    /* Never return */
    while (1);

    return 0;
}
