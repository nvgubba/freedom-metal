/* Copyright 2021 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <metal/machine.h>
#include <metal/addr_rmpr.h>

extern int __metal_addr_rmpr_enable_remap(const struct metal_addr_rmpr *addr_rmpr,
                                          int idx);
extern int __metal_addr_rmpr_disable_remap(const struct metal_addr_rmpr *addr_rmpr,
                                           int idx);
extern int __metal_addr_rmpr_enable_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                           int idxs[]);
extern int __metal_addr_rmpr_disable_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                            int idxs[]);
extern uint32_t __metal_addr_rmpr_get_valid(const struct metal_addr_rmpr *addr_rmpr,
                                            int idx);
extern int __metal_addr_rmpr_set_valid(const struct metal_addr_rmpr *addr_rmpr,
                                       int idx, uint32_t val);
extern int __metal_addr_rmpr_flush(const struct metal_addr_rmpr *addr_rmpr);
extern uint32_t __metal_addr_rmpr_get_version(const struct metal_addr_rmpr *addr_rmpr);
extern int __metal_addr_rmpr_set_version(const struct metal_addr_rmpr *addr_rmpr,
                                         uint32_t version);
extern uint32_t __metal_addr_rmpr_get_entries(const struct metal_addr_rmpr *addr_rmpr);
extern int __metal_addr_rmpr_set_remap(const struct metal_addr_rmpr *addr_rmpr,
                                       const struct metal_addr_rmpr_remap_entry *entry);
extern int __metal_addr_rmpr_set_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                        const struct metal_addr_rmpr_remap_entry *entries[]);
extern uint64_t __metal_addr_rmpr_get_from(const struct metal_addr_rmpr *addr_rmpr,
                                           int idx);
extern uint64_t __metal_addr_rmpr_get_to(const struct metal_addr_rmpr *addr_rmpr,
                                         int idx);

int metal_addr_rmpr_enable_remap(int idx) {
    return __metal_addr_rmpr_enable_remap(__METAL_DT_ADDR_RMPR_HANDLE, idx);
}

int metal_addr_rmpr_disable_remap(int idx) {
    return __metal_addr_rmpr_disable_remap(__METAL_DT_ADDR_RMPR_HANDLE, idx);
}

int metal_addr_rmpr_enable_remaps(int idxs[]) {
    return __metal_addr_rmpr_enable_remaps(__METAL_DT_ADDR_RMPR_HANDLE, idxs);
}

int metal_addr_rmpr_disable_remaps(int idxs[]) {
    return __metal_addr_rmpr_disable_remaps(__METAL_DT_ADDR_RMPR_HANDLE, idxs);
}

int metal_addr_rmpr_get_valid(int idx) {
    return __metal_addr_rmpr_get_valid(__METAL_DT_ADDR_RMPR_HANDLE, idx);
}

int metal_addr_rmpr_set_valid(int idx, uint32_t val) {
    return __metal_addr_rmpr_set_valid(__METAL_DT_ADDR_RMPR_HANDLE, idx, val);
}

int metal_addr_rmpr_flush(void) {
    return __metal_addr_rmpr_flush(__METAL_DT_ADDR_RMPR_HANDLE);
}

uint32_t metal_addr_rmpr_get_version(void) {
    return __metal_addr_rmpr_get_version(__METAL_DT_ADDR_RMPR_HANDLE);
}

uint32_t metal_addr_rmpr_get_entries(void) {
    return __metal_addr_rmpr_get_entries(__METAL_DT_ADDR_RMPR_HANDLE);
}

int metal_addr_rmpr_set_remap(const struct metal_addr_rmpr_remap_entry *entry) {
    return __metal_addr_rmpr_set_remap(__METAL_DT_ADDR_RMPR_HANDLE, entry);
}

int metal_addr_rmpr_set_remaps(const struct metal_addr_rmpr_remap_entry *entries[]) {
    return __metal_addr_rmpr_set_remaps(__METAL_DT_ADDR_RMPR_HANDLE, entries);
}

uint64_t metal_addr_rmpr_get_from(int idx) {
    return __metal_addr_rmpr_get_from(__METAL_DT_ADDR_RMPR_HANDLE, idx);
}

uint64_t metal_addr_rmpr_get_to(int idx) {
    return __metal_addr_rmpr_get_to(__METAL_DT_ADDR_RMPR_HANDLE, idx);
}

