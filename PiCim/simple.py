from kivy.app import App
from kivy.uix.image import Image
from kivy.uix.behaviors import ButtonBehavior

class MyButton(ButtonBehavior, Image):
    def __init__(self, **kwargs):
        super(MyButton, self).__init__(**kwargs)
        self.source = 'data/z2.png' #'atlas://data/images/defaulttheme/checkbox_off'

    def on_press(self):
        pass #self.source = 'data/z3.jpg' #'atlas://data/images/defaulttheme/checkbox_on'

    def on_release(self):
        self.source = 'data/z4.jpg' #'atlas://data/images/defaulttheme/checkbox_off'

class SampleApp(App):
    def build(self):
        return MyButton()
        
SampleApp().run()