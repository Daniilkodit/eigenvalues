CXX = g++
CXXFLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused \
           -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal \
           -Wpointer-arith -Wformat-security -Wmissing-format-attribute \
           -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long \
           -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual \
           -Wno-suggest-attribute=format -fsanitize=address -fno-omit-frame-pointer

LDFLAGS = -lm  -fsanitize=address

TARGET = a.out

SRCS = main.cpp Amethods.cpp Transformation.cpp QR.cpp Disrepancy.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp header.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

Amethods.o: Amethods.cpp header.h
	$(CXX) $(CXXFLAGS) -c Amethods.cpp -o Amethods.o

Transformation.o: Transformation.cpp header.h
	$(CXX) $(CXXFLAGS) -c Transformation.cpp -o Transformation.o

QR.o: QR.cpp header.h
	$(CXX) $(CXXFLAGS) -c QR.cpp -o QR.o

Disrepancy.o: Disrepancy.cpp header.h
	$(CXX) $(CXXFLAGS) -c Disrepancy.cpp -o Disrepancy.o

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all


.PHONY: all clean rebuild
