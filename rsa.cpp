#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;

long int i,e,d,n,p,q,phi,cipher[50];

int encrypt(char ch);
char decrypt(long int ch);
int gcd(long int a,long int b);
int prime(int a);
int main()
{
	int i,len;
	char text[50];
	cout<<"\nEnter the text to be encrypted :";
	cin>>text;
	len=strlen(text);
	do
	{
		p=rand()%30;
	}while(!(prime(p)));
	do
	{
		q=rand()%30;
	}while(!(prime(q)));
	n=p*q;
	phi = (p-1)*(q-1);
	do
	{
		e=rand()%phi;
	}while(gcd(e,phi)!=1);
	do
	{
		d=rand()%phi;
	}while((d*e)%phi!=1);

	cout<<"\n\n Two prime numbers (p and q):"<<p<<"and"<<q<<endl;
	cout<<"n(p*q) = "<<p<<"*"<<q<<endl;
	cout<<"phi = "<<phi<<endl;
	cout<<"Public Key (n,e):("<<n<<","<<e<<")\n";
	cout<<"Private Key (phi,d):("<<phi<<","<<d<<")\n";

	for(i=0;i<len;i++)
		cipher[i]=encrypt(text[i]);
	cout<<"\nEncrypted message: ";
	for(i=0;i<len;i++)
		cout<<cipher[i];

	for(i=0;i<len;i++)
		text[i]=decrypt(cipher[i]);
	text[i]='\0';
	cout<<"\nDecrypted message: "<<text<<endl;
	return 0;
}

int encrypt(char ch)
{
	long int temp=ch;
	for(i=1;i<e;i++)
		temp=(temp*ch)%n;
	return temp;
}

char decrypt(long int ch)
{
	long int temp=ch;
	for(i=1;i<d;i++)
		ch=(temp*ch)%n;
	return ch;
}
int prime(int a)
{
	for(i=2;i<a;i++)
		if((a%i)==0)
			return 0;
	return 1;
}
int gcd(long int a,long int b)
{
	if(a==0)return b;
	if(b==0)return a;
	return gcd(b,a%b);
}