//
// Created by William Méroz-Moreau on 2026-07-31.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
#define DATABASE_ENGINE_FROM_SCRATCH_TABLE_H

#include "Pager.h"
#include "Row.h"
// Table that points to specific rows in specific pages.

namespace db {
    class Table {
        static constexpr int PAGE_SIZE = 4096;
        static constexpr int TABLE_MAX_PAGES = 100;
        static constexpr int ROWS_PER_PAGE = PAGE_SIZE / db::Row::get_row_size();
        static constexpr int TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

        std::unique_ptr<Pager> pager;

    public:
        explicit Table(std::string filename);
        unsigned int num_rows = 0;

        char* row_slot(int row_number);
        char* get_page(int page_number);

        void db_close() const;

        static constexpr int getTableMaxRows() { return TABLE_MAX_ROWS; }
        static constexpr int getTableMaxPages() { return TABLE_MAX_PAGES; }
        static constexpr int getPageSize() { return PAGE_SIZE; }
    };
}

#endif //DATABASE_ENGINE_FROM_SCRATCH_TABLE_H
