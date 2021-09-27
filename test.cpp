#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct s_buf {
    char* buf;
    char* cur;
}test_buf;
int main() {
    test_buf.buf = reinterpret_cast<char*>(malloc(2222));
    test_buf.cur = test_buf.buf;
    int sz = sprintf(test_buf.cur, "%d %d\n", 1, 2);
    test_buf.cur += sz;
    sprintf(test_buf.cur, "%d %d\n", 3, 4);
    test_buf.cur += sz;
    *test_buf.cur = '\0';
    puts(test_buf.buf);
    free(test_buf.buf);
    test_buf.cur = nullptr;
} // namespace std;
