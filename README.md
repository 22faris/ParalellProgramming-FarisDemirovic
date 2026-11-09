# Assignment 05 Vectorization FLOPS for free

## Overview 
The goal of this assignment is to explore SIMD vectorization and improve the performance of the timestep calculation using OpenMP directives and GCC compiler optimizations.

## Implementation 

Four implementations were tested:

- **Baseline:**  original implementation without SIMD vectoriyation.
- **Optimization 1:** introduces #oragma omp simd reduction (min:mymindt).
- **Optimization 2:** adds private temporary variables using the private clause.
- **Optimization 3:** declares temporary variables locally inside the loop.

The final Optimization 3 was compiled with additional flags:

_-fno-trapping-math -fno-math-errno_

## Compiler Vectorization results

Implementation  |  Vectorized  |  Vector width

Baseline        |  NO          |  -

Opt 1           | YES          | 256 bits

opt 2           | YES          | 256 bits

opt 3           | YES          | 256 bits

opt 3 + final flags | YES          | 256 bits


GCC successfully vectorized all optimized loops using 32-byte vectors.

Compiler reports are included in the project directory.

## Program results 
All implementations produced the same output:
_Minimum dt is 0.016964_

**LIKWID Runtime results**

Baseline : _0.4125 s_

Opt 1 : _0.6294 s_

Opt 2 : _0.3272 s_

Opt 3 : _0.4419 s_

LIKWID could not access the required hardware performance counters because the program was running inside a KVM virtual machine. Therefore, FLOPS and vectorization ratio measurements were reported as zero and cannot be used for a valid performance comparison.

## Conclusion
OpenMP SIMD directives enabled GCC to vectorize the timestep loop, unlike the original baseline implementation. All optimized versions used 256-bit vectors and produced the same numerical result.

The final compiler flags also maintained successful vectorization. Although LIKWID measurements were limited by virtualization, the compiler reports confirmed successful SIMD vectorization.


