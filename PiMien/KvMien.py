# File name: KvMien.py

import kivy
kivy.require('1.7.0')
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

from PiMien import Mien

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
    
    def show(self, pixels):
        self.texture.blit_buffer(pbuffer=pixels, size=self.texture.size, colorfmt=self.texture.colorfmt)

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
    
    def preview(self):
        pixels = self.cam.get_pixels()
        size = self.cam.get_size()
        pixela = bytes(size[0]*size[1]*3)

        self.mien.run(pixels, pixela, pixelc)

        self.prv.show(pixela)

    def KvMienSetup(self):
        self.setup()
        self.prv.setup(size=self.cam.get_size())
        self.chp.setup(size=(150, 150))
        self.mien = Mien()
        self.mien.setup(size=self.cam.get_size(), colorfmt=self.cam.get_colorfmt())

    def KvMienStep(self, dt):
        pixels = self.cam.get_pixels()
        size = self.cam.get_size()
        pixela = bytes(size[0]*size[1]*3)
        pixelc = bytes(150*150*3)

        self.mien.run(pixels, pixela, pixelc)

        self.prv.show(pixela)
        self.chp.show(pixelc)

    def KvMienLoop(self, instance):
        self.KvMienSetup()
        Clock.schedule_interval(self.KvMienStep, self.dt)


class KvMienApp(App):
    def build(self):
        return KvMien()

if __name__=="__main__":
    KvMienApp().run()
