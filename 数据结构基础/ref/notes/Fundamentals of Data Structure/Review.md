## Stack
Stack is usually implemented with **array** in C. 
**Last in first out. 

```C
struct StackStruct
{
	int capcity;
	int top;
	ElementType *Data;
}*Stack;

// initialize a stack 
Stack Init()
{
	Stack S=(Stack)malloc(sizeof(struct StackStruct));
	capcity=input();
	top=-1;
	S->Data=(ElementType*)malloc(sizeof(ElementType)*capcity);
	return S;
}

// to judge if a stack is empty 
bool IsEmpty(Stack S)
{
	return S->top==-1;
}

//pop an element
ElementType Pop(Stack S)
{
	if(!IsEmpty(S))
		return S->Data[S->top--];
}

//push an element
void Push(Stack S, ElementType k)
{
	if(!IsFull(S))
		S->Data[++S->top]=k;
}
```


## Queue
The queue is usually implemented with **array** in C. And the circular queue is always used.
**First in first out.**

Attention:
	Initially the front is 0 and the rear is -1. 

```C
struct QueueStruct
{
	int capcity;
	int front;
	int rear;
	int size;
	ElementType *Array;
}*Queue;

//initialize a queue, not a circular queue
Queue Init()
{
	Queue Q=(Queue)malloc(sizeof(QueueStruct));
	Q->front=0;
	Q->rear=-1;
	Q->Array=(ElementType*)malloc(sizeof(ElementType)*capcity);
	return Q;
}

//to judge if the queue is empty 
bool IsEmpty(Queue Q)
{
	return Q->rear+1==Q->front;
}

//to pop an element
ElementType Dequeue(Queue Q);
{
	if(!IsEmpty(Q))
	{
		Q->size--;
		retrun Q->Array[Q->front++]; 
	}
}

// to push an element
void Enqueue(Queue Q,ElementType k)
{
	if(Q->rear<Q->capcity)
	{
		Q->size++;
		Q->Array[++Q->rear]=k;
	}
}

```

## Tree
The tree can be implemented with node and pointers or array. For a CST, we prefer the array and for a ordinary tree, we prefer the former one.

### Binary Tree
preorder: visit a node when meet it the first time.
inorder: visit a node when meet it the second time.
postorder: visit a node when meet it the third time.

it's easy to implement the recursive version of the traversals.
Here is an iterative version:
```C
//preorder
void PreOrder(BiTree T)
{
	SqStack* S;
	S = InitStack();
	BiTreeNode* p;
	p = T;
	while (p|| !StackEmpty(*S))
	{
		if (p)
		{
			visit(p);
			Push(S, p);
			p = p->LChild;
		}
		else
		{
			Pop(S, &p);
			p = p->RChild;
		}
	}
}

//inorder
void InOrder(BiTree T)
{
	SqStack* S;
	S = InitStack();
	BiTreeNode* p;
	p = T;
	while (p || !StackEmpty(*S))
	{
		if (p)
		{
			Push(S, p);
			p = p->LChild;
		}
		else
		{
			Pop(S, &p);
			visit(p);
			p = p->RChild;
		}
	}
}

//postorder
void Postorder(BiTree T)
{
	SqStack* S;
	S = InitStack();
	BiTreeNode* p;
	p = T;
	char tag[Maxsize] = {'0'};
	while (p || !StackEmpty(*S))
	{
		if (p)
		{
			Push(S, p);//the first or the third meet
			tag[S->top] = '0';
			p = p->LChild;
		}
		else
		{
			while (tag[S->top] == '1') {
				Pop(S, &p);
				visit(p);
			}
			if (S->top == -1) break;
			Pop(S, &p);
			Push(S, p);
			p = p->RChild;
			tag[S->top] = '1';//second meet
		}
	}
}

```

**A conclusion:**
combine $$n=n_0+n_1+n_2$$ and $$edges=n-1=n_1+2n_2$$ we have:
$$n_0=n_2+1$$


### Binary Search Tree

A binary search tree is a binary tree.  It may be empty.  If it is not empty, it satisfies the following properties:
(1)  Every node has a key which is an integer, and the keys are distinct.
(2)  The keys in a nonempty left subtree must be smaller than the key in the root of the subtree.
(3)  The keys in a nonempty right subtree must be larger than the key in the root of the subtree.
(4)  The left and right subtrees are also binary search trees.


### AVL Tree
LL RR: symmetric
LR RL: symmetric

