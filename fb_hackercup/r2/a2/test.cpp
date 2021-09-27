#include<bits/stdc++.h>
using namespace std;
const int Maxn = 800002;
const int M = 1e9 + 7;
char s[Maxn];
int n;
void mod_add(int &x, int y) {
    x += y;
    if (x >= M) x -= M;
}
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d", &n);
        scanf("%s", s);
        char bef = 'F';
        int ans = 0;
        int ans_last = 0;
        int last_non_f_ch = -1;
        for (int i = 0; i < n; i++) {
            bool change = false;
            if (s[i] != 'F' && s[i] != bef && bef != 'F') {
                change = true;
            }
            if (s[i] != 'F') {
                bef = s[i];
            }
            if (change) {
                mod_add(ans_last, (last_non_f_ch + 1) % M);
            }
            mod_add(ans, ans_last);
            if (s[i] != 'F') {
                last_non_f_ch = i;
            }
        }
        printf("%d\n", ans);
    }
}