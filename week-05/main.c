#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "sum_algorithms.h"

#define ORDERS_OF_MAGNITUDE 1.0e9

typedef double(*sum_function)(double *, long);

void cpu_timer_start(struct timespec *tstart_cpu) {
   clock_gettime(CLOCK_MONOTONIC, tstart_cpu);
}

double cpu_timer_stop(struct timespec tstart_cpu) {
   struct timespec tstop_cpu, tresult;

   clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);

   tresult.tv_sec = tstop_cpu.tv_sec - tstart_cpu.tv_sec;
   tresult.tv_nsec = tstop_cpu.tv_nsec - tstart_cpu.tv_nsec;

   double result = (double)tresult.tv_sec + (double)tresult.tv_nsec * 1.0e-9;

   return result;
}

void print_result(const char *method,
                  long double sum,
                  long double accurate_sum,
                  double runtime)
{
   long double error = fabsl(sum - accurate_sum);
   long double relative_error = error / fabsl(accurate_sum);

   printf("%-15s | %-20.12Le | %-15.6Le | %.9f seconds\n",
          method, error, relative_error, runtime);
}

/* Execute and measure a double-precision summation method */
void test_method(const char *name,
                 sum_function function,
                 double *energy,
                 long ncells,
                 long double accurate_sum)
{
   struct timespec timer;

   cpu_timer_start(&timer);
   double result = function(energy, ncells);
   double runtime = cpu_timer_stop(timer);

   print_result(name, (long double)result, accurate_sum, runtime);
}

int main(int argc, char *argv[])
{
   printf("========================================\n\n");

   /*
    * Test with different array sizes - powers of 2 from 2^10 to 2^27
    *
    * We use powers of 2 because:
    * 1. It makes pairwise summation work cleanly (can divide by 2 repeatedly)
    * 2. These are natural sizes for many computational problems
    * 3. It allows us to see how errors scale exponentially with problem size
    *
    * Range: 1,024 elements (2^10) to 134,217,728 elements (2^27)
    */
   for (int pow_of_two = 10; pow_of_two <= 27; pow_of_two++) {
      long ncells = (long)pow(2.0, (double)pow_of_two);
      long ncellsdiv2 = ncells / 2;

      printf("========================================\n");
      printf("TESTING WITH 2^%d = %ld elements\n", pow_of_two, ncells);
      printf("========================================\n");

      double high_value = 1.0e-1;
      double low_value  = 1.0e-1 / ORDERS_OF_MAGNITUDE;

      long double accurate_sum = 0.0L;

      double *energy = (double *)malloc(ncells * sizeof(double));

      if (energy == NULL) {
         fprintf(stderr, "Error: Failed to allocate memory for %ld elements\n", ncells);
         return 1;
      }

      printf("Initializing array (Leblanc problem: high values first, then low values)\n");
      for (long i = 0; i < ncells; i++){
         energy[i] = (i < ncellsdiv2) ? high_value : low_value;
      }

      for (long i = 0;i < ncells; i++) {
         accurate_sum += (long double)energy[i];
      }

      printf("Expected accurate sum: %.15Lf\n\n", accurate_sum);

      // Standard double summation
      test_method("Standard double", do_sum,energy, ncells, accurate_sum);

      // Long double sum
      struct timespec timer;

      cpu_timer_start(&timer);
      long double id_result = do_ldsum(energy, ncells);
      double ld_runtime = cpu_timer_stop(timer);

      print_result("long double", id_result, accurate_sum, ld_runtime);

      // Pairwise sum
      test_method("Pairwise",do_pair_sum,energy, ncells, accurate_sum);

      // Kahan sum
      test_method("Kahan",do_kahan_sum,energy, ncells, accurate_sum);

      // Knuth sum
      test_method("Knuth", do_knuth_sum,energy, ncells, accurate_sum);

      free(energy);
      printf("\n");
   }

   printf("========================================\n");
   printf("All tests complete!\n");
   printf("========================================\n");

   return 0;
}