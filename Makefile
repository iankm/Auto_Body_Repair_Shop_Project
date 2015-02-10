C++ = g++
CFLAGS = -c -g

all: Part1 Part2

Part1: Do.o ML_hash.o random_op.o
			 $(C++) -o Part1 Do.o ML_hash.o random_op.o

Part2:	 ML_hash.o Vehicle.o Car.o Hybrid.o Autorepair.o Bus.o Motorcycle.o Bill.o
			 $(C++)  -o Part2 ML_hash.o Vehicle.o Car.o Hybrid.o Autorepair.o Bus.o Motorcycle.o Bill.o

clean:
		rm -f *.o *.gch

%.o:	%.cpp
		$(C++) $(CFLAGS) $*.cpp
