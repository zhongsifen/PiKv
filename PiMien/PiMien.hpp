// PiMien.hpp
#include <cstdint>

extern "C"
{
    bool mien_subim(uint8_t im[], int size[2], int rect[4], uint8_t subim[], int subsiz[2]);
}