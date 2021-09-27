#include<bits/stdc++.h>
using namespace std;
int n;
char s[52][52];
int fob[52];
int main(){
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%d", &n);
        for (int i = 0; i < n; i++)fob[i] = 0;
        for(int i = 0; i < n; i++)scanf("%s", s[i]);
        int ans = -1, numans = 0;
        //enumerate row
        for (int i = 0; i < n; i++) {
            int tempans = 0;
            for (int j = 0; j < n; j++) {
                if (s[i][j] == 'O'){
                    tempans = -1;
                    break;
                }
                if (s[i][j] == '.') {
                    tempans++;
                }
            }
            if (tempans >= 0 && (ans < 0 || ans >= tempans)) {
                if (ans != tempans) {
                    numans = 1;
                }
                else {
                    numans++;
                }
                ans = tempans;
                if (ans == 1) {
                    for (int j = 0; j < n; j++) {
                        if (s[i][j] == '.') {
                            fob[j] = 1;
                        }
                    }
                }
            }
        }

        //enumerate column
        for (int i = 0; i < n; i++) {
            int tempans = 0;
            for (int j = 0; j < n; j++) {
                if (s[j][i] == 'O') {
                    tempans = -1;
                    break;
                }
                if (s[j][i] == '.') {
                    tempans++;
                }
            }

            if (tempans >= 0 && (ans < 0 || ans >= tempans)) {
                if (ans != tempans) {
                    numans = 1;
                }
                else {
                    if (tempans != 1 || !fob[i])numans++;
                }
                ans = tempans;
            }
        }
        if (ans < 0) {
            puts("Impossible");
        }
        else {
            printf("%d %d\n", ans, numans);
        }
    }
}