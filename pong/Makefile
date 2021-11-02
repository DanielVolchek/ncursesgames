game: pong.o bubble.o paddle.o ball.o
	g++ -o game pong.o bubble.o paddle.o ball.o -l ncurses
#main call
pong.o: pong.cpp
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
clean:
	rm pong.o bubble.o paddle.o ball.o game
#removed * for safety
#add extra for new objects
