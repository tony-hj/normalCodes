# #自制数据集
# # import tensorflow as tf
# from PIL import Image
# import numpy as np
# import os
# import cv2 as cv
# import pandas as pd
#
# #对图片顺时针旋转任意角度
# # def rotate_bound(image, angle):
# # 	# grab the dimensions of the image and then determine the
# # 	# center
# # 	(h, w) = image.shape[:2]
# # 	(cX, cY) = (w // 2, h // 2)
# #
# # 	# grab the rotation matrix (applying the negative of the
# # 	# angle to rotate clockwise), then grab the sine and cosine
# # 	# (i.e., the rotation components of the matrix)
# # 	M = cv.getRotationMatrix2D((cX, cY), -angle, 1.0)
# # 	cos = np.abs(M[0, 0])
# # 	sin = np.abs(M[0, 1])
# #
# # 	# compute the new bounding dimensions of the image
# # 	nW = int((h * sin) + (w * cos))
# # 	nH = int((h * cos) + (w * sin))
# #
# # 	# adjust the rotation matrix to take into account translation
# # 	M[0, 2] += (nW / 2) - cX
# # 	M[1, 2] += (nH / 2) - cY
# #
# # 	# perform the actual rotation and return the image
# # 	return cv.warpAffine(image, M, (nW, nH))
# #
# #
# # img = cv.imread('./data/0b65f857c18dda87ab0d25a2fd78e5fc.jpg')
# # cv.imshow("test",img)
# # cv.waitKey()
# # print(img.shape)
# # if img.shape[0] > img.shape[1]:
# # 	img = rotate_bound(img, 270)
# # img = cv.resize(img,(500,330))
# # x = []
# # x.append(img)
# # img = Image.open("1.jpg")
# # print(img.size[0])
# # img = img.rotate(90,Image.NEAREST,1)
# # img.show()
# from keras_preprocessing.image import ImageDataGenerator
#
# train_path = './data/'
# df = pd.read_csv('./annotation.csv')
# x_train = np.array(df['FileID']+'.jpg')
#
# def generateds(path, x_t):
#     x = []  # 建立空列表
#     for i in range(x_t.size):
#         img_path = path + x_t[i]  # 拼出图片路径和文件名
#         img = Image.open(img_path)  # 读入图片
#         img = img.resize((128,128))
#         img = np.array(img.convert('RGB'))
#         x.append(img)  # 归一化后的数据，贴到列表x
#         print('loading : ' + x_t[i])  # 打印状态提示
#
#     x = np.array(x)  # 变为np.array格式
#
#     return x
#
# x_train = generateds(train_path, x_train)
#
# #数据增强
# image_gen_train = ImageDataGenerator(
#     rescale=1. / 1.,  # 如为图像，分母为255时，可归至0～1
#     rotation_range=45,  # 随机45度旋转
#     width_shift_range=.15,  # 宽度偏移
#     height_shift_range=.15,  # 高度偏移
#     horizontal_flip=True,  # 水平翻转
#     zoom_range=0.5  # 将图像随机缩放阈量50％
# )
# image_gen_train.fit(x_train)
#
# print(x_train.shape[0])
import tensorflow as tf
import os
import numpy as np
from matplotlib import pyplot as plt
from tensorflow.keras.layers import Conv2D, BatchNormalization, Activation, MaxPool2D, Dropout, Flatten, Dense, \
    GlobalAveragePooling2D
from tensorflow.keras import Model
from PIL import Image
import pandas as pd
from tensorflow.keras.preprocessing.image import ImageDataGenerator

np.set_printoptions(threshold=np.inf)

train_path = './data/'

df = pd.read_csv('./training.csv')
x_train = np.array(df['FileID']+'.jpg')
y_train = np.array(df['SpeciesID'])
x_train_savepath = './image_label3/x_train.npy'
y_train_savepath = './image_label3/y_train.npy'


def generateds(path, x_t ,y_t):
    x = []  # 建立空列表
    for i in range(x_t.size):
        img_path = path + x_t[i]  # 拼出图片路径和文件名
        img = Image.open(img_path)  # 读入图片
        if img.size[1] > img.size[0]:
            img = img.rotate(90,Image.NEAREST,1)
        img = img.resize((151,100))
        img = np.array(img.convert('RGB'))
        x.append(img)  # 归一化后的数据，贴到列表x
        print('loading : ' + x_t[i] ,y_t[i])  # 打印状态提示

    x = np.array(x)  # 变为np.array格式
    y_t = y_t.astype(np.float64)
    return x

if os.path.exists(x_train_savepath) and os.path.exists(y_train_savepath):
    print('-------------Load Datasets-----------------')
    x_train_save = np.load(x_train_savepath,allow_pickle=True)
    y_train = np.load(y_train_savepath,allow_pickle=True)
    x_train = np.reshape(x_train_save, (len(x_train_save), 151, 100, 3))
