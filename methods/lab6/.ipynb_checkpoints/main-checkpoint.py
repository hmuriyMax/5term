import numpy as np


def rgt(t, y):
    return (2 + np.sqrt(t))/(4*t)*y


def modEiler(a, b, h, n, fun, t0, y0):
    y = y0
    t = t0
    for i in range(n):
        y = y + h*fun(t + h/2, y + h/2 * fun(t, y))
        t += h
    return y


def Eiler(a, b, h, n, fun, t0, y0):
    y = y0
    t = t0
    for i in range(n):
        y = y + h*rgt(t, y)
        t += h
    return y


def getRungeEps(a, b, h, n, rgt_fun, t0, y0, counter_fun, p):
    return((counter_fun(a, b, h/2, 2*n, rgt_fun, t0, y0) -
            counter_fun(a, b, h, n, rgt_fun, t0, y0))/(2**p - 1))


def get_n(a, b, fun, met, t0, y0, eps):
    n = 2
    old_n = 2
    h = abs(b - a)/n
    while abs(getRungeEps(a, b, h, n, fun, t0, y0, met, 1)) > eps:
        print("{:.10f}".format(getRungeEps(a, b, h, n, fun, t0, y0, met, 1)))
        old_n = n
        n *= 2
        h = abs(b-a)/n
        print(n)
    while abs(old_n - n) > 1:
        middle = (n + old_n)//2
        if getRungeEps(a, b, h, middle, fun, t0, y0, met, 1) > eps:
            old_n = middle
            print(old_n)
        else:
            n = middle
            print(n)
        h = abs(b-a)/n
    return n


if __name__ == '__main__':
    get_n(0, 2, rgt, Eiler, 1, 4, 1e-6)
