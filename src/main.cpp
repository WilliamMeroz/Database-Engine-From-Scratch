#include <iostream>

class InputBuffer {
public:
    std::string buffer;

    InputBuffer() = default;
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

int main() {
    InputBuffer input;
    while (true) {
        print_prompt();
        read_input(input);

        if (input.buffer == ".exit") {
            std::exit(EXIT_SUCCESS);
        }

        std::cout << "Unrecognized command '" << input.buffer << ".\n";
    }

    return 0;
}