else:
    print('-------------Generate Datasets-----------------')
    x_train = generateds(train_path, x_train, y_train)
    print('-------------Save Datasets-----------------')
    x_train_save = np.reshape(x_train, (len(x_train), -1))
    np.save(x_train_savepath, x_train_save)
    np.save(y_train_savepath, y_train)

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


class ConvBNRelu(Model):
    def __init__(self, ch, kernelsz=3, strides=1, padding='same'):
        super(ConvBNRelu, self).__init__()
        self.model = tf.keras.models.Sequential([
            Conv2D(ch, kernelsz, strides=strides, padding=padding),
            BatchNormalization(),
            Activation('relu')
        ])

    def call(self, x):
        x = self.model(x, training=False) #在training=False时，BN通过整个训练集计算均值、方差去做批归一化，training=True时，通过当前batch的均值、方差去做批归一化。推理时 training=False效果好
        return x


class InceptionBlk(Model):
    def __init__(self, ch, strides=1):
        super(InceptionBlk, self).__init__()
        self.ch = ch
        self.strides = strides
        self.c1 = ConvBNRelu(ch, kernelsz=1, strides=strides)
        self.c2_1 = ConvBNRelu(ch, kernelsz=1, strides=strides)
        self.c2_2 = ConvBNRelu(ch, kernelsz=3, strides=1)
        self.c3_1 = ConvBNRelu(ch, kernelsz=1, strides=strides)
        self.c3_2 = ConvBNRelu(ch, kernelsz=5, strides=1)
        self.p4_1 = MaxPool2D(3, strides=1, padding='same')
        self.c4_2 = ConvBNRelu(ch, kernelsz=1, strides=strides)

    def call(self, x):
        x1 = self.c1(x)
        x2_1 = self.c2_1(x)
        x2_2 = self.c2_2(x2_1)
        x3_1 = self.c3_1(x)
        x3_2 = self.c3_2(x3_1)
        x4_1 = self.p4_1(x)
        x4_2 = self.c4_2(x4_1)
        # concat along axis=channel
        x = tf.concat([x1, x2_2, x3_2, x4_2], axis=3)
        return x


class Inception10(Model):
    def __init__(self, num_blocks, num_classes, init_ch=16, **kwargs):
        super(Inception10, self).__init__(**kwargs)
        self.in_channels = init_ch
        self.out_channels = init_ch
        self.num_blocks = num_blocks
        self.init_ch = init_ch
        self.c1 = ConvBNRelu(init_ch)
        self.blocks = tf.keras.models.Sequential()
        for block_id in range(num_blocks):
            for layer_id in range(2):
                if layer_id == 0:
                    block = InceptionBlk(self.out_channels, strides=2)
                else:
                    block = InceptionBlk(self.out_channels, strides=1)
                self.blocks.add(block)
            # enlarger out_channels per block
            self.out_channels *= 2
        self.p1 = GlobalAveragePooling2D()
        self.f1 = Dense(num_classes, activation='softmax')

    def call(self, x):
        x = self.c1(x)
        x = self.blocks(x)
        x = self.p1(x)
        y = self.f1(x)
        return y


model = Inception10(num_blocks=2, num_classes=20)

model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=False),
              metrics=['sparse_categorical_accuracy'])

checkpoint_save_path = "./checkpoint/Inception1.ckpt"
if os.path.exists(checkpoint_save_path + '.index'):
    print('-------------load the model-----------------')
    model.load_weights(checkpoint_save_path)

cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_save_path,
                                                 save_weights_only=True,
                                                 save_best_only=True)

history = model.fit(x_train, y_train, batch_size=32, epochs=1,  validation_freq=1,
                    callbacks=[cp_callback])
model.summary()

# print(model.trainable_variables)
# file = open('./weights.txt', 'w')
# for v in model.trainable_variables:
#     file.write(str(v.name) + '\n')
#     file.write(str(v.shape) + '\n')
#     file.write(str(v.numpy()) + '\n')
# file.close()

###############################################    show   ###############################################

# 显示训练集和验证集的acc和loss曲线
# acc = history.history['sparse_categorical_accuracy']
# val_acc = history.history['val_sparse_categorical_accuracy']
# loss = history.history['loss']
# val_loss = history.history['val_loss']
#
# plt.subplot(1, 2, 1)
# plt.plot(acc, label='Training Accuracy')
# plt.plot(val_acc, label='Validation Accuracy')
# plt.title('Training and Validation Accuracy')
# plt.legend()
#
# plt.subplot(1, 2, 2)
# plt.plot(loss, label='Training Loss')
# plt.plot(val_loss, label='Validation Loss')
# plt.title('Training and Validation Loss')
# plt.legend()
# plt.show()
