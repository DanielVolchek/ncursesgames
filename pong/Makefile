main: main.o pong.o bubble.o ball.o paddle.o
	g++ -o game pong_exec.o pong.o bubble.o paddle.o ball.o -l ncurses
#main call
main.o: pong_exec.cpp
	g++ -c pong_exec.cpp
#main code
pong.o: pong.cpp pong.h
	g++ -c pong.cpp
#game
bubble.o: bubble.cpp bubble.h
	g++ -c bubble.cpp
#letters
paddle.o: paddle.cpp paddle.h
	g++ -c paddle.cpp
#paddle
ball.o: ball.cpp ball.h
	g++ -c ball.cpp
#ball
clear:
	rm *.o game
#removed * for safety
#add extra for new objects
