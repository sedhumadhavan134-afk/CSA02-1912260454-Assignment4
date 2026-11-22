#include <stdio.h>

struct account { int number; float balance; };

void addInterest(struct account *a, float rate)
{
    if (a == NULL) return;
    printf("Inside addInterest: address=%p\n", (void *)a);
    a->balance = a->balance + a->balance * rate / 100.0f;
}

/* Alternative: pass by value and return the modified copy. */
struct account addInterest_copy(struct account a, float rate)
{
    a.balance += a.balance * rate / 100.0f;
    return a;
}

int main(void)
{
    struct account list[3] = {{101, 5000}, {102, 12000}, {103, 800}};
    struct account *p = list;
    for (int i = 0; i < 3; i++) {
        printf("Main before call: address=%p\n", (void *)&list[i]);
        addInterest(&list[i], 4.0f);
    }
    printf("Updated accounts:\n");
    for (int i = 0; i < 3; i++)
        printf("%d %.2f\n", list[i].number, list[i].balance);
    printf("First account through pointer: %d %.2f\n", p->number, p->balance);

    list[0] = addInterest_copy(list[0], 4.0f);
    printf("First account after value-return alternative: %.2f\n", list[0].balance);
    return 0;
}
