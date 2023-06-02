#include <iostream>
#include <ctime>
using namespace std;
//p - рабочий указатель
struct Vertex {//вершина дерева
    int data;
    Vertex *left, *right;
};


/*void Obhod1(Vertex *p){//корень лево право
	if(p!=NULL){
	cout<<p->data<<' ';
	Obhod1(p->left);
	Obhod1(p->right);	
	}
}*/

//void Obhod2(Vertex *p){//лево право корень
//	if(p!=NULL){
//	Obhod2(p->left);
	//Obhod2(p->right);
//	cout<<p->data<<' ';
//	}
//}

void Obhod3(Vertex *p){//лево корень право
	if(p!=NULL){
	Obhod3(p->left);
	cout<<p->data<<' ';
	Obhod3(p->right);
	}
}

int treeSize(Vertex *&p) {

    if (p) {
        return 1 + treeSize(p->left) + treeSize(p->right);
    } else {
        return 0;
    }
}

int treeLenSum(Vertex *&p, int l){

    if (!p) {
        return 0;
    } else {
        return l + treeLenSum(p->left, l + 1) + treeLenSum(p->right, l + 1);
    }
}

int checkSum(Vertex *&p) {
    static int sum = 0;
    if (p) {
        sum += p->data;
        checkSum(p->left);
        checkSum(p->right);
    }
    return sum;
}

int treeHeight(Vertex *&p, int h = 0) {
    if (p) {
        h++;
        h = max(treeHeight(p->left, h), treeHeight(p->right, h));
    }
    return h;
}

double treeMediumHeight(Vertex *&p) {
    return (double) treeLenSum(p,1) / treeSize(p);
}

void FillRand(int *Arr, int size)
{
	for(int i = 0; i < size; i++)
	Arr[i] = rand() % size;
}

void PrintMas(int *Arr, int size)
{
	for(int i = 0; i < size; i++)
	cout <<Arr[i] << " ";
	cout << '\n';
}

void swap(int *xp, int *yp)
{
int temp = *xp;
*xp = *yp;
*yp = temp;
}

void selectSort(int Arr[], int n)
{
    int i, j, min_idx;
 
    for (i = 0; i < n-1; i++)
    {
       
        min_idx = i;
        for (j = i+1; j < n; j++)
        if (Arr[j] < Arr[min_idx])
            min_idx = j;

        if(min_idx!=i)
            swap(&Arr[min_idx], &Arr[i]);
    }
}

Vertex *ISDP(int left, int right, int *Arr)
{
	if(left > right)
	{
		return NULL;
	}
	else
	{
		int size = (left + right) / 2;
		Vertex *p = new Vertex;
		p -> data = Arr[size];
		p -> left = p -> right = NULL;
		p -> left = ISDP(left, size - 1, Arr);
		p -> right = ISDP(size + 1, right, Arr);
		return p;
	}
}

int main() {
	srand(time(NULL));
	Vertex *root = NULL;
	int size = 100;
	int Arr[size];
	
	cout <<"Massiv:\n ";
	FillRand(Arr, size);
	PrintMas(Arr, size);
	selectSort(Arr, size);
	
	root = ISDP(0, size - 1, Arr);
	
	cout<<"levo koren' pravo"<<'\n';
	Obhod3(root);	
	cout<<endl;
	
	cout<<"\nDlina:"<<treeLenSum(root,1)<<'\n';
	cout<<"\ntreeSize:"<<treeSize(root)<<'\n';
	cout<<"\ncheckSum:"<<checkSum(root)<<'\n';
	cout<<"\ntreeHeight:"<<treeHeight(root)<<'\n';
	cout<<"\ntreeMediumHeight:"<<treeMediumHeight(root)<<'\n';
}