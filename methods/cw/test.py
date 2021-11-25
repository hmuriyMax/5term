import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import random
from copy import deepcopy


plt.figure(figsize=(14, 7))
plt.subplot(1, 2, 1)
r1 = 1
r2 = 3

mx = 10
t = np.linspace(0, mx, 100)
num = 15
for i in range(num):
    x = np.sin(2*np.pi/num*i)*t
    y = np.cos(2*np.pi/num*i)*t
    plt.plot(x, y, c="#0002")
    
    x = np.sin(np.pi*t*2/mx)*mx/num*i
    y = np.cos(np.pi*t*2/mx)*mx/num*i
    plt.plot(x, y, c="#0002")
    
    
fi = np.linspace(0, 2*np.pi, 100)
clr = "#99F5"
for r in np.linspace(r1, r2, 80):
    x = np.sin(fi)*r
    y = np.cos(fi)*r
    plt.plot(x, y, c=clr)

    x = np.sin(fi)*r
    y = np.cos(fi)*r
    plt.plot(x, y, c=clr)

plt.ylim(-r2-1,r2+1)
plt.xlim(-r2-1,r2+1)

plt.subplot(1, 2, 2)

for t in np.linspace(r1, r2, 300):
    x = np.linspace(0, 2*np.pi, 100)
    y = x*0+t
    plt.plot(x, y, clr)

plt.grid()
plt.ylim(r1-1,r2+1)
plt.xlim(-1,7)
#plt.show()


def f(x, y):
    return x ** 2 * y ** 2


def polar_func(func, alpha, r):
    x = r * np.sin(alpha)
    y = r * np.cos(alpha)
    return (func(x, y))


fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(111, projection='3d')

r1 = 1
r2 = 3
x = []
y = []
z = []
for tx in np.linspace(-r2, r2, 70):
    for ty in np.linspace(-r2, r2, 70):
        if (tx**2 + ty**2 < r2**2) and (tx**2 + ty**2 > r1**2):
            x.append(tx)
            y.append(ty)
            z.append(f(tx,ty))
ax.plot_trisurf(x, y, z, linewidth=0, edgecolors='k', cmap='jet')

#plt.show()

a_steps = 32
r_steps = 5
table = np.zeros((a_steps, r_steps, 3))
dotlist = []
i = 0

for alpha in np.linspace(0, 2 * np.pi, a_steps):
    j = 0
    for r in np.linspace(1, 3, r_steps):
        table[i][j] = [alpha, r, polar_func(f, alpha, r)]
        dotlist.append([alpha, r, polar_func(f, alpha, r)])
        j += 1
    i += 1

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection='3d')

ax.plot_trisurf(x, y, z, linewidth=0, color = "#0003")

for el in dotlist:
    ax.scatter(np.sin(el[0])*el[1], np.cos(el[0])*el[1], el[2], s=15, color = '#F00')
    # print("[{:5.2f}, {:5.2f}, {:5.2f}] - [{:5.2f}, {:5.2f}, {:5.2f}]".format(el[0], el[1], el[2], np.sin(el[0])*el[1], np.cos(el[0])*el[1], el[2]))
#plt.show()

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection='3d')

alp = list()
r = list()
for i in range(len(x)):
    tr = np.sqrt(x[i] ** 2 + y[i] ** 2)
    r.append(tr)
    alp.append(np.arcsin(y[i] / tr) + np.pi)

ax.plot_trisurf(alp, r, z, linewidth=0.1, edgecolors='k', color="#0003")

for el in dotlist:
    ax.scatter(el[0], el[1], el[2], s=15, color='#F00')
    # print("[{:5.2f}, {:5.2f}, {:5.2f}] - [{:5.2f}, {:5.2f}, {:5.2f}]".format(el[0], el[1], el[2], np.sin(el[0])*el[1], np.cos(el[0])*el[1], el[2]))

#plt.show()

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection='3d')

ax.scatter(x, y, z, s=10, color = "#0003")

functable = []
for i in range(table.shape[0] - 1):
    tmp = []
    for j in range(table.shape[1] - 1):
        tx0 = table[i][j][0]
        tx1 = table[i+1][j][0]
        ty0 = table[i][j][1]
        ty1 = table[i][j+1][1]
        tz00 = table[i][j][2]
        tz01 = table[i][j+1][2]
        tz10 = table[i+1][j][2]
        tz11 = table[i+1][j+1][2]
        def tmpf(x, y, x1 = tx1, x0 = tx0, y0 = ty0, y1 = ty1, z00 = tz00, z10 = tz10, z01 = tz01, z11 = tz11):
            a = 1/(x1-x0)/(y1-y0)
            return a * (z00*(x1-x)*(y1-y) + z10*(x-x0)*(y1-y) + z01*(x1-x)*(y-y0) + z11*(x-x0)*(y-y0))
        ttx = np.linspace(tx0, tx1, 10)
        tty = np.linspace(ty0, ty1, 10)
        ttx, tty = np.meshgrid(ttx, tty)
        ttz = tmpf(ttx, tty)
        ax.plot_surface(np.cos(ttx)*tty, np.sin(ttx)*tty, ttz)
        tmp.append(tmpf)
    functable.append(tmp)
    
#plt.show()

def GetZ(fntable, table, x, y):
    alp = np.arctan(y/x) + np.pi/2 if x!=0 else 0
    r = np.sqrt(x**2 + y**2)
    fnX = fnY = 0
    breaker = False
    for i in range(table.shape[0]):
        if alp < table[i][0][0]:
            for j in range(table.shape[1]):
                if r < table[i-1][j][1]:
                    fnX = i-1
                    fnY = j-1
                    breaker = True
                    break
        if breaker:
            break
    return fntable[fnX][fnY](alp, r)

x = 2
y = 2
print(f(x,y))
print(GetZ(functable, table, x, y))

fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection='3d')

x = []
y = []
z = []
Iz = []
for tx in np.linspace(-r2, r2, 70):
    for ty in np.linspace(-r2, r2, 70):
        if (tx**2 + ty**2 < r2**2) and (tx**2 + ty**2 > r1**2):
            x.append(tx)
            y.append(ty)
            z.append(f(tx,ty))
            Iz.append(GetZ(functable, table, tx, ty))
ax.scatter(x, y, z, s=5, c="#000000")
ax.scatter(x, y, Iz, s=5, c="#58F")

plt.show()
