#include <iostream>
#include <sstream>
#include "../include/InputBuffer.h"
#include "../include/Statement.h"
#include "../include/Table.h"

enum MetaCommandResult {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR
};

enum ExecuteResult {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS
};

void print_prompt() {
    std::cout << "db >";
}

void read_input(InputBuffer &input) {
    if (!std::getline(std::cin, input.buffer)) {
        std::cerr << "Error reading input\n";
        std::exit(EXIT_FAILURE);
    }
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (input_buffer->buffer == ".exit") {
        exit(EXIT_SUCCESS);
    }

    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    std::istringstream ss(input_buffer->buffer);
    std::string keyword;
    ss >> keyword;
    if (keyword == "insert") {
        statement->type = StatementType::STATEMENT_INSERT;

        int id;
        std::string username, email;
        ss >> id >> username >> email;

        if (ss.fail()) {
            return PREPARE_SYNTAX_ERROR;
        }

        statement->row_to_insert.id = id;
        memcpy(&statement->row_to_insert.username, username.c_str(), statement->row_to_insert.username.size());
        memcpy(&statement->row_to_insert.email, email.c_str(), statement->row_to_insert.email.size());

        return PREPARE_SUCCESS;
    }

    if (keyword == "select") {
        statement->type = StatementType::STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult execute_insert(Statement* statement, Table* table) {
    if (table->num_rows >= Table::getTableMaxRows()) {
        return EXECUTE_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->row_to_insert);
    row_to_insert->serialize_row(table->row_slot(table->num_rows));
    table->num_rows++;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table) {
    Row row;
    for (int i = 0; i < table->num_rows; i++) {
        row.deserialize_row(table->row_slot(i));
        std::cout << row << std::endl;
    }

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case StatementType::STATEMENT_INSERT:
            return execute_insert(statement, table);
        case StatementType::STATEMENT_SELECT:
            return execute_select(statement, table);
            break;
    }
}

int main() {
    Table table;
    InputBuffer input;
    while (true) {
        print_prompt();
        read_input(input);

        if (!input.buffer.empty() && input.buffer.at(0) == '.') {
            switch (do_meta_command(&input)) {
                case META_COMMAND_SUCCESS: continue;

                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    std::cout << "Unrecognized command `" << input.buffer << "`\n";
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(&input, &statement)) {
            case PREPARE_SUCCESS: break;
            case PREPARE_SYNTAX_ERROR:
                std::cout << "Syntax error. Could not parse statement" << std::endl;
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                std::cout << std::format("Unrecognized keyword at start of '{}'", input.buffer) << std::endl;
                continue;
        }

        switch (execute_statement(&statement, &table)) {
            case EXECUTE_TABLE_FULL:
                std::cout << "Error: Table full." << std::endl;
                break;
            case EXECUTE_SUCCESS:
                std::cout << "Executed successfully." << std::endl;
                break;
        }
    }

    return 0;
}