LL:
1.  让subR的左子树作为parent的右子树。
2.  让parent作为subR的左子树。
3.  让subR作为整个子树的根。
4.  更新平衡因子。
RR:
1.  让subL的右子树作为parent的左子树。
2.  让parent作为subL的右子树。
3.  让subL作为整个子树的根。
4.  更新平衡因子。

双旋的操作实际是左右单旋的混合


### Complete Binary Tree
Usually implemented with array!

## Heap
heap is a complete binary tree. Usually implemented with array.

```C
typedef struct PriorityQueueStruct
{
	ElementType *Elements;
	int Capcity;
	int Size;
}*PriorityQueue

//initialize a heap
PriorityQueue  Init(int MaxElements)
{
     PriorityQueue H;
     
     if ( MaxElements < MinPQSize )
		  return  Error( "Priority queue size is too small" );
     
     H = malloc( sizeof ( struct HeapStruct ) );
     
     if ( H ==NULL )
		  return  FatalError( "Out of space!!!" );
     /* Allocate the array plus one extra for sentinel */
     
     H->Elements = malloc(( MaxElements + 1 ) * sizeof( ElementType ));
     
     if ( H->Elements == NULL )
		  return  FatalError( "Out of space!!!" );

     H->Capacity = MaxElements;
     H->Size = 0;
     H->Elements[ 0 ] = MinData;  /* set the sentinel */
     return  H;
}

//insert a new element into heap
void Insert(PriorityQueue H, ElementType k)
{
	if(not full)
	{
		int i;
		for(i=++H->Size;H->Elements[i/2]>k;i/=2)
			H->Elements[i]=H->Elements[i/2];
	}
	H->Elements[i]=k;
	
}

//delete the min element in a min heap
ElementType DeleteMin(PriorityQueue H)
{
	ElementType Min=H->Elements[1];
	ElementType Last=H->Elements[H->Size--];

	int i,child;
	
	for(i=1;i*2<H->Size;i=child)
	{
		child=i*2;
		
		if(child<=H->Size && H->Elements[child+1] < H->Elements[child]) 
			child+=1;
		if(H->Elements[child] < Last) 
			H->Elements[i]=H->Elements[child];
		else break;
	}
	
	H->Elements[i]=Last;
	
	return Min;
}
```
建堆的两种方式：
1. 数组中已经有了所有的元素，从第一个非叶节点开始每个向下过滤，理论时间$O(N)$
2. 数组中初始为空，每个依次进行插入，理论时间$O(NlogN)$

## Graph

### Implementation

1. Adjacent Matrix
```C
typedef struct GNode
{
	int Nv, Ne;
	int **map;
}*Graph;

```

2. Adjacent List
```C
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode
{
	Vertex AdjV; 
	PtrToAdjVNode Next; 
}; 

typedef struct Vnode
{
	PtrToAdjVNode FirstEdge; 
}AdjList[MaxVertexNum]; 

typedef struct GNode *PtrToGNode; 
struct GNode
{ 
	int Nv; 
	int Ne; 
	AdjList G; 
}; 
typedef PtrToGNode Graph;
```

3. Chained Forward Star
```C
int Nv, Ne;

struct EdgeNode
{
	int to;
	int next;
	int weight;
};

EdgeNode edges[];
int head[];//head里面储存的是以某个节点为起点的边中最后一条的序号

void Read()
{
	cin>>u>>v>>w;
	for(int i=1;i<=Ne;i++)
		edges[i].to=v;
		edges[i].weight=w;
		edges[i].next=head[u];//这两句顺序不能反过来，和链表的插入一样
		head[u]=i;// 以u为起点的边第一条的序号为i，但实际上是最后进入的
}
```

### Topological Sort
```C
void Topsort(Graph G)
{   Queue Q;
    int Counter = 0;
    Vertex V, W;

    Q = CreateQueue( NumVertex );  
    MakeEmpty( Q );

    for ( each vertex V )
		if ( Indegree[ V ] == 0 )   
			Enqueue( V, Q );
			
    while ( !IsEmpty( Q ) ) 
    {
		V = Dequeue( Q );
		TopNum[ V ] = ++ Counter; /* assign next */
		for ( each W adjacent to V )
	        if ( – – Indegree[ W ] == 0 )  Enqueue( W, Q );
    }  /* end-while */

    if ( Counter != NumVertex )
		  Error( “Graph has a cycle” );
	    DisposeQueue( Q ); /* free memory */
}
```

