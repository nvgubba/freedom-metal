/* Copyright 2021 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__SIFIVE_ADDR_RMPR0_H
#define METAL__DRIVERS__SIFIVE_ADDR_RMPR0_H

#include <metal/compiler.h>
#include <metal/addr_rmpr.h>

struct __metal_driver_vtable_sifive_addr_rmpr0 {
    const struct metal_addr_rmpr_vtable addr_rmpr;
};

__METAL_DECLARE_VTABLE(__metal_driver_vtable_sifive_addr_rmpr0)

struct __metal_driver_sifive_addr_rmpr0 {
    const struct metal_addr_rmpr addr_rmpr;
};

#endif /* METAL__DRIVERS__SIFIVE_ADDR_RMPR0_H */

