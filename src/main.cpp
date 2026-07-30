#include <iostream>
#include "../include/InputBuffer.h"
#include "../include/Statement.h"

enum MetaCommandResult {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};

enum PrepareResult {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
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
    if (input_buffer->buffer == "insert") {
        statement->type = StatementType::STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    if (input_buffer->buffer == "select") {
        statement->type = StatementType::STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement, InputBuffer* input_buffer) {
    switch (statement->type) {
        case StatementType::STATEMENT_INSERT:
            std::cout << "This is where you would do an insert." << std::endl;
            break;
        case StatementType::STATEMENT_SELECT:
            std::cout << "This is where you would do a select." << std::endl;
            break;
    }
}

int main() {
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
            case PREPARE_UNRECOGNIZED_STATEMENT:
                std::cout << std::format("Unrecognized keyword at start of '{}'", input.buffer) << std::endl;
                continue;
        }

        execute_statement(&statement, &input);
        std::cout << "Executed." << std::endl;

    }

    return 0;
}