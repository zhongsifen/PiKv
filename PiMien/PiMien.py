# File name: PiMien.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')

from PiCim.PiCim import Cim

class PiMien:
    def Setup(self):
        cam = self.ids._camera
        Cim.open(cam.get_size(), cam.get_colorfmt())
        Cim.read_rgba(cam.get_pixels())

    def Run(self):
        size = Cim.size()
        pixels = bytes((size[0]*size[1])*3)
        Cim.write_rgb(pixels)
        prv = self.ids._preview
        prv.setup(size=size)
        prv.show(pixels=pixels, size=size, colorfmt='rgb')
