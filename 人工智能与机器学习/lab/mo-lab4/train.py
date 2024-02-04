import os
import numpy as np
import jieba as jb
import torch
import math
import torch.nn as nn
import torch.nn.functional as F
import matplotlib.pyplot as plt
from torch.autograd import Variable
from torch.nn.utils.rnn import pack_padded_sequence, pad_packed_sequence, pad_sequence
from torchtext import data, datasets
from argparse import Namespace
from model import BiLSTM_Attention

try:
    from torchviz import make_dot
except:
    pass

try:
    from torchtext.data import Field, Dataset, Iterator, Example, BucketIterator
except:
    from torchtext.legacy.data import Field, Dataset, Iterator, Example, BucketIterator

if __name__ == '__main__':

    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    save_model_path = "./results/model_2.pth"  # 保存模型路径和名称
    split_ratio = 0.7

    def load_data(path):
        sentences = []  # 片段
        target = []  # 作者
        labels = {'LX': 0, 'MY': 1, 'QZS': 2, 'WXB': 3, 'ZAL': 4}
        files = os.listdir(path)  # 打开文件获取句子，存储句子及其对应作者编号
        for file in files:
            if not os.path.isdir(file) and not file[0] == '.':
                f = open(path + "/" + file, 'r', encoding='UTF-8')
                for index, line in enumerate(f.readlines()):
                    sentences.append(line)  # sentences中存储句子
                    # target中存储的是枚举数字01234即为句字作者
                    target.append(labels[file[:-4]])

        return list(zip(sentences, target))

    # sequential表示是否顺序.Field对象指定要如何处理某个字段；fields可简单理解为每一列数据和Field对象的绑定关系
    TEXT = Field(sequential=True, tokenize=lambda x: jb.lcut(x),
                 lower=True, use_vocab=True)
    LABEL = Field(sequential=False, use_vocab=False)
    FIELDS = [('text', TEXT), ('category', LABEL)]
    mydata = load_data(path='./dataset/')
    # 一个列表，为Dataset所需要，Example为对数据集中一条数据的抽象
    examples = list(map(lambda x: Example.fromlist(
        list(x), fields=FIELDS), mydata))
    # Dataset定义数据源信息，是用于构建词表的数据集，下面使用
    dataset = Dataset(examples, fields=FIELDS)
    # 构建词表：给每个单词编码，也就是用数字来表示每个单词，这样才能够传入模型 dataset为用于构建词表的数据集
    TEXT.build_vocab(dataset, vectors='glove.6B.100d')

    vocab_size = len(TEXT.vocab)  # 词表大小
    train, val = dataset.split(split_ratio=split_ratio)
    train_iter, val_iter = BucketIterator.splits(  # BucketIterator将类似长度的样本处理成一个batch，有利于训练。这里同时对训练集和验证集进行迭代器构建
        (train, val),
        batch_sizes=(16, 16),
        device=device,  # 如果使用gpu，此处将-1更换为GPU的编号
        sort_key=lambda x: len(x.text),
        sort_within_batch=False,
        repeat=False
    )
    print(train_iter)

    # 模型参数
    embedding_dim = 100  # 词向量维度
    hidden_dim = 64  # 隐藏层维度
    lr = 1e-3  # 学习率
    epoches = 1  # 训练轮数

    train_acc_list, train_loss_list, val_acc_list, val_loss_list = [], [], [], []
    model = BiLSTM_Attention(vocab_size, embedding_dim,
                             hidden_dim=hidden_dim, n_layers=2)
    print("vocab_size:", vocab_size)
    print("embedding_dim:", embedding_dim)
    print("hidden_dim:", hidden_dim)
    print("n_layers:", 2)
    # model = TextRCNN()

    pretrained_embedding = TEXT.vocab.vectors  # 预训练词向量
    model.embedding.weight.data.copy_(pretrained_embedding)  # 将预训练词向量复制到模型中
    model.to(device)
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    loss_fn = nn.CrossEntropyLoss()
    criterion = nn.BCEWithLogitsLoss()
    t = 1
    for epoch in range(epoches):
        train_acc, train_loss = 0, 0
        val_acc, val_loss = 0, 0

        for idx, batch in enumerate(train_iter):
            text, label = batch.text, batch.category
            optimizer.zero_grad()
            out = model(text)
            if t == 1:
                g = make_dot(out,
                             params=dict(model.named_parameters()))
                g.render('bilstm1', view=False)
                t = 0
            loss = loss_fn(out, label)
            # loss = criteon(out, label)
            loss.backward(retain_graph=True)  # 反向传播
            optimizer.step()  # 优化器更新参数
            accracy = np.mean((torch.argmax(out, 1) == label).cpu().numpy())

            # 计算每个样本的acc和loss之和
            train_acc += accracy * len(batch)
            train_loss += loss.item() * len(batch)

            print("\r epoch:{} loss:{}, train_acc:{}".format(
                epoch, loss.item(), accracy), end=" ")

        # 每个epoch在验证集上进行预测
        with torch.no_grad():
            for idx, batch in enumerate(val_iter):
                text, label = batch.text, batch.category
                out = model(text)
                loss = loss_fn(out, label.long())
                accracy = np.mean(
                    (torch.argmax(out, 1) == label).cpu().numpy())
                # 计算一个batch内每个样本的acc和loss之和
                val_acc += accracy * len(batch)
                val_loss += loss.item() * len(batch)

        # 在每个epoch中还需要进行这些计算 四个量，每次epoch要输出一次，所以在这里格式化输出
        train_acc /= len(train_iter.dataset)
        train_loss /= len(train_iter.dataset)
        val_acc /= len(val_iter.dataset)
        val_loss /= len(val_iter.dataset)
        train_acc_list.append(train_acc)
        train_loss_list.append(train_loss)
        val_acc_list.append(val_acc)
        val_loss_list.append(val_loss)

        print('{{"metric": "train_acc", "value": {}}}'.format(train_acc))
        print('{{"metric": "train_loss", "value": {}}}'.format(train_loss))
        print('{{"metric": "val_acc", "value": {}}}'.format(val_acc))
        print('{{"metric": "val_loss", "value": {}}}'.format(val_loss))

    # 保存模型
    # torch.save(model.state_dict(), save_model_path)
    torch.save(model, save_model_path)

    # 画图
    plt.figure(figsize=(15, 5.5))
    plt.subplot(121)
    plt.plot(train_acc_list)
    plt.plot(val_acc_list)
    plt.title("acc")
    plt.subplot(122)
    plt.plot(train_loss_list)
    plt.plot(val_loss_list)
    plt.title("loss")
    plt.savefig("results/acc_and_loss.png")
