// ctypes.hpp

#include <cstdint>
#include <string>

namespace PiCim {
    typedef struct
    {
        int32_t size_0;
        int32_t size_1;
        uint8_t *pixels;
        char *colorfmt;
    } Cim;

    bool f_rgb(void* im, int32_t *size_0, int32_t *size_1, uint8_t *pixels);
    bool t_rgb(void *im, int32_t *size_0, int32_t *size_1, uint8_t *pixels);
}