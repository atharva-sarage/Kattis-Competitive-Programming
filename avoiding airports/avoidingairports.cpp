/******************************************
*    AUTHOR:         Atharva Sarage       *
*    INSTITUITION:   IIT HYDERABAD        *
******************************************/
#include<bits/stdc++.h>
#warning Check Max_Limit,Overflows
using namespace std;
# define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
# define ff first
# define ss second
# define pb push_back
# define mod 1000000007
# define ll long long 
# define db double
# define mx2 100005
# define mx 200005
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
LineContainer airport[mx];
ll dp[mx];
pair<ll,ll> edge[mx];
vector <pair<pair<ll,ll>,ll>> vec;
set <pair<ll,pair<ll,Line>>> process;
int main()
{
	ll n,m;
	cin>>n>>m;
	for(ll i=1;i<=n;i++)
		dp[i]=LLONG_MAX;
	for(ll i=0;i<m;i++)
	{
		ll a,b,s,e;
		cin>>a>>b>>s>>e;
		edge[i]={a,b};
		vec.pb({{s,e},i});
	}
	sort(vec.begin(),vec.end());
	airport[1].add(0,0);
	for(auto p:vec)
	{
		// how much we waited before taking this edge
		ll u=edge[p.ss].ff;
		ll v=edge[p.ss].ss;
		ll temp=LLONG_MAX;
		while(!process.empty())
		{
			auto m=*(process.begin());
			if(m.ff<p.ff.ff)
			{
				airport[m.ss.ff].add(m.ss.ss.k,m.ss.ss.m);
				process.erase(process.begin());
			}
			else
				break;			
		}
		if(!airport[u].empty())
		{
			temp=p.ff.ff*p.ff.ff-airport[u].query(p.ff.ff);
			Line l={2*p.ff.ss,-(temp+p.ff.ss*p.ff.ss)};
			process.insert({p.ff.ss,{v,l}});			
		}		
		dp[v]=min(dp[v],temp);
	}
	cout<<dp[n]<<endl;
}