from pyglet import app, gl, graphics
import math
import random
from pyglet.gl import *
from pyglet import app
from pyglet.window import Window, key
import numpy as np

n_rot, chet, speed = 0, 0, 0.25
h = 60  # Половины длины ребра куба
w = 1.5 * h   # Для задания области вывода
width = height = 900    # Размер окна вывода
textureIDs = (gl.GLuint * 6)()  # Массив идентификаторов (номеров) текстур
p = gl.GL_TEXTURE_2D
tc = 1  # Число повторов текстуры
h /= 4
fwd = True


def n_rot_plus(dt):
    global n_rot, speed, fwd
    if n_rot > 360:
        fwd = False
    elif n_rot<0:
        fwd = True
    if fwd:
        n_rot += speed
    else:
        n_rot -= speed


window = Window(visible=True, width=width, height=height, resizable=True, caption='Кубы левитируют!')
gl.glClearColor(0, 0, 0, 1)     # Черный цвет фона
gl.glClear(gl.GL_COLOR_BUFFER_BIT)
gl.glCullFace(gl.GL_FRONT)   # GL_FRONT GL_BACK
gl.glEnable(gl.GL_CULL_FACE)
gl.glPolygonMode(gl.GL_FRONT, gl.GL_FILL)
gl.glShadeModel(gl.GL_SMOOTH)
gl.glEnable(gl.GL_CULL_FACE)
gl.glEnable(GL_DEPTH_TEST)
gl.glDepthFunc(GL_LESS)
gl.glDisable(p)

t_coords = ((0, 0), (0, tc), (tc, tc), (tc, 0))     # Координаты текстуры


def texInit():
    n = 64
    iWidth = iHeight = n
    n = 3 * iWidth * iHeight
    img = np.full((iWidth, iHeight, 3), 255, dtype='uint8')  # изнаально задаем белый цвет
    for i in range(iHeight):
        for j in range(iWidth):
            k = 8
            if (j//k) % 4 == 0:
                img[i, j] = np.array([255, 0, 0])
            elif (j//k) % 4 == 1:
                img[i, j] = np.array([255, 255, 255])
            elif (j//k) % 4 == 2:
                img[i, j] = np.array([0, 255, 0])
            elif (j//k) % 4 == 3:
                img[i, j] = np.array([0, 0, 0])

    img = img.reshape(n)
    img = (GLubyte * n)(*img)

    p, r = GL_TEXTURE_2D, GL_RGB

    glTexParameterf(p, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameterf(p, GL_TEXTURE_WRAP_T, GL_CLAMP)
    glTexParameterf(p, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameterf(p, GL_TEXTURE_MIN_FILTER, GL_LINEAR)

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
    glTexImage2D(p, 0, r, iWidth, iHeight, 0, r, GL_UNSIGNED_BYTE, img)
    glEnable(p)


texInit()

@window.event
def on_draw():
    global n_rot, h, clrs1, clrs2, chet
    window.clear()

    glMatrixMode(GL_PROJECTION)  # Проецирование

    glLoadIdentity()
    glOrtho(-w, w, -w, w, -w, w)

    gluLookAt(1, 1, 1,  # position of camera
              0, 0, 0,  # where camera is pointing at
              0, 1, 0)  # which direction is up

    glMatrixMode(GL_MODELVIEW)
    glPushMatrix()
    gl.glColor3f(0, 0, 1)
    graphics.draw(4, GL_LINES, ('v2f', (0, 0, 0, 1, 0, 0, 1, 0)))
    glRotatef(n_rot, 0, 1, 0)

    glDisable(GL_TEXTURE_2D)
    glColor3f(n_rot/360, 0, 1)
    graphics.draw(4, GL_POLYGON, ('v3f', (h, 0, 0,   h, 2*h, 0,   0, 2*h, 0,   0, 0, 0)))
    graphics.draw(4, GL_POLYGON, ('v3f', (0, 0, 0,   0, 2*h, 0,   0, 2*h, -h,   0, 0, -h)))

    glEnable(GL_TEXTURE_2D)
    b = 1 + (n_rot/360*3)
    graphics.draw(4, GL_POLYGON, ('v3f', ( 0, 0, 0,   0, 2*h, 0,   h, 2*h, 0,   h, 0, 0)),
                  ('t2f', (0, 1, 0, 0, b, 0, b, 1)))
    graphics.draw(4, GL_POLYGON, ('v3f', (0, 0, -h,   0, 2*h, -h,   0, 2*h, 0,   0, 0, 0)),
                  ('t2f', (0, 1, 0, 0, b, 0, b, 1)))
    glDisable(GL_TEXTURE_2D)
    glPopMatrix()

    pyglet.clock.tick()


pyglet.clock.schedule(n_rot_plus)
app.run()
