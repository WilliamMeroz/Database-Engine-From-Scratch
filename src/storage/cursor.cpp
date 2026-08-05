#include "../../include/storage/cursor.h"

namespace db {
    cursor::cursor(Table* table) {
        this->table = table;
        end_of_table = table->num_rows == 0;
    }

    cursor::cursor(Table *table, const bool end_of_table) {
        this->table = table;
        row_num = table->num_rows;
        this->end_of_table = end_of_table;
    }

    char *cursor::value() {
        const int page_num = row_num / ROWS_PER_PAGE;
        char *page = table->get_page(page_num);
        int row_offset = row_num % ROWS_PER_PAGE;
        int byte_offset = row_offset * Row::get_row_size();
        return page + byte_offset;
    }

    void cursor::advance() {
        row_num++;
        if (row_num >= table->num_rows) {
            end_of_table = true;
        }
    }

    bool cursor::at_end() const {
        return end_of_table;
    }
}
