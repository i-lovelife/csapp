#include<bits/stdc++.h>
using namespace std;
char s[200];
int cnt[27];
int vowel[27];
int main(){
    vowel['A' - 'A'] = 1;
    vowel['E' - 'A'] = 1;
    vowel['I' - 'A'] = 1;
    vowel['O' - 'A'] = 1;
    vowel['U' - 'A'] = 1;
    int _, cas=1;scanf("%d",&_);
    while (_--) {
        printf("Case #%d: ", cas++);
        scanf("%s", s);
        for (int i = 0; i < 26; i++)cnt[i] = 0;
        for (int i = 0; s[i]; i++) {
            cnt[s[i]-'A']++;
        }
        int ans = -1;
        for (int i = 0; i < 26; i++) {
            int tempans=0;
            for (int j = 0; j < 26; j++) {
                if (cnt[j] && i != j) {
                    if (vowel[i] == vowel[j]) {
                        tempans += cnt[j] * 2;
                    }
                    else {
                        tempans += cnt[j];
                    }
                }
            }
            if (ans < 0 || ans > tempans) {
                ans = tempans;
            }
        }
        printf("%d\n", ans);
    }
}