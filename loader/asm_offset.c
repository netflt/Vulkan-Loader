/*
 * Copyright (c) 2017-2021 The Khronos Group Inc.
 * Copyright (c) 2017-2021 Valve Corporation
 * Copyright (c) 2017-2021 LunarG, Inc.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Lenny Komow <lenny@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

// This code generates an assembly file which provides offsets to get struct members from assembly code.

#include <stdio.h>
#include "loader_common.h"
#include "log.h"

#if defined(__GNUC__) || defined(__clang__)
void produce_asm_define() {
    // GCC and clang make it easy to print easy to regex for values
    __asm__("# VULKAN_LOADER_ERROR_BIT = %c0" : : "i"(VULKAN_LOADER_ERROR_BIT));
    __asm__("# PTR_SIZE = %c0" : : "i"(sizeof(void *)));
    __asm__("# CHAR_PTR_SIZE = %c0" : : "i"(sizeof(char *)));
    __asm__("# FUNCTION_OFFSET_INSTANCE = %c0" : : "i"(offsetof(struct loader_instance, phys_dev_ext_disp_functions)));
    __asm__("# PHYS_DEV_OFFSET_INST_DISPATCH = %c0" : : "i"(offsetof(struct loader_instance_dispatch_table, phys_dev_ext)));
    __asm__("# PHYS_DEV_OFFSET_PHYS_DEV_TRAMP = %c0" : : "i"(offsetof(struct loader_physical_device_tramp, phys_dev)));
    __asm__("# ICD_TERM_OFFSET_PHYS_DEV_TERM = %c0" : : "i"(offsetof(struct loader_physical_device_term, this_icd_term)));
    __asm__("# PHYS_DEV_OFFSET_PHYS_DEV_TERM = %c0" : : "i"(offsetof(struct loader_physical_device_term, phys_dev)));
    __asm__("# INSTANCE_OFFSET_ICD_TERM = %c0" : : "i"(offsetof(struct loader_icd_term, this_instance)));
    __asm__("# DISPATCH_OFFSET_ICD_TERM = %c0" : : "i"(offsetof(struct loader_icd_term, phys_dev_ext)));
    __asm__("# EXT_OFFSET_DEVICE_DISPATCH = %c0" : : "i"(offsetof(struct loader_dev_dispatch_table, ext_dispatch)));
}
#elif defined(_WIN32)
// MSVC will print the name of the value and the value in hex
// Must disable optimization for this translation unit, otherwise the compiler strips out the variables
static const uint32_t PTR_SIZE = sizeof(void *);
static const uint32_t CHAR_PTR_SIZE = sizeof(char *);
static const uint32_t FUNCTION_OFFSET_INSTANCE = offsetof(struct loader_instance, phys_dev_ext_disp_functions);
static const uint32_t PHYS_DEV_OFFSET_INST_DISPATCH = offsetof(struct loader_instance_dispatch_table, phys_dev_ext);
static const uint32_t PHYS_DEV_OFFSET_PHYS_DEV_TRAMP = offsetof(struct loader_physical_device_tramp, phys_dev);
static const uint32_t ICD_TERM_OFFSET_PHYS_DEV_TERM = offsetof(struct loader_physical_device_term, this_icd_term);
static const uint32_t PHYS_DEV_OFFSET_PHYS_DEV_TERM = offsetof(struct loader_physical_device_term, phys_dev);
static const uint32_t INSTANCE_OFFSET_ICD_TERM = offsetof(struct loader_icd_term, this_instance);
static const uint32_t DISPATCH_OFFSET_ICD_TERM = offsetof(struct loader_icd_term, phys_dev_ext);
static const uint32_t EXT_OFFSET_DEVICE_DISPATCH = offsetof(struct loader_dev_dispatch_table, ext_dispatch);
#endif

#if !defined(_MSC_VER) || (_MSC_VER >= 1900)
#define SIZE_T_FMT "%-8zu"
#else
#define SIZE_T_FMT "%-8lu"
#endif

struct ValueInfo {
    const char *name;
    size_t value;
    const char *comment;
};

// This file is not intended to be executed, as the generated asm contains all the relevant data which
// the parse_asm_values.py script needs to write gen_defines.asm
int main(int argc, char **argv) { return 0; }
