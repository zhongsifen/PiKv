# PiCim.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
import os
libPiCim = CDLL(os.path.dirname(__file__) + "/../install/libPiCim.so")
from ctypes import * 
from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage

if __name__ == "__main__":
    # im = PyImage.open("z2.png")
    # im = KvImage("z2.png")
    uxi = UxImage(source="z2.png")
    im = uxi.texture
    c = im.colorfmt
    s = im.size
    d = im.pixels
    print("[main] im", s, len(d), c)

    c_size = (c_int*2)(*s)
    c_pixels = (c_byte*len(d))(*d)
    libPiCim.cim_setup(c_size)
    libPiCim.cim_input_rgba(c_pixels)
    b_size = (c_int*2)()
    libPiCim.cim_get_size(b_size)
    print("b_size = ", b_size[0], b_size[1])
    size = (b_size[0], b_size[1])
    print("size:", size)
    l = b_size[0] * b_size[1] * 3
    b_pixels = (c_ubyte*l)()
    print(b_pixels[20])
    libPiCim.cim_get_rgb(b_pixels)
    print(b_pixels[20])
    pim = PyImage.frombytes('RGB', size, b_pixels)
    pim.show()

    libPiCim.cim_run()
