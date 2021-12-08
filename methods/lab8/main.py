import numpy as np


def analiticalAns(x):
    return -31.334 * np.exp(-x) + 11.907 - 1 / 3 * x ** 3 + 2 * x ** 2 - 7 * x


def f(x):
    return x ** 2 - 2 * x + 3


def getCoefs(a, b, c, d, N):
    alpha = []
    beta = []
    alpha.append(-c[0] / b[0])
    beta.append(d[0] / b[0])

    for i in range(1, N):
        gamma = b[i] + a[i] * alpha[i - 1]
        alpha.append(-c[i] / gamma)
        beta.append((d[i] - a[i] * beta[i - 1]) / gamma)

    gamma = b[N] + a[N] * alpha[N - 1]
    beta.append((d[N] - a[N] * beta[N - 1]) / gamma)
    return (alpha, beta)


def getUVec(tpl: tuple, u0, uN):
    alpha = tpl[0]
    beta = tpl[1]
    N = len(alpha)
    U = [0 for i in range(N + 1)]
    U[N] = uN

    for i in range(N - 1, 0, -1):
        U[i] = alpha[i] * U[i + 1] + beta[i]

    U[0] = u0
    return U


def getAnyX(x, UDots, h, a, b):
    left = right = 0
    left = a
    right = a + h
    i = 0
    while right < x:
        left = right
        right += h
        i += 1
        if right > b:
            i -= 1
            break
    y1 = UDots[i]
    y0 = UDots[i - 1]
    x0 = left
    x1 = right
    return (y1 - y0) / h * x + (y0 * x1 - y1 * x0) / h


A = 2
B = 4
Ua = -1
Ub = -6
eps = 1e-4
N = 2


def getEps(A, B, Ua, Ub, N):
    h = (B-A)/N
    x = np.linspace(A, B, N+1)
    a = [h - 2 for _ in range(N + 1)]
    b = [4 for _ in range(N + 1)]
    c = [h + 2 for _ in range(N + 1)]
    d = [2 * h ** 2 * f(x[i]) for i in range(N + 1)]

    udots = getUVec(getCoefs(a,b,c,d,N), Ua, Ub)
    deltas = []
    for xi in x:
        delta = analiticalAns(xi) - getAnyX(xi, udots, h, A, B)
        deltas.append(delta)

    return max(deltas)


delta = getEps(A, B, Ua, Ub, N)
while delta > eps:
    N *= 2
    delta = getEps(A, B, Ua, Ub, N)
    print(N, (B-A)/N)
    print(delta)
