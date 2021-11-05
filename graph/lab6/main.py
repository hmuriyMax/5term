import numpy as np
import matplotlib.pyplot as plt
# библиотека базы выборок Mnist
from tensorflow.keras.datasets import mnist
# from tensorflow import keras
# from tensorflow.keras.layers import Dense, Flatten

#Загружаем датасет(картинки 28 на 28 пикселей со значениями цветов пикселей от 0 - чёрный до 255 - белый)
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# нормализация
x_train = x_train / 255
x_test = x_test / 255

# отображение первых 25 изображений из обучающей выборки
plt.figure(figsize=(10,5))
for i in range(25):
    plt.subplot(5,5,i+1)
    plt.xticks([])
    plt.yticks([])
    plt.imshow(x_train[i], cmap=plt.cm.binary)

plt.show()