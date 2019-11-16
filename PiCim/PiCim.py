# PiCim.py

import ctypes
import os
CDLL = ctypes.CDLL(os.path.dirname(__file__) + "/../install/libPiDl.so")


# bool cim_open(void * im, int size[2], char colorfmt[])
CDLL.cim_open.restype = ctypes.c_bool
CDLL.cim_open.argtypes = [ctypes.c_void_p, ctypes.c_int*2, ctypes.c_char_p]
# bool cim_close(void * im)
CDLL.cim_close.restype = ctypes.c_bool
CDLL.cim_close.argtypes = [ctypes.c_void_p]
# bool cim_size(void * im, int size[2])
CDLL.cim_size.restype = ctypes.c_bool
CDLL.cim_size.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_int)]
# bool cim_read_rgb(void * im, uint8_t pixels[])
CDLL.cim_read_rgb.restype = ctypes.c_bool
CDLL.cim_read_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_read_rgba(void * im, uint8_t pixels[])
CDLL.cim_read_rgba.restype = ctypes.c_bool
CDLL.cim_read_rgba.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]
# bool cim_write_rgb(void * im, uint8_t pixels[])
CDLL.cim_write_rgb.restype = ctypes.c_bool
CDLL.cim_write_rgb.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_byte)]

# CDLL.dl_setup.restype = ctypes.c_bool
# CDLL.dl_run_face.restype = ctypes.c_bool

# void * cim_create_face(void * face)
# CDLL.cim_create_face.restype = ctypes.c_void_p
# CDLL.cim_create_face.argtypes = [ctypes.c_void_p]
# bool cim_write_face(void * face, int rect[4])
CDLL.cim_write_face.restype = ctypes.c_bool
# CDLL.cim_write_face.argtypes = [ctypes.c_void_p, ctypes.c_int*4]


from PIL import Image as PyImage
from kivy.core.image import Image as KvImage
from kivy.uix.image import Image as UxImage


class Cim(ctypes.Structure):
    _fields_ = [
        ("size", ctypes.c_int*2), 
        ("colorfmt", ctypes.c_wchar_p), 
        ("pixels", ctypes.POINTER(ctypes.c_byte))]

    def open(self, size, colorfmt):
        return CDLL.cim_open(ctypes.pointer(self), (ctypes.c_int*2)(*size), (ctypes.c_char*len(colorfmt))(*colorfmt.encode()))

    def close(self):
        return CDLL.cim_close(ctypes.pointer(self))

    def get_size(self):
        b_size = (ctypes.c_int*2)()
        if CDLL.cim_size(ctypes.pointer(self), b_size):
            return (b_size[0], b_size[1])
        return (0, 0)

    def read_rgb(self, pixels):
        return CDLL.cim_read_rgb(ctypes.pointer(self), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    def read_rgba(self, pixels):
        return CDLL.cim_read_rgba(ctypes.pointer(self), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))

    # @staticmethod
    # def func_read(colorfmt):
    #     return Cim.read_rgba if (colorfmt == 'rgba') else Cim.read_rgb

    def write_rgb(self, pixels):
        return CDLL.cim_write_rgb(ctypes.pointer(self), ctypes.cast(pixels, ctypes.POINTER(ctypes.c_byte)))


    # @staticmethod
    # def dl_setup():
    #     return CDLL.dl_setup()

    # @staticmethod
    # def dl_run_face():
    #     return CDLL.dl_run_face()


class Cface(ctypes.Structure):
    _fields_ = [("face", ctypes.c_int*4)]


    def cim_read_face(self, face):
        return CDLL.cim_read_face(ctypes.pointer(self), face)

    def cim_write_face(self, face):
        return CDLL.cim_write_face(ctypes.pointer(self), face)


if __name__ == "__main__":
    # filename = "data/z1.jpg"
    filename = "data/z2.png"

    im = UxImage(source=filename).texture
    print(im.size, im.colorfmt)
    cim = Cim()
    ret = cim.open(im.size, im.colorfmt)
    print("Cim.open", ret)
    ret = cim.read_rgba(im.pixels)

    # Cim.dl_setup()
    # cface = Cface()
    # cface.face[0] = 42
    # print("cface", type(cface), cface)
    # pface = ctypes.pointer(cface)
    # print("pface", type(pface), pface)
    # face = (ctypes.c_int*4)(3,5,7,9)
    # print("face", type(face), face[0], face[1], face[2], face[3])
    # cface.cim_read_face(face)
    # cface.cim_write_face(face)
    # print(face[:])

    # ret = Cim.dl_run_face()
    # print("dl_run_face", ret)

    s = cim.get_size()
    d = bytes(s[0]*s[1]*3)
    print(s, type(d))
    cim.write_rgb(d)
    pim = PyImage.frombytes('RGB', s, d)
    pim.show()
    cim.close()

    print(filename)
