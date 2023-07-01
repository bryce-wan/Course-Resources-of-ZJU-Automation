//二分查找树 Binary Searching Tree
Position Find(ElementType X, BinTree BST) //递归实现查找元素X，返回其位置
{
    if (!BST)
        return NULL;
    if (X < BST->data)
        return Find(X, BST->left);
    else if (X > BST->data)
        return Find(X, BST->right);
    else
        return BST;
}

Position IterFind(ElementType X, BinTree BST) //非递归实现查找元素X，返回其位置
{
    while (BST)
    {
        if (X < BST->data)
            BST = BST->left;
        else if (X > BST->data)
            BST = BST->right;
        else
            return BST;
    }
}

Position FindMin(BinTree BST) //递归实现寻找最小值 最左结点
{
    if (!BST)
        return NULL;

    else if (!BST->left)
        return BST;

    else
        return FindMin(BST->left);
}

Position FindMax(BinTree BST) //非递归实现寻找最大值 最右结点
{
    if (BST)
    {
        while (BST->right)
            BST = BST->right;
    }
    return BST;
}

BinTree Insert(ElementType X, BinTree BST) //二叉树中插入结点
{
    if (!BST)
    {
        BST = (BinTree)malloc(sizeof(TreeNode));
        BST->data = X;
        BST->left = BST->right = NULL;
    }
    else
    {
        if (X < BST->data)
            BST = Insert(X, BST->left);
        else if (X > BST->data)
            BST = Insert(X, BST->right);
    }
    return BST;
}