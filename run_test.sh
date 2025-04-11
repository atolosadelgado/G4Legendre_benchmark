#!/bin/bash

# switch to performance to avoid cpu scaling
#sudo cpupower frequency-set -g performance

# List of executables
executables=(
  test_LegAutoP
  test_CLHEP
  test_LegTabP
  test_Boost
  test_G4PHPFastLegendre
  test_G4LegendrePolynomial
  test_G4NuclNuclDiffuseElastic
  test_G4LegendrePolynomialAssoc
)

# Loop through each executable
for exe in "${executables[@]}"; do
  if [[ -x "./build/$exe" ]]; then
    echo "Running $exe..."
    ./build/$exe > "${exe}.txt" 2>&1
  else
    echo "Skipping $exe (not executable)"
  fi
done

