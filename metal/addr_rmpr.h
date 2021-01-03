/* Copyright 2021 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__ADDR_RMPR_H
#define METAL__ADDR_RMPR_H

#include <stdint.h>

struct metal_addr_rmpr;
struct metal_addr_rmpr_remap_entry;

/*! @brief vtable for address remapper. */
struct metal_addr_rmpr_vtable {
    int (*enable_remap)(const struct metal_addr_rmpr *addr_rmpr, int idx);
    int (*disable_remap)(const struct metal_addr_rmpr *addr_rmpr, int idx);
    int (*enable_remaps)(const struct metal_addr_rmpr *addr_rmpr, int idxs[]);
    int (*disable_remaps)(const struct metal_addr_rmpr *addr_rmpr, int idxs[]);
    uint32_t (*get_valid)(const struct metal_addr_rmpr *addr_rmpr, int idx);
    int (*set_valid)(const struct metal_addr_rmpr *addr_rmpr,
                     int idx, uint32_t val);
    int (*flush)(const struct metal_addr_rmpr *addr_rmpr);
    uint32_t (*get_version)(const struct metal_addr_rmpr *addr_rmpr);
    uint32_t (*get_entries)(const struct metal_addr_rmpr *addr_rmpr);
    int (*set_remap)(const struct metal_addr_rmpr *addr_rmpr,
                     const struct metal_addr_rmpr_remap_entry *entry);
    int (*set_remaps)(const struct metal_addr_rmpr *addr_rmpr,
                      const struct metal_addr_rmpr_remap_entry *entries[]);
    uint64_t (*get_from)(const struct metal_addr_rmpr *addr_rmpr, int idx);
    uint64_t (*get_to)(const struct metal_addr_rmpr *addr_rmpr, int idx);
};

/*! @brief A handle for a address remapper device. */
struct metal_addr_rmpr {
    const struct metal_addr_rmpr_vtable *vtable;
};

/*! @brief Remap entry descriptor. */
struct metal_addr_rmpr_remap_entry {
    int idx; /*!< Index of remap entry. */
    uint64_t from_addr; /*!< From[] entry address to be remapped. */
    uint64_t to_addr; /*!< To[] entry address to be remapped. */
};

/*! @brief Enables an address remapper entry.
 * @param addr_rmpr Address remapper device handle.
 * @param idx Index of remap entry to enable.
 * @return 0 If no error.*/
inline int __metal_addr_rmpr_enable_remap(const struct metal_addr_rmpr *addr_rmpr,
                                          int idx) {
    return addr_rmpr->vtable->enable_remap(addr_rmpr, idx);
}

/*! @brief Disables an address remapper entry.
 * @param addr_rmpr Address remapper device handle.
 * @param idx Index of remap entry to disable.
 * @return 0 If no error.
 */
inline int __metal_addr_rmpr_disable_remap(const struct metal_addr_rmpr *addr_rmpr,
                                           int idx) {
    return addr_rmpr->vtable->disable_remap(addr_rmpr, idx);
}

/*! @brief Batch enables address remapper entries.
 * @param addr_rmpr Address remapper device handle.
 * @param idxs[] Array of indexes of remap entries to enable.
 * @return 0 If no error.*/
inline int __metal_addr_rmpr_enable_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                           int idxs[]) {
    return addr_rmpr->vtable->enable_remaps(addr_rmpr, idxs);
}

/*! @brief Batch disables an address remapper entries.
 * @param addr_rmpr Address remapper device handle.
 * @param idxs[] Array of indexes of remap entries to disable.
 * @return 0 If no error.
 */
inline int __metal_addr_rmpr_disable_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                            int idxs[]) {
    return addr_rmpr->vtable->disable_remaps(addr_rmpr, idxs);
}

/*! @brief Get remappervalid[] register content.
 * @param addr_rmpr Address remapper device handle.
 * @param idx Index of remappervalid[] register.
 * @return 0 If no error.
 */
inline uint32_t __metal_addr_rmpr_get_valid(const struct metal_addr_rmpr *addr_rmpr,
                                            int idx) {
    return addr_rmpr->vtable->get_valid(addr_rmpr, idx);
}

