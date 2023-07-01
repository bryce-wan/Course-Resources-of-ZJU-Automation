## 二叉树的数据类型

```C
typedef bintree Position;
struct TreeNode
{
    ElementType data;
    bintree left;
    bintree right;
};

typedef TreeNode *bintree;
```

## 二叉树的遍历（递归实现）

1. 前序遍历

```C
void PreOrderTraversal(bintree BT)
{
    if (BT)
    {
        printf("%d", BT->data);//在第一次遇到某个结点的时候输出（中-左-右）
        PreOrderTraversal(BT->left);
        PreOrderTraversal(BT->right);
    }
}
```

2. 中序遍历

```C
void InOrderTraversal(bintree BT)
{
    if (BT)
    {
        InOrderTraversal(BT->left);
        printf("%d", BT->data);//在第二次遇到某个结点的时候输出（左-中-右）
        InOrderTraversal(BT->right);
    }
}
```

3. 后序遍历

```C
void PostOrderTraversal(bintree BT)
{
    if (BT)
    {
        PostOrderTraversal(BT->left);
        PostOrderTraversal(BT->right);
        printf("%d", BT->data);//在第三次遇到某个结点的时候输出（左-右-中）
    }
}
```

## 二叉树的遍历（非递归实现）

1. 前/中序遍历

从中序遍历改为前序遍历是容易的。

```C
void Traversal(bintree BT) //非递归实现二叉树的前/中序遍历,本质是使用栈
{
    bintree T = BT;
    stack S = createStack(maxsize);

    while (T || !IsEmpty(S))
    {
        while (T)
        {
            Push(S, T); //第一次碰到这个结点
            // printf("%d ", T->data); // 先序是第一次遇到时访问
            T = T->left
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);            //第二次碰到这个结点
            printf("%d", T->data); // 中序是第二次遇到时访问
            T = T->right;          //转向右子树
        }
    }
}
```

2. 后序遍历

```C
void Traversal(bintree BT)
{
    bintree T=BT;
}
```
