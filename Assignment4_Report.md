# CSA02 – C Programming Assignment 4 (CO4)
## Modelling Real-World Data with Structures and Unions

**Student:** Sedhu Madhavan V  
**Register Number:** 1912260454  
**Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS), Chennai  
**Repository:** https://github.com/sedhumadhavan134-afk/CSA02-1912260454-Assignment4

> This report is a working design and implementation report. Replace the evidence placeholders with your own GCC version, terminal screenshots, measured values and PDF export after compiling and executing the programs.

## Task 1 – Data Design Review (6 marks)

### Diagnosis
The supplied design uses parallel arrays, a 10-byte phone buffer for ten digits (which also needs a null terminator), one float for a two-component BP reading, an eight-character date string, no capacity check, global mutable data and error-prone sorting across multiple arrays. These can cause field mismatch, buffer overflow, loss of leading zeroes, incorrect BP representation, invalid dates, out-of-bounds writes and inconsistent patient records.

### Repaired model
`Date` contains day/month/year; `BloodPressure` contains systolic/diastolic values; `Patient` groups name, age, phone, BP and visit date; `PatientRegister` owns a fixed-capacity array and count. `addPatient` receives a pointer, checks capacity and validates basic fields before writing one complete record.

### Pseudocode
```text
ALGORITHM AddPatient(register_pointer, name, age, phone, bp, date)
    IF register_pointer is NULL OR name is NULL OR phone is NULL
        RETURN failure
    END IF
    IF count equals MAX_PATIENTS OR any field fails validation
        RETURN failure
    END IF
    record ← address of records[count]
    copy name and phone into bounded destination arrays
    assign age, blood pressure and visit date
    count ← count + 1
    RETURN success
END ALGORITHM
```

### Alternative: structure-of-arrays
Parallel arrays may be useful when processing one field column-wise or when only selected fields are needed. Sorting by age takes O(n log n) comparisons with an efficient sort (or O(n²) with a simple sort). Array-of-structures swaps a whole Patient; structure-of-arrays must swap each corresponding field element. Both use O(n) storage; structure padding is ABI-dependent and should be measured with sizeof.

## Task 2 – Courier Parcel Tracking (8 marks)

### Entities and nesting
Date (day, month, year); Address (city, PIN); Parcel (ID, weight, nested receiver address and booking date); daily booking array. The full prose model may additionally include sender details, service type and charge; the provided starter-code structure specifically contains receiver address and booking date.

### Pseudocode
```text
ALGORITHM SelectionSortByWeight(parcels, n)
    FOR i ← 0 TO n-2
        min ← i
        FOR j ← i+1 TO n-1
            IF parcels[j].weight < parcels[min].weight
                min ← j
            END IF
        END FOR
        IF min is not i
            swap complete parcel structures at i and min
        END IF
    END FOR
END ALGORITHM

ALGORITHM ListByCity(parcels, n, target_city)
    found ← FALSE
    FOR each parcel in parcels
        IF parcel.receiver.city equals target_city
            print parcel
            found ← TRUE
        END IF
    END FOR
    IF NOT found, print no-match message
END ALGORITHM
```

Access paths: array/dot: `list[2].to.pincode`; pointer/arrow: `p->to.pincode` where `p = &list[2]`. Selection sort is O(n²) time and O(1) auxiliary space. A swap uses a temporary structure and two assignments; record sizeof(struct parcel) from your compiler. A flat design makes paths shorter but reduces address-type reuse.

## Task 3 – Unions and Memory Layout (9 marks)

The all-fields structure stores temperature, humidity and status simultaneously. A tagged union stores an enum tag and one shared payload, appropriate when each sensor packet contains exactly one kind of value. The provided assignment's typical GCC target expects union size 8 bytes and tagged structure size 12 bytes. The tag is typically 4 bytes and the union is 8 bytes; alignment/padding are ABI-dependent, so capture actual sizeof results.

The print function switches on the tag and reads only the active member. The requested misuse experiment stores a float and then reads the int member. Explain the observed result as an implementation/representation-dependent interpretation, not as a meaningful humidity value; do not rely on it for program logic. Tagged-union dispatch is O(1) per packet and stores O(1) bytes per packet.

## Task 4 – Structure Forensics (7 marks)

Passing `struct account a` copies the structure, so changing `a.balance` does not update the caller's array. Since `p` is a pointer, `p.number` is invalid; use `p->number` or `(*p).number`. The corrected function accepts `struct account *` and changes the original record. Address prints in main and inside the function should match for the same call.

Pass small structures by value when an independent copy is wanted; pass a pointer to mutate the caller's object; use a const pointer for read-only access without copying a potentially large structure. Both versions are O(1) per account, but pass-by-value copies sizeof(struct account), while pointer passing transfers an address.

## Task 5 – Storage Classes (7 marks)

- `auto`: block scope and automatic lifetime; the local token resets to 1000 on each call, so every call returns 1001.
- `static` local: block scope but lifetime for the entire program; its value persists between calls.
- `extern`: declaration refers to a global object defined in another translation unit; both source files share the same counter.
- `register`: a storage-class hint for a local variable; it does not make a persistent token counter. The address-of operator cannot be applied to a register-declared object in standard C.

The caller-owned alternative `next_token(int *counter)` supports independent veg/non-veg counters without hidden shared state. All approaches take O(1) time; the counter itself uses O(1) storage. Avoid multiple state-changing function calls in one printf argument list because C does not specify argument evaluation order.

## Task 6 – College Canteen Inventory and Billing (13 marks)

### Model
Date and Time are nested value types. Item stores ID, name, kind, stock, price, sold count and revenue. A tagged union stores the kind-specific payload: expiry date for packaged items, preparation time for cooked items, or up to three component IDs for combo meals.

### Pseudocode
```text
ALGORITHM RecordSale(items, count, id, quantity)
    locate item with id
    IF item is missing OR quantity <= 0 OR quantity > stock
        RETURN rejected
    END IF
    stock ← stock - quantity
    sold ← sold + quantity
    revenue ← revenue + price * quantity
    RETURN accepted
END ALGORITHM

ALGORITHM ExpiryWarnings(items, today)
    FOR each item
        IF item kind is PACKAGED AND expiry is within 0..2 days of today
            print expiry warning
        END IF
    END FOR
END ALGORITHM
```

The implementation demonstrates a normal sale, a rejected sale exceeding stock, an expiry warning and revenue sorting. The current sample expiry helper is deliberately limited to dates within the same month/year; extend it with a validated date-to-day conversion before testing month/year boundaries. The array implementation uses O(n) lookup and O(n²) revenue sorting. A linked list supports O(1) insertion/removal when the node is already known, but searching is O(n) and each node uses extra pointer storage.

## Experimental evidence to complete
For each task, attach genuine compiler/run screenshots. For Task 3 record both sizeof values. For Task 2 record sizeof(struct parcel) and swap-copy estimate. For Task 4 capture matching addresses. For Task 5 record outputs from separate runs. For Task 6 test zero/negative quantity, missing item, insufficient stock, and expiry at 0, 1, 2 and 3 days. Do not invent timing or sanitizer results.

## Final engineering decision
Use structures to keep related fields together, nested structures for reusable entities, a tagged union when exactly one payload variant is valid, and pointers when caller-owned data must be modified. Validate all inputs and capacity before writes. For larger datasets, choose dynamic allocation or file-backed/indexed storage based on measured memory and lookup requirements.
