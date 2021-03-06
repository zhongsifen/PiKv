// PiMien.hpp

#include <cstdint>
#include <string>

extern "C"
{
	bool cim_setup(void* im, int size[2]);
    bool cim_close(void* im);
    bool cim_get_size(void* im, int size[2]);
    bool cim_read_rgb(void* im, uint8_t pixels[]);
    bool cim_read_rgba(void* im, uint8_t pixels[]);
    bool cim_write_rgb(void* im, uint8_t pixels[]);

    bool cdesc_write(void* desc, float d[]);
    bool cdesc_read(void* desc, float d[]);

    bool mien_init();
	bool mien_setup(void* im, void* view);
	bool mien_run_face(void* view);
	bool mien_run_chip(void* chip, void* view);
    bool mien_run(void* desc, void* chip, void* view);
}
