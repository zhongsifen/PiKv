# PiCim.py
# from PiCim import PiCim

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from ctypes import * 
import os
libPiCim = CDLL(os.path.dirname(__file__) + "/../install/libPiCim.so")
# from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage

# def t(im):
#     return im.tobytes(), im.size
# def t(im):
#     ttr = im.texure

if __name__ == "__main__":
    # im = PyImage.open("z2.png")
    # im = KvImage("z2.png")
    im = UxImage(source="z2.png")
    # im.save("s2.png")
    s = im.texture_size
    d = im.texture.pixels
    print("[s.png]", s[0], s[1], type(d))
    # d, s = t(im)
    # im.show()
    print("[main] Hello")

    libPiCim.getCim(c_char_p(d), c_int32(s[0]), c_int32(s[1]))
    libPiCim.hello()
