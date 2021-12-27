from datetime import datetime
import numpy as np
import matplotlib.pyplot as plt


# Обрёртка над функцией func, делающая ее заданной в ЦСК
def PolarFunc(func, alpha, r):
    x = r * np.cos(alpha)
    y = r * np.sin(alpha)
    return func(x, y)


# Перевод полярных координат в декартовы
def ToDecart(alp, r):
    x = r * np.cos(alp)
    y = r * np.sin(alp)
    return x, y


# Перевод декартовых координат в полярные
def ToPolar(x, y):
    r = np.sqrt(x ** 2 + y ** 2)
    alp = np.arctan(np.abs(y) / np.abs(x)) if x != 0 else np.pi / 2
    if x * y < 0:
        alp = np.pi - alp
    if y < 0:
        alp = np.pi + alp
    return alp, r


# получаем пригодные для построения графика массивы координат
# точек, заданных на кольце r1 <= R <= R2 с заданной дискретностью
def GetFuncDots(x_steps, y_steps, r1, r2, f):
    x = []
    y = []
    z = []
    for tx in np.linspace(-r2, r2, x_steps):
        for ty in np.linspace(-r2, r2, y_steps):
            if (tx ** 2 + ty ** 2 < r2 ** 2) and (tx ** 2 + ty ** 2 > r1 ** 2):  # проверка на попадание в кольцо
                x.append(tx)
                y.append(ty)
                z.append(f(tx, ty))
    return x, y, z


# Cоздаём исходное разбиение
def GetTable(a_steps, r_steps, r1, r2, f, dec_graph=False, pol_graph=False):
    a_steps += 1  # количество точек всегда будет на 1 больше количества отрезков.
    r_steps += 1
    table = np.zeros((a_steps, r_steps, 3))  # создаём пустую таблицу нужной размерности
    i = 0

    for alpha in np.linspace(0, 2 * np.pi, a_steps, endpoint=True):  # включаем точку 2pi в разбиение
        j = 0
        for r in np.linspace(r1, r2, r_steps):
            table[i][j] = [alpha, r, PolarFunc(f, alpha, r)]  # вычисляем значения в точках и сохраняем
            j += 1
        i += 1

    x, y, z = GetFuncDots(70, 70, r1, r2, f)
    # график в ДСК
    if dec_graph:
        fig = plt.figure(figsize=(10, 10))
        ax = fig.add_subplot(projection='3d')
        ax.plot_trisurf(x, y, z, linewidth=0, color="#0003")
        for dotlist in table:
            for el in dotlist:
                out_x, out_y = ToDecart(el[0], el[1])
                ax.scatter(out_x, out_y, el[2], s=15, color='#F00')
        plt.show()

    # график в ЦСК
    if pol_graph:
        fig = plt.figure(figsize=(10, 10))
        ax = fig.add_subplot(projection='3d')
        alp = list()
        r = list()
        for i in range(len(x)):
            talp, tr = ToPolar(x[i], y[i])
            r.append(tr)
            alp.append(talp)
        ax.plot_trisurf(alp, r, z, linewidth=0.1, edgecolors='k', color="#0003")
        for dotlist in table:
            for el in dotlist:
                ax.scatter(el[0], el[1], el[2], s=15, color='#F00')
        plt.show()

    return table


