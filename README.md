# Lab 5: Parallel Algorithms and Patterns

## Overview

In this assignment we compare five methods of summing floating-point values:

1. Standard double 
2. Long double 
3. Pairwise 
4. Kahan
5. knuth

The program test different array sizes and measures the execution time.
And numerical error of each method against a reference sum.


---

## Results and Explanation

Methods produce different results because floating-point addition isn't associative.
Rounding errors can occur, especially when adding nummbers with significantly different magnitudes.

- **Standard double:** uses ordinary sequential addition.
- **Long double:** Uses greater floating-point precision to reduce rounding errors.
- **Pairwise:** Adds values in pairs and combines partial sums in a tree-like structure
- **Kahan:** Uses a correction value to compensate for rounding errors during addition.
- **Knuth:** Tracks rounding errors using a correction term to improve the accuracy of the final sum.

Pairwise, kahan, knuth summing produce smaller errors than standard double. Their calculations can increase execution time.

### Compile and Execution

make clean 
make 

Run tests:

./sum_tests

---

## Global Sum and Parallelization

In parallel programming, data is divided among processes or threads. Each process calculates a partial sum, and the partial sums are combined into a global sum.

Because floating-point addition is not associative, changing the order in which partial sums are combined can produce different results. This can lead to numerical differences between parallel executions.

Pairwise and compensated summation techniques help reduce rounding errors and make results more reliable when performing parallel reductions. This is important for obtaining accurate and reproducible results in parallel applications.

## Google sheets

[test results](https://docs.google.com/spreadsheets/d/1gf3o_h-QM5HOdgeDrF5dFdlaegdYVCEfnoi38frvyxo/edit?usp=sharing)
