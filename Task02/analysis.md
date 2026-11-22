# Task 2 – Courier Parcel Tracking

## Entities
- Date: day, month, year.
- Address: city and PIN code.
- Parcel: ID, weight, receiver address and booking date. The assignment's supplied starter program models the receiver address as `to`; the prose requirement also asks students to identify sender and receiver names/addresses, service type and charge in the full proposed model.
- Daily bookings: array of parcel structures.

## Sorting pseudocode
1. For each position i from 0 to n-2, set min=i.
2. Scan positions j=i+1 through n-1; if weight[j] is smaller than weight[min], set min=j.
3. If min is not i, swap the complete structures using a temporary variable.
4. Continue; the array is in ascending weight order.

## City filtering pseudocode
For each parcel, compare its receiver city with the requested city. Print matching records. If none match, report no matching parcels.

## Access paths
Array/dot: `list[2].to.pincode`. Pointer/arrow: `ptr->to.pincode`, with `ptr = &list[2]`.

## Swap-copy count and complexity
The supplied selection sort makes at most n-1 swaps. A swap uses three structure assignments (temporary = p[i], p[i] = p[min], p[min] = temporary), each transferring a structure value of `sizeof(struct parcel)` bytes conceptually: up to 3 * sizeof(struct parcel) bytes per swap. Comparisons are O(n²), auxiliary space O(1). A flat design makes address/date fields direct members and shortens access paths, while nested structures improve reuse and semantic grouping. Compare actual `sizeof` results because padding/alignment are implementation-dependent.
