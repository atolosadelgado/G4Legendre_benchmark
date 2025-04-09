```
./build/benchmark 
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from LegendreTest
[ RUN      ] LegendreTest.LegAutoP_vs_STL
[       OK ] LegendreTest.LegAutoP_vs_STL (49 ms)
[ RUN      ] LegendreTest.Boost_vs_STL
[       OK ] LegendreTest.Boost_vs_STL (261 ms)
[ RUN      ] LegendreTest.LegTabP_vs_STL
[       OK ] LegendreTest.LegTabP_vs_STL (162 ms)
[ RUN      ] LegendreTest.G4NuclNuclDiffuseElastic_cos_vs_STL
/home/alvarotd/work/G4Legendre_benchmark/src/your_file.cc:200: Failure
The difference between max_difference and 0.0 is 375.98078024450302, which exceeds tolerance, where
max_difference evaluates to 375.98078024450302,
0.0 evaluates to 0, and
tolerance evaluates to 1.0000000000000001e-09.
Mismatch at n=7, max difference =375.98078024450302
/home/alvarotd/work/G4Legendre_benchmark/src/your_file.cc:200: Failure
The difference between max_difference and 0.0 is 351.63299046470547, which exceeds tolerance, where
max_difference evaluates to 351.63299046470547,
0.0 evaluates to 0, and
tolerance evaluates to 1.0000000000000001e-09.
Mismatch at n=8, max difference =351.63299046470547
/home/alvarotd/work/G4Legendre_benchmark/src/your_file.cc:200: Failure
The difference between max_difference and 0.0 is 331.46534568098974, which exceeds tolerance, where
max_difference evaluates to 331.46534568098974,
0.0 evaluates to 0, and
tolerance evaluates to 1.0000000000000001e-09.
Mismatch at n=9, max difference =331.46534568098974
/home/alvarotd/work/G4Legendre_benchmark/src/your_file.cc:200: Failure
The difference between max_difference and 0.0 is 314.40410614089882, which exceeds tolerance, where
max_difference evaluates to 314.40410614089882,
0.0 evaluates to 0, and
tolerance evaluates to 1.0000000000000001e-09.
Mismatch at n=10, max difference =314.40410614089882
[  FAILED  ] LegendreTest.G4NuclNuclDiffuseElastic_cos_vs_STL (375 ms)
[ RUN      ] LegendreTest.G4LegendrePolynomial_vs_STL
[       OK ] LegendreTest.G4LegendrePolynomial_vs_STL (289 ms)
[----------] 5 tests from LegendreTest (1137 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (1138 ms total)
[  PASSED  ] 4 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] LegendreTest.G4NuclNuclDiffuseElastic_cos_vs_STL

 1 FAILED TEST
2025-04-09T17:33:10+02:00
Running ./build/benchmark
Run on (8 X 4200 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x1)
Load Average: 0.87, 0.68, 0.57
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------------------------------------------
Benchmark                                                   Time             CPU   Iterations
---------------------------------------------------------------------------------------------
BM_STD/0/iterations:1000                              1266466 ns      1261954 ns         1000
BM_STD/1/iterations:1000                              1361114 ns      1357994 ns         1000
BM_STD/2/iterations:1000                              2190988 ns      2186726 ns         1000
BM_STD/3/iterations:1000                              2934407 ns      2930133 ns         1000
BM_STD/4/iterations:1000                              4988209 ns      4966471 ns         1000
BM_STD/5/iterations:1000                              7223252 ns      7202603 ns         1000
BM_STD/6/iterations:1000                              8886805 ns      8868533 ns         1000
BM_STD/7/iterations:1000                             11896927 ns     11868022 ns         1000
BM_STD/8/iterations:1000                             13990605 ns     13965391 ns         1000
BM_STD/9/iterations:1000                             16521771 ns     16494176 ns         1000
BM_STD/10/iterations:1000                            21115196 ns     21081262 ns         1000
BM_Boost/0/iterations:1000                            5531649 ns      5521377 ns         1000
BM_Boost/1/iterations:1000                            5548169 ns      5537416 ns         1000
BM_Boost/2/iterations:1000                            5548276 ns      5537099 ns         1000
BM_Boost/3/iterations:1000                            6620799 ns      6606910 ns         1000
BM_Boost/4/iterations:1000                            8490756 ns      8474437 ns         1000
BM_Boost/5/iterations:1000                           10995739 ns     10976422 ns         1000
BM_Boost/6/iterations:1000                           14656078 ns     14619725 ns         1000
BM_Boost/7/iterations:1000                           17389277 ns     17359355 ns         1000
BM_Boost/8/iterations:1000                           19662242 ns     19626618 ns         1000
BM_Boost/9/iterations:1000                           22313217 ns     22273169 ns         1000
BM_Boost/10/iterations:1000                          25241898 ns     25200767 ns         1000
BM_LegTabP/0/iterations:1000                          4152929 ns      4147397 ns         1000
BM_LegTabP/1/iterations:1000                          4158231 ns      4152515 ns         1000
BM_LegTabP/2/iterations:1000                          4218484 ns      4211536 ns         1000
BM_LegTabP/3/iterations:1000                          4179895 ns      4169150 ns         1000
BM_LegTabP/4/iterations:1000                          4177759 ns      4167672 ns         1000
BM_LegTabP/5/iterations:1000                          4215159 ns      4203047 ns         1000
BM_LegTabP/6/iterations:1000                          4129165 ns      4120285 ns         1000
BM_LegTabP/7/iterations:1000                          4166329 ns      4156424 ns         1000
BM_LegTabP/8/iterations:1000                          4172002 ns      4161800 ns         1000
BM_LegTabP/9/iterations:1000                          4146705 ns      4136837 ns         1000
BM_LegTabP/10/iterations:1000                         4163824 ns      4153281 ns         1000
BM_LegAutoP/0/iterations:1000                         2189050 ns      2183320 ns         1000
BM_LegAutoP/1/iterations:1000                         2203244 ns      2197363 ns         1000
BM_LegAutoP/2/iterations:1000                         2207476 ns      2201461 ns         1000
BM_LegAutoP/3/iterations:1000                         2227679 ns      2221404 ns         1000
BM_LegAutoP/4/iterations:1000                         2223321 ns      2217688 ns         1000
BM_LegAutoP/5/iterations:1000                         3218247 ns      3208483 ns         1000
BM_LegAutoP/6/iterations:1000                         4573439 ns      4562147 ns         1000
BM_LegAutoP/7/iterations:1000                         6323657 ns      6310096 ns         1000
BM_LegAutoP/8/iterations:1000                         7543038 ns      7528320 ns         1000
BM_LegAutoP/9/iterations:1000                         9442861 ns      9423755 ns         1000
BM_LegAutoP/10/iterations:1000                       11081503 ns     11061117 ns         1000
BM_LegTabP_cos/0/iterations:1000                     17152207 ns     17122102 ns         1000
BM_LegTabP_cos/1/iterations:1000                     17194833 ns     17173126 ns         1000
BM_LegTabP_cos/2/iterations:1000                     17941765 ns     17805180 ns         1000
BM_LegTabP_cos/3/iterations:1000                     17912618 ns     17816541 ns         1000
BM_LegTabP_cos/4/iterations:1000                     18286365 ns     18253429 ns         1000
BM_LegTabP_cos/5/iterations:1000                     19119985 ns     18848720 ns         1000
BM_LegTabP_cos/6/iterations:1000                     19117174 ns     18430472 ns         1000
BM_LegTabP_cos/7/iterations:1000                     17280916 ns     17260582 ns         1000
BM_LegTabP_cos/8/iterations:1000                     17593819 ns     17361220 ns         1000
BM_LegTabP_cos/9/iterations:1000                     17305088 ns     17284500 ns         1000
BM_LegTabP_cos/10/iterations:1000                    17364172 ns     17245448 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/0/iterations:1000    22257721 ns     22169251 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/1/iterations:1000    22005419 ns     21981779 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/2/iterations:1000    22251487 ns     22210266 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/3/iterations:1000    24368185 ns     24295622 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/4/iterations:1000    24680991 ns     24628565 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/5/iterations:1000    23180413 ns     23156041 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/6/iterations:1000    23206437 ns     23166679 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/7/iterations:1000    38233215 ns     38195342 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/8/iterations:1000    39200779 ns     38970479 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/9/iterations:1000    40020120 ns     39603976 ns         1000
BM_G4NuclNuclDiffuseElastic_cos/10/iterations:1000   41564046 ns     40816042 ns         1000
BM_G4LegendrePolynomial/0/iterations:1000             5291079 ns      5283510 ns         1000
BM_G4LegendrePolynomial/1/iterations:1000             5431847 ns      5421574 ns         1000
BM_G4LegendrePolynomial/2/iterations:1000             6627641 ns      6586925 ns         1000
BM_G4LegendrePolynomial/3/iterations:1000             6416270 ns      6190644 ns         1000
BM_G4LegendrePolynomial/4/iterations:1000             7228627 ns      6993342 ns         1000
BM_G4LegendrePolynomial/5/iterations:1000            14296226 ns     14272449 ns         1000
BM_G4LegendrePolynomial/6/iterations:1000            16482208 ns     16460114 ns         1000
BM_G4LegendrePolynomial/7/iterations:1000            19645150 ns     19221002 ns         1000
BM_G4LegendrePolynomial/8/iterations:1000            24790421 ns     23787685 ns         1000
BM_G4LegendrePolynomial/9/iterations:1000            27626340 ns     27559178 ns         1000
BM_G4LegendrePolynomial/10/iterations:1000           31688072 ns     31648301 ns         1000
```

