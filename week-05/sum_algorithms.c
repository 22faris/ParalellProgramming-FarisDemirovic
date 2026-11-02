#include <stdlib.h>
#include <math.h>
#include "sum_algorithms.h"

double do_sum(double* restrict var, long ncells)
{
   double sum = 0.0;
   for (long i = 0; i < ncells; i++){
      sum += var[i];
   }
   return sum;
}

// Long double precision sum

long double do_ldsum(double* restrict var, long ncells) {
   long double ldsum = 0.0;
   for (long i = 0 ; i < ncells; i++) {
      ldsum += var[i];
   }
   return ldsum;
}

// Pairwise summation
double do_pair_sum(double* restrict var, long ncells) {
   if (ncells <= 0 || ncells % 2 != 0) {
      return 0.0;
   }

   double* pwsum = malloc((size_t)(ncells / 2) * sizeof(double));

   if (pwsum == NULL) {
      return 0.0;
   }

   long nmax = ncells / 2;

   for (long i = 0;i < nmax;i++) {
      pwsum[i] = var[i * 2] + var[i * 2 +1];
   }
   for (long j = 1; j < log2((double)ncells); j++) {
      nmax /=2;
      for (long i = 0; i < nmax; i++) {
         pwsum[i] = pwsum[i * 2] + pwsum[i * 2 +1];
      }
   }
   double sum = pwsum[0];
   free(pwsum);
   return sum;
}

// Kahan
double do_kahan_sum(double* restrict var, long ncells) {
   struct esum_type {
      double sum;
      double correction;
   }local;

   local.sum = 0.0;
   local.correction = 0.0;

   for (long i = 0;i < ncells; i++) {
      double corrected_next_term = var[i] + local.correction;
      double new_sum = local.sum + local.correction;

      local.correction = corrected_next_term - (new_sum - local.sum);
      local.sum = new_sum;
   }
   return local.sum + local.correction;
}

// Knuth
double do_knuth_sum(double* restrict var, long ncells) {
   struct esum_type{
     double sum;
      double correction;
   };
   double u,v,upt,up,vpp;
   struct esum_type local;
   local.sum = 0.0;
   local.correction = 0.0;
   for (long i = 0;i < ncells; i++) {
      u = local.sum;
      v = var[i] + local.correction;
      upt = u + v;
      up = upt - v;
      vpp = upt - up;

      local.sum = upt;
      local.correction = (u - up) + (v - vpp);
   }
   return local.sum + local.correction;
}
