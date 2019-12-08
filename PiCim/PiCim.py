# PiCim.py

import ctypes
import os
CDLL = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiMien.so")

# bool cim_open(void * im, int size[2], char *colorfmt)
CDLL.cim_open.restype = ctypes.c_bool
CDLL.cim_open.argtypes = [ctypes.c_void_p, ctypes.c_int*2, ctypes.c_char_p]
# bool cim_close(void * im)
CDLL.cim_close.restype = ctypes.c_bool
CDLL.cim_close.argtypes = [ctypes.c_void_p]
# bool cim_get_size(void *im, int size[2])
CDLL.cim_get_size.restype = ctypes.c_bool
CDLL.cim_get_size.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
# bool cim_read_rgb(void * im, uint8_t pixels[])
CDLL.cim_read_rgb.restype = ctypes.c_bool
CDLL.cim_read_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_read_rgba(void * im, uint8_t pixels[])
CDLL.cim_read_rgba.restype = ctypes.c_bool
CDLL.cim_read_rgba.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_write_rgb(void * im, uint8_t pixels[])
CDLL.cim_write_rgb.restype = ctypes.c_bool
CDLL.cim_write_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]

# bool cface_read(void * cface, int32_t rect[4])
CDLL.cface_read.restype = ctypes.c_bool
CDLL.cface_read.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
# bool cface_write(void * cface, int32_t rect[4])
CDLL.cface_write.restype = ctypes.c_bool
CDLL.cface_write.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]

# bool dl_setup()
CDLL.dl_setup.restype = ctypes.c_bool
CDLL.dl_setup.argtypes = None
# bool dl_run_face(void * im, void * face)
CDLL.dl_run_face.restype = ctypes.c_bool
CDLL.dl_run_face.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
# bool dl_run_landmark(void * im, void * landmark)
CDLL.dl_run_landmark.restype = ctypes.c_bool
CDLL.dl_run_landmark.argtypes = [ctypes.c_void_p, ctypes.c_void_p]

from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage


class Cim(ctypes.Structure):
    _fields_ = [
        ("size", ctypes.c_int*2), 
        ("colorfmt", ctypes.c_char_p),
        ("pixels", ctypes.POINTER(ctypes.c_byte))]

class Cface(ctypes.Structure):
    _fields_ = [("face", ctypes.c_int*4)]

class Clandmark(ctypes.Structure):
    _fields_ = [("landmark", ctypes.c_int*(68*2))]

class Cmien:
    def __init__(self):
        self.im = Cim()
        self.face = Cface()
        self.landmark = Clandmark()

    def cim_open(self, size, colorfmt):
        _size = (ctypes.c_int*2)()
        _size[:] = size
        return CDLL.cim_open(ctypes.pointer(self.im), _size, colorfmt)

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

    def dl_setup(self):
        return CDLL.dl_setup()

    def dl_run_face(self):
        return CDLL.dl_run_face(ctypes.pointer(self.im), ctypes.pointer(self.face))

    # def dl_show_face(self):
    #     return CDLL.dl_show_face(ctypes.pointer(self.im), ctypes.pointer(self.face))

    def dl_run_landmark(self):
        return CDLL.dl_run_landmark(ctypes.pointer(self.im), ctypes.pointer(self.landmark))

if __name__ == "__main__":
    filename = "data/z2.png"

    im = UxImage(source=filename).texture
    size = (ctypes.c_int*2)()
    size[0] = im.size[0]
    size[1] = im.size[1]
    colorfmt = im.colorfmt.encode()

    mien = Cmien()
    mien.cim_open(size, colorfmt)
    ret = mien.cim_read_rgba(im.pixels)

    mien.dl_setup()
    # mien.dl_run_face()
    mien.dl_run_landmark()
    # mien.dl_show_face()

    # face = (ctypes.c_int*4)()
    # mien.cface_write(face)
    # print("face:", face[:])

    s = (ctypes.c_int*2)()
    mien.cim_get_size(s)
    d = bytes(s[0]*s[1]*3)
    mien.cim_write_rgb(d)
    pim = PyImage.frombytes('RGB', (s[0], s[1]), d)
    pim.show()
    mien.cim_close()

    print(filename)