### Shortest Path


### Strongly Connected Components


### Maximum Network Flow


### Minimum Spanning Tree
#### 
####


## Sort

### Insertion Sort
```C
//时间复杂度：最好情况下：O(n)。最坏情况下：O(n^2); 
//空间复杂度：O(1)
void InsertionSort(int A[], int N)
{
	int i,j;
	for(i=1;i<N;i++)
	{
		int temp=A[i];
		
		for(j = i;j>0 && A[j-1]>temp;j--)
			A[j]=A[j-1];
		
		A[j]=temp;
	}
}
```


### Shell Sort
```C
void ShellSort(int A[],int N)
{
	int i,j,h;

	for(h=N/2;h>0;h/=2)
	{
		for(i=h;i<N;i++)
		{
			int temp=A[i];
			
			for(j=i;j>=h&&A[j-h]>temp;j-=h)
				A[j]=A[j-h];

			A[j]=temp;
		}
	}
}
```

### Heap Sort
默认应该使用max heap
```C
//Algorithm 1: bad because the space is doubled!
void HeapSort1(int A[],int N)
{
	Heap H=BuildHeap();

	for(int i=0;i<N;i++)
		tempH=DeleteMin(H);
		
	for(int i=0;i<N;i++)
		H[i]=tempH[i];
}

//Alogrithm 2:
void HeapSort2(int A[],int N)
{
	for(int i=N/2;i>=0;i--)
		PercDown(A,i,N);
		
	for(int i=N-1;i>0;i--)
	{   
		Swap(&A[0],&A[i]);
		PercDown(A,0,i);
	}
		
}
```

### Merge Sort
```C
void MSort( ElementType A[ ], ElementType TmpArray[ ],
			  int Left, int Right )
{   
	int  Center;
	
    if ( Left < Right ) 
    {  /* if there are elements to be sorted */
		Center = ( Left + Right ) / 2;

		MSort( A, TmpArray, Left, Center );   /* T( N / 2 ) */

		MSort( A, TmpArray, Center + 1, Right );   /* T( N / 2 ) */

		Merge( A, TmpArray, Left, Center + 1, Right );  /* O( N ) */
    }

}

/* Lpos = start of left half, Rpos = start of right half */
void Merge( ElementType A[ ], ElementType TmpArray[ ],
         int Lpos, int Rpos, int RightEnd )
{   
	int  i, LeftEnd, NumElements, TmpPos;

    LeftEnd = Rpos - 1;

    TmpPos = Lpos;

    NumElements = RightEnd - Lpos + 1;

    while( Lpos <= LeftEnd && Rpos <= RightEnd ) /* main loop */
        if ( A[ Lpos ] <= A[ Rpos ] )
		  TmpArray[ TmpPos++ ] = A[ Lpos++ ];
        else
		  TmpArray[ TmpPos++ ] = A[ Rpos++ ];

    while( Lpos <= LeftEnd ) /* Copy rest of first half */
        TmpArray[ TmpPos++ ] = A[ Lpos++ ];

    while( Rpos <= RightEnd ) /* Copy rest of second half */
        TmpArray[ TmpPos++ ] = A[ Rpos++ ];

    for( i = 0; i < NumElements; i++, RightEnd - - )
         /* Copy TmpArray back */
        A[ RightEnd ] = TmpArray[ RightEnd ];

}
```

