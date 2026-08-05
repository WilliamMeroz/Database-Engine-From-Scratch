//
// Created by William Méroz-Moreau on 2026-08-02.
//
#include "../../include/storage/pager.h"
#include <string>
#include <iostream>
#include <fstream>
namespace db {
    Pager::Pager(std::string& filename) {
       file_descriptor.open(filename, std::ios::in | std::ios::out | std::ios::binary);

        // Attempt to open existing file failed (in | out) so we create a new file
        if (!file_descriptor.is_open()) {
            std::cout << "File did not open properly or does not exist. Creating..." << std::endl;
            // Create a new file using ::out
            file_descriptor.open(filename, std::ios::out | std::ios::binary);
            file_descriptor.close();
            // Open the file for both reading and writing.
            file_descriptor.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        }

        if (!file_descriptor.is_open()) {
            throw std::runtime_error("Unable to open file " + filename);
        }

        file_descriptor.seekg(0, std::ios::end);
        std::streampos length = file_descriptor.tellg();

        if (file_length == -1) {
            throw std::runtime_error("Unable to determine file length: " + filename);
        }

        file_length = static_cast<uint32_t>(length);
    }

    Pager::~Pager() {
        file_descriptor.close();
    }

    char* Pager::get_page(const int page_number) {
        file_descriptor.clear();

        if (file_descriptor.bad()) {
            std::cout << "Unable to access page" << std::endl;
        }

        if (page_number > TABLE_MAX_PAGES) {
            std::cout << "Tried to fetch a page number out of bounds" << std::endl;
            std::quick_exit(EXIT_FAILURE);
        }

        if (pages[page_number] == nullptr) {
            // Cache miss, allocate memory and load the file.
            pages[page_number] = std::make_unique<char[]>(PAGE_SIZE);
            memset(pages[page_number].get(), 0, PAGE_SIZE);
            unsigned int num_pages = file_length / PAGE_SIZE; // Number of pages we have so far.

            // Truthy = We have a remainder of a row that is written but not enough to fit
            // OR we have so little rows in it that num_pages will be 0 because of a truncated float so we add 1
            if (file_length % PAGE_SIZE) {
                num_pages++;
            }

            // Make sure we are not going over the amount of pages allowed.
            if (page_number <= num_pages) {
                file_descriptor.seekg(page_number * PAGE_SIZE, std::ios::beg);
                file_descriptor.read(pages[page_number].get(), PAGE_SIZE);
                if (file_descriptor.bad()) {
                    throw std::runtime_error("Unable to read file...");
                    std::quick_exit(EXIT_FAILURE);
                }
                file_descriptor.clear();
            }
        }

        return pages[page_number].get();
    }

    uint32_t Pager::get_file_length() const {
        return file_length;
    }

    void Pager::close_file() {
        file_descriptor.flush();
        file_descriptor.close();
        if (file_descriptor.fail()) {
            std::cout << "Unable to close file..." << std::endl;
            std::quick_exit(EXIT_FAILURE);
        }
    }

    const std::unique_ptr<char[]> &Pager::get_page_ptr(int page_number) const {
        return pages[page_number];
    }

    void Pager::release_page_ptr(int page_number) {
        pages[page_number] = nullptr;
    }

    void Pager::flush(int page_number, int size) {
        file_descriptor.clear();
        if (pages[page_number] == nullptr) {
            std::cout << "Tried to flush a page out of bounds" << std::endl;
            std::quick_exit(EXIT_FAILURE);
        }

        file_descriptor.seekp(page_number * PAGE_SIZE, std::ios::beg);
        long offset = file_descriptor.tellp();

        if (offset == -1) {
            throw std::runtime_error(std::format("Unable to access page: {}", page_number));
            std::quick_exit(EXIT_FAILURE);
        }

        file_descriptor.write(pages[page_number].get(), size);
        if (file_descriptor.fail()) {
            throw std::runtime_error("Failure to write on the file");
            std::quick_exit(EXIT_FAILURE);
        }
        file_descriptor.clear();
    }
}
