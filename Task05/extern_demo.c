#include <stdio.h>
#include "extern_counter.h"
int main(void)
{
    printf("extern: %d %d %d\n",
           next_shared_token(), next_shared_token(), next_shared_token());
    return 0;
}
