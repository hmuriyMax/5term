# u = y[0], v = y[1]
import numpy as np


def f1(y: list, t):
    return (y[0] ** 2) / y[1]


def f2(y: list, t):
    return y[0] / ((y[1] + t) ** 2)


def Eiler(a, b, h, n, funcs, t0, y0):
    y = y0.copy()
    t = t0
    for i in range(n):
        tmp = []
        for k in range(len(funcs)):
            tmp.append(y[k] + h * funcs[k](y, t))
            t += h
        y = tmp
    return y


def getRungeEps(a, b, h, n, rgt_fun, t0, y0, counter_fun, p):
    lst1 = counter_fun(a, b, h / 2, 2 * n, rgt_fun, t0, y0)
    lst2 = counter_fun(a, b, h, n, rgt_fun, t0, y0)
    return [abs(lst1[i] - lst2[i] / (2 ** p - 1)) for i in range(len(y0))]


def modEiler(a, b, h, n, funcs, t0, y0):
    y = y0.copy()
    t = t0
    for i in range(n):
        tmp = []
        for i in range(len(funcs)):
            tmpy = [y[j] + h / 2 * funcs[j](y, t) for j in range(len(funcs))]
            tmp.append(y[i] + h * funcs[i](tmpy, t + h / 2))
            t += h
        y = tmp
    return y

def nEiler(a, b, h, n, funcs, t0, y0):
    y = y0.copy()
    t = t0
    for i in range(n):
        tmp = []
        # Прогноз
        for k in range(len(funcs)):
            tmp.append(y[k] + h*funcs[k](y, t))
        t += h
        tmp2 = []
        # Уточнение
        for k in range(len(funcs)):
            tmp2.append(y[k] + h*funcs[k](tmp, t)/400)
        y = tmp2
    return y


if __name__ == "__main__":
    funcs = [f1, f2]
    y = [1, 1]
    t = 0
    a = 0
    b = 1
    h = 0.01
    n = int((b - a) / h)

    A = np.array([[-7.146, -2.704, 6.981, 2.364], [-2.292, -8.358, -3.549, 6.248], [-0.016, 6.93, -4.356, 3.652],
                  [-7.508, 1.251, -0.171, -8.139]])
    B = np.array(
        [[-206.91, 79.356, -112.31, 20.083], [47.474, -25.434, 57.346, -35.228], [-112.31, 18.883, -69.502, 54.186],
         [66.685, 11.374, -2.035, -16.16]])
    Y_0 = [8.4, 8.4, 6.4, 8.4]
    Z_0 = [10.4, 5.2, 8.4, 5.2]
    print("A: Вещественные части собств. чисел:")
    An = [np.real(el) for el in np.linalg.eig(A)[0]]
    for el in An:
        print(el)
    An = [abs(el) for el in An]
    print("s = {:.2f}".format(max(An) / min(An)))
    print()

    print("В: Вещественные части собств. чисел:")
    Bn = [np.real(el) for el in np.linalg.eig(B)[0]]
    for el in Bn:
        print(el)
    Bn = [abs(el) for el in Bn]
    print("s = {:.2f}".format(max(Bn) / min(Bn)))

    funcs2 = []
    for line in A:
        tmp = list(line)


        def fun(y: list, t, arg=None):
            if arg is None:
                arg = tmp
            res = 0
            for i in range(len(y)):
                res += arg[i] * y[i]
            return res

        funcs2.append(fun)

    funcs3 = []
    for line in B:
        def fun2(y: list, t, arg=line):
            res = 0
            for i in range(len(y)):
                res += arg[i] * y[i]
            return res

        funcs3.append(fun2)

    print(funcs2[3](Y_0, t))
    ans = Eiler(a, b, h, n, funcs3, t, Z_0)
    print("A: Eiler met:  ", end='')
    for i in range(len(ans)):
        print("y{:d} = {:.5f}".format(i, ans[i]), end='  ')
    print()
    ans = nEiler(a, b, h, n, funcs3, t, Z_0)
    print("B: nEiler met:  ", end='')
    for i in range(len(ans)):
        print("y{:d} = {:.5f}".format(i, ans[i]), end='  ')
    print()
