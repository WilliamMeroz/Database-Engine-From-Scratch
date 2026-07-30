#ifndef DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H
#define DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H

#include "Row.h"
#include "StatementType.h"

class Statement {
public:
    StatementType type;
    Row row_to_insert;
};

#endif //DATABASE_ENGINE_FROM_SCRATCH_STATEMENT_H