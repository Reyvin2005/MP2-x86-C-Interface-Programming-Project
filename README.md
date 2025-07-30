# MP2-x86-C-Interface-Programming-Project
**LBYARCH, 12A**
**Submitted by: Group 9**

**Siongco, Raine Margaux A.**

**Tan, Reyvin Matthew T.** 

## I. Comparative execution time and short analysis of the performance of the kernels 

| Vector Size | C Time (s) | ASM Time (s) | Speedup (C time/ASM time) | Faster Version | Correctness |
|-------------|------------|--------------|---------------------------|----------------|-------------|
| 2²⁰         | 0.003767   | 0.003300     |          1.14×            | Assembly       | PASSED      |
| 2²⁴         | 0.063367   | 0.047633     |          1.33×            | Assembly       | PASSED      |
| 2²⁸         | 1.304900   | 1.432833     |          0.91×            | C              | PASSED      |

**Speedup is used to determine how much faster the ASM version is than the C version**
- For small (2²⁰) to medium vector sizes (2²⁴), the Assembly version is 0.003300 seconds and 0.047633 seconds respectively. Consistently outperforming the C version (0.003767 seconds, 0.063367 seconds) being 1.14 and 1.33 times faster.
- For very large vectors (2²⁸), the C version (1.304900 seconds) outperforms Assembly (1.432833 seconds) being 0.91 times faster, this may be possibly due to memory or hardware constraints.
- All results maintain correctness and are all the same outputs, showing that optimization did not compromise output accuracy.
- This suggests Assembly is best used for performance-critical applications with moderate-sized data while C is better for larger sizes.

## II. Screenshot: Program Outputs with Correctness Check 

<img width="614" height="426" alt="image" src="https://github.com/user-attachments/assets/093ff9f5-08aa-4d7a-bb4a-9abc63720b85" />

## III. Short Video:


