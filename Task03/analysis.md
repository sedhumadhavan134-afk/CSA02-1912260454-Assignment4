# Task 3 – Weather-Station Sensor Packets

## Two representations
A structure containing float temperature, int humidity and char[8] status stores all fields simultaneously. The tagged union stores an enum tag plus one shared payload. Since each packet carries exactly one value, the tagged union is the appropriate compact representation; the tag tells the printer which member is active.

## Size prediction
On the typical 64-bit GCC target specified by the assignment, the union is 8 bytes (largest member char[8]) and the tagged structure is 12 bytes: a 4-byte enum tag followed by an 8-byte union. The actual ABI determines alignment and padding; verify using sizeof on the target machine. The all-fields structure is commonly 16 bytes (4+4+8), but measure it.

## Safe printing
The show function switches on the tag and reads only the corresponding member. An inactive union member must not be treated as a valid value of another sensor type. The assignment's misuse experiment asks students to record what their compiler produces; describe it as a representation reinterpretation, not a real humidity reading, and note that its result is implementation-dependent.

## Alternatives and complexity
Separate arrays require type-specific indexing and an external mapping from packet order to type; reading a packet may need a tag dispatch plus access to the relevant array. A void-pointer-per-packet design generally needs allocation metadata/tagging, pointer indirection and separate allocations, increasing overhead. Tagged union lookup/dispatch is O(1), with O(1) payload storage per packet. The union uses the largest member's size, not the sum of all members.
