import numpy as np
from pyglet.gl import *
from pyglet.window import Window
from pyglet import app

w = 500
vp = np.full((w, w, 3), 255, dtype='uint8')

for i in range(w):
    i0, i2 = i - 2, i + 2
    vp[i0:i2, i0:i2] = [0, 255, 0]
    i00, i20 = w - i0 - 1, w - i2 - 1
    vp[i0:i2, i20:i00] = [0, 255, 0]
vp[-5:, :] = vp[:5, :] = [0, 0, 255]
vp[:, -5:] = vp[:, :5] = [0, 0, 255]
k = w // 4
k2 = 3 * k
vp[k:k2, k:k2] = [255, 0, 0]

vp = vp.flatten()
vp = (GLubyte * (w * w * 3))(*vp)
window = Window(visible=True, width=w, height=w, caption='vp')


@window.event
def on_draw():
    window.clear()
    glDrawPixels(w, w, GL_RGB, GL_UNSIGNED_BYTE, vp)
app.run()