#六步法实现模型搭建
#1.导入相关模块
import tensorflow as tf
#2.导入数据
mnist = tf.keras.datasets.mnist
#（训练集输入特征，训练集标签），（测试集输入特征，测试机标签）
(x_train, y_train), (x_test, y_test) = mnist.load_data()#导入数据集
x_train, x_test = x_train / 255.0, x_test / 255.0#对输入网络的输入特征进行归一化，将原本0~255的灰度值变为0~1的值，输入特征的数值变小更适合神经网络吸收
#3.用Sequential搭建网络结构
model = tf.keras.models.Sequential([
    tf.keras.layers.Flatten(),#将数组拉直,有784个神经元
    tf.keras.layers.Dense(128, activation='relu'),#全连接层
    tf.keras.layers.Dense(10, activation='softmax')
])
#4.用compile配置训练方法
model.compile(optimizer='adam',#优化器，优先考虑Adam或者SGD+Nesterov Momentum
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=False),#设置损失函数
              metrics=['sparse_categorical_accuracy'])#选择标注网络评测指标

#5.用fit执行训练过程
model.fit(x_train, y_train, batch_size=32, epochs=5, validation_data=(x_test, y_test), validation_freq=1)
#6.用summary打印出网络结构，和参数统计
model.summary()
