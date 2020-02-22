PROG = predict
CFLAGS = -c -Wall -std=c++14 -g -O0 -MMD -MP
LIBS =

ALL_SOURCES := main.cpp
ALL_SOURCES += gua_info.cpp
ALL_SOURCES += gua_io.cpp
ALL_SOURCES += gua_representation.cpp

ALL_OBJECTS = $(ALL_SOURCES:.cpp=.o)
ALL_HEADER_DEPS:= $(ALL_OBJECTS:.o=.d)

.PHONY: clean all

all: $(PROG)
	@echo "Job's done!"

%.o: %.cpp
	g++ $(CFLAGS) $< -o $@

-include $(ALL_HEADER_DEPS)

predict: $(ALL_OBJECTS)
	g++ $^ -o $@ $(LIBS)

clean:
	-/bin/rm $(PROG)
	-/bin/rm $(ALL_OBJECTS)
	-/bin/rm $(ALL_HEADER_DEPS)
