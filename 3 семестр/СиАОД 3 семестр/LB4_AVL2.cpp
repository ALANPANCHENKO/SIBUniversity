#include <iostream>
#include <ctime>
#include <algorithm>
#include <math.h>

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

int Average_Height(Vertex* p, int L)
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
	Vertex* ptr = new Vertex;
	ptr->data = data;
	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
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
	}	for (int i = 0; i < 100; i++)
	{
	//	cout << arr[i] << endl;
	}
}
 
void fill_mas(int *arr){
	for (int i=0;i<100;i++){
		arr[i]=i;
	}
} 

void Down_Mas (int *arr){
	for (int i=0;i>100;i++){
		arr[i]=99-i;
	}	
}
 
void traversal(Vertex* p, int type) {
	if (p != NULL) {
		if (type == 1) {
			cout << p->data << " ";
			traversal(p->left, 1);
			traversal(p->right, 1);
		}
		else if (type == 2) {
			traversal(p->left, 2);
			cout << p->data << " ";
			traversal(p->right, 2);
		}
		else if (type == 3) {
			traversal(p->left, 3);
			traversal(p->right, 3);
			cout << p->data << " ";
		}
	}
}


void rotateRR(Vertex *&p) {
  Vertex *q = p->right;
  p->Bal = 0;
  q->Bal = 0;
  p->right = q->left;
  q->left = p;
  p = q;
}

void rotateLR(Vertex *&p) {
  Vertex *q = p->left;
  Vertex *r = q->right;
  if (r->Bal < 0){
    p->Bal = 1;}
  else{
    p->Bal = 0;
	}
  if (r->Bal > 0){
    q->Bal = -1;}
  else{
    q->Bal = 0;
	}
  r->Bal = 0;
  q->right = r->left;
  p->left = r->right;
  r->left = q;
  r->right = p;
  p = r;
}

void rotateRL(Vertex *&p) {
  Vertex *q = p->right;
  Vertex *r = q->left;
  if (r->Bal > 0)
    p->Bal = -1;
  else
    p->Bal = 0;

  if (r->Bal < 0)
    q->Bal = 1;
  else
    q->Bal = 0;

  r->Bal = 0;
  q->left = r->right;
  p->right = r->left;
  r->right = q;
  r->left = p;
  p = r;
}
void rotateLL(Vertex *&p) {
  Vertex *q = p->left;
  p->Bal = 0;
  q->Bal = 0;
  p->left = q->right;
  q->right = p;
  p = q;
}
bool Rost;

Add_AVL (Vertex*& p, int data ){
	if (p == NULL) {
		p = new Vertex;
		p->data = data;
		p->left=NULL;
		p->right=NULL;
		p->Bal=0;
		Rost=true;
	}
	else if (p->data > data) {
		Add_AVL(p->left, data);
			if (Rost == true){
				if (p->Bal>0) {  p->Bal=0; Rost=false; }
				else if (p->Bal == 0){	 p->Bal=-1; Rost=true; } 
				else {
					if (p->left->Bal < 0) {	rotateLL(p); Rost=false; }
					else { rotateLR(p); Rost=false;  }
				}
			}
	}
	
	else if (p->data < data){
		Add_AVL(p->right,data);
			if (Rost == true){
				if (p->Bal < 0){  p->Bal=0; Rost=false;	}	
					else if (p->Bal == 0) { p->Bal=1; Rost=true;  }
						else {
							if (p->right->Bal > 0){ rotateRR(p); Rost=false;}
							else { rotateRL(p); Rost=false;  }
						}
		}
	}
}

int main() {
	srand(time(NULL));
	int arr[100];
	Fill_Mas(arr);
	Vertex* root= new Vertex;
	root->data=arr[0];
	root->Bal=0;
	root->left=NULL;
	root->right=NULL;	
		for (int i=0;i<100;i++){
			Add_AVL( root, arr[i]);
		} 
		
		traversal( root, 2);
		cout<<endl;
	cout << endl << "Tree summ = " << CheckSumm(root) << endl;
	cout << "Tree size = " << Size(root) << endl;
	cout << "Tree height = " << Height(root) << endl;
	cout << "Tree average height = " << (float)(Average_Height(root, 1))/Size(root) << endl;
	Fill_Mas(arr);
	Vertex* root2= new Vertex;
	root2->data=arr[0];
	root2->Bal=0;
	root2->left=NULL;
	root2->right=NULL;
		for (int i=0;i<100;i++){
			Add_AVL( root2, arr[i]);
		} 
		
	
	
	Fill_Mas(arr);
	Vertex* root3= new Vertex;
	root3->data=arr[0];
	root3->Bal=0;
	root3->left=NULL;
	root3->right=NULL;		
		for (int i=0;i<100;i++){
			Add_AVL( root3, arr[i]);
		} 
		
			
	Fill_Mas(arr);		
	Vertex* root4= new Vertex;
	root4->data=arr[0];
	root4->Bal=0;
	root4->left=NULL;
	root4->right=NULL;		
		for (int i=0;i<100;i++){
			Add_AVL( root4, arr[i]);
		} 
		
			
	Fill_Mas(arr);		
	Vertex* root5= new Vertex;
	root5->data=arr[0];
	root5->Bal=0;
	root5->left=NULL;
	root5->right=NULL;		
		for (int i=0;i<100;i++){
			Add_AVL( root5, arr[i]);
		} 
// для возрастающего	
	fill_mas(arr);		
	Vertex* root6= new Vertex;
	root6->data=arr[0];
	root6->Bal=0;
	root6->left=NULL;
	root6->right=NULL;		
		for (int i=0;i<100;i++){
			Add_AVL( root6, arr[i]);
		} 
// для убывающего	
	Down_Mas(arr);		
	Vertex* root7= new Vertex;
	root7->data=arr[0];
	root7->Bal=0;
	root7->left=NULL;
	root7->right=NULL;		
		for (int i=0;i<100;i++){
			Add_AVL( root7, arr[i]);
		} 
	
	
				
	cout << "Tree average height "<<endl;
	cout << "1= "<<(float)(Average_Height(root, 1))/Size(root)<<endl; 
	cout << "2= " <<(float)(Average_Height(root2, 1))/Size(root2)<<endl;
	cout << "3= " <<(float)(Average_Height(root3, 1))/Size(root3)<<endl;
	cout <<"4= " <<(float)(Average_Height(root4, 1))/Size(root4)<<endl; 
	cout << "5= "<<(float)(Average_Height(root5, 1))/Size(root5) << endl;		
	cout << "Fill= "<<(float)(Average_Height(root6, 1))/Size(root6) << endl;		
	cout << "Yb= "<<(float)(Average_Height(root7, 1))/Size(root7) << endl;		
	
	
	
	return (0);	
}