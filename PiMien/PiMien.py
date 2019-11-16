# File name: PiMien.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from PiCim.PiCim import Cim

class Dl:
    pass
    
class PiMien:
    def setup(self, size, colorfmt):
        self.size = size
        self.colorfmt = colorfmt
        self.pixels = bytes((size[0]*size[1]) * 3)
        self.cim = Cim()
        self.cim.open(size, colorfmt)
        self.read = cim.func_read(colorfmt)

    def run(self, pixels):
        self.read(pixels)

        Cim.write_rgb(self.pixels)
