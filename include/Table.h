//
// Created by William Méroz-Moreau on 2026-07-31.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
#define DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
#include <memory>
#include <array>
#include "Row.h"
// Table that points to specific rows in specific pages.
class Table {
    static constexpr int PAGE_SIZE = 4096;
    static constexpr int TABLE_MAX_PAGES = 100;
    static constexpr int ROWS_PER_PAGE = PAGE_SIZE / Row::get_row_size();
    static constexpr int TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

public:
    int num_rows = 0;
    std::array<std::unique_ptr<char[]>, TABLE_MAX_PAGES> pages{};

    char* row_slot(int row_number);

    static constexpr int getTableMaxRows() { return TABLE_MAX_ROWS; }
    static constexpr int getTableMaxPages() { return TABLE_MAX_PAGES; }
};

#endif //DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
