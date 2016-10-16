#!/bin/bash

rm -rf tc && mkdir tc && python runner.py

echo 2 > tc/panitia_sample.in
for i in {1..2}; do
	cat "tc/sample_$i.in" >> tc/panitia_sample.in
done

../solution_irvan < tc/panitia_sample.in > tc/panitia_sample.out

echo 10 > tc/panitia_1.in
for i in {1..10}; do
	cat "tc/random_$i.in" >> tc/panitia_1.in
done

../solution_irvan < tc/panitia_1.in > tc/panitia_1.out


echo 10 > tc/panitia_2.in
for i in {1..3}; do
	cat "tc/best_$i.in" >> tc/panitia_2.in
done
for i in {1..3}; do
	cat "tc/worst_$i.in" >> tc/panitia_2.in
done
for i in {1..4}; do
	cat "tc/special_$i.in" >> tc/panitia_2.in
done

../solution_irvan < tc/panitia_2.in > tc/panitia_2.out


echo 10 > tc/panitia_3.in
for i in {1..2}; do
	cat "tc/proportional_$i.in" >> tc/panitia_3.in
done
for i in {1..6}; do
	cat "tc/limited_shirts_$i.in" >> tc/panitia_3.in
done
for i in {1..2}; do
	cat "tc/none_$i.in" >> tc/panitia_3.in
done

../solution_irvan < tc/panitia_3.in > tc/panitia_3.out

rm tc/r* tc/b* tc/w* tc/s* tc/pr* tc/l* tc/n*
