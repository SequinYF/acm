/********************************************************************
 * File Name: Knights_of_the_round_table.cpp
 * Author: Sequin
 * mail: Catherine199787@outlook.com
 * Created Time: 五  9/22 18:01:36 2017
 *************************************************************************/


#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <queue>
#include <map>
#include <ctype.h>
#include <set>
#include <vector>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <climits>
#include <string>
#include <list>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

#define lson 2*i
#define rson 2*i+1
#define LS l,mid,lson
#define RS mid+1,r,rson
#define UP(i,x,y) for(i=x;i<=y;i++)
#define DOWN(i,x,y) for(i=x;i>=y;i--)
#define MEM(a,x) memset(a,x,sizeof(a))
#define W(a) while(a)
#define gcd(a,b) __gcd(a,b)
#define pi acos(-1.0)
#define pii pair<int,int>
#define ll long long
#define MAX 10000005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define lowbit(x) (x&-x)
#define maxn 1002
ll qpow(ll p,ll q){ll f=1;while(q){if(q&1)f=f*p;p=p*p;q>>=1;}return f;}

struct Edge{
    int u, v;
};

int odd[maxn];
int color[maxn];
int pre[maxn], iscut[maxn], bccno[maxn], dfs_clock, bcc_cnt;
vector<int> G[maxn], bcc[maxn];
stack<Edge> S;

bool bipartite(int u, int b) {
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(bccno[v] != b) {
            continue;
        }

        if(color[v] == color[u]) {
            return false;
        }

        if(!color[v]) {
            color[v] = 3 - color[u];
            if(!bipartite(v, b)) {
                return false;
            }
        }
    }
    return true;
}


int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        Edge e = (Edge) {u, v};

        if(!pre[v]) {
            S.push(e);
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) {
                iscut[u] = true;
                bcc_cnt++;
                bcc[bcc_cnt].clear();

                W(true) {
                    Edge x = S.top();
                    S.pop();

                    if(bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if(bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }

                    if(x.u == u && x.v == v) {
                        break;
                    }
                }
            }
        }

        else if(pre[v] < pre[u] && v != fa) {
            S.push(e);
            lowu = min(lowu, pre[v]);
        }
    }

    if(fa < 0 && child == 1) {
        iscut[u] = 0;
    }
    return lowu;
}




void find_bcc(int n) {
    MEM(pre, 0);
    MEM(iscut, 0);
    MEM(bccno, 0);

    for(int i = 1; i <= n; i++) {
        if(!pre[i]) {
            dfs(i, -1);
        }
    }
}

int mm[maxn][maxn];

int main() {
    std::ios::sync_with_stdio(false);
    int n ,m;
    while(cin >> n >> m && n + m) {

        for(int i = 1; i <= n; i++) {
            G[i].clear();
        }

        MEM(mm, 0);
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            mm[a][b] = 1;
            mm[b][a] = 1;
        }

        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                if(!mm[i][j]) {
                    G[i].push_back(j);
                    G[j].push_back(i);
                }
            }
        }

        dfs_clock = 0;
        bcc_cnt = 0;
        find_bcc(n);
        MEM(odd, 0);

        for(int i = 1; i <= bcc_cnt; i++) {
            MEM(color, 0);
            for(int j = 0; j < bcc[i].size(); j++) {
                bccno[bcc[i][j]] = i;
            }

            int u = bcc[i][0];
            color[u] = 1;
            if(!bipartite(u, i)) {
                for(int j = 0; j < bcc[i].size(); j++) {
                    odd[bcc[i][j]] = 1;
                }
            }
        }

        int ret = n;
        for(int i = 1; i <= n; i++) {
            if(odd[i]) {
                ret--;
            }
        }

        cout << ret << endl;

    }
}
