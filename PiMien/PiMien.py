# File name: PiMien.py

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')
from PiCim.PiCim import Cim

class PiMien:
    def setup(self, pixels, size, colorfmt):
        Cim.open(size, colorfmt)
        if (colorfmt == 'rgba'):
            Cim.read_rgba(pixels)

    def run(self):
        size = Cim.size()
        pixels = bytes((size[0]*size[1])*3)
        Cim.write_rgb(pixels)
        prv = self.ids._preview
        prv.setup(size=size)
        prv.show(pixels=pixels, size=size, colorfmt='rgb')

    # def KvFace(self, instance):
    #     dt = 1.0 / 25.0
    #     self.KvFaceSetup()
    #     Clock.schedule_interval(self.KvFaceRun, dt)

    # def KvFaceSetup(self):
    #     cam = self.ids._camera
    #     Cim.open(cam.get_size(), cam.get_colorfmt())
    #     Cim.read_rgba(cam.get_pixels())

    # def KvFaceRun(self, dt):
    #     size = Cim.size()
    #     pixels = bytes((size[0]*size[1])*3)
    #     Cim.write_rgb(pixels)
    #     prv = self.ids._preview
    #     prv.setup(size=size)
    #     prv.show(pixels=pixels, size=size, colorfmt='rgb')
