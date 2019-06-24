#include<bits/stdc++.h>
# define mx 200005
typedef long long ll;
using namespace std;
ll  depth[mx];
ll  visited[mx];
ll  D;
vector<ll > adj[mx];
ll  par[30][mx];

void addedge(ll  x,ll  y)
{
	adj[x].push_back(y);
	adj[y].push_back(x);
}
ll  calc(ll  n)
{
	ll  count=-1;
	while(n>=1)
		{
			count++;
			n/=2;
		}
	return count;
}
ll  walk(ll  i,ll  k)
{
	for(ll  d=0;d<=D;d++)
	{
		if((k & 1<<d )>0)
			i=par[d][i];
	}
	return i;
}
ll  lca(ll  i,ll  j)
{
	if(depth[i]>depth[j])
		i=walk(i,depth[i]-depth[j]);
	if(depth[i]<depth[j])
		j=walk(j,depth[j]-depth[i]);
	if(i==j)
		{
			//prll f("##\n");
			return i;
		}

	for(ll  d=D;d>=0;d--)
	{
		if(par[d][i]!=par[d][j])
		{
			i=par[d][i];
			j=par[d][j];
		}
	}
	return par[0][i];
}
ll  dist(ll  i,ll  j)
{
	//prll f("%d***\n",lca(i,j) );
	return depth[i]+depth[j]-2*depth[lca(i,j)];
}
int  main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(visited,false,sizeof(visited));
	memset(depth,0,sizeof(depth));
	memset(par,-1,sizeof(par));
	ll  n;
	cin>>n;
	D=calc(n);
	D=D+2;

	for(ll  i=0;i<n-1;i++)
	{
		ll  x,y;
		cin>>x>>y;
		x--;y--;
		addedge(x,y);
	}
	queue <ll > q;
	q.push(0);
	visited[0]=true;
	depth[0]=0;
	while(!q.empty())
	{
		ll  u=q.front();
		visited[u]=true;
		q.pop();
		for(ll  i=0;i<adj[u].size();i++)
		{
			ll  v=adj[u][i];
			if(!visited[v])
			{
				depth[v]=depth[u]+1;
				par[0][v]=u;
				q.push(v);
			}
		}
	}

	// compute parent table
			for(ll  d=1;d<=D;d++)
			{
				for(int i=0;i<n;i++)
			{ 
				ll  mid=par[d-1][i];
				if(mid!=-1)
				par[d][i]=par[d-1][mid];
			}
	
	}
	ll sum1=0;
	for(ll  i=1;i<=n;i++)
	{

		for(ll  j=2*i;j<=n;j+=i)
		{
			ll  i1=i;
			ll  j1=j;
			i1--;j1--;			
			sum1+=(dist(i1,j1)+1);			
		}
	}
	cout<<sum1<<endl;

}
