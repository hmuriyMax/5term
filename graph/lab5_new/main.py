import math

from pyglet.gl import *
from pyglet import clock
from pyglet import app, graphics
from pyglet.window import Window, key
import numpy as np
import random

d, d1, d2 = 5, 10, 15
wx, wy = 1.5 * d2, 1.5 * d2
width, height = int(40 * wx), int(40 * wy)
window = Window(visible=True, width=width, height=height, resizable=True)
glClearColor(0.1, 0.1, 0.1, 1.0)
flag = False


gl.glClear(gl.GL_COLOR_BUFFER_BIT | gl.GL_DEPTH_BUFFER_BIT)
gl.glEnable(gl.GL_DEPTH_TEST)
gl.glDepthFunc(gl.GL_LESS)

glEnable(GL_NORMALIZE)

def make_GL_array(data):
    arr = (GLfloat*len(data))()
    for i in range(len(data)):
        arr[i] = data[i]
    return arr

lgtCol0 = [1, 0, 1, 0]
lgtCol1 = [0, 1, 0, 0]

mtClr = (gl.GLfloat * 4)(1, 1, 1, 0)
lgt0Pos = (gl.GLfloat * 4)(20, 10, 0, 0)
lgtCol = (gl.GLfloat * 4)(1, 0, 0, 0)
lgt1Pos = (gl.GLfloat * 4)(20, 30, 0, 0)
lgt2Col = (gl.GLfloat * 4)(0, 1, 1, 0)

for k in range(4):
    lgtCol[k] = lgtCol0[k]
for k in range(4):
    lgt2Col[k] = lgtCol1[k]

n_rot = 0
da = 5

# Включение/выключение вывода оснований
flag1 = True
# Включение/отключение отображений нормалей
flag2 = False
# Включение/отключение теста глубины
flag4 = True
# Включение/выключение режима отсечения нелицевых сторон
flag5 = False
# Нормализация/отказ от нормализации нормалей при их расчете
flag7 = True
# Включение/выключение освещения
flag8 = True
# Включение/выключение DIFFUSE
flag9 = True
# Включение/отключение неподвижного источника
flag6 = True

# Перемена нормалей
flagn = True

upper = []
lower = []

low_normals = []
upp_normals = []
# Координаты вершин нижнего основания
vertex_normals = []

gl.glMaterialfv(gl.GL_FRONT_AND_BACK, gl.GL_DIFFUSE, mtClr)

ang = 0
r = 8
n = 6
h = 15
for i in range(n):
    x = r * math.cos(i / n * 2 * math.pi)
    z = r * math.sin(i / n * 2 * math.pi)
    upper.append((x, 0, z))
    lower.append((x, h, z))


def nrmlz(vect):
    return vect/np.linalg.norm(vect)


