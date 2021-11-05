from sys import exit

import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
from keras.layers import Input, Dense, Flatten
from keras.models import Model

#
img_rows = img_cols = 28 
show_k = not True # False True 
pred = not True 
mnist = True
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
# 
def show_x(x, img_rows, img_cols, N): 
    n = int(np.sqrt(N)) 
    print(x[0].shape, len(x), n) 
    for i, j  in enumerate(np.random.randint(1000, size = n*n)): 
        plt.subplot(n, n, i + 1) 
        # Убираем 3-е измерение 
        plt.imshow(x[j].reshape(img_rows, img_cols), cmap = 'gray') 
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
    plt.plot(loss_acc, color = 'r', label = lb, linestyle = '--') 
    plt.plot(val_loss_acc, color = 'g', label = lb2) 
    plt.ylabel(y_lb) 
    plt.xlabel('Эпоха') 
    plt.ylim([0.95 * yMin, yMax]) 
    plt.legend() 
# 
def loadBinData(pathToData, img_rows, img_cols): 
    print('Загрузка данных из двоичных файлов...') 
    with open(pathToData + 'imagesTrain.bin', 'rb') as read_binary: 
        x_train = np.fromfile(read_binary, dtype = np.uint8) 
    with open(pathToData + 'labelsTrain.bin', 'rb') as read_binary: 
        y_train = np.fromfile(read_binary, dtype = np.uint8) 
    with open(pathToData + 'imagesTest.bin', 'rb') as read_binary: 
        x_test = np.fromfile(read_binary, dtype = np.uint8) 
    with open(pathToData + 'labelsTest.bin', 'rb') as read_binary: 
        y_test = np.fromfile(read_binary, dtype = np.uint8) 
    # Преобразование целочисленных данных в float32 и нормализация; данные лежат в диапазоне [0.0, 1.0] 
    x_train = np.array(x_train, dtype = 'float32') / 255 
    x_test = np.array(x_test, dtype = 'float32') / 255 
    print(x_test.shape) 
    x_train_shape_0 = int(x_train.shape[0] / (img_rows * img_cols)) 
    x_test_shape_0 = int(x_test.shape[0] / (img_rows * img_cols)) 
    x_train = x_train.reshape(x_train_shape_0, img_rows, img_cols, 1) # 1 - оттенок серого цвета 
    x_test = x_test.reshape(x_test_shape_0, img_rows, img_cols, 1) 
    # Преобразование в категориальное представление: метки - числа из диапазона [0, 9] в двоичный вектор размера num_classes 
    # Так, в случае MNIST метка 5 (соответствует классу 6) будет преобразована в вектор [0. 0. 0. 0. 0. 0. 1. 0. 0. 0.] 
    #print(y_train[0]) # (MNIST) Напечатает: 5 
    print('Преобразуем массивы меток в категориальное представление') 
    y_train = tf.keras.utils.to_categorical(y_train, num_classes) 
    y_test = tf.keras.utils.to_categorical(y_test, num_classes) 
    #print(y_train[0]) # (MNIST) Напечатает: [0. 0. 0. 0. 0. 1. 0. 0. 0. 0.] 
    return x_train, y_train, x_test, y_test 
# 
# Загрузка обучающего и проверочного множества из бинарных файлов 
# Загружаются изображения и их метки 
x_train, y_train, x_test, y_test = loadBinData(pathToData, img_rows, img_cols) 
if show_k: 
    show_x(x_test, img_rows, img_cols, 16) 
    exit() 
if pred: 
    from keras.models import load_model 
    model = load_model(fn_model) 
    # Оценка модели НС на тестовых данных 
    score = model.evaluate(x_test, y_test, verbose = 0) 
    # Вывод потерь и точности 
    print('Потери при тестировании:', round(score[0], 4)) 
    print('Точность при тестировании: {}{}'.format(score[1] * 100, '%')) 
    # Прогноз 
    y_pred = model.predict(x_test) 
    # print(y_pred[0]) 
    # print(y_test[0]) 
    # [6.8e-6 1.5e-10 7.6e-6 1.5e-3 7.0e-9 6.2e-5 2.2e-11 9.9e-1 3.0e-7 5.9e-6] 
    # [0.     0.      0.     0.     0.     0.     0.      1.     0.     0.] 
    # Заносим в массив predicted_classes метки классов, предсказанных моделью НС 
    predicted_classes = np.array([np.argmax(m) for m in y_pred]) 
    true_classes = np.array([np.argmax(m) for m in y_test]) 
    n_test = len(y_test) 
    # Число верно классифицированных изображений 
    true_classified = np.sum(predicted_classes == true_classes) 
    # Число ошибочно классифицированных изображений 
    false_classified = n_test - true_classified 
    acc = 100.0 * true_classified / n_test 
    print('Точность: {}{}'.format( acc, '%')) 
    print('Неверно классифицированно:', false_classified) 
    m, m_max = 0, 15 
    lst_false = [] 
    print('Индекс | Прогноз | Правильный класс') 
    for i in range(n_test): 
        cls_pred = predicted_classes[i] # Предсказанное моделью имя класса 
        cls_true = true_classes[i] # Истинное имя класса 
        if cls_pred != cls_true: 
            m += 1 
            lst_false.append([i, cls_pred, cls_true]) 
            if (m == min(m_max, false_classified)): break 
            print('  {}   |   {}    |    {}'.format(i, cls_pred, cls_true)) 
    plt.figure('Ошибки классификации') 
    for k in range(len(lst_false)): 
        plt.subplot(3, 5, k + 1) 
        lst = lst_false[k] 
        plt.imshow(x_test[lst[0]].reshape(img_rows, img_cols), cmap = 'gray') 
        plt.title('{}/{}'.format(lst[1], lst[2])) 
        plt.axis('off') 
    plt.show() 
    exit() 
# 
# Определяем форму входных данных 
input_shape = (img_rows, img_cols, 1) 
# 
# Создание модели нейронной сети 
inp = Input(shape = input_shape) # Входной слой 
x = inp 
x = Flatten()(x) # Преобразование 2D в 1D 
x = Dense(units = 32, activation = 'relu')(x) 
output = Dense(num_classes, activation = 'softmax')(x) 
model = Model(inputs = inp, outputs = output) 
model.summary() 
model.compile(optimizer = 'Adam', loss = 'mse', metrics = ['accuracy']) 
# 
# Обучение нейронной сети 
history = model.fit(x_train, y_train, batch_size = 128, epochs = epochs, 
                        verbose = 2, validation_data = (x_test, y_test)) 
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
plt.figure(figsize = (9, 4)) 
plt.subplots_adjust(wspace = 0.5) 
one_plot(1, 'Потери', history['loss'], history['val_loss']) 
one_plot(2, 'Точность', history['accuracy'], history['val_accuracy']) 
plt.suptitle('Потери и точность') 
plt.show() 
