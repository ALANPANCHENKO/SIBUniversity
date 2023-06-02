#include <iostream>
#include <time.h>
using namespace std;


struct Vertex 
{
	int data;
	int Bal;
	Vertex* left;
	Vertex* right;
};
Vertex* root;
int Size(Vertex* p)
{
	int SizeTree;
	if (p == NULL) 
	{
		return 0;
	}
	else 
	{
		SizeTree = 1 + Size(p->left) + Size(p->right);
		return SizeTree;
	}
}

int CheckSumm(Vertex* p)
{
	int CheckSummTree;
	if (p == NULL) 
	{
		return 0;
	}
	else 
	{
		CheckSummTree = p->data + CheckSumm(p->left) + CheckSumm(p->right);
		return CheckSummTree;
	}
}

float Average_Height(Vertex* p, int L)
{
	int Average_Height_Tree;
	if (p == NULL) 
	{
		return 0;
	}
	else 
	{
		Average_Height_Tree = L + Average_Height(p->left, L + 1) + Average_Height(p->right, L + 1);
		return Average_Height_Tree;
	}
}

int Height(Vertex* p)
{
	int HeightTree;
	if (p == NULL) 
	{
		return 0;
	}
	HeightTree = 1 + max(Height(p->left), Height(p->right));
	return HeightTree;
}

Vertex* new_element(int data)
{
	Vertex* p = new Vertex;
	p->data = data;
	p->left = NULL;
	p->right = NULL;
	return p;
	
}

void Fill_Mas(int *arr)
{
	bool mas[100] = {0};
	int RandomDigit;
	int a = 0;
	for (int i = 0; i<100; i++)
	{
		a = 0;
		while (a == 0)
		{
		RandomDigit = rand()%100;
		if (mas[RandomDigit] == true) a = 0;
		else 
		{
			mas[RandomDigit] = true;
			arr[i] = RandomDigit;
			a = 1;
		}
	}
	}	
}

void Fill(int* arr){
	for (int i=0;i<100;i++){
		arr[i]=i;
	}
}
 
void Down(int* arr){
	for (int i=0;i<100;i++){
		arr[i]=99-i;
	}	
} 



void Fill_Mas_Dec (int *arr){
	for (int i=0;i>100;i++){
		arr[i]=99-i;
	}	
}
 

void Traversal(Vertex* p, int type) {
	if (p != NULL) {
		if (type == 1) {
			cout << p->data << " ";
			Traversal(p->left, 1);
			Traversal(p->right, 1);
		}
		else if (type == 2) {
			Traversal(p->left, 2);
			cout << p->data << " ";
			Traversal(p->right, 2);
		}
		else if (type == 3) {
			Traversal(p->left, 3);
			Traversal(p->right, 3);
			cout << p->data << " ";
		}
	}
}


int VR=1;
int HR=1;
void DBD(Vertex*& p, int data){

		if (p == NULL){
				p = new Vertex;
				p->data=data;
				p->left=NULL;
				p->right=NULL;
				p->Bal=0;
				VR=1;
		}
		else if (p->data > data){
			DBD(p->left, data);
				if (VR == 1){
						if 	(p->Bal == 0){
							Vertex* q=p->left;
							p->left=q->right;
							q->right=p;
							p=q;
							q->Bal=1;
							VR=0;
							HR=1;
						}
						else {
							p->Bal=0;
							VR=1;
							HR=0;
						}	
				}
				else HR=0;
		}
	else if (p->data < data){
			DBD(p->right, data);
				if (VR == 1){
						p->Bal=1;
						HR=1;
						VR=0;
				}
				else if (HR == 1){
						if (p->Bal == 1){
									Vertex* q=p->right;
									p->Bal=0;
									q->Bal=0;
									p->right=q->left;
									q->left=p;
									p=q;
									VR=1;
									HR=0;
						} else HR=0;
					
				} 
	}	
}

int main() {
	srand(time(NULL));
	int arr[100];
	Fill_Mas(arr);
	Vertex* root = new Vertex;
	root->data = arr[0];
	root->left = NULL;
	root->right = NULL;
	cout << "DBD" << endl;
	cout << "---------------------------" << endl;
	for (int i = 0; i<100; i++)
	{
		DBD(root, arr[i]);
	}
	Traversal (root, 2);
	
	Vertex* root2 = new Vertex;
	root2->Bal=0;
	root2->data=arr[0];
	root2->left=NULL;
	root2->right=NULL;
	

	cout << endl << "Tree summ = " << CheckSumm(root) << endl;
	cout << "Tree size = " << Size(root) << endl;
	cout << "Tree height = " << Height(root) << endl;
	cout << "Tree average height = " << (float)(Average_Height(root, 1))/Size(root) << endl;
	

		Vertex* root3 = new Vertex;
	Fill(arr);
	root3->data = arr[0];
	root3->left = NULL;
	root3->right = NULL;
	cout << "DBD" << endl;
	cout << "---------------------------" << endl;
	for (int i = 0; i<100; i++)
	{
		DBD(root3, arr[i]);
	}
	Traversal (root3, 2);
	
	
		Vertex* root4 = new Vertex;
		Down(arr);
	root4->data = arr[0];
	root4->left = NULL;
	root4->right = NULL;
	cout << '\n';
	cout << "---------------------------" << endl;
	cout << '\n';
	cout << "DBD" << endl;
	for (int i = 0; i<100; i++)
	{
		DBD(root4, arr[i]);
	}
	Traversal (root4, 2);
	
	cout << endl << "Tree summ = " << CheckSumm(root3) << endl;
	cout << "Tree size = " << Size(root3) << endl;
	cout << "Tree height = " << Height(root3) << endl;
	cout << "Tree average height = " << (float)(Average_Height(root3, 1))/Size(root3) << endl;
	



}
