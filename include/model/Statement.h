#ifndef DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H
#define DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H

#include "Row.h"
enum class StatementType { STATEMENT_INSERT, STATEMENT_SELECT };
class Statement {
public:
    StatementType type;
    db::Row row_to_insert;
};

#endif //DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H