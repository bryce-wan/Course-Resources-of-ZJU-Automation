struct PolyNode
{
    int coef;
    int expo;
    struct PolyNode *link;
};
typedef struct PolyNode *polynomial;
polynomial p1, p2;

polynomial polysum(polynomial p1, polynomial p2)
{
    polynomial p = NULL, pt1 = p1, pt2 = p2, head = NULL;
    if (!p1)
    {
        return p2;
    }
    if (!p2)
    {
        return p2;
    }

    head = p;

    while (pt1 && pt2)
    {
        p = (polynomial)malloc(sizeof(*polynomial));
        p->link = NULL;
        if (pt1->expo == pt2->expo)
        {
            p->coef = pt1->coef + pt2->coef;
            p->expo = pt1->expo;
            pt1 = pt1->link;
            pt2 = pt2->link;
        }
        else if (pt1->expo > pt2->expo)
        {
            p->coef = pt1->coef;
            p->expo = pt1->expo;
            pt1 = pt1->link;
        }
        else if (pt1->expo < pt2->expo)
        {
            p->coef = pt2->coef;
            p->expo = pt2->expo;
            pt1 = pt2->link;
        }
        p = p->link;
    }

    if (pt1->link == NULL)
    {
        p->link = pt2;
        return head;
    }
    if (pt2->link == NULL)
    {
        p->link = pt1;
        return head;
    }
    return head;
}
