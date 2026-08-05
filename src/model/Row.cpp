#include "../../include/model/Row.h"
#include <ostream>
#include <format>


namespace db {
    // The use of memcpy here is problematic, we would need check the buffer sizes, which we aren't doing.
    // This would obviously bring in issues of stack, heap overflows. Or plain old undefined behaviors.
    void Row::serialize_row(char* destination) const {
        memcpy(destination + ID_OFFSET, &id, ID_SIZE);
        memcpy(destination + USERNAME_OFFSET, &username, USERNAME_SIZE);
        memcpy(destination + EMAIL_OFFSET, &email, EMAIL_SIZE);
    }

    void Row::deserialize_row(const char* source) {
        memcpy(&id, source + ID_OFFSET, ID_SIZE);
        memcpy(&username, source + USERNAME_OFFSET, USERNAME_SIZE);
        memcpy(&email, source + EMAIL_OFFSET, EMAIL_SIZE);
        username.back() = '\0';
        email.back() = '\0';
    }

    std::ostream& operator<<(std::ostream& os, const Row& row) {
        os << std::format("ID: {} Username: {} Email: {}", row.id,
                                                    std::string(row.username.data()),
                                                    std::string(row.email.data()));
        return os;
    }
}