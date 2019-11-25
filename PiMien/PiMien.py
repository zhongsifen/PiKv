# File name: PiMien.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from PiCim.PiCim import Cmien

class Dl:
    pass
    
class Mien:
    def __init__(self):
        self.mien = Cmien()

    def setup(self, size, colorfmt):
        self.size = [size[0], size[1]]
        self.colorfmt = colorfmt.encode()
        self.mien.cim_open(self.size, self.colorfmt)

    def run(self, pixels, pixela):
        self.mien.cim_read_rgba(pixels)

        # processing(pixela)

        self.mien.cim_write_rgb(pixela)
