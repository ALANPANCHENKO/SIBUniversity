#include <iostream>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

int h;
const int N = 10;
int V[N];
int W[N];
int **AW, **AP, **AR;

struct Vertex
{
	int data = 0;
	Vertex *left = NULL;
	Vertex *right = NULL;
};

Vertex *root{NULL};
Vertex *root3(NULL);

int Size(Vertex *p)
{
	int SizeTree;
	if (p == nullptr)
	{
		return 0;
	}
	else
	{
		SizeTree = 1 + Size(p->left) + Size(p->right);
		return SizeTree;
	}
}

void SelectSortDec (int V[], int arr_len, int W[])    
           {
            int j = 0;
            int tmp = 0;
            int C,M;
                for(int i=1; i<arr_len-1; i++){
                j = i;
                  for(int k = i+1 ; k<arr_len; k++){
                          if(W[k] > W[j]){
                          j = k;
                          }
                  }
                  if (W[i]!=W[j]){
                tmp = W[j];
                W[j] = W[i];
                W[i] = tmp;
				
				tmp=V[j];
				V[j]=V[i];
				V[i]=tmp;
				}
            } 
       }

void SelectSortInc (int V[], int arr_len, int W[])    
           {
            int j = 0;
            int tmp = 0;
            int C,M;
                for(int i=1; i<arr_len-1; i++){
                j = i;
                  for(int k = i+1 ; k<arr_len; k++){
                          if(W[k] < W[j]){
                          j = k;
                          }
                  }
                  if (W[i]!=W[j]){
                tmp = W[j];
                W[j] = W[i];
                W[i] = tmp;
				
				tmp=V[j];
				V[j]=V[i];
				V[i]=tmp;
				}
            } 
       }


           
int Check_Summ(Vertex *p)
{
	int CheckSummTree;
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		CheckSummTree = p->data + Check_Summ(p->left) + Check_Summ(p->right);
		return CheckSummTree;
	}
}

void Fill_Mas(int *arr, int n)
{
	arr[0] = 0;
	bool mas[n] = {0};
	int RandomDigit;
	int a = 0;
	for (int i = 1; i < n; i++)
	{
		a = 0;
		while (a == 0)
		{
			RandomDigit = rand() % (n-1) + 1;
			if (mas[RandomDigit] == true)
				a = 0;
			else
			{
				mas[RandomDigit] = true;
				arr[i] = RandomDigit;
				a = 1;
			}
		}
	}
}

void Traversal(Vertex *p, int type)
{
	if (p != NULL)
	{
		if (type == 1)
		{
			cout << p->data << " ";
			Traversal(p->left, 1);
			Traversal(p->right, 1);
		}
		else if (type == 2)
		{
			Traversal(p->left, 2);
			cout << p->data << " ";
			Traversal(p->right, 2);
		}
		else if (type == 3)
		{
			Traversal(p->left, 3);
			Traversal(p->right, 3);
			cout << p->data << " ";
		}
	}
}

void RSDP(Vertex *&p, int number)
{
	if (p == NULL)
	{
		p = new Vertex;
		p->data = number;
		p->left = NULL;
		p->right = NULL;
	}
	else if (number < p->data)
		RSDP(p->left, number);
	else if (number > p->data)
		RSDP(p->right, number);
}


void OutputMas(int Arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << Arr[i] << " ";
	}
}

void OutputMasW(int Arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		cout << Arr[i] << " ";
	}
}

void FillInc(int Arr[], int n)
{
	for (int i = 1; i < n; i++)
	{
		Arr[i] = i;
	}
}

void CreateAW(int W[], int **AW, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			AW[i][j] = AW[i][j - 1] + W[j];
		}
	}
};

void OutputMatrix(int **AW, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(2) << AW[i][j] << " ";
		}
		cout << endl;
	}
}

