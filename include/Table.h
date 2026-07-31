//
// Created by William Méroz-Moreau on 2026-07-31.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
#define DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
#include "Row.h"
// Table that points to specific rows in specific pages.
class Table {
    static constexpr uint32_t PAGE_SIZE = 4096;
    static constexpr uint32_t TABLE_MAX_PAGE = 100;
    static constexpr uint32_t ROWS_PER_PAGE = PAGE_SIZE / Row::get_row_size();
    static constexpr uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGE;

public:
    uint32_t num_rows = 0;
    char* pages[TABLE_MAX_PAGE];

    static char* row_slot(Table* table, uint32_t row_num) {
        const uint32_t page_num = row_num / ROWS_PER_PAGE;
        char* page = table->pages[page_num];
        if (page == nullptr) {
            page = table->pages[page_num] = new char[PAGE_SIZE]; // Allocate memory for that page, could be byte too.
        }

        uint32_t row_offset = row_num % ROWS_PER_PAGE; // Offset is the exact location (row number) of the row in the page.
        uint32_t byte_offset = row_offset * Row::get_row_size(); // Byte offset is just the exact byte location
        return page + byte_offset; // Return that location (page (current location) + offset). Pointer arithmetic
    }
};

#endif //DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
