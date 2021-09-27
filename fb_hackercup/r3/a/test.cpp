#include<bits/stdc++.h>
using namespace std;
const int Maxn = 1000002;
int n, m;
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d%d", &n, &m);
        int total = n * m;
        multiset<int>changed, unchanged;
        for (int i = 0; i < m; i++) {
            int x;
            scanf("%d", &x);
            unchanged.insert(x);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            multiset<int>cur;
            for (int i = 0; i < m; i++) {
                int x;
                scanf("%d", &x);
                cur.insert(x);
            }
            for (auto it=unchanged.begin();it!=unchanged.end();) {
                if (cur.find(*it) == cur.end()) {
                    unchanged.erase(it++);
                }
                else {
                    cur.erase(cur.find(*it));
                    it++;
                }
            }
            for (auto it = cur.begin();it!=cur.end();it++){
                changed.insert(*it);
            }
        }
        printf("%d\n", ans);
    }
}