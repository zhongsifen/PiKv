# PiCim.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
# from PiCim import PiCim
from ctypes import * 
import os
libPiCim = CDLL(os.path.dirname(__file__) + "/../install/libPiCim.so")
from PIL import Image as PyImage


def t(im):
    return im.tobytes(), im.size

if __name__ == "__main__":
    im = PyImage.open("z2.png")
    d, s = t(im)
    im.show()
    print("Hello")
    print(type(d), s)

    libPiCim.getCim(c_void_p(POINTER(d)), c_int32(s[0]), c_int32(s[1]))
    libPiCim.hello()
