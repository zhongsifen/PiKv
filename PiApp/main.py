# main.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from PiCim import PiCim
from PIL import Image as PyImage

class PiPim():
    def t(im):
        return im.size, im.getdata()

if __name__ == "__main__":
    PiCim.dummy()

    im = PyImage.open("z2.png")
    s, d = PiPim.t(im)
    im.show()
    print("Hello")
    print(s)
