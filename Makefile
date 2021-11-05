main: main.o pong.o bubble.o ball.o paddle.o snake.o getinput.o
	g++ -o game main.o pong.o bubble.o paddle.o ball.o snake.o getinput.o -l ncurses
#main call
main.o: main.cpp
	g++ -c main.cpp
#main code
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
snake.o: snake/snake.cpp snake/snake.h
	g++ -c snake/snake.cpp
getinput.o: snake/getinput.cpp snake/getinput.o
	g++ -c snake/getinput.cpp
clear:
	rm *.o game

