# PiCim.py

import ctypes
import os
CDLL = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiMien.so")

# bool cim_setup(void* im, int size[2], char *colorfmt)
CDLL.cim_setup.restype = ctypes.c_bool
CDLL.cim_setup.argtypes = [ctypes.c_void_p, ctypes.c_int*2]
# bool cim_close(void* im)
CDLL.cim_close.restype = ctypes.c_bool
CDLL.cim_close.argtypes = [ctypes.c_void_p]
# bool cim_get_size(void* im, int size[2])
CDLL.cim_get_size.restype = ctypes.c_bool
CDLL.cim_get_size.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
# bool cim_read_rgb(void* im, uint8_t pixels[])
CDLL.cim_read_rgb.restype = ctypes.c_bool
CDLL.cim_read_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_read_rgba(void* im, uint8_t pixels[])
CDLL.cim_read_rgba.restype = ctypes.c_bool
CDLL.cim_read_rgba.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_write_rgb(void* im, uint8_t pixels[])
CDLL.cim_write_rgb.restype = ctypes.c_bool
CDLL.cim_write_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]

# bool cface_read(void* cface, int32_t rect[4])
CDLL.cface_read.restype = ctypes.c_bool
CDLL.cface_read.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
# bool cface_write(void* cface, int32_t rect[4])
CDLL.cface_write.restype = ctypes.c_bool
CDLL.cface_write.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]


# bool mien_setup(void* im, void* view)
CDLL.mien_setup.restype = ctypes.c_bool
CDLL.mien_setup.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
# bool mien_run_face(void* view)
CDLL.mien_run_face.restype = ctypes.c_bool
CDLL.mien_run_face.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
# bool mien_run_chip(void* view)
# CDLL.mien_run_chip.restype = ctypes.c_bool
# CDLL.mien_run_chip.argtypes = [ctypes.c_void_p, ctypes.c_void_p]


# # bool mien_run_landmark(void* im, void* landmark)
# CDLL.mien_run_landmark.restype = ctypes.c_bool
# CDLL.mien_run_landmark.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
# # bool mien_run_chip(void* im, void* chip)
# CDLL.mien_run_chip.restype = ctypes.c_bool
# CDLL.mien_run_chip.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
# # bool mien_run_desc(void* im, void* face, void* landmark, void* chip, void* desc)
# CDLL.mien_run_desc.restype = ctypes.c_bool
# CDLL.mien_run_desc.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]

from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage


class Cim(ctypes.Structure):
    _fields_ = [
        ("size", ctypes.c_int*2), 
        # ("colorfmt", ctypes.c_char_p),
        ("pixels", ctypes.POINTER(ctypes.c_byte))]

class Cface(ctypes.Structure):
    _fields_ = [("face", ctypes.c_int*4)]

class Clandmark(ctypes.Structure):
    _fields_ = [("landmark", ctypes.c_int*(68*2))]

class Cdesc(ctypes.Structure):
    _fields_ = [("desc", ctypes.c_int*128)]

class Cmien:
    def __init__(self):
        self.im = Cim()
        self.face = Cface()
        self.landmark = Clandmark()
        self.chip = Cim()
        self.desc = Cdesc()

    def cim_setup(self, size):
        _size = (ctypes.c_int*2)()
        _size[:] = size
        return CDLL.cim_setup(ctypes.pointer(self.im), _size)

    def cim_close(self):
        return CDLL.cim_close(ctypes.pointer(self.im))

    def cim_get_size(self, size):
        return CDLL.cim_get_size(ctypes.pointer(self.im), ctypes.cast(size, ctypes.POINTER(ctypes.c_int)))

    def cim_read_rgb(self, pixels):
        return CDLL.cim_read_rgb(ctypes.pointer(self.im), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def cim_read_rgba(self, pixels):
        return CDLL.cim_read_rgba(ctypes.pointer(self.im), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def cim_write_rgb(self, pixels):
        return CDLL.cim_write_rgb(ctypes.pointer(self.im), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def cface_read(self, face):
        return CDLL.cface_read(ctypes.pointer(self.face), face)

    def cface_write(self, face):
        t = (ctypes.c_int*4)()
        ret = CDLL.cface_write(ctypes.pointer(self.face), ctypes.cast(t, ctypes.POINTER(ctypes.c_int)))
        face[:] = t
        return ret

    def cchip_get_size(self, size):
        return CDLL.cim_get_size(ctypes.pointer(self.chip), ctypes.cast(size, ctypes.POINTER(ctypes.c_int)))

    def cchip_write(self, pixels):
        return CDLL.cim_write_rgb(ctypes.pointer(self.chip), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def mien_setup(self, im, view):
        return CDLL.mien_setup(ctypes.pointer(im), ctypes.pointer(view))

    def mien_run_face(self, view):
        return CDLL.mien_run_face(ctypes.pointer(view))

    # def mien_run_landmark(self):
    #     return CDLL.mien_run_landmark(ctypes.pointer(self.im), ctypes.pointer(self.landmark))
    
    # def mien_run_chip(self):
    #     return CDLL.mien_run_chip(ctypes.pointer(self.im), ctypes.pointer(self.chip))

    # def mien_run_desc(self):
    #     return CDLL.mien_run_desc(ctypes.pointer(self.im), ctypes.pointer(self.face), ctypes.pointer(self.landmark), ctypes.pointer(self.chip), ctypes.pointer(self.desc))

if __name__ == "__main__":
    filename = "data/z2.png"

    im = UxImage(source=filename).texture
    size = (ctypes.c_int*2)()
    size[0] = im.size[0]
    size[1] = im.size[1]
    colorfmt = im.colorfmt.encode()

    mien = Cmien()
    mien.cim_setup(size)
    ret = mien.cim_read_rgba(im.pixels)

    view = Cim()
    mien.mien_setup(mien.im, view)
    # mien.mien_run_face()
    # mien.mien_run_landmark()
    # _size = (ctypes.c_int*2)()
    # _size[:] = size
    # CDLL.cim_setup(ctypes.pointer(mien.chip), (ctypes.c_int*2)(150, 150), b'rgb')
    
    # mien.mien_show_face()
    # mien.mien_run_chip()
    # mien.mien_run_face()

    # face = (ctypes.c_int*4)()
    # mien.cface_write(face)
    # print("face:", face[:])

    s = (ctypes.c_int*2)()
    # print(mien.chip.size[:])
    # print(mien.chip.pixels)
    mien.cim_get_size(s)
    d = bytes(s[0]*s[1]*3)
    mien.cim_write_rgb(d)
    pim = PyImage.frombytes('RGB', (s[0], s[1]), d)
    pim.show()
    # size_chip = (mien.chip.size[0], mien.chip.size[1])
    # print("size_chip", type(size_chip), size_chip)
    # pchip = PyImage.frombytes('RGB', size_chip, mien.im.pixels)
    # pchip.show()
    mien.cim_close()

    print(filename)
