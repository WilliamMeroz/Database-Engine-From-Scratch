//
// Created by William Méroz-Moreau on 2026-08-02.
//

#ifndef DATABASE_ENGINE_FROM_SCRATCH_PAGER_H
#define DATABASE_ENGINE_FROM_SCRATCH_PAGER_H
#include <array>
#include <fstream>

namespace db {
    static constexpr int TABLE_MAX_PAGES = 100;
    static constexpr int PAGE_SIZE = 4096;

    class pager {
        std::fstream file_descriptor;
        uint32_t file_length = 0;
        std::array<std::unique_ptr<char[]>, TABLE_MAX_PAGES> pages{};

        public:
            explicit pager(std::string& filename);
            ~pager();
            pager(const pager&) = delete;
            pager& operator =(const pager&) = delete;

            char* get_page(int page_number);
            const std::unique_ptr<char[]>& get_page_ptr(int page_number) const;
            void release_page_ptr(int page_number);
            void flush(int page_number, int size);

            uint32_t get_file_length() const;
            void close_file();
    };
}

#endif //DATABASE_ENGINE_FROM_SCRATCH_PAGER_H
