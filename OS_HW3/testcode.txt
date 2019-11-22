g++ -Wall -o 0616027_ST 0616027_ST.cpp

time ./0616027_ST <input1.txt> output1_ST.txt

time ./0616027_ST <input2.txt> output2_ST.txt

g++ -Wall -o 0616027_MT 0616027_MT.cpp -lpthread

time ./0616027_MT <input1.txt> output1_MT.txt

time ./0616027_MT <input2.txt> output2_MT.txt

python print.py < input1.txt > testdata.txt

time ./0616027_ST < testdata.txt > o1.txt

time ./0616027_MT < testdata.txt > o2.txt

