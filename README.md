# Parallel Diameter of a Convex Polygon (C++ / OpenMP)

**What this is.** The diameter of a convex polygon is the largest distance between any two of its vertices. This is a C++/OpenMP implementation of a parallel algorithm for it. The algorithm follows the presentation in Goodrich's algorithms textbook: points are converted to polar coordinates and split into "red" and "blue" chains, and candidate antipodal pairs are found with parallel prefix sums and merging. It was written as a parallel-algorithms exercise.

## Files

- `diameter.cpp`: the whole program (polar conversion, red/blue partition, prefix sums, antipodal-pair search, and `main`). The maximum number of vertices is the compile-time constant `maxi = 100`.

## Build and run

```bash
g++ -O2 -fopenmp -o diameter diameter.cpp
./diameter
```

`main()` runs a hard-coded 5-vertex example polygon (`(0,0), (0,2), (1,3), (2,2), (2,0)`). To try another convex polygon, edit the `polyg[]` assignments and the vertex count passed to `diameter(n)`. There is no file or stdin input. Part of a sequential reference loop is left commented out in the source ("implementation omitted"), so treat this as a teaching implementation.

## License

MIT, see `LICENSE`.
