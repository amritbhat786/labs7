#include <iostream>
#include<string.h>
using namespace std;

//int mode =1;

int crc(char in[],char out[],const char gp[],int mode)
{
	int j,k;
	strcpy(out,in);
	if(mode)
	{
		for(j=1;j<strlen(gp);j++)
			strcat(out,"0");
	}
	for(j=0;j<strlen(in);j++)
	{
		if(out[j]=='1')
			for(k=0;k<strlen(gp);k++)
			{
				if((*(out+j+k)=='0' && (gp[k]=='0'))||(*(out+j+k)=='1' && (gp[k]=='1')))
					*(out+j+k)='0';
				else
					*(out+j+k)='1';
			}
	}
	for(j=0;j<strlen(out);j++)
	{
		if(out[j]=='1')
			return 1;
	}
return 0;
} 

int main()
{
char in[50],out[50],rec[50];
const char gp[18]="10001000000100001";
cout<<"\nEnter the input message in binary";
cin>>in;
crc(in,out,gp,1);
cout<<"\nThe transmitted message is:"<<in<<out+strlen(in)<<endl;
cout<<"\n\nEnter the received message in binary\n";
cin>>rec;
if(!crc(rec,out,gp,0))
	cout<<"\nNo error in data\n";
else
	cout<<"\nError in data transmission has occured\n";
return 0;  
}

