# Task 1 – Data Design Review

## 1.1 Deficiencies
1. **Parallel arrays:** A patient's fields are spread across arrays. Sorting or deleting requires identical index operations in every array; one missed operation associates the wrong phone or BP with a patient.
2. **Phone in char[10]:** Ten digits require eleven bytes including the null terminator. strcpy can overflow it. A phone number is text because leading zeroes and '+' may matter.
3. **BP in one float:** Blood pressure is a systolic/diastolic pair, not one scalar; 120/80 cannot be represented faithfully as one ordinary float.
4. **Date in char[8]:** Format is implicit, validation and date arithmetic are awkward, and the buffer cannot hold a full ISO date plus terminator.
5. **No capacity check:** At count 100, the next write goes out of bounds, causing undefined behaviour and possible corruption.
6. **Global state:** Any function can change the arrays and count, making invariants difficult to protect and reuse harder.
7. **Sorting difficulty:** Every field array must be swapped consistently or records become corrupted.

## 1.2 Repair
main.c defines Date, BloodPressure, Patient and PatientRegister. The register owns an array of complete patient structures and a count. addPatient accepts a pointer, checks capacity and basic field validity, and writes one complete record.

## 1.3 Design defence (under 100 words)
A patient structure keeps all fields for one person together, so sorting or swapping a patient moves one complete record and cannot desynchronise parallel arrays. A structure pointer lets a function update the caller's register without copying the full array. Nested date and blood-pressure structures express the meaning of those values and can be reused elsewhere. New fields can be added to Patient without creating and synchronising another parallel array.

## Alternative concept and complexity
A structure-of-arrays layout can be preferred when processing one field across many records, such as vectorised age analysis, or when only selected columns are loaded. Both layouts need O(n log n) comparisons for an efficient comparison sort (or O(n²) for a simple sort). Swapping two array-of-structures records moves approximately 2 * sizeof(Patient) bytes; parallel arrays move the corresponding element in each field array. Both use O(n) storage. sizeof(Patient) may exceed the sum of member sizes because of alignment padding; inspect it on the target compiler.

## Test plan
- Add a valid patient.
- Reject invalid age or BP.
- Fill all 100 slots and verify the next insertion is rejected.
- Test maximum accepted name and phone lengths.

Capture actual compiler output and terminal screenshots after running locally.
