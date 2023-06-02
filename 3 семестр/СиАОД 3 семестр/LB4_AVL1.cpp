#include <iostream>
#include <ctime>

using namespace std;

bool rost = false;

struct Vertex
{
    int Data;
    int bal;
    Vertex* Left;
    Vertex* Right;
}; 

void RR(Vertex*& p) {
    Vertex* q = p->Right;
    p->bal = 0;
    q->bal = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void LL(Vertex*& p) {
    Vertex* q = p->Left; 
    p->bal = 0; 
    q->bal = 0; 
    p->Left = q->Right; 
    q->Right = p; 
    p = q; 
} 

void RL(Vertex*& p) {
    Vertex* q = p->Right;
    Vertex* r = q->Left;
    if (r->bal < 0)
        p->bal = 1;
    else
        p->bal = 0;
    if (r->bal > 0)
        q->bal = -1;
    else
        q->bal = 0;
    r->bal = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Right = q;
    r->Left = p;
    p = r;
}

void LR(Vertex*& p) {
    Vertex* q = p->Left;
    Vertex* r = q->Right;
    if (r->bal < 0)
        p->bal = 1;
    else
        p->bal = 0;
    if
        (r->bal > 0) 
		q->bal = -1;
    else
        q->bal = 0;
    r->bal = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}

void Add_AVL(int D, Vertex*& p) { 
    if (p == NULL) { 
        p = new Vertex; 
        p->Data = D; 
        p->Left = NULL; 
        p->Right = NULL;
        p->bal = 0; 
        rost = true;
    }
    else if (p->Data > D) {
        Add_AVL(D, p->Left); 
        if (rost){ 
            if (p->bal > 0) { 
                p->bal = 0; 
                rost = false; 
            }
            else if (p->bal == 0) {  
                p->bal = -1; 
                rost = true; 
            }
            else { 
                if (p->Left->bal < 0) { 
                    cout << "LL "; 
                    LL(p); 
                }
                else { 
                    cout << "LR "; 
                    LR(p);
                }
                rost = false;
            }
        }
    }
    else if (p->Data < D) {
        Add_AVL(D, p->Right); 
        if (rost){  
            if (p->bal < 0) { 
                p->bal = 0; 
                rost = false; 
            }
            else if (p->bal == 0) { 
                p->bal = 1; 
                rost = true; 
            }
            else { 
                if (p->Right->bal > 0) {
                    cout << "RR ";
                    RR(p);  
                }
                else {
                    cout << "RL ";
                    RL(p); 
                }
                rost = false; 
            }
        }
    }
}


Vertex* TreeSearch(Vertex* Root, int X) {
    struct Vertex* cell = Root;
    while (cell != NULL) {
        if (cell->Data > X)
            cell = cell->Left;
        else if (cell->Data < X)
            cell = cell->Right;
        else
            break;
    }
    if (cell != NULL) {
        cout << "Vershina najdena\n\n";
        return cell;
    }
    else {
        cout << "Vershina ne najdena\n\n";
        return NULL;
    }
}



void Obhod(Vertex* p, int N) {
    switch (N) {
    case 1:
        if (p != NULL) {
            cout << p->Data << "\t";
            Obhod(p->Left, 1);
            Obhod(p->Right, 1);
        }
        break;
    case 2:
        if (p != NULL) {
            Obhod(p->Left, 2);
            cout << p->Data << "\t";
            Obhod(p->Right, 2);
        }
        break;
    case 3:
        if (p != NULL) {
            Obhod(p->Left, 3);
            Obhod(p->Right, 3);
            cout << p->Data << "\t";
        }
        break;
    default:
        cout << "Error";
        break;
    }
}

int SizeTree(Vertex* p) {//Определение размера дерева
    int n;
    if (p == NULL) n = 0;
    else
        n = 1 + SizeTree(p->Left) + SizeTree(p->Right);
    return n;
}


int HeightTree(Vertex* p) {//Определение высоты дерева
    int h;
    if (p == NULL) h = 0;
    else
        h = 1 + max(HeightTree(p->Left), HeightTree(p->Right));
    return h;
}


int SumOfLengthsTree(Vertex* p, int L) {//Определение средней высоты дерева
    int s;
    if (p == NULL) s = 0;
    else
        s = L + SumOfLengthsTree(p->Left, L + 1) + SumOfLengthsTree(p->Right, L + 1);
    return s;
}

int AmountTree(Vertex* p) {//Определение контрольной суммы дерева
    int s;
    if (p == NULL) s = 0;
    else
        s = p->Data + AmountTree(p->Left) + AmountTree(p->Right);
    return s;
}

void TestTree(Vertex* p) {//Операции с деревом
    int size = SizeTree(p);
    cout << "\n\nRazmer dereva:\t" << size << "\n";
    int checksum = AmountTree(p);
    cout << "Kontrol'naya summa dereva:\t" << checksum << "\n";
    int height = HeightTree(p);
    cout << "Vysota dereva:\t" << height << "\n";
    float average_height = (float)SumOfLengthsTree(p, 1) / SizeTree(p);
    cout << "Srednyaya vysota dereva:\t" << average_height << "\n";
}


int main() {
    srand(time(0));
    Vertex* Root_AVL = new Vertex; 
    Root_AVL = NULL; 
    int MaxValue = 100;
//    int X;
//	cout << "VVedite vershinu, kotoryu nygno nayti: ";
//	cin >> X;
    int i = 0;
    int R = 0;
    int* A = new int[MaxValue]; 
    while (i < MaxValue) 
    {
        R = rand() % 100 + 1;
        for (int j = i; j >= 0; --j) {
            if (A[j] == R)
                break;
            else if (j == 0)
            {
                A[i] = R;
                ++i;
            }
        }
    }
    for (int i = 0; i < MaxValue; i++)
    {
        Add_AVL(A[i], Root_AVL); 
    }
    cout << endl;
    Obhod(Root_AVL, 2);
    TestTree(Root_AVL);
//    TreeSearch(Root_AVL, X);

    delete[] A;
    return 0;
}









