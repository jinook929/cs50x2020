// http://valgrind.org/docs/manual/quick-start.html#quick-start.prepare

#include <stdlib.h>

void f(void)
{
    int *x = malloc(10 * sizeof(int));
    x[9] = 0;
    // x[10] = 0; => Invalid write of size 4
    free(x);
}

int main(void)
{
    f();
    return 0;
}