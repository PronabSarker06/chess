CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla
EXEC = chess-exec
OBJECTS = Move.o main.o King.o Bishop.o Knight.o Rook.o Queen.o Pawn.o Board.o Game.o Piece.o Position.o window.o # Comment out for Q3
#OBJECTS = subject.o main.o grid.o textdisplay.o cell.o graphicsdisplay.o window.o # Uncomment for Q3
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 # Comment out for Q3
	#${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 # Uncomment for Q3

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
