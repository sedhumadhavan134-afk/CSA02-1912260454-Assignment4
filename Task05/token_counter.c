#include "extern_counter.h"
int shared_token = 1000;
int next_shared_token(void)
{
    return ++shared_token;
}
