import numpy as np
import torch
from torchvision.datasets import mnist
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import torch.nn.functional as F
import torch.optim as optim
from torch import nn

#定义超参数
train_batch_size = 64
test_batch_size = 128
learning_rate = 0.01
num_epoches = 20
lr = 0.01
mimentum = 0.5

#下载数据并进行预处理

#定义预处理函数，这些预处理一次放在Compose函数中
transform = transforms.Compose([transforms.ToTensor(),transforms.Normalize([0.5],[0.5])])#Normalize([0.5],[0.5])对张量进行归一化。两个0.5分别表示全局平均值和方差
                                                                                        #此处为1通道，若为3通道。Normalize([m1,m2,m3],[n1,n2,n3])
#下载数据，并对数据进行预处理
train_dataset = mnist.MNIST('./data',train=True,transform=transform,download=True)
test_dataset = mnist.MNIST('./data',train=False,transform=transform)
#dataloader是一个迭代对象，可以使用迭代器一样使用
train_loader = DataLoader(train_dataset,batch_size=train_batch_size,shuffle=True)
test_loader = DataLoader(test_dataset,batch_size=test_batch_size,shuffle=False)

#构建网络
class Net(nn.Module):
    """
    使用sequential 构建网络，Sequentital()函数的功能是将网络的层组合到一起
    """
    def __init__(self,in_dim,n_hidden_1,n_hidden_2,out_dim):
        super(Net,self).__init__()
        self.layer1 = nn.Sequential(nn.Linear(in_dim, n_hidden_1), nn.BatchNorm1d(n_hidden_1))
        self.layer2 = nn.Sequential(nn.Linear(n_hidden_1, n_hidden_2), nn.BatchNorm1d(n_hidden_2))
        self.layer3 = nn.Sequential(nn.Linear(n_hidden_2, out_dim))

    def forward(self,x):
        x = F.relu(self.layer1(x))
