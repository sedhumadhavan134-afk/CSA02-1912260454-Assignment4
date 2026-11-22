#include <stdio.h>

enum kind { TEMPERATURE, HUMIDITY, STATUS };
struct reading {
    enum kind type;
    union { float celsius; int percent; char status[8]; } value;
};

int main(void)
{
    struct reading sample = {TEMPERATURE, {.celsius = 31.5f}};
    printf("Active temperature member: %.1f C\n", sample.value.celsius);

    /* Deliberate assignment misuse experiment: interpret same bytes as int. */
    printf("Inactive percent member interpretation on this compiler: %d\n",
           sample.value.percent);
    puts("This is not a valid humidity measurement; do not use it in application logic.");
    return 0;
}
