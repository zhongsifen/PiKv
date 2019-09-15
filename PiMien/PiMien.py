# File name: PiMien.py

import kivy
kivy.require('1.7.0')
from kivy.app import App
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.image import Image as Monitor
from kivy.uix.camera import Camera
from kivy.graphics.texture import Texture
from kivy.clock import Clock
from kivy.config import Config
Config.set('graphics', 'width',  '960')
Config.set('graphics', 'height', '960')

from PIL import Image as Img


class PiCam(Camera):
    _img = None

    def get_img(self):
        return self._img

    def img(self):
        self._img = Img.frombytes(mode='RGBA', size=self.texture.size, data=self.texture.pixels)
        return self._img

class PiMon(Monitor):
    def setup(self, size):
        self.texture = Texture.create(size=size, colorfmt='rgba', bufferfmt='ubyte')
        self.texture.flip_vertical()
        
    def mon(self, img):
        self.texture.blit_buffer(pbuffer=img.tobytes(), size=img.size, colorfmt='rgba', bufferfmt='ubyte')

class PiMien(AnchorLayout):
    def PiRun(self, dt):
        img = self._cam.img()
        self._mon.mon(img)

    def PiStart(self, instance):
        self._dt = 1.0 / 25
        self._cam = self.ids._camera
        self._mon = self.ids._monitor
        self._mon.setup(self._cam.resolution)
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
    

class PiMienApp(App):
    def build(self):
        return PiMien()

if __name__=="__main__":
    PiMienApp().run()
