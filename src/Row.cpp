#include "../include/Row.h"

// The use of memcpy here is problematic, we would need check the buffer sizes, which we aren't doing.
// This would obviously bring in issues of stack, heap overflows. Or plain old undefined behaviors.
void Row::serialize_row(Row* source, char* destination) {
    memcpy(destination + ID_OFFSET, &source->id, ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &source->username, USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &source->email, EMAIL_SIZE);
}

void Row::deserialize_row(char* source, Row* destination) {
    memcpy(&destination->id, source + ID_OFFSET, ID_SIZE);
    memcpy(&destination->username, source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&destination->email, source + EMAIL_OFFSET, EMAIL_SIZE);
}
