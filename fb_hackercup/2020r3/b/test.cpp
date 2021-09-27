#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int Maxn=8020;
double f[Maxn][Maxn];
int n;
double p;
double get_val(int x, int y) {
    if (x < 0 || y < 0) {
        return 0;
    }
    return f[x][y];
}
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d:\n", cas++);
        scanf("%d%lf", &n, &p);
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 && j == 0) {
                    f[i][j] = 0;
                    continue;
                }
                // high rank win with pro p
                double p_both_high = (i+.0) * (i - 1) / (i + j + 1)/ (i + j);
                double p_both_low = (j+.0) * (j - 1) / (i + j + 1)/ (i + j);
                double p_meet_high = (i+.0) * 2 / (i + j + 1) / (i + j);
                double p_meet_low = (j+.0) * 2 / (i + j + 1) / (i + j);
                double p_high_low = (i+.0) * j * 2 / (i + j + 1) / (i + j);
                f[i][j] = (1 + get_val(i - 1, j)) * p_both_high + (1 + get_val(i, j - 1)) * p_both_low;
                f[i][j] += p_meet_high * ((1 + get_val(i - 1, j)) * (1 - p) + 1 * p);
                f[i][j] += p_meet_low * ((1 + get_val(i, j - 1)) * p + (1 - p));
                f[i][j] += p_high_low * ((1 + get_val(i - 1, j)) * (1 - p) + (1 + get_val(i, j - 1)) * p); 
                //printf("%d %d %.6f\n", i, j, f[i][j]);
            }
        }
        for (int i = 0; i < n; i++) {
            double ans = f[n - 1 -i][i];
            printf("%.8f\n", ans);
        }
    }
}