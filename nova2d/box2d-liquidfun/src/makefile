CC := em++ -std=c++14
CFLAGS :=

I1 := -I.\

SRCS := $(wildcard Box2D/*.cpp) $(wildcard Box2D/Collision/*.cpp) $(wildcard Box2D/Common/*.cpp) $(wildcard Box2D/Dynamics/*.cpp)  $(wildcard Box2D/Dynamics/Contacts/*.cpp) $(wildcard Box2D/Dynamics/Joints/*.cpp) $(wildcard Box2D/Particle/*.cpp) $(wildcard Box2D/Rope/*.cpp)

objects := $(SRCS:.cpp=.o)
objectsInOut := $(addprefix out/,$(objects))

all: $(objects)

$(objects): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(I1) $< -o out/$@
	
library:
	emar -crs box2d.a $(objectsInOut)