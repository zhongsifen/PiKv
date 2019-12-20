# File name: PiMien.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from PiCim.PiCim import Cmien

class Mien:
    def __init__(self):
        self.mien = Cmien()

    def setup(self, size, colorfmt):
        self.size = [size[0], size[1]]
        self.colorfmt = colorfmt.encode()
        self.mien.cim_open(self.size, self.colorfmt)
        self.mien.dl_setup()

    def run(self, pixels, pixela, pixelc):
        self.mien.cim_read_rgba(pixels)

        # self.mien.dl_run_face()
        # self.mien.dl_run_landmark()
        self.mien.dl_run_chip()

        self.mien.cim_write_rgb(pixela)
        self.mien.cchip_write(pixelc)


if __name__ == "__main__":
    pass
