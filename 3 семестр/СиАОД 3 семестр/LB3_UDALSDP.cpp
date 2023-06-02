#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct Vertex
{
	int Data;
	Vertex *right;
	Vertex *left;	
};

void FillRand(int n, int* A)
{
srand(time(NULL));
for(int i=0;i<n;i++)
{
A[i]=rand()%200;
	for(int j=0;j<i;j++)
	{
		if(A[i]==A[j])
		{
			A[i]=rand()%200;
			j=-1;
		}
	}
}
}
Vertex* SDP_dc(int *A,int n,Vertex **root) 
{
	int i=0;
	for(int i=0;i<n;i++)
	{
		Vertex **p=root; 
		while(*p!=NULL) 
		{
			if(A[i]<(*p)->Data)  
				p=&((*p)->left); 
			else if(A[i]>(*p)->Data)
				p=&((*p)->right); 
			else
				break; 
		}
	
		if(*p==NULL) 
		{
			 *p=new Vertex; 
			(*p)->Data=A[i]; 
			(*p)->left=NULL;
			(*p)->right=NULL;
		}
	}
	return (*root);

}

void left_to_right(Vertex *p) 
{
	 if(p!=NULL)
	 {
	 
	 left_to_right(p->left);
	 		cout<<p->Data<<"	";
	 	left_to_right(p->right);
	 }
}
void deleteV(Vertex **root, int D) 
{
	Vertex **p=root; 
	Vertex *r = NULL;
    Vertex *S = NULL;
    Vertex *q = NULL;
	while((*p)!=NULL)
	{
		if(D<(*p)->Data) 
			p=&((*p)->left);
		else if(D>(*p)->Data)
			p=&((*p)->right);
		else if(D==(*p)->Data)
			break;
		
	}
	if((*p)!=NULL) 
	{
		q= *p; 
		if(q->left==NULL) 
		*p=q->right; 
		else if(q->right==NULL) 
		*p=q->left; 
		else 
		{
			r=q->left;	
			S=q;
			if(r->right==NULL)
			{
				r->right=q->right;
				*p=r;
			}
			else
			{
				while(r->right!=NULL)
				{
					S=r;
					r=r->right;
				}
				S->right=r->left;
				r->left=q->left;
				r->right=q->right;
				*p=r;
				
			}
		}
		p=root;
		delete q;
	}
	else
	{
		cout<<"elementa net"<<endl;
	}
}

int main()
{
	int m=100;
	int A[m]; // создаем массив из 100 чисел
	FillRand(m,A); // заполняем рандомными числами
	Vertex *root=NULL; // создаем указатель на корень и зануляем его
	root=SDP_dc(A,m,&root); // в этот указатель кладем функцию создания СДП (эта функция создает СДП способом двойной косвенности)
	
	left_to_right(root); // обход слева направо
	for(int i=0;i<10;i++) 
	{
		int k;
		cout<<endl;
		cout<<"Vvedite vershinu:";
		cin>>k; // вводим вершину которую хоти удалить
		deleteV(&root, k); // функция удаления
		cout<<endl;
		left_to_right(root); // после каждого удаления печатается обход дерева
	}

	
	return 0;
}