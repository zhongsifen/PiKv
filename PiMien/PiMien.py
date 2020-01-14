# PiMien.py

import ctypes
import os
CDLL = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiMien.so")

import ctypes
import os
CDLL = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiMien.so")

# bool cim_setup(void* im, int size[2], char *colorfmt)
CDLL.cim_setup.restype = ctypes.c_bool
CDLL.cim_setup.argtypes = [ctypes.c_void_p, ctypes.c_int*2]
# bool cim_close(void* im)
CDLL.cim_close.restype = ctypes.c_bool
CDLL.cim_close.argtypes = [ctypes.c_void_p]
# bool cim_get_size(void* im, int size[2])
CDLL.cim_get_size.restype = ctypes.c_bool
CDLL.cim_get_size.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
# bool cim_read_rgb(void* im, uint8_t pixels[])
CDLL.cim_read_rgb.restype = ctypes.c_bool
CDLL.cim_read_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_read_rgba(void* im, uint8_t pixels[])
CDLL.cim_read_rgba.restype = ctypes.c_bool
CDLL.cim_read_rgba.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_write_rgb(void* im, uint8_t pixels[])
CDLL.cim_write_rgb.restype = ctypes.c_bool
CDLL.cim_write_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]

# bool cdesc_write(void* desc, float d[])
CDLL.cdesc_write.restype = ctypes.c_bool
CDLL.cdesc_write.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_float)]

# bool mien_init()
CDLL.mien_init.restype = ctypes.c_bool
CDLL.mien_init.argtypes = []
# bool mien_setup(void* im, void* view)
CDLL.mien_setup.restype = ctypes.c_bool
CDLL.mien_setup.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
# bool mien_run_face(void* view)
CDLL.mien_run_face.restype = ctypes.c_bool
CDLL.mien_run_face.argtypes = [ctypes.c_void_p]
# bool mien_run_chip(void* view)
CDLL.mien_run_chip.restype = ctypes.c_bool
CDLL.mien_run_chip.argtypes = [ctypes.c_void_p, ctypes.c_void_p]


from PIL import Image as PyImage
# from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage

class Cim(ctypes.Structure):
    _fields_ = [
        ("size", ctypes.c_int*2), 
        ("pixels", ctypes.POINTER(ctypes.c_byte))]

    def setup(self, size):
        _size = (ctypes.c_int*2)()
        _size[:] = size
        return CDLL.cim_setup(ctypes.pointer(self), _size)

    def close(self):
        return CDLL.cim_close(ctypes.pointer(self))

    def get_size(self, size):
        return CDLL.cim_get_size(ctypes.pointer(self), ctypes.cast(size, ctypes.POINTER(ctypes.c_int)))

    def read_rgb(self, pixels):
        return CDLL.cim_read_rgb(ctypes.pointer(self), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def read_rgba(self, pixels):
        return CDLL.cim_read_rgba(ctypes.pointer(self), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def write_rgb(self, pixels):
        return CDLL.cim_write_rgb(ctypes.pointer(self), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

class Cdesc(ctypes.Structure):
    _fields_ = [
        ("desc", ctypes.c_float*128)] 

    def write(self, desc):
        return CDLL.cdesc_write(ctypes.pointer(self), ctypes.cast(desc, ctypes.POINTER(ctypes.c_float)))

    def read(self, desc):
        return CDLL.cdesc_read(ctypes.pointer(self), ctypes.cast(desc, ctypes.POINTER(ctypes.c_float)))

class Cmien:
    def __init__(self):
        self.im = Cim()
        self.chip = Cim()
        self.view = Cim()
        self.desc = Cdesc()
        CDLL.mien_init()

    def setup_size(self, size_im, size_chip=(150, 150)):
        self.im.setup(size_im)
        self.view.setup(size_im)
        self.chip.setup(size_chip)

    def setup(self):
        CDLL.mien_setup(ctypes.pointer(self.im), ctypes.pointer(self.view))

    def run_face(self):
        CDLL.mien_run_face(ctypes.pointer(self.view))

    def run_chip(self):
        CDLL.mien_run_chip(ctypes.pointer(self.chip), ctypes.pointer(self.view))

    def run(self):
        CDLL.mien_run(ctypes.pointer(self.desc), ctypes.pointer(self.chip), ctypes.pointer(self.view))

    def save_desc(self, path, filename):
        desc = (ctypes.c_float*128)()
        self.desc.write(desc)
        fdesc = open(path + filename, 'w')
        for k in range(128):
            fdesc.writelines('%f\n' % desc[k])
        fdesc.close()

    def load_desc(self, path, filename):
        desc = (ctypes.c_float*128)()
        fdesc = open(path + filename)
        k = 0
        for l in fdesc:
            desc[k] = float(l)
            k = k + 1
        fdesc.close()
        self.desc.read(desc)

if __name__ == "__main__":
    filename = "data/z2.png"

    im = UxImage(source=filename).texture
    size = (ctypes.c_int*2)()
    size[0] = im.size[0]
    size[1] = im.size[1]

    mien = Cmien()
    mien.setup_size(size)
    mien.im.read_rgba(im.pixels)
    mien.setup()
    mien.run_face()
    mien.run()
    s = (ctypes.c_int*2)()
    mien.view.get_size(s)
    d = bytes(s[0]*s[1]*3)
    mien.view.write_rgb(d)
    pim = PyImage.frombytes('RGB', (s[0], s[1]), d)
    pim.show()
    chip = bytes(150*150*3)
    mien.chip.write_rgb(chip)
    t = PyImage.frombytes('RGB', (150, 150), chip)
    t.show()

    # mien = Cmien()
    # mien.load_desc('data/', 'p_2.desc')
    # desc = (ctypes.c_float*128)()
    # mien.desc.write(desc)
    # mien.save_desc('data/', 'p_3.desc')
