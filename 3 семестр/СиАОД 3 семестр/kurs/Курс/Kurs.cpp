#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class String {
protected:
	char* str;
	int size;
public:
	String(){
		str = nullptr;
		size = 0;
	}
	
	String(const char* L){
	size = strlen(L);
	str = new char[size];
	for(int i = 0; i < size; i++){
		str[i] = L[i];
		}	
	}
	
	String(const String&Other){
		size = Other.size;
		str = new char[size];
		for(int i = 0; i < size; i++){
			str[i] = Other.str[i];
		}
	}
	
	String(String&&Other){
		size = Other.size;
		Other.size = 0;
		str = Other.str;
		Other.str = nullptr;
	}
	
	String operator = (const String&Other){
	
		if(this == &Other){
			return *this;
		}
		size = Other.size;
		str = new char[size];
		for(int i = 0; i < size; i++){
		str[i] = Other.str[i];
		}
		return *this; 
	}
	
	~String(){
		clear();
	}
	
	void clear(){
		size = 0;
		delete[] str;
		str = nullptr;
	}
	
	char & operator[](int i){

		if(i >= size||i < 0){
			throw "invalid index";	
		}                    
		return str[i];
	}	
	
	
	int Size() const{
		return size;
	}
	
	const char* c_str() const{
		return str;
	}
	
	void Show() const;				
};



ostream& operator << (ostream &os, String &p)
{
	for(int i = 0; i < p.Size(); i++){
	os << p[i];
	}
	return os;
}

istream& operator >> (istream &in, String &s)
{
    char *buf = new char[100001];
//	getline(buf, in);
	in >> buf;
	String str(buf);
	s = str;
	return in;    
}

String operator + (String lhs, String rhs)
{
	char* p = new char[lhs.Size() + rhs.Size()];
	for(int i = 0; i < lhs.Size(); i++){
		p[i] = lhs[i];		
	}
	for(int i = 0; i < rhs.Size(); i++){
		p[lhs.Size() + i] = rhs[i];
	}
	String h(p);
	delete[] p;
	return h;
}


bool operator == (String lhs, String rhs)
{
	if(lhs.Size() != rhs.Size()){
		return false;
	}
	for(int i = 0; i < lhs.Size(); i++){
		if(lhs[i] != rhs[i]){
			return false;
		}		
	}
	return true;
}


bool operator != (String lhs, String rhs)
{
	return !(lhs==rhs);
}

class ConsoleString:public String{
	public:	
		
	ConsoleString():String(){
	}
	
	ConsoleString(const char* L):String(L){	
	}
	
	ConsoleString(const String&Other):String(Other){
	}
	
	ConsoleString(String&&Other):String(Other){
	}
	
			
		void Show() const{
				for(int i = 0; i < Size(); i++){
				cout << str[i];
				}	
		}
				
};

class FileString:public String{
	private:
		const char* filename;
	public:	
		
	FileString():String(){
	}
	
	FileString(const char* L):String(L){	
	}
	
	FileString(const String&Other):String(Other){
	}
	
	FileString(String&&Other):String(Other){
	}
	
	void SetFileName(const char * p){
		filename = p;		
	}
			
		void Show() const{	
			ofstream file(filename);
				for(int i = 0; i < Size(); i++){
				file << str[i];
				}
				file.close();	
		}
				
};

int main(){		
ConsoleString text("hello");
text.Show();
FileString text1("hello");
text1.SetFileName("TEXT.txt");
text1.Show();
cout<<text;
//	try{
//		String text("hello");
//		String text1(" world");	
//		String text3(text + text1);
//		String text4("hello");
//		int ind;
//		cout << "Enter index of string " << text << endl;
//		cin >> ind;
//		cout << text[ind];		
//		cout << endl;
//		cout << (text == text1) << endl;
//		cout << (text != text1) << endl;
//		cout << (text == text4) << endl;
//		cout << (text != text4) << endl;
//		cout << text3 << endl;
//		cout << "Enter string" << endl;
//		String text5;
//	    cin >> text5;
//	    cout << text5;		
//	}
//	catch(const char* str){
//		cout << str << endl; 
//	}
//	catch(...){
//	cout << "Error" << endl; 
//	}
	
	
}