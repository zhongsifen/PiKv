# File name: KvMien.py

import kivy
kivy.require('1.7.0')
import sys
sys.path.append('/Users/zhongsifen/Work/PiKv')

from kivy.app import App
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.popup import Popup
from kivy.uix.image import Image
from kivy.uix.camera import Camera
from kivy.uix.behaviors import ButtonBehavior 
from kivy.graphics.texture import Texture
from kivy.graphics import Line
from kivy.clock import Clock
from kivy.config import Config
Config.set('graphics', 'width',  '960')
Config.set('graphics', 'height', '960')

from PiCim.PiCim import Cmien
# from PiMien.PiMien import Mien

class KvCam(ButtonBehavior, Camera):
    def get_size(self):
        return self.texture.size

    def get_colorfmt(self):
        return self.texture.colorfmt

    def get_pixels(self):
        return self.texture.pixels


class KvIm(Image):
    def setup(self, size, colorfmt='rgb'):
        self.texture = Texture.create(size=size, colorfmt=colorfmt)
        self.texture.flip_vertical()
        self.buffer = bytes(size[0]*size[1]*3)

    def show(self):
        self.texture.blit_buffer(pbuffer=self.buffer, size=self.texture.size, colorfmt=self.texture.colorfmt)

class KvDlg(FloatLayout):
    def load(self, dir, file):
        pass

    def cancel(self):
        pass

class KvCard(ButtonBehavior, Image):
    def path(self):
        dlg = Popup(title="path", content=KvDlg(), size_hint=(0.8, 0.8))
        dlg.open()

    def card(self):
        self.source = 'card/card_2.png'

class KvPreview(ButtonBehavior, KvIm):
    pass

class KvChip(KvIm):
    pass

class KvMien(AnchorLayout):
    def setup(self):
        self.dt=(1.0/10)
        self.cam=self.ids._camera
        self.prv=self.ids._preview
        self.prv.setup(size=self.cam.get_size())
        self.chp=self.ids._chip
        self.chp.setup(size=(150, 150))

        self.mien = Cmien()
        self.mien.cim_open(self.cam.get_size())
   
    def preview_step(self, dt):
        self.mien.cim_read_rgba(self.cam.get_pixels())
        self.mien.cim_write_rgb(self.prv.buffer)
        self.prv.show()

    def preview(self):
        self.setup()

        Clock.schedule_interval(self.preview_step, self.dt)



class KvMienApp(App):
    def build(self):
        return KvMien()

if __name__=="__main__":
    KvMienApp().run()
