ptr reverse_linklist(ptr head, int n)
{
    ptr new, old, tmp;
    if (head)
    {
        new = head->next;
        old = new->next;
        while (cnt < n)
        {
            tmp = old->next;
            old->next = new;
            new = old;
            old = tmp;
            cnt++;
        }
        head->next->next = old;
        return new;
    }
    return NULL;
}
