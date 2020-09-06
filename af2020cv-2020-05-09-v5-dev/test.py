import tensorflow as tf
from PIL import Image
import numpy as np
import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator

train_path = './image_label/train_jpg/'
train_txt = './image_label/train_jpg.txt'
x_train_savepath = './image_label/x_train.npy'
y_train_savepath = './image_label/y_train.npy'

test_path = './image_label/test_jpg/'
test_txt = './image_label/test_jpg.txt'
x_test_savepath = './image_label/x_test.npy'
y_test_savepath = './image_label/y_test.npy'

def generateds(path, txt):
    f = open(txt, 'r')  # 以只读形式打开txt文件
    contents = f.readlines()  # 读取文件中所有行
    f.close()  # 关闭txt文件
    x, y_ = [], []  # 建立空列表
    for content in contents:  # 逐行取出
        value = content.split()  # 以空格分开，图片路径为value[0] , 标签为value[1] , 存入列表
        img_path = path + value[0]  # 拼出图片路径和文件名
        img = Image.open(img_path)  # 读入图片
        img = img.resize((128,128))
#        print(np.shape(img))
        img = np.array(img.convert('RGB'))
#        print(np.shape(img))
#        img = img / 255.  # 数据归一化 （实现预处理）
        x.append(img)  # 归一化后的数据，贴到列表x
        y_.append(value[1])  # 标签贴到列表y_
        print('loading : ' + content)  # 打印状态提示

    x = np.array(x)  # 变为np.array格式
    y_ = np.array(y_)  # 变为np.array格式
    y_ = y_.astype(np.int64)  # 变为64位整型
    # print(x)
    # print(y_)
    return x, y_  # 返回输入特征x，返回标签y_

#generateds(train_path,train_txt)

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
    x_train, y_train = generateds(train_path, train_txt)
    x_test, y_test = generateds(test_path, test_txt)

    print('-------------Save Datasets-----------------')
    x_train_save = np.reshape(x_train, (len(x_train), -1))
    x_test_save = np.reshape(x_test, (len(x_test), -1))
    np.save(x_train_savepath, x_train_save)
    np.save(y_train_savepath, y_train)
    np.save(x_test_savepath, x_test_save)
    np.save(y_test_savepath, y_test)




image_gen_train = ImageDataGenerator(
    rescale=1. / 1.,  # 如为图像，分母为255时，可归至0～1
    rotation_range=45,  # 随机45度旋转
    width_shift_range=.15,  # 宽度偏移
    height_shift_range=.15,  # 高度偏移
    horizontal_flip=True,  # 水平翻转
    zoom_range=0.5  # 将图像随机缩放阈量50％
)
image_gen_train.fit(x_train)

# x_train = tf.keras.layers.x_train(shape=(None,None,3))
# model = tf.keras.models.Sequential([
#     tf.keras.layers.Flatten(),
# #    tf.keras.layers.Dense(512, activation='relu'),
#     tf.keras.layers.Dense(128, activation='relu'),
#     tf.keras.layers.Dense(20, activation='softmax')
# ])

def get_model():
    model = tf.keras.Sequential([
        tf.keras.layers.InputLayer(input_shape=(128,128,3)),
        tf.keras.layers.Conv2D(kernel_size = (5,5), filters= 100 , activation= 'relu'),
        tf.keras.layers.MaxPool2D(),
        tf.keras.layers.Conv2D(kernel_size= (3,3), filters= 150, activation= 'relu'),
        tf.keras.layers.MaxPool2D(),
        tf.keras.layers.Conv2D(kernel_size= (3,3), filters= 250, padding= 'same',activation= 'relu'),
        tf.keras.layers.MaxPool2D(),
        tf.keras.layers.Flatten(),
        tf.keras.layers.Dense(512, activation='relu'),
        tf.keras.layers.Dense(300, activation='relu'),
        tf.keras.layers.Dense(20, activation='softmax')
    ])
    return model

model = get_model()

model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=False),
              metrics=['sparse_categorical_accuracy'])

checkpoint_save_path = "./checkpoint/mnist.ckpt"
if os.path.exists(checkpoint_save_path + '.index'):
    print('-------------load the model-----------------')
    model.load_weights(checkpoint_save_path)

cp_callback = tf.keras.callbacks.ModelCheckpoint(filepath=checkpoint_save_path,#保存路径
                                                 save_weights_only=True,#只保存权重
                                                 save_best_only=True)#只保存最好的模型

history = model.fit(x_train, y_train, batch_size=32, epochs=10, validation_data=(x_test, y_test), validation_freq=1,
                    callbacks=[cp_callback])
model.summary()