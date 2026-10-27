# Parallel Programming- assignment 03

## Overview 

This assignment explores memory organization, matrix allocation, and performance of different data layouts.

- ### example_1,2:
Contains first two tasks from lab 04. 
Matrix allocation using fragmented memory.
Matrix allocation using contiguous memory.
- ### example_3:
Contains an array of structures of arrays(AoSoA).
A benchmark measuring initialization time for different vector lengths and dataset sizes.

CSV files: storing benchmark results.
- ### Makefile:
Compilation and execution of the experiments.

## Benchmark Results
Tested dataset sizes:
- 1000 elements
- 10,000 elements
- 100,000 elements
- 1,000,000 elements
- 10,000,000 elements

Tested vector lengths:
- 2, 4, 8, 16, 32, 64, 128, 256

CSV files contain dataset size (N), vector length (V), and measured execution time in ms.

Results were imported into Google Sheets for comparing execution times and to create a chart showing results.
## Performance Graph
[View the AoSoA Benchmark Graph](https://docs.google.com/spreadsheets/d/1beCYm75sBrLtXhXoZfNehDZ4FG4LqMXoHyt0IPJUCcs/edit?usp=sharing)
