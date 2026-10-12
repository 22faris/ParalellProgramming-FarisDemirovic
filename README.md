## Description

I've concluded that I am not very fond of C and linux.
There was an error in the original code that the program was searching an array of 10 elements and leaving the scope because in the loop i<=10
that made it go from 0 to 10 instead of 0 to 9.

Fixed issues: initializing variables,using valid array indices,checking memory allocation,releasing memory with 'free()'.

## Valgrind Memory Check

Valgrind is used to detect memory errors and leaks.

Run the check with: "make valgrind"

### Valgrind output

valgrind --leak-check=full --track-origins=yes ./main 5
==19692== Memcheck, a memory error detector
==19692== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==19692== Using Valgrind-3.26.0 and LibVEX; rerun with -h for copyright info
==19692== Command: ./main 5
==19692==
Value 5 found at index 5
==19692==
==19692== HEAP SUMMARY:
==19692==     in use at exit: 0 bytes in 0 blocks
==19692==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
==19692==
==19692== All heap blocks were freed -- no leaks are possible
==19692==
==19692== For lists of detected and suppressed errors, rerun with: -s
==19692== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)