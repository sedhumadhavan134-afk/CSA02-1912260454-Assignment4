# Task 6 – College Canteen Inventory and Billing

## Stage 1: Testable requirements
- Store item ID, name, kind, stock, price, sold quantity and revenue.
- Packaged goods store an expiry date; cooked goods store preparation time; combo meals store up to three component IDs.
- A sale is accepted only for a known item, positive quantity and sufficient stock.
- Accepted sales reduce stock and increase sold quantity and revenue.
- Packaged items expiring within two days generate a warning.
- The daily summary is sorted by descending revenue.

## Stage 2: Data model
`Date` and `Time` are nested value types. `Item` is an array element. Its tagged union stores exactly one kind-specific payload: expiry date, preparation time or combo component list. The enum tag determines which union member is valid.

## Stage 3: Critical decisions
Stock changes occur only after all validation passes. The demo expiry comparison is intentionally limited to dates in the same month and year; a production implementation should convert validated calendar dates to a day number or use a proper date library to handle month/year boundaries. No global mutable inventory is needed; the inventory and count are passed to functions. A static/global value is not justified by this small design.

## Stage 4: Function interfaces
- `int find_item(const Item items[], int count, int id)`
- `int record_sale(Item items[], int count, int id, int quantity)`
- `void expiry_warnings(const Item items[], int count, Date today)`
- `void sort_by_revenue(Item items[], int count)`
- `void print_summary(const Item items[], int count)`

**Sale pseudocode:** Find item; reject if absent, quantity non-positive or stock insufficient; otherwise subtract quantity from stock, add quantity to sold count, add price × quantity to revenue, return success.

**Expiry pseudocode:** For each item, if kind is packaged and expiry is from today through two days ahead, print warning.

## Stage 5: Demonstration
The sample run attempts a valid milk sale, an over-stock combo sale, a cooked-meal sale, an expiry warning and a revenue-sorted summary. Compile and execute locally to capture the real output.

## Alternative: linked list
A linked list can insert a new item at the head in O(1) if no search is required; finding an item is O(n), and removing a known item is O(1) after its predecessor is known (otherwise O(n) to find it). An array has O(n) search and may require O(n) shifting for insertion/removal while preserving order, but provides contiguous storage and O(1) indexed access. Each linked-list node needs an extra next pointer and allocation metadata. For a small, bounded canteen catalogue, an array is simpler and cache-friendly; use a linked list if frequent insertion/removal is a dominant requirement.
