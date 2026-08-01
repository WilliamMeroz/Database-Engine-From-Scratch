#include "../include/Table.h"

char* Table::row_slot(const int row_number) {
    const int page_num = row_number / ROWS_PER_PAGE;
    auto& page = pages[page_num];
    if (page == nullptr) {
        page = std::make_unique<char[]>(PAGE_SIZE); // Allocate memory for that page, could be byte too.
        std::memset(page.get(), 0, PAGE_SIZE);
    }

    const int row_offset = row_number % ROWS_PER_PAGE; // Offset is the exact location (row number) of the row in the page.
    const int byte_offset = row_offset * Row::get_row_size(); // Byte offset is just the exact byte location
    return page.get() + byte_offset; // Return that location (page (current location) + offset). Pointer arithmetic
}