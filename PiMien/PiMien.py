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
from PIL import Image as Img

from kivy.config import Config
Config.set('graphics', 'width',  '960')
Config.set('graphics', 'height', '960')

_img = None

class PiCam(Camera):
    def img(self):
        _img = Img.frombytes(mode='RGBA', size=self.texture.size, data=self.texture.pixels)
        return _img

class PiMon(Monitor):
    def setup(self, size):
        self.texture = Texture.create(size=size, colorfmt='rgba', bufferfmt='ubyte')
        self.texture.flip_vertical()
        
    def mon(self, img):
        self.texture.blit_buffer(pbuffer=img.tobytes(), size=img.size, colorfmt='rgba', bufferfmt='ubyte')

class PiMien(AnchorLayout):
    def PiStart(self, instance):
        self.ids._monitor.start()
    
    def PiSetup(self, instance):
        self.ids._monitor.setup(self.ids._camera.resolution)

    def PiPause(self, button):
        if button.state == "down":
            self.ids._camera.play = False
            button.text = 'Play'
        else:
            self.ids._camera.play = True
            button.text = 'Pause'

    def PiStop(self, instance):
        self.ids._camera.stop()

    def PiRefresh(self, instance):
        img = self.ids._camera.img()
        #
        # processing
        #
        self.ids._monitor.mon(img)

    def play_normal(self, instance):
        print("play_normal")

    def play_down(self, instance):
        print("play_down")
    

class PiMienApp(App):
    def build(self):
        return PiMien()

if __name__=="__main__":
    PiMienApp().run()