@window.event
def on_draw():
    global n_rot, da, ang
    window.clear()
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()

    glOrtho(-30, 30, -30, 30, -30, 30)
    gluLookAt(0.2, 0.5, 0.5,  # position of camera
              0, 0, 0,  # where camera is pointing at
              0, 1, 0)  # which direction is up

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glPointSize(15)

    gl.glEnable(gl.GL_LIGHT0)

    if flag6:
        gl.glEnable(gl.GL_LIGHT1)
    else:
        gl.glDisable(gl.GL_LIGHT1)

    gl.glLightfv(gl.GL_LIGHT1, gl.GL_POSITION, lgt1Pos)
    gl.glLightfv(gl.GL_LIGHT1, gl.GL_DIFFUSE, lgt2Col)
    graphics.draw(1, gl.GL_POINTS,
                  ('v3f', (lgt1Pos[0], lgt1Pos[1], lgt1Pos[2])),
                  ('c3f', tuple(lgtCol1[0:3])))

    # Обработка подвижного источника света
    glPushMatrix()
    glRotatef(n_rot, 0, 1, 0)
    if flag:
        glTranslatef(0, random.randint(-10, 10), 0)

    gl.glLightfv(gl.GL_LIGHT0, gl.GL_POSITION, lgt0Pos)
    gl.glLightfv(gl.GL_LIGHT0, gl.GL_DIFFUSE, lgtCol)
    graphics.draw(1, gl.GL_POINTS,
                  ('v3f', (lgt0Pos[0], lgt0Pos[1], lgt0Pos[2])),
                  ('c3f', tuple(lgtCol0[0:3])))
    glPopMatrix()

    if flag4:
        gl.glEnable(gl.GL_DEPTH_TEST)
    else:
        gl.glDisable(gl.GL_DEPTH_TEST)

    if flag5:
        glCullFace(GL_FRONT)
        glEnable(GL_CULL_FACE)
    else:
        glDisable(GL_CULL_FACE)

    if flag7:
        glEnable(GL_NORMALIZE)
    else:
        glDisable(GL_NORMALIZE)

    glLineWidth(5)

    a = 1, 2
    if a != 3:
        break

    # glPolygonMode(GL_BACK, GL_LINE)
    glPolygonMode(GL_FRONT, GL_FILL)

    gl.glColor3f(1, 1, 1)

    graphics.draw(6, GL_LINES, ('v3f', (0, 0, 0, 0, 100, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 100)))

    glRotatef(ang, 1, 0, 0)
    glRotatef(ang, 0, 0, 1)
    if flag1:
        # Включение/выключение расчета освещения
        if flag8:
            glEnable(GL_LIGHTING)
        else:
            glDisable(GL_LIGHTING)

        # Нижнее основание
        glColor3f(0, 1, 0)
        glBegin(gl.GL_POLYGON)
        glNormal3f(0, 1, 0)
        lower.reverse()
        upper.reverse()
        for dot in lower:
            glVertex3f(dot[0], dot[1], dot[2])
        glEnd()

        glBegin(gl.GL_POLYGON)
        glNormal3f(0, -1, 0)
        for dot in upper:
            glVertex3f(dot[0], dot[1], dot[2])
        glEnd()
        glDisable(GL_LIGHTING)
        lower.reverse()
        upper.reverse()

    gl.glColor3f(1, 0, 0)


    for i in range(n):

        prv = i
        ths = (i + 1) % n
        nxt = (i + 2) % n

        # Вычисление нормалей к граням (нижнее основание)
        v1 = np.array([lower[prv][0], lower[prv][1], lower[prv][2]])
        v0 = np.array([lower[ths][0], lower[ths][1], lower[ths][2]])
        v2 = np.array([upper[ths][0], upper[ths][1], upper[ths][2]])
        a1 = v1 - v0
        b1 = v2 - v0
        nrml1 = -np.cross(a1, b1)

        low_normals.append(nrml1)

        v3 = np.array([lower[nxt][0], lower[nxt][1], lower[nxt][2]])
        a2 = v2 - v0
        b2 = v3 - v0
        nrml2 = -np.cross(a2, b2)

        low_normals.append(nrml2)

        # Вычисление нормалей к граням (верхнее основание)
        v1 = np.array([upper[prv][0], upper[prv][1], upper[prv][2]])
        v0 = np.array([upper[ths][0], upper[ths][1], upper[ths][2]])
        v2 = np.array([lower[ths][0], lower[ths][1], lower[ths][2]])
        a1 = v2 - v0
        b1 = v1 - v0
        nrml3 = -np.cross(a1, b1)

        upp_normals.append(nrml3)

        v3 = np.array([upper[nxt][0], upper[nxt][1], upper[nxt][2]])
        a2 = v3 - v0
        b2 = v2 - v0
        nrml4 = -np.cross(a2, b2)

        upp_normals.append(nrml4)

        if flag8:
            gl.glEnable(gl.GL_LIGHTING)
        else:
            gl.glDisable(gl.GL_LIGHTING)

        # Вывод боковых граней призмы
        glBegin(gl.GL_QUADS)
        tmp1 = tmp2 = []
        if (flagn):
            tmp1 = nrmlz(nrml1 + nrml2) + (0, -1, 0)
            tmp2 = nrmlz(nrml3 + nrml4) + (0, 1, 0)
        else:
            tmp1 = nrmlz(nrml1)
            tmp2 = nrmlz(nrml3)

        glNormal3fv(make_GL_array(lower[ths] + tmp1*5))
        glVertex3f(lower[ths][0], lower[ths][1], lower[ths][2])
        # Задаем нормали к верхним вершинам
        glNormal3fv(make_GL_array(upper[ths] + tmp2*5))
        glVertex3f(upper[ths][0], upper[ths][1], upper[ths][2])
        # Задаем нормали к верхним вершинам
        glNormal3fv(make_GL_array(upper[nxt] + tmp2*5))
        glVertex3f(upper[nxt][0], upper[nxt][1], upper[nxt][2])
        # Задаем нормали к верхним вершинам
        glNormal3fv(make_GL_array(lower[nxt] + tmp1*5))
        glVertex3f(lower[nxt][0], lower[nxt][1], lower[nxt][2])
        glEnd()
        glDisable(GL_LIGHTING)

    if flag2:
        for i in range(n):
            gl.glBegin(gl.GL_LINES)
            if (flagn):
                glColor3f(1, 1, 0)
                glVertex3fv(make_GL_array(upper[(i + 1) % n]))
                glVertex3fv(make_GL_array(upper[(i + 1) % n] + low_normals[i * 2] / 16))

                glVertex3fv(make_GL_array(upper[(i + 1) % n]))
                glVertex3fv(make_GL_array(upper[(i + 1) % n] + low_normals[i * 2 + 1] / 16))

            else:
                glColor3f(0.5, 0, 0.5)
                glVertex3fv(make_GL_array(upper[(i + 1) % n]))
                glVertex3fv(make_GL_array(upper[(i + 1) % n]
                                          + (nrmlz(low_normals[2 * i + 1] + low_normals[i * 2]) + (0, -1, 0))*5))

            if (flagn):
                glColor3f(1, 1, 0)
                glVertex3fv(make_GL_array(lower[(i + 1) % n]))
                glVertex3fv(make_GL_array(lower[(i + 1) % n] + upp_normals[i * 2] / 16))

                glVertex3fv(make_GL_array(lower[(i + 1) % n]))
                glVertex3fv(make_GL_array(lower[(i + 1) % n] + upp_normals[i * 2 + 1] / 16))

            else:
                glColor3f(0.5, 0, 0.5)
                glVertex3fv(make_GL_array(lower[(i + 1) % n]))
                glVertex3fv(make_GL_array(lower[(i + 1) % n]
                                          + (nrmlz(upp_normals[2 * i + 1] + upp_normals[i * 2]) + (0, 1, 0))*5))

            gl.glEnd()


