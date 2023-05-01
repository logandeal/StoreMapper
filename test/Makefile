CXXFLAGS := -std=c++17 -Wall -ggdb -O0
HEADERS := $(wildcard *.hpp)
#SOURCES := $(wildcard *.cpp)
SOURCES := main.cpp ../src/BruteForceStrategy.cpp ../src/Context.cpp ../src/GroceryStore.cpp ../src/ItemNode.cpp ../src/NearestNeighborStrategy.cpp ../src/ShoppingList.cpp ../src/TwoOptStrategy.cpp
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