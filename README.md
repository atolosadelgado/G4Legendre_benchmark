Numerical and time test of different implementations of Legendre polynomials
============================================================================

# Structure of this repository:

## include
The files with name "test_*.hh" Contain the Google tests and benchmarks for each implementation. The file "test_config.hh" contain the global configuration for all the tests (array of points to evaluate the functions, number of iterations for the benchmark, etc).

In addition, two custom implementations of Legendre polynomials (LegAutoP.hh, LegTabP.hh) are also here.

## src

Each model is tested individually. Google benchmark and test require an explicit main function to work together, which is provided in the files "test_*.cc" for each implementation.

## output

Results of running the test in a laptop and lxplus at Cern.
