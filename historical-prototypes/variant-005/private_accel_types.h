/* Private experiment only. MPL-2.0. No runtime executable memory or generated host code. */
#ifndef FLOE_PRIVATE_ACCEL_TYPES_H
#define FLOE_PRIVATE_ACCEL_TYPES_H

typedef struct {
    uint32_t instruction;
    int32_t immediate;
    uint8_t kind, rd, rs1, rs2;
    uint8_t valid;
} FloePrivateDecoded;

typedef struct {
    int mode; /* 0 original path, 1 generic predecode, 2 fixture AOT */
    uint64_t cache_hits, cache_misses, fast_instructions, fallbacks;
    uint64_t aot_blocks, aot_rejects, aot_budget_fallbacks;
    FloePrivateDecoded cache[128];
} FloePrivateAccel;

#endif
