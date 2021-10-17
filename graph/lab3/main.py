#
# Лицевая и нелицевая стороны треугольника
# Угол поворот в glRotatef меняется после нажатия на 1 (key._1) или 2 (key._2)
#
import math
import random
import numpy as np
import pyglet.gl
from pyglet.gl import *
from pyglet import app
from pyglet.window import Window, key

# Координаты вершин треугольника
coords0 = [-3, -2, 0]
coords1 = [3, -2, 0]
coords2 = [0, 3, 0]
v0 = (GLfloat * 3)(*coords0)
v1 = (GLfloat * 3)(*coords1)
v2 = (GLfloat * 3)(*coords2)
# Окно вывода
w = 600
h = 600
window = Window(visible=True, width=w, height=h, caption='Pencil Inc.')
glClearColor(0.9, 0.9, 0.9, 1.0)
glClear(GL_COLOR_BUFFER_BIT)
glLineWidth(3)
glPolygonMode(GL_FRONT, GL_FILL)    # Заливка лицевой стороны
glPolygonMode(GL_BACK, GL_LINE)  # Вывод нелицевой стороны в виде линей (ребер)
px = py = 0
fl = displayRound = interpolate = pat = True
gl.glShadeModel(gl.GL_SMOOTH)   # выключить - GL_FLAT


def generateV(i: int, minh: float, maxh: float):
    tmp = [-1+i*0.5, random.uniform(minh, maxh), 0]
    return tmp


def addVer(v: list, center: list, accur_coef: int, rad: float, c1=True,
           c2=True, c3=True, c4=True, multx = 1.0, multy = 1.0):
    if not c1 or not c4:
        v.append((GLfloat * 3)(*center))

    left = center[0] - rad
    right = center[0] + rad
    if not c1:
        right = center[0]
    if not c2:
        left = center[0]

    for x in np.linspace(right, left, accur_coef):
        tmp = [x, math.sqrt(abs(rad ** 2 - (x - center[0]) ** 2)) + center[1], 0]
        tmp[1] *= multy
        tmp[0] *= multx
        v.append((GLfloat * 3)(*tmp))

    if not c2 or not c3:
        v.append((GLfloat * 3)(*center))

    left = center[0] - rad
    right = center[0] + rad
    if not c4:
        right = center[0]
    if not c3:
        left = center[0]

    for x in np.linspace(left, right, accur_coef):
        tmp = [x, -math.sqrt(abs(rad ** 2 - (x - center[0]) ** 2)) + center[1], 0]
        tmp[1] *= multy
        tmp[0] *= multx
        v.append((GLfloat * 3)(*tmp))


@window.event
def on_draw():
    window.clear()
    # Аффинные преобразования выполняем в мировой система координат
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glRotatef(180*px, 1, 0, 0)  # Поворот вокруг оси X
    glRotatef(180*py, 0, 1, 0)  # Поворот вокруг оси Y
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-4, 4, -4, 4, -1, 1)    # Прямоугольное проецирование

    glEnable(GL_BLEND)  # Добавляем эффект смешения цветов
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

    if pat:
        glEnable(GL_LINE_STIPPLE)
        pattern = '0b1111100110011111'
        gl.glLineStipple(2, int(pattern, 2))
        print(type(pattern))
    # треугольник
    glColor3f(0.9, 0.7, 0.1)
    glBegin(GL_TRIANGLES)
    glVertex3fv(v0)
    glVertex3fv(v1)
    glVertex3fv(v2)
    glEnd()

    # грифель
    glColor3f(0.4, 0.4, 0.4)
    glBegin(GL_POLYGON)
    rad = 0.5
    coords3 = [(coords0[0] + coords2[0])/2, (coords0[1] + coords2[1])/2, 0]
    coords8 = [(coords1[0] + coords2[0])/2, (coords1[1] + coords2[1])/2, 0]
    v = list()
    v.append((GLfloat * 3)(*coords3))
    for i in range(4):
        tmp = generateV(i, (coords0[1] + coords2[1])/2 - rad, (coords0[1] + coords2[1])/2)
        v.append((GLfloat * 3)(*tmp))
    v.append((GLfloat * 3)(*coords8))

    for ver in v:
        glVertex3fv(ver)
    glColor3f(0, 0, 0)
    glVertex3fv(v2)
    glEnd()

    if displayRound:
        # кружочек
        glColor3f(0.5, 0.3, 0.5)
        glBegin(GL_POLYGON)
        accur_coef = 40
        center = [0, -2, 0]
        rad = 1
        v = list()
        addVer(v, center, accur_coef, rad, c3=False, c4=False)
        for ver in v:
            glVertex3fv(ver)
        glEnd()

        glBegin(GL_LINE_STRIP)

        v = list()
        addVer(v, center, accur_coef, rad-1.5*8/w, c1=False, c2=False, c3=False)
        for ver in v:
            glVertex3fv(ver)

        glEnd()

    glDisable(GL_BLEND)

    if pat:
        glDisable(GL_LINE_STIPPLE)

@window.event
def on_key_press(symbol, modifiers):
    global px, py, fl, displayRound, interpolate, pat
    if symbol == key.W or symbol == key.S:
        px = 1 - px
        py = 0
    elif symbol == key.A or symbol == key.D:
        px = 0
        py = 1 - py
    elif symbol == key.C:
        if fl:
            glPolygonMode(GL_BACK, GL_POINT)
            glPointSize(3)
            fl = False
        else:
            glPolygonMode(GL_BACK, GL_LINE)
            glPointSize(1)
            fl = True
    elif symbol == key.R:
        displayRound = not displayRound
    elif symbol == key.I:
        interpolate = not interpolate
        if interpolate:
            glShadeModel(gl.GL_SMOOTH)
        else:
            glShadeModel(gl.GL_FLAT)
    elif symbol == key.P:
        pat = not pat

app.run()