def rot_func(dt):
    global n_rot, da
    if abs(n_rot) > 360:
        n_rot = 0
    n_rot += da


clock.schedule_interval(rot_func, 0.001)


@window.event
def on_key_press(char, modifiers):
    global da, ang, flag1, flag2, flag4, flag5, flag7, flag9, flag8, flag6, trans, flag, flagn

    # Отключение/включение вывода оснований
    if char == key._1:
        flag1 = not(flag1)

    # Отключение/включение вывода нормалей
    if char == key._2:
        flag2 = not(flag2)

    # Произвольное изменение ориентации фигуры
    if char == key._3:
        ang = random.randint(-90, 90)

    # Отключение/включение теста глубины
    if char == key._4:
        flag4 = not (flag4)

    # Отключение/включение режима отсечения нелицевых сторон
    if char == key._5:
        flag5 = not(flag5)

    # Отключение/включение неподвижного источника
    if char == key._6:
        flag6 = not(flag6)

    # Включение/отключение нормализации
    if char == key._7:
        flag7 = not (flag7)

    # Отключение/включение режима расчета освещенности
    if char == key._8:
        flag8 = not(flag8)

    # Отключение/включение компоненты материала GL_DIFFUSE
    if char == key._9:
        flag9 = not(flag9)
        if flag9:
            gl.glMaterialfv(gl.GL_FRONT_AND_BACK, gl.GL_DIFFUSE, mtClr)
        else:
            gl.glMaterialfv(gl.GL_FRONT_AND_BACK, gl.GL_DIFFUSE, make_GL_array((0, 0, 0)))

    # Управление подвижным источником света по оси Y
    if char == key.Z:
        da += 1

    if char == key.X:
        da -= 1

    # Произвольное изменение положения одного источника света
    if char == key.R:
        flag = not(flag)

    if char == key.N:
        flagn = not(flagn)


app.run()