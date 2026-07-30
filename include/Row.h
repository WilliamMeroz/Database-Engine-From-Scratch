//
// Created by William Méroz-Moreau on 2026-07-30.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_ROW_H
#define DATABASE_ENGINE_FROM_SCRATCH_ROW_H
#include <array>

constexpr uint16_t COLUMN_USERNAME_SIZE = 32;
constexpr uint16_t COLUMN_EMAIL_SIZE = 255;

class Row {
public:
    uint32_t id;
    std::array<char, COLUMN_USERNAME_SIZE> username{};
    std::array<char, COLUMN_EMAIL_SIZE> email{};
};

#endif //DATABASE_ENGINE_FROM_SCRATCH_ROW_H
