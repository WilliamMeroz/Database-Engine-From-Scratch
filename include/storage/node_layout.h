//
// Created by William Méroz-Moreau on 2026-08-05.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_NODE_LAYOUT_H
#define DATABASE_ENGINE_FROM_SCRATCH_NODE_LAYOUT_H

#include "../model/row.h"
#include "pager.h"

/*
 * Common Node Header Layout
 *
 * Every node stores its type, whether or not it's the root and a pointer to its parent.
 */
constexpr uint32_t NODE_TYPE_SIZE = sizeof(uint8_t);
constexpr uint32_t NODE_TYPE_OFFSET = 0;
constexpr uint32_t IS_ROOT_SIZE = sizeof(uint8_t);
constexpr uint32_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
constexpr uint32_t PARENT_POINTER_SIZE = sizeof(uint32_t);
constexpr uint32_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_SIZE;
constexpr uint8_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;

/*
 * Leaf Node Header Layout
 *
 * Leaf Nodes need to know how many cells (KV pair (Key - Serialized row) they contain.
 */
constexpr uint32_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t);
constexpr uint32_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
constexpr uint32_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;

/*
 * Leaf Node Body Layout
 */

constexpr uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
constexpr uint32_t LEAF_NODE_KEY_OFFSET = 0;
constexpr uint32_t LEAF_NODE_VALUE_SIZE = db::Row::get_row_size();
constexpr uint32_t LEAF_NODE_VALUE_OFFSET = LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
constexpr uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
constexpr uint32_t LEAF_NODE_SPACE_FOR_CELLS = db::PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
constexpr uint32_t LEAF_NODE_MAX_CELLS = LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;

#endif //DATABASE_ENGINE_FROM_SCRATCH_NODE_LAYOUT_H
