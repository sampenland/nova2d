CC := em++ -std=c++14
CFLAGS :=

I1 = -I.\box2d

SRCS := $(wildcard *.cpp) 

objects := $(SRCS:.cpp=.o)
objectsInOut := $(addprefix out/,$(objects))

all: $(objects)

$(objects): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(I1) $< -o out/$@
	
library:
	emar -crs box2d.a $(objectsInOut)