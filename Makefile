SRCS = src/*.cpp
FLAGS = -Wall
FLAGS_DBG = -g $(FLAGS)
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt
BIN = bin/abstrac-engine
OUT = -o $(BIN)

REMOTE = root@nova
REMOTE_BIN = $(REMOTE):/usr/bin
REMOTE_SYSTEMD = $(REMOTE):/etc/systemd/system

build:
	g++ $(FLAGS) $(SRCS) $(OUT) $(LDLIBS)

debug:
	g++ $(FLAGS_DBG) $(SRCS) $(OUT) $(LDLIBS)

run: build
	$(BIN)

deploy: build
	ssh $(REMOTE) systemctl stop abstrac-engine.service

	scp $(BIN) $(REMOTE_BIN)
	scp service/abstrac-engine-starter $(REMOTE_BIN)
	scp service/abstrac-engine.service $(REMOTE_SYSTEMD)
	scp service/abstrac-engine.timer   $(REMOTE_SYSTEMD)

	scp service/abstrac-engine-stop.timer   $(REMOTE_SYSTEMD)
	scp service/abstrac-engine-stop.service   $(REMOTE_SYSTEMD)

	ssh $(REMOTE) systemctl daemon-reload
	ssh $(REMOTE) systemctl start abstrac-engine.service
	ssh $(REMOTE) systemctl start abstrac-engine.timer
	ssh $(REMOTE) systemctl start abstrac-engine-stop.timer

	ssh $(REMOTE) systemctl enable abstrac-engine.timer
	ssh $(REMOTE) systemctl enable abstrac-engine-stop.timer

	ssh $(REMOTE) systemctl status abstrac-engine.service
