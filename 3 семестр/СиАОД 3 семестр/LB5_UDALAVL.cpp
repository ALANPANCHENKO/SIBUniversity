#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

bool rost = 1;
const int N = 100;
int A[N] = { 0 };
bool decrease = 1;


struct Vertex {
	int data;
	int bal;
	struct Vertex* left;
	struct Vertex* right;
};



void LeftRight(Vertex* root)
{
	if (root == NULL)
		return;
	LeftRight(root->left);
	if (root->data)
		printf("%d ", root->data);
	LeftRight(root->right);
}

void FillRand(int* A, int n)
{
	bool chislo;

	for (int i = 0; i < n;)
	{
		chislo = false;
		int random = rand() % 100 + 1;

		for (int j = 0; j < i; j++)
		{
			if (A[j] == random)
			{
				chislo = true;
				break;
			}
		}

		if (!chislo)
		{
			A[i] = random;
			i++;
		}
	}
}

void LL(Vertex*& tree) {
	Vertex* q = tree->left;
	tree->bal = 0;
	q->bal = 0;
	tree->left = q->right;
	q->right = tree;
	tree = q;
}

void RR(Vertex*& tree) {
	Vertex* q = tree->right;
	tree->bal = 0;
	q->bal = 0;
	tree->right = q->left;
	q->left = tree;
	tree = q;
}

void LR(Vertex*& tree) {
	Vertex* q = tree->left;
	Vertex* r = q->right;
	if (r->bal < 0)
		tree->bal = 1;
	else
		tree->bal = 0;
	if
		(r->bal > 0) q->bal = -1;
	else
		q->bal = 0;
	r->bal = 0;
	q->right = r->left;
	tree->left = r->right;
	r->left = q;
	r->right = tree;
	tree = r;
}

void RL(Vertex*& tree) {
	Vertex* q = tree->right;
	Vertex* r = q->left;
	if (r->bal < 0)
		tree->bal = 1;
	else
		tree->bal = 0;
	if (r->bal > 0)
		q->bal = -1;
	else
		q->bal = 0;
	r->bal = 0;
	q->left = r->right;
	tree->right = r->left;
	r->right = q;
	r->left = tree;
	tree = r;
}

void Add_ABL(int X, Vertex*& p) {
	if (p == NULL) {
		p = new Vertex;
		p->data = X;
		p->left = NULL;
		p->right = NULL;
		p->bal = 0;
		rost = 1;
	}
	else if (p->data > X) {
		Add_ABL(X, *&p->left);
		if (rost == 1) {
			if (p->bal > 0) {
				p->bal = 0;
				rost = 0;
			}
			else if (p->bal == 0) {
				p->bal = -1;
			}
			else {
				if (p->left->bal < 0) {
					cout << "LL" << endl;
					LL(p);
					rost = 0;
				}
				else {
					cout << "LR" << endl;
					LR(p);
					rost = 0;
				}
			}
		}
	}
	else if (p->data < X) {
		Add_ABL(X, *&p->right);
		if (rost == 1) {
			if (p->bal < 0) {
				p->bal = 0;
				rost = 0;
			}
			else if (p->bal == 0) {
				p->bal = 1;
			}
			else {
				if (p->right->bal > 0) {
					cout << "RR" << endl;
					RR(p);
					rost = 0;
				}
				else {
					cout << "RL" << endl;
					RL(p);
					rost = 0;
				}
			}
		}
	}

}


void LL1(Vertex*& p) 
{
	Vertex* q = p->left; 
	if (q->bal == 0) 
	{
		q->bal = 1; 
		p->bal = -1; 
		decrease = false;
	}
	else 
	{
		q->bal = 0; 
		p->bal = 0;
	}
	p->left = q->right; 
	q->right = p; 
	p = q; 
}

void RR1(Vertex*& p) 
{
	Vertex* q = p->right;
	if (q->bal == 0)
	{
		q->bal = -1;
		p->bal = 1;
		decrease = false;
	}
	else
	{
		q->bal = 0;
		p->bal = 0;
	}
	p->right = q->left;
	q->left = p;
	p = q;
}

void BL(Vertex*& p) 
{
	if (p->bal == -1) 
	{
		p->bal = 0; 
	}
	else if (p->bal == 0) 
	{
		p->bal = 1; 
		decrease = false; 
	}
	else if (p->bal == 1) 
	{
		if (p->right->bal >= 0) 
		{
			cout<<"RR1"<<endl;
			RR1(p); 
		}
		else
		{
			cout<<"RL"<<endl;
			RL(p);
		}
	}
}

void BR(Vertex*& p) 
{
	if (p->bal == 1)
	{
		p->bal = 0;
	}
	else if (p->bal == 0)
	{
		p->bal = -1;
		decrease = false;
	}
	else if (p->bal == -1)
	{
		if (p->left->bal <= 0)
		{
			cout<<"LL1"<<endl;
			LL1(p);
		}
		else
		{
			cout<<"LR"<<endl;
			LR(p);
		}
	}
}


void DEL(Vertex*& l, Vertex*& q)
{
	if (l->right != NULL) 
	{
		DEL(l->right,q); 
		if (decrease) 
		{
			BR(l);
		}
	}
	else 
	{		
		q -> data = l -> data;
		q = l;
		l = l->left;
		decrease = true;
	}
}

void DELETEAVL(int& x, Vertex*& p)
{
	if (p == NULL);
	else if (x < p->data)
	{
		DELETEAVL(x, p->left);
		if (decrease == true) 
		{

			BL(p);
		}
	}
	else if (x > p->data)
	{
		DELETEAVL(x, p->right);
		if (decrease == true)
		{
			BR(p);
		}
	}
	else 
	{
		Vertex* q = p; 
		if (q->left == NULL) 
		{
			p = q->right; 
			decrease = true;
		}
		else if (q->right == NULL)
		{
			p = q->left;
			decrease = true;
		}
		else
		{
			DEL(q->left,q);
			if (decrease == true)
			{
				BL(p);
			}
		}
		delete q;
	}
	
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	Vertex* root = NULL;
	FillRand(A, N);
	for (int i = 0; i < 100; i++) {

		Add_ABL(A[i], *&root);
	}
	cout << endl;
	LeftRight(root);
	cout << endl;
 	int a;
	while(1) 
	{
		cin >> a; 
		DELETEAVL(a, *&root);
		LeftRight(root);
		cout << endl;
		if (!root) break;
	}
	cout << endl;

}