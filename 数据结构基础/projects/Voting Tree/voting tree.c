#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265

typedef struct Point // The structure to contain the information of a point in shape A or B
{
    double x; // The x coordinate

    double y; // The y coordinate

} *PointSet;

typedef struct TreeNode *Tree;

struct TreeNode // The node  of the voting tree
{
    int a; // The index of a point in the correspondence in set A

    int b; // The index of a point in the correspondence in set B

    int depth; // The depth of the node

    Tree *next; // an array of pointers to TreeNode

    Tree pre; // a pointer to the previous TreeNode
};

void BuildTree(Tree R, PointSet A, PointSet B, int M, int N); // The function to build a first child- next sibling tree

void InitRoot(Tree R); // To initilize the  root

int DeleteSubTree(Tree T, int M, int N, int EmptyNodes); // To delete the sub tree that did nt pass the result

void Free(Tree R); // Clear the entire voting tree

int Judge(Tree temp, PointSet A, PointSet B); // Judging whether a node of the voting tree(a correspondence) is acceptable

int IsNew(Tree T); // To judge if the node represents a new correspondence

void TreeTraversal(Tree R, int vote[101][101], int M, int N); // Traverse the voting tree and record the number of votes for each correspondence

void Count(int n, int m, int idxA[], int idxB[], int vote[101][101], int *best_pair, int *max_votes, const int M); // Deal with the vote table

void PrintResult(PointSet A, PointSet B, int vote[101][101], int M, int N); // Print the result

double Max(double a, double b); // Compare A and B and then return the max number

double CalculateAngle(double x1, double y1, double x2, double y2); // Claculate the inner angle of a point in a shape

double Compare(double element1, double element2); // Compare two element(angle or length of edge) and return the viability

double Dist(double x, double y); // Calculate the length of the vector (x,y)

int main()
{

    int M, N;

    int vote[101][101] = {0}; // Initilize the 2-D array vote table to store all the votes

    scanf("%d %d", &M, &N); // Get the M and N

    if ((M < 3) || (N < 3)) // Examine the legality of input M and N
    {
        printf("Error Input"); // Print error message if the M or N is

        return 0;
    }

    PointSet A = (PointSet)malloc(sizeof(struct Point) * (M + 1)); // allocate memory for the point set A

    PointSet B = (PointSet)malloc(sizeof(struct Point) * (N + 1)); // Allocate memory for the point set B

    Tree R = (Tree)malloc(sizeof(struct TreeNode)); // Allocate memory for the root node

    // Initialize the root node

    R->next = (Tree *)malloc(sizeof(Tree) * (N + 1));

    for (int i = 1; i <= N; i++)

        R->next[i] = NULL;

    R->a = 0;

    R->b = 0;

    R->depth = 0;

    R->pre = NULL;

    for (int i = 1; i <= M; i++) // Read the points in set A
    {
        scanf("%lf %lf", &A[i].x, &A[i].y);
    }

    for (int i = 1; i <= N; i++) // Read the points in set B
    {
        scanf("%lf %lf", &B[i].x, &B[i].y);
    }

    BuildTree(R, A, B, M, N); // Build the voting tree R with the point sets A and B

    while (DeleteSubTree(R, M, N, 0) != 0)
        ; // Delete the empty subtree in the voting tree until all the path is complete

    TreeTraversal(R, vote, M, N); // Traverse the voting tree R and store the votes in the array vote[][]

    // Exibit the vote table

    // for (int i = 1; i <= M; i++)
    // {
    //     for (int j = 1; j <= N; j++)
    //     {
    //         printf("%d ", vote[i][j]);
    //     }
    //     printf("\n");
    // }

    PrintResult(A, B, vote, M, N); // Print the best correspondences

    system("pause");

    return 0;
}

void BuildTree(Tree R, PointSet A, PointSet B, int M, int N)
{

    if (R->depth == M) // Return when the depth is equal to M
    {
        return;
    }

    for (int i = 1; i <= N; i++)
    {
        Tree T = (Tree)malloc(sizeof(struct TreeNode)); // Allocate memory

        T->next = (Tree *)malloc(sizeof(Tree) * (N + 1));

        for (int j = 1; j <= N; j++)

            T->next[j] = NULL;

        // Initialize the next nodes of T

        R->next[i] = T;

        T->pre = R;

        T->a = T->pre->a + 1;

        T->b = (T->pre->b + i) % (N + 1);

        if (T->b == 0) // Avoid the zero

            T->b = 1;

        T->depth = T->pre->depth + 1;

        if ((R->depth == 0) || (R->depth == 1)) // If R is the root node or a child of the root
        {
            BuildTree(T, A, B, M, N); // Build the voting tree in a recursive way
        }

        else
        {
            if (Judge(T, A, B) && IsNew(T)) // If the node represents a new correspondence and the correspondence pass the tests
            {

                BuildTree(T, A, B, M, N); // Build the voting tree in a recursive way
            }

            else // Else delete the node
            {
                free(T);

                R->next[i] = NULL;

                continue;
            }
        }
    }
}

int IsNew(Tree T)
{

    if (T->depth == 0) // If the T is the root

        return 1;

    Tree temp = T->pre; // Start the search from the previous node of T

    while (temp->depth != 0)
    {
        if (temp->b == T->b) // Exit when find a node's b is equal to the T's b

            return 0;

        temp = temp->pre;
    }

    return 1;
}

