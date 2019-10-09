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
    # size = (0,0)
    # length = 0
    # colorfmt = 'rgb'

    @staticmethod
    def open(size, colorfmt):
        c_size = (ctypes.c_int*2)(*size)
        c_colorfmt = (ctypes.c_char*len(colorfmt))(*colorfmt.encode())
        libPiCim.cim_open(c_size, c_colorfmt)

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
        c_pixels = (ctypes.c_byte*len(pixels))(*pixels)
        libPiCim.cim_read_rgba(c_pixels)

    @staticmethod
    def write_rgb(pixels):
        libPiCim.cim_write_rgb(ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

if __name__ == "__main__":
    # im = PyImage.open("z2.png")
    # im = KvImage("z2.png")
    im = UxImage(source="z2.png").texture

    Cim.open(im.size, im.colorfmt)
    Cim.read_rgba(im.pixels)

    s = Cim.size()
    d = bytes(s[0]*s[1]*3)
    p = Cim.write_rgb(d)
    # b_size = (ctypes.c_int*2)()
    # libPiCim.cim_get_size(b_size)
    # size = (b_size[0], b_size[1])

    # l = b_size[0] * b_size[1] * 3
    # b_pixels = (ctypes.c_ubyte*l)()
    # print(b_pixels[20])
    # libPiCim.cim_get_rgb(b_pixels)
    # print(b_pixels[20])
    pim = PyImage.frombytes('RGB', s, d)
    pim.show()
    Cim.close()

    print("Bye")

    # libPiCim.cim_run()
