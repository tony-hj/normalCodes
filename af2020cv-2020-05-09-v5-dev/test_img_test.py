from PIL import Image
import numpy as np
import tensorflow as tf
import pandas as pd
import csv


model_save_path = './checkpoint/VGG.ckpt'
img_path = "./data/"

#df = pd.read_csv('./training.csv')
df = pd.read_csv('./annotation.csv')
test_path =  np.array(df['FileID'])

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

model.load_weights(model_save_path)


csvFile=open("./aaaaaa/test.csv",'w',newline='')
writer=csv.writer(csvFile)
writer.writerow(('FileID','SpeciesID'))

for i in range(test_path.size):
    img = Image.open(img_path + test_path[i] + '.jpg')
    img = img.resize((128, 128), Image.ANTIALIAS)
    img_arr = np.array(img.convert('RGB'))

#    print("img_arr:", img_arr.shape)
    x_predict = img_arr[tf.newaxis, ...]
#    print("x_predict:", x_predict.shape)
    result = model.predict(x_predict)

#    pred = tf.argmax(result, axis=1)
    pred = np.argmax(result)
#    print('\n')
    print(test_path[i] ,pred)
    writer.writerow((test_path[i], pred))

#    tf.print(pred)

csvFile.close()