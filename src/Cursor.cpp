#include "../include/Cursor.h"

Cursor::Cursor(Table* table) {
    this->table = table;
    end_of_table = table->num_rows == 0;
}