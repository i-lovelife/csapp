#include<bits/stdc++.h>
using namespace std;
const int Maxn = 800002;
char s[Maxn];
int n;
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d", &n);
        scanf("%s", s);
        char bef = 'F';
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != 'F' && s[i] != bef && bef != 'F') {
                ans++;
            }
            if (s[i] != 'F') {
                bef = s[i];
            }
        }
        printf("%d\n", ans);
    }
}