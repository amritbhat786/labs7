#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
#define NOP 10

int rand(int a)
{
	int rn = (random()%10)%a;
	return rn==0?1:rn;
}

int main()
{
	int psz[NOP],i,clk,bsize,pszrm=0,p_time,orate,op;
	for(i=0;i<NOP;i++)
		psz[i]=rand(6)%10;
	for(i=0;i<NOP;i++)
		cout<<"packet("<<i<<"):"<<psz[i]<<" bytes\n";
	cout<<"Enter output rate:";
	cin>>orate;
	cout<<"Enter bucket size\n";
	cin>>bsize;
	for(i=0;i<NOP;i++)
	{
		if((psz[i]+pszrm)>bsize)
		{
			if(psz[i]>bsize)
				cout<<"Incoming packet is bigger than bucket size.Packet REJECTED"<<endl;
			else
				cout<<"Bucket capacity exceeded. PACKET REJECTED"<<endl;
		}
		else
		{
			pszrm+=psz[i];
			cout<<"Incoming Packet size:"<<psz[i]<<endl;
			cout<<"Bytes remaining to transmit:"<<pszrm<<endl;
			p_time= rand(4)%10;
			cout<<"Time left for transmission: "<<p_time<<endl;
			for(clk=1;clk<=p_time;clk+=1)
			{	//cout<<"Here";
				sleep(1);
				if(pszrm)
				{
					if(pszrm<orate)
					{
						op=pszrm;
						pszrm=0;
					}
					else
					{
						op=orate;
						pszrm-=orate;
						cout<<"Packet of size"<<op<<" transmitted\n";
						cout<<"Bytes remaining to transmit:"<<pszrm<<endl;
					}
				}
				else
				{
					cout<<"Time left for transmission "<<p_time<<" units\n";
					cout<<"No packets to transmit\n";
				}
			}
		}
		cout<<"\n";
	}
}

