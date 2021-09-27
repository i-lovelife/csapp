#include<bits/stdc++.h>
using namespace std;
char s[200];
int cnt[27];
int G[27][27];
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%s", s);
        for (int i = 0; i < 26; i++)cnt[i] = 0;
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                G[i][j] = -1;
            }
        }
        for (int i = 0; s[i]; i++) {
            cnt[s[i]-'A']++;
        }
        int K;
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            scanf("%s",s);
            G[s[0] - 'A'][s[1] - 'A'] = 1;
        }
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 26; j++) {
                for (int k = 0; k < 26; k++) {
                    if (G[j][i] >= 0 && G[i][k] >= 0){
                        if(G[j][k] < 0 || G[j][k] > G[j][i] + G[i][k]) {
                            G[j][k] = G[j][i] + G[i][k];
                        }
                    }
                }
            }
        }
        int ans = -1;
        for (int i = 0; i < 26; i++) {
            int tempans=0;
            for (int j = 0; j < 26; j++) {
                if (cnt[j] && i != j) {
                    if (G[j][i] < 0) {
                        tempans = -1;
                        break;
                    }
                    tempans += G[j][i] * cnt[j];
                }
            }
            if (tempans >= 0 && (ans < 0 || ans > tempans)) {
                ans = tempans;
            }
        }
        printf("%d\n", ans);
    }
}