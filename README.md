# MP2-x86-C-Interface-Programming-Project
**LBYARCH, 12A**
**Submitted by: Group 9**

**Siongco, Raine Margaux A.**

**Tan, Reyvin Matthew T.** 

## I. Comparative execution time and short analysis of the performance of the kernels 

| Vector Size | C Time (s) | ASM Time (s) | Speedup (C time / ASM time) | Faster Version | Correctness |
| ----------- | ---------- | ------------ | --------------------------- | -------------- | ----------- |
| 2²⁰         | 0.003133   | 0.001700     | 1.84×                       | Assembly       | PASSED      |
| 2²⁴         | 0.045200   | 0.017200     | 2.63×                       | Assembly       | PASSED      |
| 2²⁸         | 0.768167   | 0.475733     | 1.61×                       | Assembly       | PASSED      |

- Across all tested vector sizes, the Assembly implementation consistently outperforms the C version.

- For small (2²⁰), medium (2²⁴), and large (2²⁸) input sizes, the Assembly version demonstrates clear efficiency: 1.84×, 2.63×, and 1.61× faster, respectively.

- This improvement indicates effective vectorization and reduced overhead in the ASM version, especially evident in medium-sized data.

- All tests passed correctness checks, confirming identical output values between the two implementations.

- These results highlight Assembly’s advantage in speed for performance-critical operations, while C remains valid for ease of development and maintainability.

## II. Screenshot: Program Outputs with Correctness Check 



## III. Short Video:


