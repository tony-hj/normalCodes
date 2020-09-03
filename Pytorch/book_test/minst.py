import numpy as np
import torch
from torchvision.datasets import mnist
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import torch.nn.functional as F
import torch.optim as optim
from torch import nn
import matplotlib.pyplot as plt

#定义超参数
train_batch_size = 64
test_batch_size = 128
learning_rate = 0.01
num_epoches = 20
lr = 0.01
momentum = 0.5

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
        x = F.relu(self.layer2(x))
        x = F.relu(self.layer3(x))
        return x

#检测是否有可用的GPU，有则使用，否则使用CPU
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
#实例化网络
model = Net(28*28, 300, 100, 10)
model.to(device)

#定义损失函数和优化器
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=lr, momentum=momentum)

#开始训练
losses = []
acces = []
eval_losses = []
eval_acces = []

for epoch in range(num_epoches):
    train_loss = 0
    train_acc = 0
    model.train()
#动态修改学习率
    if epoch%5 == 0:
        optimizer.param_groups[0]['lr']*=0.1
    for img, label in train_loader:
        img = img.to(device)
        label = label.to(device)
        img = img.view(img.size(0), -1)
        #前向传播
        out = model(img)
        loss = criterion(out, label)
        #反向传播
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        #记录误差
        train_loss += loss.item()
        #计算分类的准确率
        _, pred = out.max(1)
        num_correct = (pred == label).sum().item()
        acc = num_correct / img.shape[0]
        train_acc += acc

    losses.append(train_loss / len(train_loader))
    acces.append(train_acc / len(train_loader))
    #在测试集上检验效果
    eval_loss = 0
    eval_acc = 0
#将模型改为预测模式
    model.eval()
    for img, label in test_loader:
        img = img.to(device)
        label = label.to(device)
        img = img.view(img.size(0), -1)
        out = model(img)
        loss = criterion(out, label)
        #记录误差
        eval_loss += loss.item()
        #记录准确率
        _,pred = out.max(1)
        num_correct = (pred == label).sum().item()
        acc = num_correct / img.shape[0]
        eval_acc += acc

    eval_losses.append(eval_loss / len(test_loader))
    eval_acces.append(eval_acc / len(test_loader))
    print('epcho: {}, Train Loss: {:.4f}, Train ACC: {:.4f}, Test Loss: {:.4f}, Test ACC: {:.4f}'.format(epoch, train_loss / len(train_loader), train_acc / len(train_loader),
                                                                                                         eval_loss / len(test_loader), eval_acc / len(test_loader)))

plt.title("trainloss")
plt.plot(np.arange(len(losses)), losses)
plt.legend(['Train Loss'], loc='upper right')
plt.show()





