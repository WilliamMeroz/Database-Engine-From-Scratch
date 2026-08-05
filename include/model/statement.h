#ifndef DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H
#define DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H

#include "row.h"
enum class StatementType { STATEMENT_INSERT, STATEMENT_SELECT };
class statement {
public:
    StatementType type;
    db::row row_to_insert;
};

#endif //DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H