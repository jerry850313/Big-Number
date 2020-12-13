BigNumber: BigNumber.o

	g++ BigNumber.o -o BigNumber

BigNumber.o: BigNumber.cpp

	g++ -c BigNumber.cpp -o BigNumber.o

clean:

	rm *.o BigNumber