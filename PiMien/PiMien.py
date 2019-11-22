# File name: PiMien.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from PiCim.PiCim import Cim

class Dl:
    pass
    
class Mien:
    def setup(self, size, colorfmt):
        self.size = [size[0], size[1]]
        self.colorfmt = colorfmt.encode()
        # self.pixels = bytes((size[0]*size[1]) * 3)
        self.cim = Cim()
        print("size colorfmt:", type(size), type(colorfmt))
        print("setup: size colorfmt", type(self.size), self.size[0], self.size[1], type(self.colorfmt), self.colorfmt)
        self.cim.open(self.size, self.colorfmt)

    def run(self, pixels, pixela):
        self.cim.read_rgba(pixels)

        # processing(pixela)

        self.cim.write_rgb(pixela)
