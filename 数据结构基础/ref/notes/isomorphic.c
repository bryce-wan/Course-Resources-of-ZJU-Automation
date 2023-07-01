#define Tree int
#define Null -1
int isomorphic(Tree R1, Tree R2)
{
    if ((R1 == Null) && (R2 == Null))
        return 1; // both empty

    if (((R1 == Null) && (R2 != Null)) || ((R2 == Null) && (R1 != Null)))
        return 0; // one of them is empty

    if (T1[R1].element != T2[R2].element)
        return 0; // the root is different

    if ((T1[R1].left == Null) && (T2[R2].left == Null))
        return isomorphic(T1[R1].right, T2[R2].right); // the left tree is empty

    if ((T1[R1].left != Null) && (T2[R2].left != Null) && (T1[T1[R1].left].element == T2[T2[R2].left].element))
        return isomorphic((T1[R1].left, T1[R2].left) && (T1[R1].right, T1[R2].right)); // the left tree is not empty

    else
        return isomorphic((T1[R1].left, T1[R2].right) && (T1[R1].right, T1[R2].left)); // after rotation?
}