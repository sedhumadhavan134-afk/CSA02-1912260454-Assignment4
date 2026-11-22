#include <stdio.h>

/* Issues the next mess token number, starting from 1001. */
int next_token(void)
{
    static int token = 1000;
    return ++token;
}

/* Automatic local variable: reinitialised on every call. */
int auto_token(void)
{
    int token = 1000;
    return ++token;
}

int main(void)
{
    int s1 = next_token(), s2 = next_token(), s3 = next_token();
    int a1 = auto_token(), a2 = auto_token(), a3 = auto_token();
    printf("static: %d %d %d\n", s1, s2, s3);
    printf("auto : %d %d %d\n", a1, a2, a3);

    puts("register loop variable demonstration:");
    for (register int i = 1; i <= 3; ++i)
        printf("token display slot %d\n", i);

    /* Caller-owned counters: two counters remain independent. */
    int veg = 1000, nonveg = 2000;
    printf("caller counters: veg=%d nonveg=%d\n", ++veg, ++nonveg);
    return 0;
}
