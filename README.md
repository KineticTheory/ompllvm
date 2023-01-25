# Summary

* The `/openmp:llvm` compile open for MSVC is throwing an assertion as captured by this small
  reproducer.

# Demonstration

* Use Developer Command Prompt for VS2022.
* `mkdir %build_dir%`
* `cd %build_dir%`
* `cmake -G "Visual Studio 17 2022" c:\ompllvm`
* `cmake --build . --config Debug`
* `Debug\tstomp.exe`

```
Assertion failure at D:\a\_work\1\s\src\vctools\asan\llvm\openmp\runtime\src\z_Windows_NT_util.cpp(1577): num >= 1.
OMP: Error #13: Assertion failure at D:\a\_work\1\s\src\vctools\asan\llvm\openmp\runtime\src\z_Windows_NT_util.cpp(1577).
OMP: Hint Please submit a bug report with this message, compile and run commands used, and machine configuration info
including native compiler and operating system versions. Faster response will be obtained by including all program
sources. For information on submitting this issue, please see https://bugs.llvm.org/.

```

# Status

* This issue was reported in March 2021 [here](https://developercommunity.visualstudio.com/t/-openmpllvm-runtime-failure-on-omp-parallel-privat/1359795) for Visual Studio 2019.
* The same issue continues to cause issues as of Jan 2023.
* A new clue that might be useful is the discovery that appending the `#pragma omp` line in
  `tstOMP.cc` with `num_threads(1)` eliminates the assertion.  Unfortunately, this also limits the
  number of threads to the scalar case.


