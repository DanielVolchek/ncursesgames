CC:=g++
#compiler
CFLAGS:= -Wall -Wextra -pedantic -std=c++14
#flags
main: main.o pong_ snake_ conway_
	$(CC) $(CFLAGS) -o game main.o -l ncurses
#main call
pong_: pong_exec.o pong.o bubble.o ball.o paddle.o
	$(CC) $(CFLAGS) -o .pong pong_exec.o pong.o bubble.o ball.o paddle.o -l ncurses
snake_: snake_exec.o snake.o getinput.o
	$(CC) $(CFLAGS) -o .snake snake_exec.o snake.o getinput.o -l ncurses
conway_: conway.o
	$(CC) $(CFLAGS) -o .conway conway.o -l ncurses
#pong executable
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
#main code
pong_exec.o: pong/pong_exec.cpp
	$(CC) $(CFLAGS) -c pong/pong_exec.cpp
#pong executable
#snake executable
# *Pong Dependencies* #
pong.o: pong/pong.cpp pong/pong.h
	$(CC) $(CFLAGS) -c pong/pong.cpp
#game
bubble.o: pong/bubble.cpp pong/bubble.h
	$(CC) $(CFLAGS) -c pong/bubble.cpp
#letters
paddle.o: pong/paddle.cpp pong/paddle.h
	$(CC) $(CFLAGS) -c pong/paddle.cpp
#paddle
ball.o: pong/ball.cpp pong/ball.h
	$(CC) $(CFLAGS) -c pong/ball.cpp
#ball
# *Snake Dependencies* #
snake_exec.o: snake/snake_exec.cpp
	$(CC) $(CFLAGS) -c snake/snake_exec.cpp
snake.o: snake/snake.cpp snake/snake.h
	$(CC) $(CFLAGS) -c snake/snake.cpp
getinput.o: snake/getinput.cpp snake/getinput.o
	$(CC) $(CFLAGS) -c snake/getinput.cpp
# *Conway GoL Dependencies* #
conway.o: conway/conway.cpp
	$(CC) $(CFLAGS) -c conway/conway.cpp
clean:
	rm *.o game ./.pong ./.snake

