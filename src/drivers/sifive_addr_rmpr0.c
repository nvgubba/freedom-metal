/* Copyright 2021 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/machine/platform.h>

#ifdef METAL_SIFIVE_ADDR_RMPR0

#include <metal/drivers/sifive_addr_rmpr0.h>
#include <metal/machine.h>
#include <metal/io.h>
#include <stdio.h>
#include <stdint.h>

#define METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM   7

#define METAL_SIFIVE_ADDR_RMPR_ENABLE_KEY   0x51f15e

#define METAL_SIFIVE_ADDR_RMPR0_FROM_REG_OFFSET(idx) \
    (METAL_SIFIVE_ADDR_RMPR0_FROM_BASE + idx * 16)
#define METAL_SIFIVE_ADDR_RMPR0_TO_REG_OFFSET(idx)   \
    (METAL_SIFIVE_ADDR_RMPR0_FROM_BASE + idx * 16 + 8)

/* Macros to access registers */
#define ADDR_RMPR_REG(offset) (((unsigned long)base + offset))
#define ADDR_RMPR_REGW(offset)                                          \
    (__METAL_ACCESS_ONCE((__metal_io_u32 *)ADDR_RMPR_REG(offset)))

static void
__metal_driver_sifive_addr_rmpr_set_key_state(const struct metal_addr_rmpr *addr_rmpr) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_KEY) =
        METAL_SIFIVE_ADDR_RMPR_ENABLE_KEY;
}

int
__metal_driver_sifive_addr_rmpr_enable_remap(const struct metal_addr_rmpr *addr_rmpr,
                                             int idx) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    int reg_idx = idx / 32;
    int bit_offset = idx % 32;

    __metal_driver_sifive_addr_rmpr_set_key_state(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + reg_idx * 4) |=
        (1 << bit_offset);
    __METAL_IO_FENCE(o, rw);

    return 0;
}

int
__metal_driver_sifive_addr_rmpr_disable_remap(const struct metal_addr_rmpr *addr_rmpr,
                                              int idx) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    int reg_idx = idx / 32;
    int bit_offset = idx % 32;

    __metal_driver_sifive_addr_rmpr_set_key_state(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + reg_idx * 4) &=
        ~(1 << bit_offset);
    __METAL_IO_FENCE(o, rw);

    return 0;
}

int
__metal_driver_sifive_addr_rmpr_enable_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                             int idxs[]) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    uint32_t enables[METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM] = {0};

    for (int i = 0; i < sizeof(*idxs) / sizeof(int); i++) {
        int reg_idx = idxs[i] / 32;
        int bit_offset = idxs[i] % 32;
        enables[reg_idx] |= (1 << bit_offset);
    }

    for (int i = 0; i < METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM; i++) {
        uint32_t remappervalid =
            ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + i * 4);
        ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + i * 4) =
            remappervalid | enables[i];
    }

    return 0;
}

int
__metal_driver_sifive_addr_rmpr_disable_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                              int idxs[]) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    uint32_t disables[METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM] = {0};

    for (int i = 0; i < sizeof(*idxs) / sizeof(int); i++) {
        int reg_idx = idxs[i] / 32;
        int bit_offset = idxs[i] % 32;
        disables[reg_idx] |= (1 << bit_offset);
    }

    for (int i = 0; i < METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM; i++) {
        uint32_t remappervalid =
            ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + i * 4);
        ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + i * 4) =
            remappervalid & ~disables[i];
    }

    return 0;
}

uint32_t
__metal_driver_sifive_addr_rmpr_get_valid(const struct metal_addr_rmpr *addr_rmpr,
                                          int idx) {
    if (idx < 0 || idx >= METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM) {
        return 0;
    }

    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    return ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + idx * 4);
}

