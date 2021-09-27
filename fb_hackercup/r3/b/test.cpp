#include<bits/stdc++.h>
using namespace std;
const int Maxn = 800002;
int n, m;
vector<int>G[Maxn];
int h[Maxn];
int f[Maxn][21];
int frac[Maxn];
int first[Maxn],val[Maxn];
void dfs(int cur, int fa) {
    h[cur] = h[fa] + 1;
    f[cur][0] = fa;
    for (auto v:G[cur]) {
        if (v != fa) {
            dfs(v, cur);
        }
    }
}
void dfs2(int cur, int fa){
    for(auto v:G[cur]) {
        if(v != fa) {
            dfs2(v, cur);
            val[cur] += val[v];
        }
    }
}
int get_lca(int u, int v) {
    if (h[u] > h[v]) {
        swap(u,v);
    }
    int req = 0;
    while((1<<req) <= n) req++;
    req--;
    int delta = h[v] - h[u];
    for (int i = 0; i <= req; i++) {
        if (delta>>i&1){
            v = f[v][i];
        }
    }
    for (int i=req;i>=0;i--){
        if(f[u][i]!=f[v][i]){
            u = f[u][i];
            v = f[v][i];
        }
    }
    return u==v?u:f[u][0];
}
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d", &n);
        for(int i =1;i<=n;i++)G[i].clear();
        for(int i =1;i<=n;i++)first[i]=-1,val[i]=0;
        for (int i = 0; i < n - 1; i++){
            int u,v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        //puts("start");
        dfs(1, 0);
        //puts("ok0");
        for (int i = 0; (1<<(i+1)) <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[j][i+1] = f[f[j][i]][i];
            }
        }
        //puts("ok1");
        for(int i=1;i<=n;i++)scanf("%d",frac+i);
        //for(int i =1;i<=n;i++)printf("%d ",frac[i]);puts("");
        for(int i=1;i<=n;i++) {
            if(first[frac[i]] < 0) {
                first[frac[i]] = i;
            }
            else {
                int u = i;
                int v = first[frac[i]];
                int lca=get_lca(u,v);
                val[u]++;
                val[v]++;
                val[lca]-=2;
                // printf("u=%d v=%d lca=%d frac=%d frac=%d\n",u,v,lca,frac[u],frac[v]);
            }
        }
        //puts("ok2");
        
        // for(int i=1;i<=n;i++)printf("%d ", val[i]);puts("");
        dfs2(1, 0);
        //puts("ok3");
        int ans = 0;
        for(int i=1;i<=n;i++) {
            if(i!=1&&val[i]==0){
                ans++;
            }
        }
        // for(int i=1;i<=n;i++)printf("%d ", val[i]);puts("");
        printf("%d\n",ans);
    }
}