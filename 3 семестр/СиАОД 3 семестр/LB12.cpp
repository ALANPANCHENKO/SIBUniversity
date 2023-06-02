#include <iostream>
#include <iomanip>

using namespace std;

struct cod{
	char c;
	double chance;
	int code[10];
};

void out_float(float f)
{
  size_t size = sizeof(f);
  unsigned char * p = (unsigned char *) &f;
  p += size-1;
  while (size--)
  {
    int n;
    for (n=0; n<8; n++)
    {
      putchar('0' + (*p & 128 ? 1 : 0));
      *p <<= 1;
    }
    p--;
  }
}
		

double coding(cod *sym,double *Q,FILE *file,int n,int sz)
{
	double *l=new double[sz];
	double *h=new double[sz];
	double *r=new double[sz];
	
	l[0]=0.0;
	r[0]=1.0;
	h[0]=1.0;
	int i=0,m=1;
	char c;
	while(!feof(file))
	{
		c=fgetc(file);
		if(c==EOF)
			break;
		//cout<<c;
		i++;
		for(int j=0;j<n;j++)
		{
			if(c==sym[j].c)//для определения порядкового номера
			{
				m=j+1;
			}
		}
		cout<<c<<" :"<<m<<endl;
		l[i]=l[i-1]+r[i-1]*Q[m-1];
		h[i]=l[i-1]+r[i-1]*Q[m];
		r[i]=h[i]-l[i];
		cout << setiosflags(ios::fixed);
		cout<<setprecision(5)<<" "<<l[i]<<" "<<h[i]<<" "<<r[i]<<endl;
		
	}
	cout<<setprecision(5)<<l[i]<<" "<<h[i]<<" "<<r[i]<<endl;
	cout<<setprecision(8)<<l[i]<<endl;
	out_float(l[i]);
	return l[i];
	
		
}



int main()
{
	int n=4,j=0,k=1;
	int symbols[127];
	cod sym[n];
	char c=0;
	double *Q=new double[n];
	Q[0]=0.0;
	FILE *file=fopen("read.txt","r");
	fseek(file, 0L, SEEK_END);       
	int sz = ftell(file);
	rewind(file);
	for(int i=0;i<127;i++)
	{
		symbols[i]=0;
	}
	while(!feof(file))
	{
		c=fgetc(file);
		symbols[(int)c]++;
	}
	for(int i=0;i<127;i++)
	{
		if(symbols[i]>0)
		{
			sym[j].c=(char)i;
			sym[j].chance=(double)symbols[i]/sz;
			
			Q[k]=Q[k-1]+sym[j].chance;
			
			j++;
			k++;
		}
	}

	rewind(file);
	coding(sym,Q,file,n,sz);
	//out_float(num_for_code);
	
}
