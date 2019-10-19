# File name: KvMien.py

import kivy
kivy.require('1.7.0')
from kivy.app import App
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.image import Image
from kivy.uix.camera import Camera
from kivy.graphics.texture import Texture
from kivy.clock import Clock
from kivy.config import Config
Config.set('graphics', 'width',  '960')
Config.set('graphics', 'height', '960')

import PiMien

class KvCam(Camera):
    def get_size(self):
        return self.texture.size

    def get_colorfmt(self):
        return self.texture.colorfmt

    def get_pixels(self):
        return self.texture.pixels


class KvPreview(Image):
    def setup(self, size):
        self.texture = Texture.create(size=size, colorfmt='rgba')
        self.texture.flip_vertical()
    
    def show(self, pixels, size, colorfmt):
        self.texture.blit_buffer(pbuffer=pixels, size=size, colorfmt=colorfmt)


class KvMien(AnchorLayout):
    def setup(self):
        self.dt=(1.0/25)
        self.cam=self.ids._camera
        self.prv=self.ids._preview
        self.prv.setup(self.cam.get_size())
    
    def run(self, parameter_list):
        self.prv.show(pixels=self.cam.get_pixels(), size=self.cam.get_size(), colorfmt=self.cam.get_colorfmt())

    def PiStart(self, instance):
        self.setup()
        Clock.schedule_interval(self.run, self.dt)

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
        pass

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


class KvMienApp(App):
    def build(self):
        return KvMien()

if __name__=="__main__":
    KvMienApp().run()