int
__metal_driver_sifive_addr_rmpr_set_valid(const struct metal_addr_rmpr *addr_rmpr,
                                          int idx, uint32_t val) {
    if (idx < 0 || idx >= METAL_SIFIVE_ADDR_RMPR0_VALID_REGS_NUM) {
        return 1;
    }

    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VALID_BASE + idx * 4) = val;

    return 0;
}

int
__metal_driver_sifive_addr_rmpr_flush(const struct metal_addr_rmpr *addr_rmpr) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    __metal_driver_sifive_addr_rmpr_set_key_state(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_FLUSH) = 1;
    __METAL_IO_FENCE(o, rw);

    return 0;
}

uint32_t
__metal_driver_sifive_addr_rmpr_get_version(const struct metal_addr_rmpr *addr_rmpr) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    return ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_VERSION);
}

uint32_t
__metal_driver_sifive_addr_rmpr_get_entries(const struct metal_addr_rmpr *addr_rmpr) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    return ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_ENTRIES);
}

int
__metal_driver_sifive_addr_rmpr_set_remap(const struct metal_addr_rmpr *addr_rmpr,
                                          const struct metal_addr_rmpr_remap_entry *entry) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    __metal_driver_sifive_addr_rmpr_set_key_state(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_FROM_REG_OFFSET(entry->idx)) = entry->from_addr;
    __metal_driver_sifive_addr_rmpr_set_key_state(addr_rmpr);
    ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_TO_REG_OFFSET(entry->idx)) = entry->to_addr;
    __METAL_IO_FENCE(o, rw);

    return 0;
}

int
__metal_driver_sifive_addr_rmpr_set_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                           const struct metal_addr_rmpr_remap_entry *entries[]) {
    for (int i = 0; i < sizeof(*entries) / sizeof(void *); i++) {
        __metal_driver_sifive_addr_rmpr_set_remap(addr_rmpr, entries[i]);
    }

    return 0;
}

uint64_t
__metal_driver_sifive_addr_rmpr_get_from(const struct metal_addr_rmpr *addr_rmpr,
                                         int idx) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    return ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_FROM_REG_OFFSET(idx));
}

uint64_t
__metal_driver_sifive_addr_rmpr_get_to(const struct metal_addr_rmpr *addr_rmpr,
                                       int idx) {
    unsigned long base = __metal_driver_sifive_addr_rmpr0_base(addr_rmpr);
    return ADDR_RMPR_REGW(METAL_SIFIVE_ADDR_RMPR0_TO_REG_OFFSET(idx));
}

__METAL_DEFINE_VTABLE(__metal_driver_vtable_sifive_addr_rmpr0) = {
    .addr_rmpr.enable_remap = __metal_driver_sifive_addr_rmpr_enable_remap,
    .addr_rmpr.disable_remap = __metal_driver_sifive_addr_rmpr_disable_remap,
    .addr_rmpr.enable_remaps = __metal_driver_sifive_addr_rmpr_enable_remaps,
    .addr_rmpr.disable_remaps = __metal_driver_sifive_addr_rmpr_disable_remaps,
    .addr_rmpr.get_valid = __metal_driver_sifive_addr_rmpr_get_valid,
    .addr_rmpr.set_valid = __metal_driver_sifive_addr_rmpr_set_valid,
    .addr_rmpr.flush = __metal_driver_sifive_addr_rmpr_flush,
    .addr_rmpr.get_version = __metal_driver_sifive_addr_rmpr_get_version,
    .addr_rmpr.get_entries = __metal_driver_sifive_addr_rmpr_get_entries,
    .addr_rmpr.set_remap = __metal_driver_sifive_addr_rmpr_set_remap,
    .addr_rmpr.set_remaps = __metal_driver_sifive_addr_rmpr_set_remaps,
    .addr_rmpr.get_from = __metal_driver_sifive_addr_rmpr_get_from,
    .addr_rmpr.get_to = __metal_driver_sifive_addr_rmpr_get_to,
};

#endif /* METAL_SIFIVE_ADDR_RMPR0 */

typedef int no_empty_translation_units;

