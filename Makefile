CC= clang++
PROG= ./bin/tetris
OBJS= ./src/main.o ./src/Tetris.o ./src/log.o
LIBS= allegro-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_color-5.0
CXXFLAGS= -g -Wall -std=c++11 $(shell pkg-config --cflags ${LIBS})
LDFLAGS= $(shell pkg-config --static --libs ${LIBS})

all: $(PROG)

$(PROG): $(OBJS)
	mkdir -p ./bin/
	$(CC) -o $(PROG) $(LDFLAGS) $(CFLAGS) $(OBJS)
	rm -f $(OBJS)

clean:
	rm -f $(PROG) $(TEST_PROG) $(OBJS)