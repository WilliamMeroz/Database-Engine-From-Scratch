#include "../include/Table.h"
#include "../include/Pager.h"

#include <string>

namespace db {
    Table::Table(std::string filename) {
        pager = std::make_unique<db::Pager>(filename);
        num_rows = pager->get_file_length() / db::Row::get_row_size();
    }

    char* Table::row_slot(const int row_number) {
        const int page_num = row_number / ROWS_PER_PAGE;
        char *page = pager->get_page(page_num);
        const int row_offset = row_number % ROWS_PER_PAGE; // Offset is the exact location (row number) of the row in the page.
        const int byte_offset = row_offset * db::Row::get_row_size(); // Byte offset is just the exact byte location
        return page + byte_offset; // Return that location (page (current location) + offset). Pointer arithmetic
    }

    char* Table::get_page(int page_number) {
        return pager->get_page(page_number);
    }

    void Table::db_close() const {
        int num_full_pages = num_rows / ROWS_PER_PAGE;

        for (int i = 0; i < num_full_pages; i++) {
            if (pager->get_page_ptr(i) != nullptr) {
                pager->flush(i, PAGE_SIZE);
                pager->release_page_ptr(i);
            }
        }

        // There might be a partial page that needs to be written at the end of the file
        // Won't be necessary with B-trees
        int num_additional_rows = num_rows % ROWS_PER_PAGE;
        if (num_additional_rows > 0) {
            if (pager->get_page_ptr(num_full_pages) != nullptr) {
                pager->flush(num_full_pages, num_additional_rows * db::Row::get_row_size());
                pager->release_page_ptr(num_full_pages);
            }
        }

        pager->close_file();
    }
}

