#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define NAME_LEN 50
#define PHONE_LEN 16

typedef struct { int day, month, year; } Date;
typedef struct { int systolic, diastolic; } BloodPressure;
typedef struct {
    char name[NAME_LEN];
    int age;
    char phone[PHONE_LEN];
    BloodPressure bp;
    Date visit_date;
} Patient;
typedef struct { Patient records[MAX_PATIENTS]; size_t count; } PatientRegister;

/* Returns 1 on success; 0 for invalid data or a full register. */
int addPatient(PatientRegister *reg, const char *name, int age,
               const char *phone, BloodPressure bp, Date visit_date)
{
    if (reg == NULL || name == NULL || phone == NULL ||
        reg->count >= MAX_PATIENTS || age < 0 ||
        strlen(name) >= NAME_LEN || strlen(phone) >= PHONE_LEN ||
        bp.systolic <= 0 || bp.diastolic <= 0 ||
        visit_date.day < 1 || visit_date.day > 31 ||
        visit_date.month < 1 || visit_date.month > 12 || visit_date.year < 1)
        return 0;

    Patient *p = &reg->records[reg->count];
    (void)snprintf(p->name, sizeof p->name, "%s", name);
    p->age = age;
    (void)snprintf(p->phone, sizeof p->phone, "%s", phone);
    p->bp = bp;
    p->visit_date = visit_date;
    reg->count++;
    return 1;
}

void printPatient(const Patient *p)
{
    if (p == NULL) return;
    printf("%-20s age=%d phone=%s BP=%d/%d visit=%02d/%02d/%04d\n",
           p->name, p->age, p->phone, p->bp.systolic, p->bp.diastolic,
           p->visit_date.day, p->visit_date.month, p->visit_date.year);
}

int main(void)
{
    PatientRegister reg = {0};
    BloodPressure bp = {120, 80};
    Date visit = {22, 11, 2026};
    if (!addPatient(&reg, "Arun Kumar", 45, "9876543210", bp, visit)) {
        fprintf(stderr, "Could not add patient. Check fields or capacity.\n");
        return 1;
    }
    printf("Patients registered: %zu\n", reg.count);
    for (size_t i = 0; i < reg.count; ++i) printPatient(&reg.records[i]);
    return 0;
}
