import matplotlib.pyplot as plt
from copy import deepcopy
import numpy as np
from tensorflow.keras.layers import Input, Dense, LeakyReLU, Dropout


img_rows = img_cols = 28
pathToData = 'mnist/'
print('Загрузка данных из двоичных файлов...')
with open(pathToData + 'imagesTrain.bin', 'rb') as read_binary:
    x_train = np.fromfile(read_binary, dtype=np.uint8)
with open(pathToData + 'labelsTrain.bin', 'rb') as read_binary:
    y_train = np.fromfile(read_binary, dtype=np.uint8)
with open(pathToData + 'imagesTest.bin', 'rb') as read_binary:
    x_test = np.fromfile(read_binary, dtype=np.uint8)
with open(pathToData + 'labelsTest.bin', 'rb') as read_binary:
    y_test = np.fromfile(read_binary, dtype=np.uint8)

x_train = np.array(x_train, dtype='float32') / 255
x_test = np.array(x_test, dtype='float32') / 255
x_train = x_train.reshape(-1, img_rows, img_cols)
x_test = x_test.reshape(-1, img_rows, img_cols)


def one_part(units, x):
    x = Dense(units)(x)
    x = LeakyReLU()(x)
    return Dropout(0.25)(x)


def show(img, title):
    plt.figure(figsize=(2, 2))
    plt.title(title)
    plt.imshow(img, cmap='gray')
    plt.axis('off')
    plt.show()


def move(img, x, y):
    rgx = range(img.shape[0]) if x > 0 else range(img.shape[0] - 1, -1, -1)
    rgy = range(img.shape[1]) if y > 0 else range(img.shape[1] - 1, -1, -1)

    for i in rgx:
        for j in rgy:
            if i + x > 0 and i + x < img.shape[0] and j + y > 0 and j + y < img.shape[1]:
                img[i][j] = img[i + x][j + y]
            else:
                img[i][j] = 0
    return img


def colorBorder(res, firstPic, movedPic):
    for i in range(img_rows):
        for j in range(img_cols):
            if firstPic[i][j] <= 0.35 and movedPic[i][j] > 0.35:
                res[i][j] += 0.1
    return res


def addBorder(x, y, res, image):
    image2 = deepcopy(image)
    move(image2, x, y)
    # show(image2)
    colorBorder(res, image, image2)


def getBorderOf(num):
    res = np.zeros((img_rows, img_cols))

    digits = []
    for i in range(x_test.shape[0]):
        if (y_test[i] == num):
            digits.append(x_test[i])

    image = digits[0]
    for i in range(1, len(digits)):
        image += digits[i]

    image /= len(digits)
    # show(image, num)

    addBorder(1, 1, res, image)
    addBorder(-1, 1, res, image)
    addBorder(-1, -1, res, image)
    addBorder(1, -1, res, image)
    addBorder(1, 0, res, image)
    addBorder(-1, 0, res, image)
    addBorder(0, -1, res, image)
    addBorder(0, 1, res, image)

    show(res, num)


for i in range(10):
    getBorderOf(i)