# PiCim.py

import ctypes
import os
cdll = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiDl.so")
from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage


class Cim:

    @staticmethod
    def open(size, colorfmt):
        cdll.cim_open((ctypes.c_int*2)(*size), (ctypes.c_char*len(colorfmt))(*colorfmt.encode()))

    @staticmethod
    def close():
        cdll.cim_close()

    @staticmethod
    def size():
        b_size = (ctypes.c_int*2)()
        cdll.cim_size(b_size)
        size = (b_size[0], b_size[1])
        return size

    @staticmethod
    def read_rgba(pixels):
        cdll.cim_read_rgba(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    @staticmethod
    def write_rgb(pixels):
        cdll.cim_write_rgb(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    @staticmethod
    def dl_setup():
        cdll.dl_setup()


if __name__ == "__main__":
    filename = "data/z2.png"
    
    im = UxImage(source=filename).texture
    Cim.open(im.size, im.colorfmt)
    # Cim.dl_setup()
    Cim.read_rgba(im.pixels)
    s = Cim.size()
    d = bytes(s[0]*s[1]*3)
    Cim.write_rgb(d)
    pim = PyImage.frombytes('RGB', s, d)
    print("size: ", pim.size)
    pim.show()
    Cim.close()

    print(filename)
