#ifndef DATABASE_ENGINE_FROM_SCRATCH_CURSOR_H
#define DATABASE_ENGINE_FROM_SCRATCH_CURSOR_H
#import "Table.h"

namespace db {
    class Cursor {
        Table* table = nullptr;
        int row_num = 0;
        bool end_of_table = false;

        static constexpr int ROWS_PER_PAGE = PAGE_SIZE / Row::get_row_size();

    public:
        explicit Cursor(Table* table);
        explicit Cursor(Table* table, bool end_of_table);
        Cursor(const Cursor& cursor) = delete;
        Cursor& operator=(const Cursor& cursor) = delete;

        char* value();
        void advance();
        [[nodiscard]] bool at_end() const;
    };
}

#endif //DATABASE_ENGINE_FROM_SCRATCH_CURSOR_H
