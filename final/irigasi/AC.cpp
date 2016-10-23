/*#include <iostream>
#include <set>
#include <vector>*/
#include <bits/stdc++.h>
using namespace std;

struct node
{
  vector<int> edges;
  int depth;
  int par;
  int fmap;
};
struct dat
{
  int d,n;
};
struct cmp
{
  bool operator ()(dat a, dat b)
  {
    if (a.d!=b.d) return a.d>b.d;
    return a.n<b.n;
  }
};
int TC,V,K;
node nodes[300001];
bool used[300001];
int invmap[300001];
set<dat,cmp> st;
int gctr;

void dfs1(int x, int p, int d)
{
  int sz = nodes[x].edges.size();
  nodes[x].depth = d;
  nodes[x].par = p;
  for (int i = 0; i < sz; i++)
  {
    int t = nodes[x].edges[i];
    if (t==p) continue;
    dfs1(t,x,d+1);
  }
  nodes[x].fmap = gctr;
  invmap[gctr++] = x;
  return;
}
void dfs2(int x, int p, int d, int md)
{
  int sz = nodes[x].edges.size();
  /*dat td;
  td.n = x;
  td.d = nodes[x].depth;
  st.erase(td);*/
  used[nodes[x].fmap] = true;

  if (d==md) return;
  for (int i = 0; i < sz; i++)
  {
    int t = nodes[x].edges[i];
    if (t==p) continue;
    dfs2(t,x,d+1,md);
  }
  return;
}

bool test(int mt)
{
  //st.clear();
  for (int i = 0; i < V; i++)
  {
    /*dat td;
    td.n = i;
    td.d = nodes[i].depth;
    st.insert(td);*/
    used[i] = false;
  }
  int ctr = 0;
  for (int i = 0; i < V; i++)
  {
    if (used[i]) continue;
    ctr++;
    if (ctr>K) return false;
    int t = invmap[i];
    for (int i = 0; i < mt; i++)
    {
      if (nodes[t].par==-1) break;
      t = nodes[t].par;
    }
    dfs2(t,-1,0,mt);
  }
  return true;
}

int main ()
{
  scanf("%d", &TC);
  //TC = 1;
  for (int tc = 0; tc < TC; tc++)
  {
    scanf("%d%d", &V,&K);
    gctr = 0;
    for (int i = 0; i < V; i++)
    {
      nodes[i].edges.clear();
    }
    for (int i = 0; i < V-1; i++)
    {
      int t1,t2;
      scanf("%d%d",&t1,&t2);
      t1--;
      t2--;
      nodes[t1].edges.push_back(t2);
      nodes[t2].edges.push_back(t1);
    }
    if (V==K)
    {
      printf("0\n");
      continue;
    }

    dfs1(0,-1,0);
    int l = 0,r = V;
    while (l<r-1) //l impossible, r possible
    {
      int m = (l+r)/2;
      if (test(m))
      {
        r = m;
      } else {
        l = m;
      }
    }
    printf("%d\n", r);
  }
  return 0;
}
