#include <iostream>
#include <sstream>
#include <cassert>

#include "../include/storage/cursor.h"
#include "../include/repl/InputBuffer.h"
#include "../include/model/Statement.h"
#include "../include/storage/table.h"

namespace {
    enum MetaCommandResult {
        META_COMMAND_SUCCESS,
        META_COMMAND_UNRECOGNIZED_COMMAND
    };

    enum PrepareResult {
        PREPARE_SUCCESS,
        PREPARE_UNRECOGNIZED_STATEMENT,
        PREPARE_SYNTAX_ERROR,
        PREPARE_STRING_TOO_LONG,
        PREPARE_NEGATIVE_ID
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

    MetaCommandResult do_meta_command(const InputBuffer* input_buffer, const db::Table* table) {
        if (input_buffer->buffer == ".exit") {
            table->db_close();
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

            if (id < 0) {
                return PREPARE_NEGATIVE_ID;
            }

            if (username.length() > db::COLUMN_USERNAME_SIZE || email.length() > db::COLUMN_EMAIL_SIZE) {
                return PREPARE_STRING_TOO_LONG;
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

    ExecuteResult execute_insert(Statement* statement, db::Table* table) {
        if (table->num_rows >= db::Table::getTableMaxRows()) {
            return EXECUTE_TABLE_FULL;
        }

        db::Row* row_to_insert = &(statement->row_to_insert);
        db::Cursor cursor(table, true);
        row_to_insert->serialize_row(cursor.value());

        table->num_rows++;

        return EXECUTE_SUCCESS;
    }

    ExecuteResult execute_select(Statement* statement, db::Table* table) {
        db::Row row;
        db::Cursor cursor(table);
        while (!cursor.at_end()) {
            row.deserialize_row(cursor.value());
            std::cout << row << std::endl;
            cursor.advance();
        }

        return EXECUTE_SUCCESS;
    }

    ExecuteResult execute_statement(Statement* statement, db::Table* table) {
        switch (statement->type) {
            case StatementType::STATEMENT_INSERT:
                return execute_insert(statement, table);
            case StatementType::STATEMENT_SELECT:
                return execute_select(statement, table);
                break;
        }
        assert(false && "Unhandled ExecuteResult, will never be ran.");
        return ExecuteResult{};
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "You must supply a database name" << std::endl;
        exit(EXIT_FAILURE);
    }
    char* db_name = argv[1];
    db::Table table(db_name);
    InputBuffer input;
    while (true) {
        print_prompt();
        read_input(input);

        if (!input.buffer.empty() && input.buffer.at(0) == '.') {
            switch (do_meta_command(&input, &table)) {
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
            case PREPARE_STRING_TOO_LONG:
                std::cout << std::format("String {} is longer than maximum allowed length.", input.buffer) << std::endl;
                continue;
            case PREPARE_NEGATIVE_ID:
                std::cout << "Only positive IDs are allowed" << std::endl;
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