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

    void serialize_row(Row* source, char* destination);
    void deserialize_row(char* source, Row* destination);

private:
    static constexpr uint16_t ID_SIZE = sizeof(id);
    static constexpr uint16_t USERNAME_SIZE = sizeof(username);
    static constexpr uint16_t EMAIL_SIZE = sizeof(email);
    static constexpr uint16_t ID_OFFSET = 0;
    static constexpr uint16_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
    static constexpr uint16_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
    static constexpr uint16_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

};



#endif //DATABASE_ENGINE_FROM_SCRATCH_ROW_H
