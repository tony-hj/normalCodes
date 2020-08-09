# -*- coding: utf-8 -*-
"""
Created on Sun Aug  2 17:20:32 2020

@author: 花祭
"""

import numpy as np 
import pandas as pd
# array = np.array([[1,2,3]
#                  ,[2,3,4]])

# print(array)
# #维度
# print('number of dim:',array.ndim)
# #几行几列
# print('shape:',array.shape)
# #总共的元素个数
# print('size:',array.size)

# a = np.array([[2,3,4],
#               [5,2,65]])
# #生成一个3×4的零矩阵
# b = np.zeros((3,4))
# #生成一个3×4的单位矩阵
# c = np.ones((3,4))
# #生成一个空矩阵
# d = np.empty((3,4))
# #生成随机值
# e = np.arange(10,20,2)

# print(a)
# print(b)
# print(c)
# print(d)
# print(e)

# a = np.array([3,4,5])
# b = np.array(4)

# print(a)
# print(b)
# print(a-b)
# print(a+b)
# print(a*b)
# print(a/b)

# a = np.random.random((2,4))
# print(a)
# print(np.sum(a))
# print(np.min(a))
# print(np.max(a))

# a = np.arange(2,14).reshape(3,4)
# #平均值
# print(np.mean(a))
# print(a.mean())
# print(np.average(a))
# #中位数
# print(np.median(a))
# #逐项累加
# print(np.cumsum(a))
# #逐项累差
# print(np.diff(a))
# #分别对应输出对应值所在的行与列 
# print(np.nonzero(a))
# #排序
# print(np.sort(a))
# #转置矩阵
# print(a.T)
# #二值化滤波
# print(np.clip(a,5,9))

# a = np.arange(3,15).reshape(3,4)
# print(a)
# #索引方式类似于多维数组 
# print(a[2])
# #print(a[2,2])
# print(a[2][2])
# #输出第二列的所有数，可用 : 代替 
# print(a[:,1])
# #对每一行进行迭代输出
# for row in a:
#     print(row)
# #对每一列进行迭代输出 
# for column in a.T:
#     print(column)
# #迭代输出每一项
# for item in a.flat:
#     print(item)

# a = np.array([1,1,1])
# b = np.array([2,2,2])
# #进行上下合并 
# print(np.vstack((a,b))) 
# #进行左右合并（还是一个序列）
# print(np.hstack((a,b)))
# #在行上增加一个维度
# print(a[np.newaxis,:])
# #在列上增加一个维度
# print(a[:,np.newaxis])

# #进行多个序列的合并(需先给序列增加一个维度) 
# a =  a[np.newaxis,:]
# b =  b[np.newaxis,:]
# print(np.concatenate((a,b,b,a),axis = 0))
# print(np.concatenate((a,b,b,a),axis = 1))

# a = np.arange(12).reshape(3,4)
# print(a)

# #均等分割
# #按列将其分成两块竖着的两块 
# print(np.split(a,2,axis = 1))
# #按行将其分成横着的三块
# print(np.split(a,3,axis = 0))

# #不均等分割
# print(np.array_split(a,3,axis = 1))
# #比较简便的方式（均等分割）
# print(np.vsplit(a,3))
# print(np.hsplit(a, 2))

# a = np.arange(4)
# #a,b,c,d关联 ，改变其中任意一个，其他都会变化
# b = a
# c = a
# d = b
# a[0] = 12
# print(b)
# print(b is a) 
# print(d is a)
# #只把值赋给b,a与b不关联，改变a，b不会变化
# b = a.copy()
# a[1] = 45
# print(a)
# print(b)

# s = pd.Series([1,3,6,np.nan,44,1])
# print(s)

# dates = pd.date_range('20200807',periods=6)
# print(dates)

# #自己设定行列的索引名称(也可用字典直接导入)
# df = pd.DataFrame(np.random.randn(6,4),index = dates,columns = ['a','b','c','d'])
# print("自己设定索引名称：",df)

# #默认索引名称
# df1 = pd.DataFrame(np.arange(12).reshape(3,4))
# print("索引名称默认：",df1)
# #输出列的索引,index
# print("列的索引：",df.index)
# #输出行的索引,columns
# print("行的索引：",df.columns)
# #输出所有的值
# print("所有的值：",df.values)
# #输出有关属性，和，平均值，方差等等
# print("相关属性:",df.describe())
# #同理，要进行行的提取计算，对矩阵进行转置即可
# print("相关属性（行）:",df.T.describe())
# #排序
# print("按列排序：",df.sort_index(axis=1, ascending=False))
# print("按行排序：",df.sort_index(axis=0, ascending=False))
# #对某一列进行排序
# print("对a列进行排序",df.sort_values(by='a'))







