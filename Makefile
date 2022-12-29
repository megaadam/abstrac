SRCS = src/*.cpp
FLAGS = -Wall
FLAGS_DBG = -g $(FLAGS)
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt
OUT = -o bin/engine


build:
	g++ $(FLAGS) $(SRCS) $(OUT) $(LDLIBS)

debug:
	g++ $(FLAGS_DBG) $(SRCS) $(OUT) $(LDLIBS)

run: build
	bin/engine
