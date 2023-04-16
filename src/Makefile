CXXFLAGS := -std=c++17 -Wall -ggdb -O0
HEADERS := $(wildcard *.hpp)
SOURCES := $(wildcard *.cpp)
OBJS := $(SOURCES:%.cpp=%.o)

TARGET := main

LDFLAGS := -L/usr/local/lib
LDLIBS := -lgtest -lgtest_main -pthread

.PHONY : all
all : $(TARGET)

%.o : %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	rm -rf $(TARGET) $(OBJS)