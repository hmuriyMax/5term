from sys import exit

import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
from keras.layers import Input, Dense, Flatten
from keras.models import Model

#
img_rows = img_cols = 28
show_k = True  # False True
pred = True
mnist = not True
pathToData = 'mnist/' if mnist else 'emnist/'
num_classes = 10 if mnist else 26
epochs = 20
fn_model = pathToData + 'lk3.h5'
#
pathToHistory = 'mnist/' if mnist else 'emnist/'
suff = '.txt'
# Имена файлов, в которые сохраняется история обучения
fn_loss = pathToHistory + 'loss_' + suff
fn_acc = pathToHistory + 'acc_' + suff
fn_val_loss = pathToHistory + 'val_loss_' + suff
fn_val_acc = pathToHistory + 'val_acc_' + suff


def ch(i):
    return i if mnist else str(chr(ord('A')+i-1))


def show_x(x, y, img_rows, img_cols, N):
    n = int(np.sqrt(N))
    plt.figure(figsize=(10,10))
    for i, j in enumerate(np.random.randint(20800, size=n * n)):
        plt.subplot(n, n, i+1)
        # Убираем 3-е измерение
        plt.title(ch(y[j]))
        plt.imshow(x[j].reshape(img_rows, img_cols), cmap='gray')
        plt.axis('off')
    plt.show()


#
# Вывод графиков
def one_plot(n, y_lb, loss_acc, val_loss_acc):
    plt.subplot(1, 2, n)
    if n == 1:
        lb, lb2 = 'loss', 'val_loss'
        yMin = 0
        yMax = 1.05 * max(max(loss_acc), max(val_loss_acc))
    else:
        lb, lb2 = 'acc', 'val_acc'
        yMin = min(min(loss_acc), min(val_loss_acc))
        yMax = 1.0
    plt.plot(loss_acc, color='r', label=lb, linestyle='--')
    plt.plot(val_loss_acc, color='g', label=lb2)
    plt.ylabel(y_lb)
    plt.xlabel('Эпоха')
    plt.ylim([0.95 * yMin, yMax])
    plt.legend()


#
def loadBinData(pathToData, img_rows, img_cols):
    print('Загрузка данных из двоичных файлов...')
    with open(pathToData + 'imagesTrain.bin', 'rb') as read_binary:
        x_train = np.fromfile(read_binary, dtype=np.uint8)
    with open(pathToData + 'labelsTrain.bin', 'rb') as read_binary:
        y_train = np.fromfile(read_binary, dtype=np.uint8)
    with open(pathToData + 'imagesTest.bin', 'rb') as read_binary:
        x_test = np.fromfile(read_binary, dtype=np.uint8)
    with open(pathToData + 'labelsTest.bin', 'rb') as read_binary:
        y_test = np.fromfile(read_binary, dtype=np.uint8)
    # Преобразование целочисленных данных в float32 и нормализация; данные лежат в диапазоне [0.0, 1.0]
    if not mnist:
        y_train -= 1
        y_test -= 1
    x_train = np.array(x_train, dtype='float32') / 255
    x_test = np.array(x_test, dtype='float32') / 255
    x_train = x_train.reshape(-1, img_rows, img_cols)
    x_test = x_test.reshape(-1, img_rows, img_cols)
    # Преобразование в категориальное представление: метки - числа из диапазона [0, 9] в двоичный вектор размера num_classes
    # Так, в случае MNIST метка 5 (соответствует классу 6) будет преобразована в вектор [0. 0. 0. 0. 0. 0. 1. 0. 0. 0.]
    # print(y_train[0]) # (MNIST) Напечатает: 5
    print('Преобразуем массивы меток в категориальное представление')
    y_train = tf.keras.utils.to_categorical(y_train, num_classes)
    y_test = tf.keras.utils.to_categorical(y_test, num_classes)
    # print(y_train[0]) # (MNIST) Напечатает: [0. 0. 0. 0. 0. 1. 0. 0. 0. 0.]
    return x_train, y_train, x_test, y_test


#
# Загрузка обучающего и проверочного множества из бинарных файлов
# Загружаются изображения и их метки
x_train, y_train, x_test, y_test = loadBinData(pathToData, img_rows, img_cols)
if show_k:
    show_x(x_test, np.array([np.argmax(m) for m in y_test]), img_rows, img_cols, 25)

#
# Определяем форму входных данных
input_shape = (img_rows, img_cols)
#
# Создание модели нейронной сети
inp = Input(shape=input_shape)  # Входной слой
x = inp
x = Flatten()(x)  # Преобразование 2D в 1D
x = Dense(units=32, activation='relu')(x)
output = Dense(num_classes, activation='softmax')(x)
model = Model(inputs=inp, outputs=output)
model.summary()
model.compile(optimizer='Adam', loss='mse', metrics=['accuracy'])
# 
# Обучение нейронной сети 
history = model.fit(x_train, y_train, batch_size=128, epochs=epochs,
                    verbose=2, validation_data=(x_test, y_test))
print('Модель сохранена в файле', fn_model)
model.save(fn_model)
# Запись истории обучения в текстовые файлы 
history = history.history
##for itm in history.items(): print(itm) 
with open(fn_loss, 'w') as output:
    for val in history['loss']: output.write(str(val) + '\n')
with open(fn_acc, 'w') as output:
    for val in history['accuracy']: output.write(str(val) + '\n')
with open(fn_val_loss, 'w') as output:
    for val in history['val_loss']: output.write(str(val) + '\n')
with open(fn_val_acc, 'w') as output:
    for val in history['val_accuracy']: output.write(str(val) + '\n')
# Вывод графиков обучения 
plt.figure(figsize=(9, 4))
plt.subplots_adjust(wspace=0.5)
one_plot(1, 'Потери', history['loss'], history['val_loss'])
one_plot(2, 'Точность', history['accuracy'], history['val_accuracy'])
plt.suptitle('Потери и точность')
plt.show()