# Структура решения, содержащая все необходимые данные для вывода статистики и графиков
class Solution:
    def __init__(self, functable=None, r1=0.0, r2=0.0, asteps=0, rsteps=0):
        if functable is None:
            functable = []
        self.da = 0
        self.dr = 0
        self.functable = functable
        self.r1 = r1
        self.r2 = r2
        self.asteps = asteps
        self.rsteps = rsteps

    # метод, генерирующий таблицу функций интерполяции
    def solve(self, dot_table, graph=False):
        self.da = np.abs(dot_table[0][0][0] - dot_table[1][0][0])  # сохраняем в нашу структуру шаги разбиения
        self.dr = np.abs(dot_table[0][0][1] - dot_table[0][1][1])
        ax = None
        if graph:
            fig = plt.figure(figsize=(10, 10))
            ax = fig.add_subplot(111, projection='3d')
        for i in range(dot_table.shape[0] - 1):  # итерируемся по таблице значений
            tmp = []
            for j in range(dot_table.shape[1] - 1):
                tx0 = dot_table[i][j][0]  # получаем коэффициенты для формулы билинейного многочлена
                tx1 = dot_table[i + 1][j][0]
                ty0 = dot_table[i][j][1]
                ty1 = dot_table[i][j + 1][1]
                tz00 = dot_table[i][j][2]
                tz01 = dot_table[i][j + 1][2]
                tz10 = dot_table[i + 1][j][2]
                tz11 = dot_table[i + 1][j + 1][2]

                # создаём функцию, интерполирующую текущую область
                def tmpf(x, y, x1=tx1, x0=tx0, y0=ty0, y1=ty1, z00=tz00, z10=tz10, z01=tz01, z11=tz11):
                    a = 1 / (x1 - x0) / (y1 - y0)
                    return a * (z00 * (x1 - x) * (y1 - y) + z10 * (x - x0) * (y1 - y) + z01 * (x1 - x) * (
                                y - y0) + z11 * (x - x0) * (y - y0))

                if graph:
                    ttx = np.linspace(tx0, tx1, 10)
                    tty = np.linspace(ty0, ty1, 10)
                    ttx, tty = np.meshgrid(ttx, tty)
                    ttz = tmpf(ttx, tty)
                    ax.plot_surface(ttx, tty, ttz)  # выводим текущий "лоскуток"
                tmpf.__name__ += str(i) + str(j)
                tmp.append(tmpf)  # сохраняем текущую функцию в список функций
            self.functable.append(tmp)  # Сохраняем список функций в список списков.
            continue  # Получаем двумерную таблицу
        if graph:
            plt.show()
        # вывод в декартовых координатах
        if graph:
            fig = plt.figure(figsize=(10, 10))
            ax = fig.add_subplot(111, projection='3d')
            for i in range(dot_table.shape[0] - 1):
                for j in range(dot_table.shape[1] - 1):
                    tx0 = dot_table[i][j][0]
                    tx1 = dot_table[i + 1][j][0]
                    ty0 = dot_table[i][j][1]
                    ty1 = dot_table[i][j + 1][1]
                    ttx = np.linspace(tx0, tx1, 10)
                    tty = np.linspace(ty0, ty1, 10)
                    ttx, tty = np.meshgrid(ttx, tty)
                    ttz = self.functable[i][j](ttx, tty)
                    tx, ty = ToDecart(ttx, tty)
                    ax.plot_surface(tx, ty, ttz)
            plt.show()

    # метод получения одной аппрокс. точки по ее декартовым координатам
    def get(self, x, y):
        alp, r = ToPolar(x, y)
        fnX = int(alp / self.da)  # находим нужный нам индекс по индексу ближайшей сверху слева точки
        fnY = int((r - self.r1) / self.dr)  # разбиения. Для этого делим координату на шаг и округляем вниз
        return self.functable[fnX][fnY](alp, r)

    # метод для получения набора аппрокс. точек на прямоугольной сетке в ДСК
    def dots(self, x_steps, y_steps):
        x = []
        y = []
        Iz = []
        for tx in np.linspace(-self.r2, self.r2, x_steps):
            for ty in np.linspace(-self.r2, self.r2, y_steps):
                if (tx ** 2 + ty ** 2 < self.r2 ** 2) and (tx ** 2 + ty ** 2 > self.r1 ** 2):
                    x.append(tx)
                    y.append(ty)
                    Iz.append(self.get(tx, ty))
        return x, y, Iz


# Функция вывода значений функции и разницы между ними. Также нахождение максимума погрешности
def GetStats(true_values, mine_values, every_num=1, prints=False):
    deltas = []
    if prints:
        print("  F(x,y)   | MineF(x,y) |      Delta(x,y)      ")
        print("===============================================")
    for i in range(len(true_values)):
        delt = np.abs(true_values[i] - mine_values[i])
        deltas.append(delt)
        if prints and i % every_num == 0:
            print("%10.4f | %10.4f | %20.15f" % (true_values[i], mine_values[i], delt))

    if prints:
        mx = np.max(deltas)
        print("Максимум погрешности: ", mx)
    return deltas


