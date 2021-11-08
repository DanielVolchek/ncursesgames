main: main.o pong_ snake_ conway_
	g++ -o game main.o -l ncurses
#main call
pong_: pong_exec.o pong.o bubble.o ball.o paddle.o
	g++ -o .pong pong_exec.o pong.o bubble.o ball.o paddle.o -l ncurses
snake_: snake_exec.o snake.o getinput.o
	g++ -o .snake snake_exec.o snake.o getinput.o -l ncurses
conway_: conway.o
	g++ -o .conway conway.o -l ncurses
#pong executable
main.o: main.cpp
	g++ -c main.cpp
#main code
pong_exec.o: pong/pong_exec.cpp
	g++ -c pong/pong_exec.cpp
#pong executable
#snake executable
# *Pong Dependencies* #
pong.o: pong/pong.cpp pong/pong.h
	g++ -c pong/pong.cpp
#game
bubble.o: pong/bubble.cpp pong/bubble.h
	g++ -c pong/bubble.cpp
#letters
paddle.o: pong/paddle.cpp pong/paddle.h
	g++ -c pong/paddle.cpp
#paddle
ball.o: pong/ball.cpp pong/ball.h
	g++ -c pong/ball.cpp
#ball
# *Snake Dependencies* #
snake_exec.o: snake/snake_exec.cpp
	g++ -c snake/snake_exec.cpp
snake.o: snake/snake.cpp snake/snake.h
	g++ -c snake/snake.cpp
getinput.o: snake/getinput.cpp snake/getinput.o
	g++ -c snake/getinput.cpp
# *Conway GoL Dependencies* #
conway.o: conway/conway.cpp
	g++ -c conway/conway.cpp
clear:
	rm *.o game ./.pong ./.snake

