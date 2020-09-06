import tensorflow as tf
from PIL import Image
import numpy as np
import pandas as pd
import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow_core.python.keras import regularizers
from matplotlib import pyplot as plt
from tensorflow.keras import Model
from tensorflow.keras.layers import Conv2D, BatchNormalization, Activation, MaxPool2D, Dropout, Flatten, Dense

train_path = './data/'
test_path = './data/'

df = pd.read_csv('./training.csv')
x_train = np.array(df['FileID']+'.jpg')
y_train = np.array(df['SpeciesID'])
x_train_savepath = './image_label2/x_train.npy'
y_train_savepath = './image_label2/y_train.npy'

df = pd.read_csv('./annotation.csv')
x_test = np.array(df['FileID']+'.jpg')
y_test = np.array(df['SpeciesID'])
x_test_savepath = './image_label2/x_test.npy'
y_test_savepath = './image_label2/y_test.npy'

def generateds(path, x_t ,y_t):
    x = []  # 建立空列表
    for i in range(x_t.size):
        img_path = path + x_t[i]  # 拼出图片路径和文件名
        img = Image.open(img_path)  # 读入图片
        img = img.resize((128,128))
        img = np.array(img.convert('RGB'))
        x.append(img)  # 归一化后的数据，贴到列表x
        print('loading : ' + x_t[i] ,y_t[i])  # 打印状态提示

    x = np.array(x)  # 变为np.array格式

    return x

if os.path.exists(x_train_savepath) and os.path.exists(y_train_savepath) and os.path.exists(
        x_test_savepath) and os.path.exists(y_test_savepath):
    print('-------------Load Datasets-----------------')
    x_train_save = np.load(x_train_savepath,allow_pickle=True)
    y_train = np.load(y_train_savepath,allow_pickle=True)
    x_test_save = np.load(x_test_savepath,allow_pickle=True)
    y_test = np.load(y_test_savepath,allow_pickle=True)
    x_train = np.reshape(x_train_save, (len(x_train_save), 128, 128, 3))
    x_test = np.reshape(x_test_save, (len(x_test_save), 128, 128, 3))
else:
    print('-------------Generate Datasets-----------------')
    x_train = generateds(train_path, x_train, y_train)
    x_test = generateds(test_path, x_test, y_test)

    print('-------------Save Datasets-----------------')
    x_train_save = np.reshape(x_train, (len(x_train), -1))
    x_test_save = np.reshape(x_test, (len(x_test), -1))
    np.save(x_train_savepath, x_train_save)
    np.save(y_train_savepath, y_train)
    np.save(x_test_savepath, x_test_save)
    np.save(y_test_savepath, y_test)

#数据增强
image_gen_train = ImageDataGenerator(
    rescale=1. / 1.,  # 如为图像，分母为255时，可归至0～1
    rotation_range=45,  # 随机45度旋转
    width_shift_range=.15,  # 宽度偏移
    height_shift_range=.15,  # 高度偏移
    horizontal_flip=True,  # 水平翻转
    zoom_range=0.5  # 将图像随机缩放阈量50％
)
image_gen_train.fit(x_train)



#VGG
# def get_model():
#     model = tf.keras.Sequential([
#         tf.keras.layers.InputLayer(input_shape=(128,128,3)),
#
#         tf.keras.layers.Conv2D(filters=64, kernel_size=(3,3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=64, kernel_size=(3,3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.MaxPool2D(strides=2,padding='same'),
#         tf.keras.layers.Dropout(0.2),
#
#         tf.keras.layers.Conv2D(filters=128, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=128, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.MaxPool2D(strides=2, padding='same'),
#         tf.keras.layers.Dropout(0.2),
#
#         tf.keras.layers.Conv2D(filters=256, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=256, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=256, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.MaxPool2D(strides=2, padding='same'),
#         tf.keras.layers.Dropout(0.2),
#
#         tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.MaxPool2D(strides=2, padding='same'),
#         tf.keras.layers.Dropout(0.2),
#
#         tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
#         tf.keras.layers.BatchNormalization(),
#         tf.keras.layers.Activation('relu'),
#         tf.keras.layers.MaxPool2D(strides=2, padding='same'),
#         tf.keras.layers.Dropout(0.2),
#
#         tf.keras.layers.Flatten(),
#         tf.keras.layers.Dense(512, activation='relu'),
#         tf.keras.layers.Dropout(0.2),
#         tf.keras.layers.Dense(512, activation='relu',regularizers=0.001),
#         tf.keras.layers.Dropout(0.2),
#         tf.keras.layers.Dense(20, activation='softmax')
#     ])
#     return model


regularizer = 0.001


def get_model():
    model = tf.keras.Sequential([
        tf.keras.layers.InputLayer(input_shape=(128,128,3)),

        tf.keras.layers.Conv2D(filters=64, kernel_size=(3,3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=64, kernel_size=(3,3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.MaxPool2D(strides=2,padding='same'),
        tf.keras.layers.Dropout(0.2),

        tf.keras.layers.Conv2D(filters=128, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=128, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.MaxPool2D(strides=2, padding='same'),
        tf.keras.layers.Dropout(0.2),

        tf.keras.layers.Conv2D(filters=256, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=256, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=256, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.MaxPool2D(strides=2, padding='same'),
        tf.keras.layers.Dropout(0.2),

        tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.MaxPool2D(strides=2, padding='same'),
        tf.keras.layers.Dropout(0.2),

        tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.Conv2D(filters=512, kernel_size=(3, 3), padding='same'),
        tf.keras.layers.BatchNormalization(),
        tf.keras.layers.Activation('relu'),
        tf.keras.layers.MaxPool2D(strides=2, padding='same'),
        tf.keras.layers.Dropout(0.2),

        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(512, activation='relu'),
        tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(512, activation='relu'),
        tf.keras.layers.Dropout(0.2),
        tf.keras.layers.Dense(20, activation='softmax')
    ])
    return model

model = get_model()

model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=False),
              metrics=['sparse_categorical_accuracy'])

checkpoint_save_path = "./checkpoint/VGG.ckpt"
if os.path.exists(checkpoint_save_path + '.index'):
    print('-------------load the model-----------------')
    model.load_weights(checkpoint_save_path)

cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_save_path,#保存路径
                                                 save_weights_only=True,#只保存权重
                                                 save_best_only=True)#只保存最好的模型

history = model.fit(x_train, y_train, batch_size=32, epochs=10, validation_data=(x_test, y_test), validation_freq=1,
                    callbacks=[cp_callback])
model.summary()


# 显示训练集和验证集的acc和loss曲线
acc = history.history['sparse_categorical_accuracy']
val_acc = history.history['val_sparse_categorical_accuracy']
loss = history.history['loss']
val_loss = history.history['val_loss']

plt.subplot(1, 2, 1)
plt.plot(acc, label='Training Accuracy')
plt.plot(val_acc, label='Validation Accuracy')
plt.title('Training and Validation Accuracy')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(loss, label='Training Loss')
plt.plot(val_loss, label='Validation Loss')
plt.title('Training and Validation Loss')
plt.legend()
plt.show()

