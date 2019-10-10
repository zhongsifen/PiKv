# PiCim.py

import ctypes
# from ctypes import *
# import sys
# sys.path.append('/Users/zhongsifen/Work/PiKv')
import os
libPiCim = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiCim.so")
from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage


class Cim:

    @staticmethod
    def open(size, colorfmt):
        libPiCim.cim_open((ctypes.c_int*2)(*size), (ctypes.c_char*len(colorfmt))(*colorfmt.encode()))

    @staticmethod
    def close():
        libPiCim.cim_close()

    @staticmethod
    def size():
        b_size = (ctypes.c_int*2)()
        libPiCim.cim_size(b_size)
        size = (b_size[0], b_size[1])
        return size

    @staticmethod
    def read_rgba(pixels):
        libPiCim.cim_read_rgba(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    @staticmethod
    def write_rgb(pixels):
        libPiCim.cim_write_rgb(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

if __name__ == "__main__":
    filename = "z2.png"
    
    im = UxImage(source=filename).texture
    Cim.open(im.size, im.colorfmt)
    Cim.read_rgba(im.pixels)
    s = Cim.size()
    d = bytes(s[0]*s[1]*3)
    Cim.write_rgb(d)
    pim = PyImage.frombytes('RGB', s, d)
    pim.show()
    Cim.close()

    print(filename)