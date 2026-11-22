# Task 1 – Pseudocode and Test Design

## Pseudocode: print all patient records
1. Set index to zero.
2. While index is less than register count, pass the address of the current record to the print function.
3. Increment index.

## Complexity
Adding a patient to the next free slot is O(1) time and O(1) extra space. Printing all n patients is O(n) time. Sorting the records by age with selection sort would be O(n²) time and O(1) auxiliary space; an efficient comparison sort can achieve O(n log n).

## Test cases
| Case | Input | Expected behaviour |
|---|---|---|
| Valid | age 45, phone 10 digits, BP 120/80, valid date | Record accepted |
| Negative age | age -1 | Rejected |
| Invalid BP | systolic 0 | Rejected |
| Full register | 100 records already present | Next record rejected |
| Long phone | length >= PHONE_LEN | Rejected without overflow |
