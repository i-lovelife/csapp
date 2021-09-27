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
struct Mat {
    static const int SZ = 4;
    int a[SZ][SZ];
    Mat() {
        for (int i = 0; i < SZ; i++) {
            for (int j = 0; j < SZ; j++) {
                a[i][j] = 0;
            }
        }
    }
    Mat operator* (const Mat& rhs) {
        Mat ret;
        for (int i = 0; i < SZ; i++) {
            for (int j = 0; j < SZ; j++) {
                for (int k = 0; k < SZ; k++) {
                    mod_add(ret.a[i][j], 1LL*this->a[i][k]*rhs.a[k][j]%M); 
                }
            }
        }
        return ret;
    }
    void pt() {
        for (int i = 0; i < SZ; i++){
            for (int j = 0; j < SZ; j++){
                printf("%d ",a[i][j]);
            }
            puts("");
        }
    }
};
//XOX
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d", &n);
        scanf("%s", s);
        int ans = 0;
        Mat cur0, cur1;
        cur0.a[0][0] = cur0.a[1][1] = cur0.a[2][2] = cur0.a[3][3] = 1;
        cur1.a[0][0] = cur1.a[1][1] = cur1.a[2][2] = cur1.a[3][3] = 1;
        int cur_len = 0;
        int last_non_f = -1;
        int first_non_f = -1;
        int prefixF = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '.') {
                // puts("inside .");
                // puts("cur0=");
                // cur0.pt();
                // puts("cur1=");
                // cur1.pt();
                // putchar(s[last_non_f]);
                if (first_non_f >= 0) {
                    int delta0 = (cur_len - cur0.a[3][2] + M)%M;
                    int delta1 = (cur_len - cur1.a[3][2] + M)%M;
                    Mat temp0;
                    temp0.a[0][0] = temp0.a[1][1] = temp0.a[2][2] = temp0.a[3][3] = 1;
                    temp0.a[3][2] = delta0;
                    if (s[last_non_f] != s[first_non_f]) {
                        temp0.a[3][1] = (M - delta0)%M;
                        temp0.a[3][0] = 1LL * prefixF * delta0 %M;
                    } 
                    
                    Mat temp1;
                    temp1.a[0][0] = temp1.a[1][1] = temp1.a[2][2] = temp1.a[3][3] = 1;
                    temp1.a[3][2] = (cur_len - cur1.a[3][2] + M)%M;
                    if (s[last_non_f] != s[first_non_f]) {
                        temp1.a[3][1] = (cur1.a[3][2] - cur_len + M)%M;
                        temp1.a[3][0] = 1LL * prefixF * delta1 %M;
                    }
                    if (s[last_non_f] == 'X') {//'X':0, 'O':1
                        cur1 = cur1 * temp1 * cur0;
                        cur0 = cur0 * temp0 * cur0;
                    }
                    else {
                        cur0 = cur0 * temp0 * cur1;
                        cur1 = cur1 * temp1 * cur1;
                    }
                }
                else {
                    cur0 = cur0 * cur0;
                    cur1 = cur1 * cur1;
                    prefixF = (prefixF + prefixF)%M;
                }
                cur_len = cur_len * 2 % M;
                // puts("outside .");
            }
            else {
                Mat temp;
                temp.a[0][0] = temp.a[1][1] = temp.a[2][2] = temp.a[3][3] = 1;
                temp.a[1][0] = 1;
                if (s[i] == 'F') {
                    cur0 = cur0 * temp;
                    cur1 = cur1 * temp;
                    if (first_non_f < 0) {
                        prefixF = (prefixF + 1)%M;
                    }
                }
                else { // 'X' or 'O'
                    if (first_non_f < 0) {
                        // calculate cur0
                        temp.a[2][1] = temp.a[2][0] = s[i] == 'X' ? 0 : 1;
                        temp.a[3][2] = (cur_len + 1 - cur0.a[3][2] + M)%M;
                        cur0 = cur0 * temp;
                        temp.a[2][1] = temp.a[2][0] = s[i] == 'O' ? 0 : 1;
                        temp.a[3][2] = (cur_len + 1 - cur1.a[3][2] + M)%M;
                        cur1 = cur1 * temp;
                    }
                    else {
                        if (s[last_non_f] != s[i]) {
                            temp.a[2][1] = temp.a[2][0] = 1;
                            temp.a[3][2] = (cur_len + 1 - cur0.a[3][2] + M)%M;
                            cur0 = cur0 * temp;
                            temp.a[3][2] = (cur_len + 1 - cur1.a[3][2] + M)%M;
                            cur1 = cur1 * temp;
                        }
                        else {
                            temp.a[3][2] = (cur_len + 1 - cur0.a[3][2] + M)%M;
                            cur0 = cur0 * temp;
                            temp.a[3][2] = (cur_len + 1 - cur1.a[3][2] + M)%M;
                            cur1 = cur1 * temp;
                        }
                    }
                    last_non_f = i;
                    if (first_non_f < 0) {
                        first_non_f = i;
                    }
                }
                mod_add(cur_len, 1);
            }
            // printf("i=%d\n",i);
            // puts("cur0=");
            // cur0.pt();
            // puts("cur1=");
            // cur1.pt();
        }
        if (first_non_f < 0) ans = 0;
        else if (s[first_non_f] == 'X') ans = cur0.a[3][0];
        else ans = cur1.a[3][0];
        printf("%d\n", ans);
    }
}