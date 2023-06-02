#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>

using namespace std;

struct Vertex
{
    int data;
    Vertex *left = NULL;
    Vertex *right = NULL;
};

int num = 1;
int u = 64;

	void PrintTree (Vertex *, int );
	bool addRST_R(Vertex *&, int );

	bool addRST_DI(Vertex *&, int );
	Vertex *createRST_R(int, bool );
	Vertex *createRST_DI(int, bool );
	Vertex *ISDP(int L, int R, int *A);
	Vertex *createISDP(int n);
	int TreeSize(Vertex *);
	int CheckSum(Vertex *);
	int Visota(Vertex *);
	int SDPV(Vertex *, int);
	void DeleteTree(Vertex *);
	void ObhodV(Vertex *);
	void ObhodP(Vertex *);
	void ObhodN(Vertex *);
	void numberv(Vertex *);


int main(int argc, const char **argv)
{
    int n = 100;
    srand (time(0));

    //Vertex *root = createISDP(n); 
    //printf("Obhod sleva\n");
    //printf("ISDP\n");
    //ObhodP(root); 

    printf("\nDouble\n");
    Vertex *root2 = createRST_DI(n, 1);
    ObhodP(root2); 

    printf("\nRecurcion\n");
    Vertex *root3 = createRST_R(n, 1); 
    ObhodP(root3); 

    //int treesize1 = TreeSize(root); 
    int treesize2 = TreeSize(root2); 
    int treesize3 = TreeSize(root3); 
	bool search(Vertex *&p, int D);





    printf("\n");
    printf(" _________________________________________________\n");
    printf("|n=100  | Size | Check sum   | Height | Mid Height |\n");
    printf("|------ |------|-------------|--------|------------|\n");
    //printf("| ISDP |%4d  |%9d    |%6d  |%9.2f   |\n",treesize1, CheckSum(root), Visota(root), SDPV(root, 2) / (float)treesize1);
    printf("| SDP_D |%4d  |%9d    |%6d  |%9.2f   |\n",treesize2,CheckSum(root2), Visota(root2), SDPV(root2, 2) / (float)treesize2);
    printf("| SDP_R |%4d  |%9d    |%6d  |%9.2f   |\n",treesize3, CheckSum(root3), Visota(root3),SDPV(root3, 2) / (float)treesize3);
    printf("| ______|______|_____________|________|____________|\n");
    printf("\n\n");
    int d;
    scanf("%d", &d);
	search(root2, d);



    //printf("\n\n\nDvoynaya kosvenost\n\n\n");
    //PrintTree(root2,0);
    //printf("\n\n\nREQRSIA\n\n\n");
    //PrintTree(root3,0);
    //DeleteTree(root);
    DeleteTree(root2);
    DeleteTree(root3);
    return 0;
}



void ObhodP(Vertex * p)
{
    if (p != NULL)
    {
        ObhodP(p->left);
        printf("%d ",p->data);
        ObhodP(p->right);
    }
}

void ObhodN(Vertex * p)
{
    if (p != NULL)
    {
        ObhodN(p->left);
        ObhodN(p->right);
        printf("%d ",p->data);
    }
}

//Vertex *ISDP(int left, int right, int *Mas)
//{
//    if(left > right)
//    {
//        return NULL;
//    }
//    else
//    {
//        int size = (left + right) / 2;
//        Vertex *p = new Vertex;
//        p -> data = Mas[size];
//        p -> left = p -> right = NULL;
//        p -> left = ISDP(left, size - 1, Mas);
//        p -> right = ISDP(size + 1, right, Mas);
//        return p;
//    }
//}
//
//
//Vertex *createISDP(int n)    
//{
//    int num=1;
//    int *Arr = new int[n];
//    for (int i = 0; i < n; i++)
//    {
//        Arr[i] = i + 1;
//    }
//    return ISDP(0, n - 1, Arr); 
//}


bool addRST_DI(Vertex *&p, int D)   
{
    Vertex **q = &p;
    while (*q != NULL)
    {
        if (D < (*q)->data)
            q = &((*q)->left);
        else if (D > (*q)->data)
            q = &((*q)->right);
        else
        {
            return false;
        }
    }
    if (*q == NULL)
    {
        *q = new Vertex;
        (*q)->data = D;
        (*q)->left = NULL;
        (*q)->right = NULL;
    }
    return true;
}

Vertex *createRST_DI(int n, bool log)   
{
    srand (time(0));
    Vertex *root = NULL;
    int i = 0;
    while (i < n)
    {
        int D = rand() % 1000 + 1; 
        if (addRST_DI(root, D)) 
            i++; 
        //else if (log) 
           // printf ("Data already have this -> %d \n", D);
    }
    return root; 
}


bool addRST_R(Vertex *&p, int D)  
{
    bool fl = true;
    if (p == NULL)
    {
        p = new Vertex;
        p->data = D;
        p->left = NULL;
        p->right = NULL;
    }
    else if (D < p->data)
        fl = addRST_R(p->left, D);
    else if (D > p->data)
        fl = addRST_R(p->right, D);
    else
        fl = false;
    return fl;
}

Vertex *createRST_R(int n, bool log)   
{
    Vertex *root = NULL;
    int i = 0;
    while (i < n)
    {
        int D = rand () % 1000 + 1;
        if (addRST_R(root, D))
            i++;
        //else if (log)
            //printf ("Data have: %d \n", D);
    }
    return root;
}
//void Delete_el(int D, Vertex* root)
//{
//    Vertex* q;
//    Vertex* r;
//    Vertex* S;
//    Vertex** p;
//    p = &root;
//
//    while (*p != NULL)
//    {
//
//        if ((*p) -> data < D)
//        {
//            p = &((*p)->right);
//        }
//        else if (D < ((*p) -> data ))
//        {
//            p = &((*p) -> left);
//        }
//    }
//    if (*p != NULL)
//    {
//        q = *p;
//        if (q -> left == NULL ) *p = q->right;
//        else if (q->right==NULL) *p = q->left;
//        else
//        {
//            r = q->left;
//            S = q;
//        }
//        while(r->right != NULL)
//        {
//            S = r;
//            r = r -> right;
//        }
//        S -> right = r -> left;
//        r -> left = q -> left;
//        r -> right = q -> right;
//        *p = r;
//    }
//    free(q);
//
//}

bool search(Vertex *&p, int D){
	Vertex **q = &p;
	while (*q != NULL)
    {
        if (D < (*q)->data)
            q = &((*q)->left);
            
        else if (D > (*q)->data)
            q = &((*q)->right);
        
        else
        {
        	printf ("Key: %d \n",(*q)->data);
            return false;
        }
        
    }
    
}

int TreeSize(Vertex *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + TreeSize(p -> left) + TreeSize(p -> right));
    }
}

int CheckSum(Vertex * p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return (p->data + CheckSum(p->left) + CheckSum(p->right));
    }
}

int Visota(Vertex * p)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + max(Visota(p->left), Visota(p->right)));
    }
}

int SDPV(Vertex * p, int L)
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return (L + SDPV(p->left, L + 1) + SDPV(p->right, L + 1));
    }
}

void DeleteTree(Vertex *p)  
{
    if (p != NULL)
    {
        DeleteTree(p->left);
        DeleteTree(p->right);
        delete p;
    }
}
