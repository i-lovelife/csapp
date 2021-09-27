#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int Maxn=1000020;
int ori[Maxn], sx[Maxn], sy[Maxn];
int n, k;
void read_data(int* array) {
    int a, b, c, d;
    for (int i = 0; i < k; i++) {
        scanf("%d", array + i);
    }
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for(int i = k; i < n; i++) {
        array[i] = (1LL * a * array[i-2]%d + 1LL * b * array[i-1]%d + c) %d;
    }
}
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d%d", &n, &k);
        read_data(ori);
        read_data(sx);
        read_data(sy);
        LL rest_low = 0, rest_up = 0, require_low = 0, require_up = 0;
        for (int i = 0; i < n; i++) {
            LL low = sx[i];
            LL up = sy[i] + sx[i];
            if (ori[i] < low) {
                require_low += low - ori[i];
                rest_up += up - ori[i];
            }
            else if (ori[i] > up) {
                require_up += ori[i] - up;
                rest_low += ori[i] - low;
            }
            else {
                rest_low += ori[i] - low;
                rest_up += up - ori[i];
            }
        }
        LL ans = max(require_low, require_up);
        if (require_low < require_up) {
            if (require_up > rest_up) {
                ans = -1;
            }
        }
        else {
            if (require_low > rest_low) {
                ans = -1;
            }
        }
        printf("%lld\n", ans);
    }
}