#ifndef DATABASE_ENGINE_FROM_SCRATCH_CURSOR_H
#define DATABASE_ENGINE_FROM_SCRATCH_CURSOR_H
#import "Table.h"

class Cursor {
    Table* table = nullptr;
    int row_num = 0;
    bool end_of_table = false;

public:
    explicit Cursor(Table* table);
    explicit Cursor(Table* table, bool end_of_table);
    Cursor(const Cursor& cursor) = delete;
    Cursor& operator=(const Cursor& cursor) = delete;
};
#endif //DATABASE_ENGINE_FROM_SCRATCH_CURSOR_H
