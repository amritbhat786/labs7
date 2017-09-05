#include <stdio.h>
#include <iostream>

using namespace std;

struct node
{
	int dist[20];
	int from[20];
}rt[10];

int main()
{
	int dm[20][20];
	int i,j,k,n,src,dest,cnt=0;
	cout<<"Enter no. of nodes:"<<endl;
	cin>>n;
	cout<<"Distance matrix:"<<endl;
	for(i=0;i<n;i++)
		//dm[i][i]=0;
		for(j=0;j<n;j++)
		{
			cin>>dm[i][j];
			dm[i][i]=0;
			rt[i].dist[j]=dm[i][j];
			rt[i].from[j]=j;
		}
	do
	{
		cnt=0;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(k=0;k<n;k++)
					if((rt[i].dist[j])>(dm[i][k]+rt[k].dist[j]))
					{
						rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
						rt[i].from[j]=k;
						cnt++;
					}
	}while(cnt!=0);
	for(i=0;i<n;i++)
	{
		cout<<"\nRouter info for router "<<i+1<<endl;
		cout<<"Dest\tNext Hop\tDist\n";
		for(j=0;j<n;j++)
			cout<<j+1<<"\t"<<rt[i].from[j]+1<<"\t\t"<<rt[i].dist[j]<<endl;
	}
	return 0;
}