void CreateAPAR(int **AW, int **AP, int **AR, int n)
{
	for (int i = 0; i< n-1; i++)
	{
		int j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for (int h = 2; h < n; h++)
	{
		for (int i = 0; i < (n - h); i++)
		{
			int j = i + h;
			int m = AR[i][j - 1];
			int min = AP[i][m - 1] + AP[m][j];
			for (int k = m + 1; k <= AR[i + 1][j]; k++)
			{
				int x = AP[i][k - 1] + AP[k][j];
				if (x < min)
				{
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void CreateDOP(int L, int R, int **AR)
{
	int k;
	if (L < R) 
	{
		k = AR[L][R];
		RSDP(root, V[k]);
		CreateDOP(L, k - 1, AR);
		CreateDOP(k, R, AR);
	}
}

int SearchLevel(Vertex *p, int key)
{
	int h = 1;
	while (p != nullptr)
	{
		if (key < p->data)
		{
			p = p->left;
			h++;
		}
		else if (key > p->data)
		{
			p = p->right;
			h++;
		}
		else
			return h;
	}
}

int *l;

double TreeHeight(Vertex* p)
{
	double q = 0;
	l = new int[N];
	int h = 0;
	for (size_t i = 1; i < N; ++i)
	{
		l[i] = SearchLevel(p, V[i]);
		q += W[i];
		h += W[i] * l[i];
	}
	return (double)h / q;
}


void A2(int L, int R, int V[], int w[])
{
    int wes = 0, sum = 0;
    int i;
    if (L <= R)
    {
        for (i = L; i <= R; i++)
            wes += w[i];
        for (i = L; i <= R - 1; i++)
        {
            if ((sum <( wes / 2)) && ((sum + w[i])>(wes / 2))) break;
            sum += w[i];
        }
        RSDP(root3, V[i]);
        A2(L, i - 1, V, W);
        A2(i + 1, R, V, W);
    }
}


int main()
{
	srand(time(NULL));
	V[0] = 0;
	//Матрица весов поддеревьев
	int **AW = new int *[N];
	for (int i = 0; i < N; i++)
	{
		AW[i] = new int[N];
	}
	//матрица среденевзвешенных весов
	int **AP = new int *[N];
	for (int i = 0; i < N; i++)
	{
		AP[i] = new int[N];
	}
	//матрица, по которой строится дерево
	int **AR = new int *[N];
	for (int i = 0; i < N; i++)
	{
		AR[i] = new int[N];
	}
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			AW[i][j] = 0;
			AP[i][j] = 0;
			AR[i][j] = 0;
		}
	}
	
	FillInc(V, N);
	// OutputMas(V, N);
	cout << endl
		  << endl;
	Fill_Mas(W, N);
	// OutputMas(W, N);
	cout << endl;
		//DOP
		CreateAW(W, AW, N);
		CreateAPAR(AW, AP, AR, N);
		CreateDOP(0, N - 1, AR);
		cout<<"Tochnoe tree search"<<endl;
		Traversal(root, 2);
		cout << endl;
		cout << "Average height of tree: " << setprecision(4) << TreeHeight(root);
		cout << endl
			  << "Average height accroding to matrix: " << setprecision(4) << (double)AP[0][N - 1] / AW[0][N - 1];
		cout << endl;
		cout << endl;
		cout << endl;
		//A1
	 	SelectSortDec(V,N,W);
		
		Vertex* root2 = new Vertex;
		root2->data = V[1];
		root2->left = NULL;
		root2->right = NULL;
		
		for (int i=2;i<N;i++){
			RSDP(root2,V[i]);
		}
		cout<<"A1 DOP"<<endl;
		//OutputMas(V,N);
		cout<<endl;
		//OutputMas(W,N);
		//cout<<endl;
		Traversal(root2, 2);
		cout << endl;
		cout << "Average height of tree: " << setprecision(4) << TreeHeight(root2);
		cout << endl;
		
		//A2
		SelectSortInc(W,N,V);
		cout <<"A2 Dop"<<endl;
		//OutputMas(V,N);
		cout<<endl;
		//OutputMas(W,N);
		cout<<endl;
			
		A2(1, N-1, V, W);
		cout<<endl;
		Traversal(root3, 2);
		cout << endl;
		cout << "Average height of tree: " << setprecision(4) << TreeHeight(root3);
		cout << endl;
		
	
	for (int i = 0; i < N; i++)
	{
		delete[] AP[i];
	}
	delete[] AP;
	for (int i = 0; i < N; i++)
	{
		delete[] AW[i];
	}
	for (int i = 0; i < N; i++)
	{
		delete[] AR[i];
	}
	delete[] AR;
	delete root;
	delete root2;
	delete root3;
	return 0;
}