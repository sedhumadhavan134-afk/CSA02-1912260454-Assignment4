# CSA02 – C Programming Assignment 4 (CO4)

**Student:** Sedhu Madhavan V  
**Register Number:** 1912260454  
**Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS), Chennai

## Compiler
Use GCC with warnings enabled. Record your actual version using `gcc --version`.

## Build and run
- Task 1: `gcc -std=c11 -Wall -Wextra -pedantic Task01/main.c -o Task01/task01` then `./Task01/task01`.
- Task 2: `gcc -std=c11 -Wall -Wextra -pedantic Task02/complete_code.c -o Task02/task02` then `./Task02/task02`.
- Task 3: `gcc -std=c11 -Wall -Wextra -pedantic Task03/complete_code.c -o Task03/task03` then `./Task03/task03`.
- Task 4: `gcc -std=c11 -Wall -Wextra -pedantic Task04/main.c -o Task04/task04` then `./Task04/task04`.
- Task 5 (static + automatic + register): `gcc -std=c11 -Wall -Wextra -pedantic Task05/main.c -o Task05/task05` then `./Task05/task05`.
- Task 5 (extern across files): `gcc -std=c11 -Wall -Wextra -pedantic Task05/extern_demo.c Task05/token_counter.c -o Task05/extern_demo` then `./Task05/extern_demo`.
- Task 6: `gcc -std=c11 -Wall -Wextra -pedantic Task06/main.c -o Task06/task06` then `./Task06/task06`.

On Windows, run the corresponding `.exe` file. The source `Task02/complete_code.c` and `Task03/complete_code.c` preserve the supplied starter-program structure with TODO sections completed.

## Task summaries
1. Diagnose parallel-array patient data and repair it with nested structures and a pointer-based insertion function.
2. Model parcels with nested address/date structures; selection-sort by weight and print the supplied sample list.
3. Compare all-fields structure and tagged union; print active values using the tag and inspect sizes.
4. Demonstrate pass-by-value versus pointer mutation, address evidence and the arrow operator.
5. Compare automatic, static, extern-shared and register storage usage.
6. Model packaged, cooked and combo canteen items; validate stock, warn about expiry and sort revenue.

## Submission evidence still to capture
- [ ] Record actual GCC version and OS/compiler environment.
- [ ] Compile and execute every program locally; save genuine terminal screenshots in the matching task folders.
- [ ] Test the boundary cases listed in each task analysis.
- [ ] Measure `sizeof` on the actual compiler and record timings/copy counts where required.
- [ ] Add the final report PDF and working repository URL to its cover page.

This repository's sample outputs and design notes are not substitutes for the student's own execution screenshots and experimental measurements. Capture and add those after running the code locally.
