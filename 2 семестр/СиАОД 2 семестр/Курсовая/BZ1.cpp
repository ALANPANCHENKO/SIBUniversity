#include <Windows.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 4000;

struct Data {
	char Name[30];
     union {
        short int Nomerotdela;
        char chars[2];
    };
    char Position[22];
    char BTDate[10];
};


struct Node
{
    Node* next;
    Data data;
};


struct queue
{
    Node* head, * tail;
}q[256];


void make_index_array(Data *arr[], Node *root, int n = N) {
    Node *p = root;
    for (int i = 0; i < n; i++) {
        arr[i] = &(p->data);
        p = p->next;
    }
}

int strcomp(const string &str1, const string &str2, int len = -1) {
    if (len == -1) {
        len = (int) str1.length();
    }
    for (int i = 0; i < len; ++i) {
        if (str1[i] == '\0' && str2[i] == '\0') {
            return 0;
        } else if (str1[i] == ' ' && str2[i] != ' ') {
            return -1;
        } else if (str1[i] != ' ' && str2[i] == ' ') {
            return 1;
        } else if (str1[i] < str2[i]) {
            return -1;
        } else if (str1[i] > str2[i]) {
            return 1;
        }
    }
    return 0;
}

void digitalSort(Node *&head) {
    int first_f = 2;
    int sec_f = 30;
    int L = first_f + sec_f;
    Node *p;

    for (int j = 0; j < L; j++) {
        for (auto &i : q) {
            i.tail = i.head = NULL;
        }
        while (head) {
            int d;
            if (j < sec_f) {
                d = 255 - abs(head->data.Name[sec_f - j - 1 ]);
            } else
			 if (j < sec_f + first_f) {
                d = (unsigned char) head->data.chars[L - j - 1];
            }
            p = q[d].tail;
            if (q[d].head == NULL)
                q[d].head = head;
            else
                p->next = head;

            p = q[d].tail = head;
            head = head->next;
            p->next = NULL;
        }
        int i;
        for (i = 0; i < 256; i++) {
            if (q[i].head != NULL)
                break;
        }
        head = q[i].head;
        p = q[i].tail;
        for (int k = i + 1; k < 256; k++) {
            if (q[k].head != NULL) {
                p->next = q[k].head;
                p = q[k].tail;
            }
        }
    }
}


Node* printList(Node* f, int& count)
{
    for (int i = 0; i < 20; i++, count++)
    {
    	if(f == nullptr){
    		break;
		}
    	printf("%d) %s\t%d\t%s\t%s\n", count, f->data.Name, f->data.Nomerotdela, f->data.Position, f->data.BTDate);
        f = f->next;      
    }
    
    return f;
}


void print(Node* p , int n = N){
	int count = 1;
	int b;
	 for (int i = 0; i < n / 20 + 1; i++)
        {
            p = printList(p, count);
            
			if(p == nullptr){
    		break;
			}
            printf("Next 20?  1/0: ");
            scanf("%d",&b);
            if (b == 0)
            {
                break;
            
            }
        }
}


void printall(Node* f){
	for(int i = 0; i < N; i++)
	{
		printf("%d) %s\t%d\t%s\t%s\n", i+1, f->data.Name, f->data.Nomerotdela, f->data.Position, f->data.BTDate);
        f = f->next;      
	}
}


void print_record(Data *data, int i) {
	printf("%d) %s\t%d\t%s\t%s\n", i , data->Name, data->Nomerotdela, data->Position, data->BTDate);
}


int bin_search(Data *arr[], int key) {
    int l = 0;
    int r = N - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (arr[m]->Nomerotdela < key) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    if (arr[r]->Nomerotdela == key) {
        return r;
    }
    return -1;
}


void search(Data *arr[], int &ind) {
    int key;
    cout<<"Input search key Nomerotdela"<<'\n';
    cin>>key;
    ind = bin_search(arr, key);
    if (ind == -1) {
        cout << "Not found\n";
    } else {
        int i;
        for (i = ind; i < 4000 && arr[i]->Nomerotdela == key; ++i) {
        	printf("%d) %s\t%d\t%s\t%s\n", i+1, arr[i]->Name, arr[i]->Nomerotdela, arr[i]->Position, arr[i]->BTDate);
        }
        
    }
    
}

