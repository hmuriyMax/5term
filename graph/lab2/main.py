import numpy as np, random
from pyglet.gl import *
from pyglet.window import Window
from pyglet import app

# frac = ((0.636364, -0.727273, -0.515152, -0.405303, 3.395211, 5.032732),
#         (0.151515, -0.321970, 0.484848, -0.155303, -3.669363, 5.726923))
# weight = (0.826733, 0.173267)


# frac = ((0.3333, 0.00, 0.00, 0.3333, 0.00, 0.00),
# (0.1677, -0.2887, 0.2887, 0.1677, 0.3333, 0.00),
# (-0.1677, 0.2887, 0.2887, 0.1677, 0.6666, 0.00),
# (0.3333, 0.00, 0.00, 0.3333, 0.6666, 0.00))

# weight = (0.25, 0.25, 0.25, 0.25)


frac = ((0.47, 0.17, -0.17, 0.47, 0.00, 0.00),
 (-0.11, 0.77, -0.77, -0.11, 1.11, 0.77))

weight = (0.45, 0.55)

N = 10

w = 400    # Размеры окна вывода
vp = np.full((w, w, 3), 5, dtype='uint8')

# Создаем окно визуализации
window = Window(visible=True, width=w, height=w, caption='Needle', resizable=True)     # Заливка окна цветом фона

# beginning spot
stx = random.randint(0, w)
sty = random.randint(0, w)

for _ in range(N):
    tmp = random.choices(frac, weight)[0]
    tmx = stx
    stx = tmp[0]*stx + tmp[1]*sty + tmp[4]
    sty = tmp[2]*stx + tmp[3]*sty + tmp[5]
print("start: ({}, {})".format(stx, sty))

x, y = stx, sty
for _ in range(5000):
    tmp = random.choices(frac, weight)[0]
    tx = x
    x = tmp[0] * x + tmp[1] * y + tmp[4]
    y = tmp[2] * tx + tmp[3] * y + tmp[5]
    OutX = int(x*150 + 500) % w
    OutY = int(y*150 + 500) % w
    print("dot: ({}, {})".format(OutX, OutY))
    vp[OutX, OutY] = [0, 255, 0]


vp = vp.flatten()
vp = (GLubyte * (w * w * 3))(*vp)


@window.event
def on_draw():
    window.clear()
    glDrawPixels(w, w, GL_RGB, GL_UNSIGNED_BYTE, vp)


app.run()
