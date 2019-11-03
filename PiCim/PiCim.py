# PiCim.py

import ctypes
import os
CDLL = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiDl.so")
CDLL.cim_open.restype = ctypes.c_bool
CDLL.cim_close.restype = ctypes.c_bool
CDLL.cim_size.restype = ctypes.c_bool
CDLL.cim_read_rgb.restype = ctypes.c_bool
CDLL.cim_read_rgba.restype = ctypes.c_bool
CDLL.cim_write_rgb.restype = ctypes.c_bool
CDLL.dl_setup.restype = ctypes.c_bool
CDLL.dl_run_face.restype = ctypes.c_bool


from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage


class Cim:

    @staticmethod
    def open(size, colorfmt):
        return CDLL.cim_open((ctypes.c_int*2)(*size), (ctypes.c_char*len(colorfmt))(*colorfmt.encode()))

    @staticmethod
    def close():
        return CDLL.cim_close()

    @staticmethod
    def size():
        b_size = (ctypes.c_int*2)()
        if CDLL.cim_size(b_size):
            return (b_size[0], b_size[1])
        return (0, 0)

    @staticmethod
    def read_rgb(pixels):
        return CDLL.cim_read_rgb(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    @staticmethod
    def read_rgba(pixels):
        return CDLL.cim_read_rgba(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    @staticmethod
    def func_read(colorfmt):
        return Cim.read_rgba if (colorfmt == 'rgba') else Cim.read_rgb

    @staticmethod
    def write_rgb(pixels):
        return CDLL.cim_write_rgb(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    @staticmethod
    def dl_setup():
        return CDLL.dl_setup()

    @staticmethod
    def dl_run_face():
        return CDLL.dl_run_face()


if __name__ == "__main__":
    # filename = "data/z1.jpg"
    filename = "data/z2.png"

    im = UxImage(source=filename).texture
    print(im.size, im.colorfmt)
    ret = Cim.open(im.size, im.colorfmt)
    print("Cim.open", ret)
    read = Cim.func_read(im.colorfmt)
    read(im.pixels)

    Cim.dl_setup()
    ret = Cim.dl_run_face()
    print("dl_run_face", ret)

    s = Cim.size()
    d = bytes(s[0]*s[1]*3)
    print(s, type(d))
    Cim.write_rgb(d)
    pim = PyImage.frombytes('RGB', s, d)
    pim.show()
    Cim.close()

    print(filename)
