g++ principal.cpp floydwarshall.cpp -o main -Wall

./main < ../casosDeTeste/1.in > ../casosDeTeste/execution_1.out
./main < ../casosDeTeste/2.in > ../casosDeTeste/execution_2.out
./main < ../casosDeTeste/3.in > ../casosDeTeste/execution_3.out
./main < ../casosDeTeste/4.in > ../casosDeTeste/execution_4.out
./main < ../casosDeTeste/5.in > ../casosDeTeste/execution_5.out

cd ../casosDeTeste

diff 1.out execution_1.out
diff 2.out execution_2.out
diff 3.out execution_3.out
diff 4.out execution_4.out
diff 5.out execution_5.out

cd ../src

echo "Terminei"