int DeleteSubTree(Tree R, int M, int N, int EmptyNodes)
{
    if (R == NULL) // If the voting tree is NULL

        return 0;

    int empty = 1;

    for (int i = 1; i <= N; i++)
    {
        if (R->next[i] == NULL) // Pass if the R's child is NULL

            continue;

        if (R->next[i]->depth == M) // Pass if the R's child are leaves

            continue;

        empty = 1;

        for (int j = 1; j <= N; j++) // Mark the node as empty if all its childs are NULL
        {
            if (R->next[i]->next[j] != NULL)
            {
                empty = 0;

                break;
            }
        }

        if (empty == 1) // If the node is empty
        {
            free(R->next[i]);

            R->next[i] = NULL;

            EmptyNodes++;
        }
    }

    for (int i = 1; i <= N; i++) // Recursion
    {
        EmptyNodes += DeleteSubTree(R->next[i], M, N, EmptyNodes); // Add the number of nodes deleted to the EmptyNodes
    }

    return EmptyNodes; // Return the number of nodes deleted
}

void PrintResult(PointSet A, PointSet B, int vote[101][101], int M, int N)
{
    int best_pair[101] = {0}; // Store the best corrspondence of points in B

    int idxA[101], idxB[101] = {0}; // Temporarily store the indices

    for (int i = 0; i < N; i++)
    {
        idxA[i] = i + 1; // Initialization
    }

    int max_votes = -1; // Record the max number of votes

    Count(N, M, idxA, idxB, vote, best_pair, &max_votes, M); // Traverse all the combinations and count the votes

    for (int i = 1; i <= M; i++)
    {
        printf("(%d,%d)\n", i, best_pair[i]); // Print the best correspondences
    }
}

void Count(int n, int m, int idxA[], int idxB[], int vote[101][101], int *best_pair, int *max_votes, const int M)
{
    int temp_votes = 0; // To record the temperary votes of a combination of the indices of shape B

    for (int j = n; j >= m; j--)
    {

        idxB[m - 1] = j - 1;

        if (m > 1) // When the combination is not complete

            Count(j - 1, m - 1, idxA, idxB, vote, best_pair, max_votes, M); // Using recursion to generate combinations

        else // When the combination is generated
        {
            for (int i = 0; i < M; i++)
            {
                temp_votes += vote[i + 1][idxA[idxB[i]]];
            }

            if (temp_votes > *max_votes) // If the votes of the current path is larger the max one
            {
                *max_votes = temp_votes; // Update the max votes

                for (int i = 0; i < M; i++)
                {
                    best_pair[i + 1] = idxA[idxB[i]]; // Update the best path
                }
            }

            temp_votes = 0;
        }
    }
}

void TreeTraversal(Tree R, int vote[101][101], int M, int N)
{

    if (R == NULL) // If the tree is empty, report error
    {
        printf("ERROR: The Tree is Empty!");

        return;
    }

    if (R->depth != 0)
    {

        vote[R->a][R->b]++; // Every node gives a vote!
    }

    for (int i = 1; i <= N; i++)
    {
        if (R->next[i] != NULL)

            TreeTraversal(R->next[i], vote, M, N); // Traversal in a recursive way
    }
}

int Judge(Tree temp, PointSet A, PointSet B)
{
    int angle_test = 0, edge_test = 0;

    double a1_x = A[temp->pre->a].x - A[temp->pre->pre->a].x;

    double a1_y = A[temp->pre->a].y - A[temp->pre->pre->a].y;

    double a2_x = A[temp->pre->a].x - A[temp->a].x;

    double a2_y = A[temp->pre->a].y - A[temp->a].y;

    double alpha = CalculateAngle(a1_x, a1_y, a2_x, a2_y); // Calculate the angle in shape A

    double b1_x = B[temp->pre->b].x - B[temp->pre->pre->b].x;

    double b1_y = B[temp->pre->b].y - B[temp->pre->pre->b].y;

    double b2_x = B[temp->pre->b].x - B[temp->b].x;

    double b2_y = B[temp->pre->b].y - B[temp->b].y;

    double beta = CalculateAngle(b1_x, b1_y, b2_x, b2_y); // Calculate the correspond angle in shape B

    angle_test = Compare(alpha, beta); // Compare alpha and beta

    edge_test = Compare(Dist(a1_x, a1_y), Dist(b1_x, b1_y)) && Compare(Dist(a2_x, a2_y), Dist(b2_x, b2_y)); // Compare the lateral dege

    return (angle_test && edge_test); // If the angle_test and the edge_test both equal to 1, the correspondence is accepted
}

double CalculateAngle(double x1, double y1, double x2, double y2)
{
    double b = Dist(x1, y1);

    double c = Dist(x2, y2);

    double a = Dist(x1 - x2, y1 - y2); // the opposite edge of the object angle

    double cos_alpha = (b * b + c * c - a * a) / (2 * b * c); // Using the cosine theorem to calculate the cos_alpha

    double val = 180.0 / PI;

    return acos(cos_alpha) * val; // Return the angle which
}

double Compare(double element1, double element2)
{
    if ((abs(element1 - element2) / Max(element1, element2)) > 0.25) // Calculate the difference make comparison

        return 0; // Not pass the test

    else

        return 1; // Pass the test
}

double Dist(double x, double y)
{

    return sqrt(x * x + y * y); // Return the Euclidean distance from (0,0) to (x,y)
}

double Max(double a, double b)
{
    return a > b ? a : b; // Return the maxnimum number
}