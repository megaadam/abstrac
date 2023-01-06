SRCS = src/*.cpp
FLAGS = -Wall
FLAGS_DBG = -g $(FLAGS)
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt
BIN = bin/abstrac_engine
OUT = -o $(BIN)

build:
	g++ $(FLAGS) $(SRCS) $(OUT) $(LDLIBS)

debug:
	g++ $(FLAGS_DBG) $(SRCS) $(OUT) $(LDLIBS)

run: build
	$(BIN)
