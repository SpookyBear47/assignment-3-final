CC=g++
CFLAGS=-c -Wall -std=c++11
LFLAGS=-Wall -std=c++11
DEPS=coffee.h menu.h order.h shop.h
OBJ=coffee.o menu.o order.o shop.o prog.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

prog: $(OBJ)
	$(CC) $(LFLAGS) -o $@ $^

coffee.o: coffee.cpp coffee.h
	$(CC) $(CFLAGS) -o $@ $<

menu.o: menu.cpp menu.h coffee.h
	$(CC) $(CFLAGS) -o $@ $<

order.o: order.cpp order.h coffee.h
	$(CC) $(CFLAGS) -o $@ $<

shop.o: shop.cpp shop.h menu.h order.h
	$(CC) $(CFLAGS) -o $@ $<

prog.o: prog.cpp shop.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) prog
