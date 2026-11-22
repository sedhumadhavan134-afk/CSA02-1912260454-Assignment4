# Task 5 – Storage Classes

## Supplied complete-code program
The TODO is completed with a static local counter initialized to 1000 and pre-incremented on each call. Expected output is:
- static: 1001 1002 1003
- auto: 1001 1001 1001

## Four versions
- **auto:** local token is recreated and initialized to 1000 on every call; each result is 1001.
- **static local:** block scope, static storage duration, initialized once (zero-initialized if no initializer); retains its value between calls.
- **extern/global:** definition in token_counter.c and declaration in a header with extern; shared across translation units.
- **register:** a loop variable may be declared register as a hint; it has block scope and automatic storage duration. The compiler may ignore the hint. C does not permit applying address-of to a register-qualified object.

## Two independent counters
Static version: use two static variables or a structure containing both counters. Extern version: expose two named globals or a counter structure. Auto version: maintain two caller-owned variables and pass their addresses. Register applies to local loop indices, not persistent token state.

## Evaluation
All next-token operations are O(1). Static and global state have program lifetime and can accidentally be modified by any code with access; caller-owned counters have lifetime controlled by the caller and support independent counters cleanly. The pointer approach is `int next_token(int *counter)`, validating the pointer and incrementing the caller's integer. Argument evaluation order in a single printf is unspecified, so the three calls can execute in an order different from their textual order; store each result in a separate statement to guarantee displayed order.
