from PIL import Image
import numpy as np
import tensorflow as tf

model_save_path = './checkpoint/VGG.ckpt'

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

preNum = int(input("input the number of test pictures:"))

for i in range(preNum):
    image_path = input("the path of test picture:")
    img = Image.open(image_path)
    img = img.resize((128, 128), Image.ANTIALIAS)
    img_arr = np.array(img.convert('RGB'))

    print("img_arr:", img_arr.shape)
    x_predict = img_arr[tf.newaxis, ...]
    print("x_predict:", x_predict.shape)
    result = model.predict(x_predict)

    pred = tf.argmax(result, axis=1)

    print('\n')
    tf.print(pred)
