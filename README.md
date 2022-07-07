# Multi Threaded Calc Pi

Calculates PI by summing the circle's area, as explained here:

https://en.wikipedia.org/wiki/Approximations_of_%CF%80#Summing_a_circle's_area

The included driver (main.cpp) parses the command line arguments, calls count_pixels() and prints the results. The driver takes 2 command line arguments: an integer radius and number of threads. The function uint64_t count_pixels(int r, int N) takes two parameters – the radius and number of threads, and returns the number of pixels inside the circle or radius 𝑟 centered at (0,0) for every pixel (𝑥, 𝑦) in squre −𝑟 ≤ 𝑥, 𝑦 ≤ 𝑟.

To compile the code:
```
$ make
```

To run it with r=1000 and n_threads=1:
```
$ ./calcpi 1000 1
```

