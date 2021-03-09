#include <iostream>
#include <omp.h>

int main(int, char **) {
  omp_set_dynamic(1);
  int num_dynamic_threads = omp_get_dynamic();
  int tid(-1);
  int maxthreads = omp_get_max_threads();
#pragma omp parallel private(tid)
  {
    std::cout << "omp parallel block 2" << std::endl;
    int nthreads = omp_get_num_threads();
    tid = omp_get_thread_num();
    if (tid == 0) {
      std::cout << "Using OMP threads."
                << "\n   OMP thread     : " << tid << "\n   OMP num threads: " << nthreads
                << ", maxthreads = " << maxthreads << "\n   Dynamic threads : "
                << (num_dynamic_threads == 0 ? std::string("OFF") : std::string("ON")) << "\n"
                << std::endl;
    }
  }
  return 0;
}
