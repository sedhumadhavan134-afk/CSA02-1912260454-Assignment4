#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_COMBOS 3
#define NAME_LEN 32

typedef struct { int day, month, year; } Date;
typedef struct { int hour, minute; } Time;
typedef enum { PACKAGED, COOKED, COMBO } ItemKind;
typedef struct {
    int component_ids[MAX_COMBOS];
    int component_count;
} ComboInfo;
typedef struct {
    int id;
    char name[NAME_LEN];
    ItemKind kind;
    int stock;
    float price;
    union {
        Date expiry;
        Time prepared;
        ComboInfo combo;
    } detail;
    int sold;
    float revenue;
} Item;

static int find_item(const Item items[], int count, int id)
{
    for (int i = 0; i < count; ++i)
        if (items[i].id == id) return i;
    return -1;
}

static int record_sale(Item items[], int count, int id, int quantity)
{
    int index = find_item(items, count, id);
    if (index < 0 || quantity <= 0 || items[index].stock < quantity)
        return 0;
    items[index].stock -= quantity;
    items[index].sold += quantity;
    items[index].revenue += items[index].price * quantity;
    return 1;
}

static int expires_within_two_days(Date today, Date expiry)
{
    /* Assignment demo uses dates in the same month and year. */
    if (today.year != expiry.year || today.month != expiry.month) return 0;
    int difference = expiry.day - today.day;
    return difference >= 0 && difference <= 2;
}

static void expiry_warnings(const Item items[], int count, Date today)
{
    for (int i = 0; i < count; ++i)
        if (items[i].kind == PACKAGED &&
            expires_within_two_days(today, items[i].detail.expiry))
            printf("EXPIRY WARNING: %s expires %02d/%02d/%04d\n",
                   items[i].name, items[i].detail.expiry.day,
                   items[i].detail.expiry.month, items[i].detail.expiry.year);
}

static void sort_by_revenue(Item items[], int count)
{
    for (int i = 0; i < count - 1; ++i) {
        int best = i;
        for (int j = i + 1; j < count; ++j)
            if (items[j].revenue > items[best].revenue) best = j;
        if (best != i) {
            Item temp = items[i]; items[i] = items[best]; items[best] = temp;
        }
    }
}

static void print_summary(const Item items[], int count)
{
    puts("Daily revenue summary (descending):");
    for (int i = 0; i < count; ++i)
        printf("%-16s sold=%d revenue=Rs. %.2f stock=%d\n",
               items[i].name, items[i].sold, items[i].revenue, items[i].stock);
}

int main(void)
{
    Item items[3] = {
        {1, "Milk Packet", PACKAGED, 10, 30.0f, {.expiry = {24,11,2026}}, 0, 0.0f},
        {2, "Veg Meal", COOKED, 20, 80.0f, {.prepared = {11,30}}, 0, 0.0f},
        {3, "Combo Meal", COMBO, 5, 120.0f, {.combo = {{1,2},2}}, 0, 0.0f}
    };
    const int count = 3;
    const Date today = {22,11,2026};

    puts("Normal sale (2 milk packets):");
    printf("%s\n", record_sale(items, count, 1, 2) ? "Sale accepted" : "Sale rejected");
    puts("Sale exceeding stock (6 combo meals):");
    printf("%s\n", record_sale(items, count, 3, 6) ? "Sale accepted" : "Rejected: insufficient stock");
    (void)record_sale(items, count, 2, 3);
    expiry_warnings(items, count, today);
    sort_by_revenue(items, count);
    print_summary(items, count);
    return 0;
}
