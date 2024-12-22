CC := g++
CXXFLAGS := 
LIBS := 
SRC_DIR := source
INCDIR := include
OBJDIR := obj

SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')

OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

EXECUTABLE := sea_battle

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CXXFLAGS) $^ -o $@ $(LIBS)


$(OBJDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) $(EXECUTABLE)

.PHONY: all clean docs
