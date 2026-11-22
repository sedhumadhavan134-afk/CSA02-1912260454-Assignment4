# Task 4 – Structure Forensics

## Defects in the supplied program
1. `addInterest(struct account a, ...)` receives a copy. Updating `a.balance` changes only the local copy, not the array element.
2. `p` is a pointer, so `p.number` and `p.balance` are invalid member access. Use `p->number` and `p->balance`, or `(*p).number`.
3. The function should receive `struct account *` to update the original record.

## Address evidence
The corrected program prints `&list[i]` in main and the received pointer inside addInterest. The corresponding addresses should match for each call, showing that the function operates on the original array element. Addresses vary between executions; record your own output.

## Passing guidance
- Pass by value for small structures when a copy is intended and mutation must not affect the caller.
- Pass by pointer when the function must modify the original or avoid copying a large structure.
- Pass by const pointer for read-only access to a structure, preventing accidental member modification through that pointer.

## Alternative and complexity
The return-by-value alternative is `list[i] = addInterest_copy(list[i], 4.0f)`. Both approaches take O(1) time per account and O(1) auxiliary space. Passing a pointer passes an address (typically one pointer-sized argument); by-value passes/copies `sizeof(struct account)` bytes and returns a structure copy. The compiler ABI may use registers or hidden return storage, so measure rather than assuming physical copy instructions.
