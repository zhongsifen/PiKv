# main.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
import PiCim
from PIL import Image as PyIm

class PiPim(PyIm.Image):
    def t(self):
        return self.size, self.getdata()

if __name__ == "__main__":
    im = PyIm.Image()
    im= PyIm.open("z2.png")
    s, d = PiPim.t(im)
    # size = im.size
    # data = im.getdata()
    im.show()
    print("Hello")
    print(s)