#####################
# Начальные условия #


def F(x, y):
    return y*(x**2 + y**2)**3


R1 = 0
R2 = 10

A_steps = 32
R_steps = 4

graph = False

# выводим график исходной функции
if graph:
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(111, projection='3d')
    x, y, z = GetFuncDots(70, 70, R1, R2, F)
    ax.plot_trisurf(x, y, z, linewidth=0, edgecolors='k', cmap='jet')
    plt.show()

tbl = GetTable(A_steps, R_steps, R1, R2, F, graph, graph)  # получаем разбиение
sln = Solution(r1=R1, r2=R2, asteps=A_steps, rsteps=R_steps)  # создаём экземпляр класса решения
sln.solve(tbl, graph)  # решаем
_, _, Iz = sln.dots(50, 50)  # получаем значения 50х50 аппрокс. точек
x, y, z = GetFuncDots(50, 50, R1, R2, F)  # -//- точек исходной функции

# поточечный итоговый график
if graph:
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(projection='3d')
    ax.scatter(x, y, z, s=5, c="#0009")
    ax.scatter(x, y, Iz, s=5, c="#58F")
    plt.show()

deltas = GetStats(z, Iz, 100, graph)

# график погрешности
if graph:
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(projection='3d')
    ax.scatter(x, y, z, s=5, c="#0001")
    ax.scatter(x, y, Iz, s=5, c="#58F1")
    ax.plot_trisurf(x, y, deltas, linewidth=0, edgecolors='k', cmap='jet')
    plt.show()

# вывод данных о зависимости погрешности от разбиения
a_start = 1
a_finish = 100
a_nstep = 20

r_start = 1
r_finish = 100
r_nstep = 20

alps = np.linspace(a_start, a_finish, a_nstep, endpoint=True)
rads = np.linspace(r_start, r_finish, r_nstep, endpoint=True)

gralps = []
grrads = []
deltas = []
gtimes = []

start_time = datetime.now()

i = 0
for alp in alps:
    alp = int(alp)
    j = 0
    for rad in rads:
        rad = int(rad)
        stime = datetime.now()
        tbl = GetTable(alp, rad, R1, R2, F, False, False)  # получаем разбиение
        sln = Solution(r1=R1, r2=R2, asteps=alp, rsteps=rad)  # создаём экземпляр класса решения
        sln.solve(tbl, False)  # решаем
        _, _, Iz = sln.dots(50, 50)  # получаем значения 50х50 аппрокс. точек
        x, y, z = GetFuncDots(50, 50, R1, R2, F)
        time = datetime.now() - stime
        gralps.append(alp)
        grrads.append(rad)
        deltas.append(np.log10(np.max(GetStats(z, Iz))))
        gtimes.append(time.microseconds)
        j += 1
    i += 1

print("Затрачено времени: ", datetime.now() - start_time)
print("(среди разбиений)\nМинимальная погрешность: ", np.min(np.power(10, deltas)))
print("Максимальная погрешность: ", np.max(np.power(10, deltas)))

# вывод графика зависимости погрешности от разбиения
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection='3d')
ax.set_xlabel('отрезков разбиения по углу')
ax.set_ylabel('отрезков разбиения по радиусу')
ax.plot_trisurf(gralps, grrads, deltas, linewidth=0, edgecolors='k', cmap='jet')
plt.show()

# вывод графика зависимости времени от разбиения
fig = plt.figure(figsize=(10, 10))
ax = fig.add_subplot(projection='3d')
ax.set_xlabel('отрезков разбиения по углу')
ax.set_ylabel('отрезков разбиения по радиусу')
ax.plot_trisurf(gralps, grrads, gtimes, linewidth=0, edgecolors='k', cmap='rainbow')
plt.show()
