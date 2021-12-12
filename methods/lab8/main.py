import numpy as np
from matplotlib import pyplot as plt


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
        if left > b:
            i -= 1
            break
    if i + 1 > len(UDots) - 1:
        i -= 1
        right = b
        left = b - h
    y1 = UDots[i + 1]
    y0 = UDots[i]
    x0 = left
    x1 = right
    return (y1 - y0) / h * x + (y0 * x1 - y1 * x0) / h




def k1(x):
    return 6-x


def k2(x):
    return np.sqrt(x+3)


def k3(x):
    return 16


def k(x, prstn):
    if x < 0 or x > 3:
        return 0
    elif x <= 1:
        return prstn[0](x)
    elif x <= 2:
        return prstn[1](x)
    else:
        return prstn[2](x)


A = 0
B = 3
Ua = 5
Ub = 1
N = 50
x0 = 2.2


def GetUdots(A, B, Ua, Ub, N, prstn):
    h = (B - A) / N
    x = np.linspace(A, B, N + 1)
    a = [-k(x[i] - h / 2, prstn) for i in range(N + 1)]
    b = [k(x[i] + h / 2, prstn) + k(x[i] - h / 2, prstn) for i in range(N + 1)]
    c = [-k(x[i] + h / 2, prstn) for i in range(N + 1)]
    d = [h ** 2 * f(x[i]) for i in range(N + 1)]

    d[0] = Ua
    d[N] = Ub
    b[0] = 1
    c[0] = 0
    a[N] = 0
    b[N] = 1

    return getUVec(getCoefs(a, b, c, d, N), Ua, Ub)


plt.figure(figsize=(9, 9))
funcs = [k1, k2, k3]
prstn = []
for i in range(3):
    prstn.append(funcs[i])
    for j in range(3):
        if j == i:
            continue
        prstn.append(funcs[j])
        for l in range(3):
            if l == i or l == j:
                continue
            x = np.linspace(A, B, N + 1)
            prstn.append(funcs[l])
            udots = GetUdots(A, B, Ua, Ub, N, prstn)
            y = [getAnyX(xi, udots, h, A, B) for xi in x]

plt.legend()