void search2(Data *arr[], int &ind, int &n) {
    int key;
    cout<<"Input search key Nomerotdela"<<'\n';
    cin>>key;
    ind = bin_search(arr, key);
    if (ind == -1) {
        cout << "Not found\n";
    } else {
        int i;
        for (i = ind; i < 4000 && arr[i]->Nomerotdela == key; ++i) {
        	//printf("%d) %s\t%d\t%s\t%s\n", i+1, arr[i]->Name, arr[i]->Nomerotdela, arr[i]->Position, arr[i]->BTDate);
        }
        n = i - ind;
        
    }
    
}

struct Vertex {
    Data *record;
    int bal;
    Vertex* left;
    Vertex* right;

};

bool rost = false;

void RR(Vertex*& p) {//RR поворот 
    Vertex* q = p->right; 
    p->bal = 0;
    q->bal = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}


void LL(Vertex*& p) {//LL поворот
    Vertex* q = p->left; 
    p->bal = 0; 
    q->bal = 0; 
    p->left = q->right; 
    q->right = p; 
    p = q; 
} 


void RL(Vertex*& p) {//RL 
    Vertex* q = p->right;
    Vertex* r = q->left;
    if (r->bal < 0)
        p->bal = 1;
    else
        p->bal = 0;
    if (r->bal > 0)
        q->bal = -1;
    else
        q->bal = 0;
    r->bal = 0;
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
}


void LR(Vertex*& p) {//LR поворот это малый левый разворот
    Vertex* q = p->left;
    Vertex* r = q->right;
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
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}


void Add_AVL(Vertex*& p, Data *record) { 
    if (!p) {
        p = new Vertex{record, NULL, NULL, 0}; 
        rost = true; 
    }
    else if (strcomp(p->record->Name, record->Name) > 0) {
        Add_AVL(p->left, record); 
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
                if (p->left->bal < 0) {     
                    LL(p); 
            }
            else {  
                LR(p); 
                }
                rost = false; 
            }
        }
    }
    else if (strcomp(p->record->Name, record->Name) < 0) {
        Add_AVL(p->right, record); 
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
                if (p->right->bal > 0) { 
                    RR(p); 
                }
                else {
                    RL(p); 
                }
                rost = false; 
            }
        }       
    }
    else
    cout<<"Element already exists"<<endl;

}

void Obhod(Vertex *p, int &i) {//лево корень право
    if (p) {
    Obhod(p->left, i);
    print_record(p->record, i++);
    Obhod(p->right, i);
    }
}



void SearchInTree(Vertex *root, const string &key ,int &i) {
    if (root) {
        if (strcomp(root->record->Name, key.c_str(), key.size()) > 0) {       	
            SearchInTree(root->left, key, i);      
        } else if (strcomp(root->record->Name ,key.c_str(), key.size()) < 0) {
            SearchInTree(root->right, key, i);
        }  else {		          
           print_record(root->record, i++);
       }
	}
}

void deletee(Vertex *root) {
    if (root) {
        deletee(root->right);
        deletee(root->left);
        delete root;
    }
}

void tree(Data *arr[], int n) {
    Vertex *root = nullptr;

    for (int i = 0; i < n; ++i) {
       Add_AVL(root, arr[i]);
    }
    int i = 1;
    Obhod(root, i);
    string key;
    do {
        getline(cin, key);
        if (!key.empty() && key != "q") {
            i = 1;
            SearchInTree(root, key, i);
        }
        cout << "Input search key (Department Number), q - exit\n> ";
    } while (key[0] != 'q');

    deletee(root);
}



void GilbertMura(const int n, double p[], int Length[], char c[][20]) {
    double *q = new double[n];
    Length[0] = -floor(log2(p[0])) + 1;
    q[0] = p[0] / 2;
    for (int i = 1; i < n; ++i) {
        double tmp = 0;
        for (int k = 0; k < i; k++)
            tmp += p[k];

        q[i] = tmp + p[i] / 2;
        Length[i] = -floor(log2(p[i])) + 1;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < Length[i]; ++j) {
            q[i] *= 2;
            c[i][j] = floor(q[i]) + '0';
            if (q[i] >= 1) {
                q[i] -= 1;
            }
        }

    }
}



