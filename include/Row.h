//
// Created by William Méroz-Moreau on 2026-07-30.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_ROW_H
#define DATABASE_ENGINE_FROM_SCRATCH_ROW_H
#include <array>

namespace db {
    constexpr int COLUMN_USERNAME_SIZE = 32;
    constexpr int COLUMN_EMAIL_SIZE = 255;

    class Row {
    public:
        int id = 0;
        std::array<char, COLUMN_USERNAME_SIZE + 1> username{};
        std::array<char, COLUMN_EMAIL_SIZE + 1> email{};

        void serialize_row(char* destination) const;
        void deserialize_row(const char* source);

        constexpr static int get_row_size() {
            return ROW_SIZE;
        }

        friend std::ostream& operator<<(std::ostream& os, const Row& row);
    private:
        static constexpr int ID_SIZE = sizeof(id);
        static constexpr int USERNAME_SIZE = sizeof(username);
        static constexpr int EMAIL_SIZE = sizeof(email);
        static constexpr int ID_OFFSET = 0;
        static constexpr int USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
        static constexpr int EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
        static constexpr int ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

    };
}

#endif //DATABASE_ENGINE_FROM_SCRATCH_ROW_H
