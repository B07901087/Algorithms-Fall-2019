#! /bin/bash
for i in {1..8}
do
    echo "======= case${i} ========="
    ./pa3_checker public_cases/public_case_${i}.in output/piblic_case_${i}.out
done
