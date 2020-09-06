import tensorflow as tf
import os
import numpy as np
import pandas as pd
from PIL import Image
from keras_preprocessing.image import ImageDataGenerator
from efficientnet import efficientnet_model

train_path = './data/'
test_path = './data/'

df = pd.read_csv('./training.csv')
x_train = np.array(df['FileID']+'.jpg')
y_train = np.array(df['SpeciesID'])
x_train_savepath = './image_label/x_train.npy'
y_train_savepath = './image_label/y_train.npy'

df = pd.read_csv('./annotation.csv')
x_test = np.array(df['FileID']+'.jpg')
y_test = np.array(df['SpeciesID'])
x_test_savepath = './image_label/x_test.npy'
y_test_savepath = './image_label/y_test.npy'

def generateds(path, x_t ,y_t):
    x = []  # 建立空列表
    for i in range(x_t.size):
        img_path = path + x_t[i]  # 拼出图片路径和文件名
        img = Image.open(img_path)  # 读入图片
        if img.size[1] > img.size[0]:
            img = img.rotate(90,Image.NEAREST,1)
        img = img.resize((151,100))
        # img = img.resize((128, 128))
        img = np.array(img.convert('RGB'))
        x.append(img)  # 归一化后的数据，贴到列表x
        print('loading : ' + x_t[i] ,y_t[i])  # 打印状态提示

    x = np.array(x)  # 变为np.array格式
    y_t = y_t.astype(np.float64)
    return x

if os.path.exists(x_train_savepath) and os.path.exists(y_train_savepath) and os.path.exists(
        x_test_savepath) and os.path.exists(y_test_savepath):
    print('-------------Load Datasets-----------------')
    x_train_save = np.load(x_train_savepath,allow_pickle=True)
    y_train = np.load(y_train_savepath,allow_pickle=True)
    x_test_save = np.load(x_test_savepath,allow_pickle=True)
    y_test = np.load(y_test_savepath,allow_pickle=True)
    x_train = np.reshape(x_train_save, (len(x_train_save), 151, 100, 3))
    x_test = np.reshape(x_test_save, (len(x_test_save), 151, 100, 3))
    # x_train = np.reshape(x_train_save, (len(x_train_save), 128, 128, 3))
    # x_test = np.reshape(x_test_save, (len(x_test_save), 128, 128, 3))
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

x_train=x_train.astype(np.float64)


#数据增强
image_gen_train = ImageDataGenerator(
#    rescale=1. / 1.,  # 如为图像，分母为255时，可归至0～1
    rotation_range=45,  # 随机45度旋转
    width_shift_range=.30,  # 宽度偏移
    height_shift_range=.30,  # 高度偏移
    horizontal_flip=True,  # 水平翻转
    vertical_flip=True,
    zoom_range=0.3  # 将图像随机缩放阈量50％
)
image_gen_train.fit(x_train)



alpha = 1.0   #depth_coefficient
beta = 1.0    #width_coefficient
gamma = 1.0   #resolution_coefficient
dropout = 0.2

model = efficientnet_model(alpha, beta, gamma, dropout)
# model.compile(
#     loss={
#         'output':
#             tf.keras.losses.CategoricalCrossentropy(
#                 from_logits=True, label_smoothing=0.1
#             )
#     },
#     # optimizer=tf.keras.optimizers.SGD(learning_rate=0.0001, momentum=0.9),
#     optimizer='adam',
#     # metrics={
#     #     'output':[
#     #         tf.keras.metrics.CategoricalAccuracy(name='top_1_accuracy'),
#     #         tf.keras.metrics.TopKCategoricalAccuracy(k=5, name='top_5_accuracy')
#     #     ]
#     # }
#     metrics=['sparse_categorical_accuracy']
# )

model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=False),
              metrics=['sparse_categorical_accuracy'])

checkpoint_save_path = "./checkpoint/efficientnet.ckpt"
if os.path.exists(checkpoint_save_path + '.index'):
    print('-------------load the model-----------------')
    model.load_weights(checkpoint_save_path)

cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_save_path,
                                                 save_weights_only=True,
                                                 save_best_only=True)

history = model.fit(x_train, y_train, batch_size=32, epochs=300, validation_data=(x_test, y_test), validation_freq=1,
                    callbacks=[cp_callback])
# model.summary()