CC=g++
CFLAGS=-c -pedantic-errors
LDFLAGS=
SOURCES=main.cpp turingmachine.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tm

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