### Quick Sort
```C
void  Quicksort( ElementType A[ ], int N )
{
  Qsort( A, 0, N - 1 );
  /* A:   the array   */
  /* 0:   Left index   */
  /* N – 1: Right index  */
}

void  Qsort( ElementType A[ ], int Left, int Right )
{   int  i,  j;

    ElementType  Pivot;

    if ( Left + Cutoff <= Right ) 
    {  /* if the sequence is not too short */
        Pivot = Median3( A, Left, Right );  /* select pivot */
        i = Left;     
        j = Right – 1;  /* why not set Left+1 and Right-2? */

        while(1) 
        {
	        while ( A[ + +i ] < Pivot ) { }  /* scan from left */
			while ( A[ – –j ] > Pivot ) { }  /* scan from right */
    		
    		if ( i < j )
				Swap( &A[ i ], &A[ j ] );  /* adjust partition */
		    else     
			    break;  /* partition done */
        }

        Swap( &A[ i ], &A[ Right - 1 ] ); /* restore pivot */

        Qsort( A, Left, i - 1 );      /* recursively sort left part */

        Qsort( A, i + 1, Right );   /* recursively sort right part */

	}  /* end if - the sequence is long */
    else /* do an insertion sort on the short subarray */
        InsertionSort( A + Left, Right - Left + 1 );

}

/* Return median of Left, Center, and Right */
/* Order these and hide the pivot */
ElementType Median3( ElementType A[ ], int Left, int Right )
{
    int  Center = ( Left + Right ) / 2;

    if ( A[ Left ] > A[ Center ] )
        Swap( &A[ Left ], &A[ Center ] );
    if ( A[ Left ] > A[ Right ] )
        Swap( &A[ Left ], &A[ Right ] );
    if ( A[ Center ] > A[ Right ] )
        Swap( &A[ Center ], &A[ Right ] );
    /* Invariant: A[ Left ] <= A[ Center ] <= A[ Right ] */
    Swap( &A[ Center ], &A[ Right - 1 ] ); /* Hide pivot */
    /* only need to sort A[ Left + 1 ] … A[ Right – 2 ] */
    return  A[ Right - 1 ];  /* Return pivot */
}

// Never care about the worst case~
void quicksort(int a[], int low, int high) // 从小到大
{
    int l ,r, key;
    l = low;
    r = high;
    key = a[l];
    if(low > high)  return ;
    while(l < r) //
    {
        while(l < r && a[r] > key) // 从右往左找到比key小的元素
            r--;
        a[l] = a[r]; // 交换之后,  r之后的元素都比key大
        while(l < r && a[l] < key)// 从左往右找到比key大的元素
            l++;
        a[r] = a[l];//交换之后,   l之前的元素都比key小
        //之后再将l到r之间的元素进行排序
    }
    a[l] =  key;
    // 此时0到l-1的元素都比l+1到high的元素小
    //但是0到l-1的元素和l+1到high的元素都是无序的
    quicksort(a, low, l-1); // 将0到l-1的元素进行快速排序
    quicksort(a, l+1, high); //将l+1到high的元素进行快速排序

}


//快速排序
void quick_sort(int q[], int l, int r) 
{
    //边界不满足左边小，直接返回
    if (l >= r) return;
    //第一步，确定边界
    //tips1：由于i和j都是先自减或自增后判断，初始时i、j往边界两端扩一步
    int i = l - 1, j =  r + 1, x = q[l + r >> 1];
    //第二步，划分区间，使得一边小于x，一边大于x；
    while (i < j)
    {
        while (q[++i] < x);
        while (q[--j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    //第三步，递归处理两边
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

```

### Bucket Sort


### LSD and MSD

LSD的基数排序适用于位数少的数列，如果位数多的话，使用MSD的效率会比较好。
（LSD合并的时候不要求有序，因为后续的权重会更新顺序，和队列很像）

MSD的方式由高位数为基底开始进行分配，但在分配之后并不马上合并回一个数组中，而是在每个“桶子”中建立“子桶”，将每个桶子中的数值按照下一数位的值分配到“子桶”中。在进行完最低位数的分配后再合并回单一的数组中。
（MSD合并时必须保证桶中的元素顺序是有序的，和栈很像）


## Hash
set the table size to be a prime number is good

### Solutions to Collisions

#### Separate Chaining
![[Pasted image 20230105215949.png]]

#### Opening Addressing
find another empty cell to solve collision.
```C
//Algorithm: insert key into an array of hash table
{
    index = hash(key);

    initialize i = 0 // the counter of probing;

    while ( collision at index ) 
    {
	  index = ( hash(key) + f(i) ) % TableSize;
	  if ( table is full )    
		  break;
	  else    
		  i ++;
    }

    if ( table is full )
	  ERROR (“No space left”);
    else
	  insert key at index;

}
```

1. Linear Probing
2. Quadratic Probing
	If quadratic probing is used, and the table size is prime, then a new element can always be inserted if the table is at least half empty.
3. Double Hashing
$$	f ( i ) = i * hash_2( x )$$
$hash_2(x)=R-(x\%R)$ with R a prime smaller than TableSize, will work well.
$$(hash1(key) + i * hash2(key)) \% TABLESIZE$$

### Rehash

When to rehash?
1. As soon as the table is half full
2. When an insertion fails
3. When the table reaches a certain load factor

new table size: >2\*original table size and be a prime number
