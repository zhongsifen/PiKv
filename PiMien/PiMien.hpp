// PiMien.hpp
#include <cstdint>

extern "C"
{
	bool dl_setup();
	bool dl_run_face(void* im, void* face);
	bool dl_show_face(void* im, void* face);
	bool dl_run_landmark(void* im, void* landmark);
	bool dl_run_chip(void* im, void* chip);
	bool dl_run_desc(void* im, void* face, void* landmark, void* chip, void* desc);
}