unordered_map<char, int> get_char_counts_from_file(const string &file_name, int &file_size, int n = N) {
    ifstream file(file_name, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }
    char ch_arr[sizeof(Data) * n];
    file.read((char *) ch_arr, sizeof(Data) * n);
    file.close();

    unordered_map<char, int> counter_map;
    file_size = 0;
    for (auto ch : ch_arr) {
        counter_map[ch]++;
        file_size++;
    }
    return counter_map;
}





vector<pair<double, char>> calc_probabilities(const unordered_map<char, int> &counter_map, int count) {
    vector<pair<double, char>> probabilities;
    probabilities.reserve(counter_map.size());
    for (auto i : counter_map) {
        probabilities.emplace_back(make_pair((double) i.second / count, i.first));
    }
    return probabilities;
}

bool Predicate(pair<double, char> x,pair<double, char> y){//
	if(x.first > y.first){
		return true;
	}
	else
		return false;
}


void coding() {
    int file_size;
    unordered_map<char, int> counter_map;
    counter_map = get_char_counts_from_file("testBase2.dat", file_size);//подсчет повторений

    auto probabilities = calc_probabilities(counter_map, file_size);//подсчет вероятностей
    counter_map.clear();

    sort(probabilities.begin(), probabilities.end(), Predicate);//сортировка по вероятностям от большего к меньшему
    cout << "Probabil.  char\n";
    for (auto i : probabilities) {
        cout << fixed << i.first << " | " << i.second << '\n';// i.first - вероятность i.second - буква
    }

    const int n = (int) probabilities.size();

    auto c = new char[n][20];//код из 0 1 
    auto Length = new int[n];//длина каждого кода
    auto p = new double[n];//вероятности 
    for (int i = 0; i < n; ++i) {
        p[i] = probabilities[i].first; 
    }

    double shen = 0;
    GilbertMura(n, p, Length, c); // получение кодов символов
    cout << "\nMur Code:\n";
    cout << "\nCh  Prob      Code\n";
    double avg_len = 0;
    double entropy = 0;
    for (int i = 0; i < n; i++) {
        avg_len += Length[i] * p[i];
        entropy -= p[i] * log2(p[i]);
        printf("%c | %.5lf | ", probabilities[i].second, p[i]);
        for (int j = 0; j < Length[i]; ++j) {
            printf("%c", c[i][j]);
        }
        cout << '\n';
        shen += p[i];
    }
    cout << "Average length = " << avg_len << '\n'
         << "Entropy = " << entropy << '\n'
         << "Average length < entropy + 2\n"
         << "N = " << n << endl;
}


int main() {	
    SetConsoleCP(1280);
    SetConsoleOutputCP(1280);
    FILE* inputfile;   
    inputfile = fopen("testBase2.dat", "rb"); 
    Node* head = new Node;
    Node* p = head;


    for (int i = 0; i < N; i++)
    {
        p->data = *(new Data);
        fread(&(p->data), sizeof(Data), 1, inputfile);
	if (i != N - 1)
        {
            p->next = new Node;
            p = p->next;
        }
        else
        {
            p->next = NULL;
        }
    }
    p = head;
    int nabor = 0;
    int search_n = -1;
	int search_ind;
	while(true){
    printf("Vse elementu (1)\n");
    printf("20 elementov (2)\n");
    printf("Search (3)\n");
    printf("AVL tree (4)\n");
    printf("Coding (5)\n");
    printf("Exit(6)\n");
    scanf("%d", &nabor);
    if(nabor == 1){
    	digitalSort(p);
    	printall(p);
	}
	
	if(nabor == 2){
			printf("\nPress 1 to display 20 items \n");
    		scanf("%d", &nabor); 
    		digitalSort(p);
			print(p);
    	}
    	
	if(nabor == 3){		
		auto arr = new Data*[N];
		digitalSort(head);
		make_index_array(arr, head);
		search(arr, search_ind);
		delete[] arr;				
	}
	
	if(nabor == 4){		
		auto arr = new Data*[N];
		digitalSort(head);
		make_index_array(arr, head);
		search2(arr, search_ind, search_n);
		tree(&arr[search_ind], search_n);     
		delete[] arr;     
	}
	
	if(nabor == 5){
	coding();	
	}
	
	if(nabor == 6){
		break;
	}
    }
	
    Node* j = p;
    
    while(p != NULL){
    	p = p->next;
    	delete j;
    	j = p;
	}	
		
    return 0;
    
}
	



