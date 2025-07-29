# MP2-x86-C-Interface-Programming-Project
**Submitted by:**
**Siongco, Raine Margaux A.**
**Tan, Reyvin Matthew** 

I. Comparative execution time and short analysis of the performance of the kernels 

| Vector Size | C Time (s) | ASM Time (s) | Speedup (C/ASM) | Faster Version | Correctness |
|-------------|------------|--------------|-----------------|----------------|-------------|
| 2²⁰         | 0.003767   | 0.003300     | 1.14×           | Assembly       | ✅          |
| 2²⁴         | 0.063367   | 0.047633     | 1.33×           | Assembly       | ✅          |
| 2²⁸         | 1.304900   | 1.432833     | 0.91×           | C              | ✅          |

- For small to medium vector sizes, the Assembly version consistently outperforms the C version.
- For very large vectors, the C version outperforms Assembly, possibly due to memory or hardware constraints.
- All results maintain correctness, showing that optimization did not compromise output accuracy.
- This suggests Assembly is best used for performance-critical applications with moderate-sized data.

II. Screenshot: Program Output with Correctness Check 

<img width="614" height="426" alt="image" src="https://github.com/user-attachments/assets/093ff9f5-08aa-4d7a-bb4a-9abc63720b85" />

III. Short Video:


