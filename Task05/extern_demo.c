#include <stdio.h>
#include "extern_counter.h"

int main(void)
{
    int t1 = next_shared_token();
    int t2 = next_shared_token();
    int t3 = next_shared_token();
    printf("extern: %d %d %d\n", t1, t2, t3);
    return 0;
}
