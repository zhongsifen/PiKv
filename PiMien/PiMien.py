# File name: PiMien.py

import kivy
kivy.require('1.7.0')
from kivy.app import App
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.image import Image as Preview
from kivy.uix.camera import Camera
from kivy.graphics.texture import Texture
from kivy.clock import Clock
from kivy.config import Config
Config.set('graphics', 'width',  '960')
Config.set('graphics', 'height', '960')

from PIL import Image as Img

import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')

from PiCim.PiCim import Cim

class PiCam(kivy.uix.camera.Camera):
    pass

class KvPreview(kivy.uix.image.Image):
    def setup(self, size):
        self.texture = Texture.create(size=size, colorfmt='rgba')
        self.texture.flip_vertical()
    
    def show(self, pixels, size, colorfmt):
        self.texture.blit_buffer(pbuffer=pixels, size=size, colorfmt=colorfmt)

class PiMien(AnchorLayout):
    def PiRun(self, dt):
        img = self._cam.img()
        self._prv.show(pixels=img.tobytes(), size=img.size, colorfmt='rgba')

    def PiStart(self, instance):
        self._dt = 1.0 / 25
        self._cam = self.ids._camera
        self._prv = self.ids._preview
        self._prv.setup(self._cam.resolution)
        Clock.schedule_interval(self.PiRun, self._dt)

    def PiPause(self, button):
        if button.state == "down":
            self.ids._camera.play = False
            button.text = 'Play'
        else:
            self.ids._camera.play = True
            button.text = 'Pause'

    def PiSetup(self, instance):
       pass

    def PiStop(self, instance):
        pass
    
    def KvFace(self, instance):
        cam = self.ids._camera.texture
        size = cam.size
        Cim.open(size, 'rgba')
        Cim.read_rgba(cam.pixels)

        pixels = bytes((size[0]*size[1])*3)
        Cim.write_rgb(pixels)
        prv = self.ids._preview
        prv.setup(size=size)
        prv.show(pixels=pixels, size=size, colorfmt='rgb')


class PiMienApp(App):
    def build(self):
        return PiMien()

if __name__=="__main__":
    PiMienApp().run()
