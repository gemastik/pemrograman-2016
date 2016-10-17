#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

class node{
private:
	vector<node*> adj;

public:
	int dp[2][2];
	void add_child(node *c){
		adj.push_back(c);
	}

	node(){
		memset(dp,-1,sizeof dp);
	}

	int size(){
		return adj.size();
	}

	node* get(int id){
		return adj[id];
	}
};

node** all_node;


int dfs(node* pos,node* par,int state,int state_par){
	if (pos->dp[state][state_par] != -1)
		return pos->dp[state][state_par];

	int &tmp = pos->dp[state][state_par];
	tmp = 0;
	int anak = pos->size();
	int reverse_gap = 0;
	for (int i=0;i<anak;i++){
		if (par == pos->get(i))
			continue;
		int reverse = (state^1) + dfs(pos->get(i) , pos, state^1,state);
		tmp += reverse;
		int same = state + dfs(pos->get(i) , pos, state,state);
		if (state != state_par)
			reverse_gap = max(reverse_gap, reverse - same);
	}
	tmp -= reverse_gap;
	return tmp;
}

int main() {
	int N,T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		all_node = new node*[N];

		for (int i=0;i<N;i++){
			all_node[i] = new node();
		}

		for (int i=1;i<N;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			a--;
			b--;
			all_node[a]->add_child(all_node[b]);
			all_node[b]->add_child(all_node[a]);
		}
		if (N == 3)
			cout<<1<<endl;
		else if(N < 3)
			cout<<0<<endl;
		else
			cout<<min(min(dfs(all_node[0],0,0,0) , dfs(all_node[0],0,0,1)) ,1 + min(dfs(all_node[0],0,1,0) , dfs(all_node[0],0,1,1)) )<<endl;
		delete[] all_node;
	}
}