/*! @brief Set remappervalid[] register with given value.
 * @param addr_rmpr Address remapper device handle.
 * @param idx Index of remappervalid[] register.
 * @param val Value to be set.
 * @return 0 If no error.
 */
inline int __metal_addr_rmpr_set_valid(const struct metal_addr_rmpr *addr_rmpr,
                                       int idx, uint32_t val) {
    return addr_rmpr->vtable->set_valid(addr_rmpr, idx, val);
}

/*! @brief Disable all address remapper entries.
 * @param addr_rmpr Address remapper device handle.
 * @return 0 If no error.
 */
inline int __metal_addr_rmpr_flush(const struct metal_addr_rmpr *addr_rmpr) {
    return addr_rmpr->vtable->flush(addr_rmpr);
}

/*! @brief Get hardware version of address remapper.
 * @param addr_rmpr Address remapper device handle.
 * @return current hardware version of address remapper.
 */
inline uint32_t __metal_addr_rmpr_get_version(const struct metal_addr_rmpr *addr_rmpr) {
    return addr_rmpr->vtable->get_version(addr_rmpr);
}

/*! @brief Get number of entries in address remapper.
 * @param addr_rmpr Address remapper device handle.
 * @return number of entries in address remapper.
 */
inline uint32_t __metal_addr_rmpr_get_entries(const struct metal_addr_rmpr *addr_rmpr) {
    return addr_rmpr->vtable->get_entries(addr_rmpr);
}

/*! @brief Set from/to remap entry.
 * @param addr_rmpr Address remapper device handle.
 * @param entry Pointer to the remap entry descriptor.
 * @return 0 If no error.
 */
inline int __metal_addr_rmpr_set_remap(const struct metal_addr_rmpr *addr_rmpr,
                                       const struct metal_addr_rmpr_remap_entry *entry) {
    return addr_rmpr->vtable->set_remap(addr_rmpr, entry);
}

/*! @brief Batch set from/to remap entries.
 * @param addr_rmpr Address remapper device handle.
 * @param entries Array of pointers to the remap entry descriptors.
 * @return 0 If no error.
 */
inline int __metal_addr_rmpr_set_remaps(const struct metal_addr_rmpr *addr_rmpr,
                                        const struct metal_addr_rmpr_remap_entry *entries[]) {
    return addr_rmpr->vtable->set_remaps(addr_rmpr, entries);
}

/*! @brief Get the from address of a remap entry.
 * @param addr_rmpr Address remapper device handle.
 * @param idx Index of remap entry.
 * @return From address of the remap entry.
 */
inline uint64_t __metal_addr_rmpr_get_from(const struct metal_addr_rmpr *addr_rmpr,
                                           int idx) {
    return addr_rmpr->vtable->get_from(addr_rmpr, idx);
}

/*! @brief Get the to address of a remap entry.
 * @param addr_rmpr Address remapper device handle.
 * @param idx Index of remap entry.
 * @return To address of the remap entry.
 */
inline uint64_t __metal_addr_rmpr_get_to(const struct metal_addr_rmpr *addr_rmpr,
                                         int idx) {
    return addr_rmpr->vtable->get_to(addr_rmpr, idx);
}

/*!
 * @brief The public METAL address remapper interfaces.
 */
int metal_addr_rmpr_enable_remap(int idx);
int metal_addr_rmpr_disable_remap(int idx);
int metal_addr_rmpr_enable_remaps(int idx[]);
int metal_addr_rmpr_disable_remaps(int idx[]);
int metal_addr_rmpr_get_valid(int idx);
int metal_addr_rmpr_set_valid(int idx, uint32_t val);
int metal_addr_rmpr_flush(void);
uint32_t metal_addr_rmpr_get_version(void);
uint32_t metal_addr_rmpr_get_entries(void);
int metal_addr_rmpr_set_remap(const struct metal_addr_rmpr_remap_entry *entry);
int metal_addr_rmpr_set_remaps(const struct metal_addr_rmpr_remap_entry *entries[]);
uint64_t metal_addr_rmpr_get_from(int idx);
uint64_t metal_addr_rmpr_get_to(int idx);

#endif /*METAL__ADDR_RMPR_H */

