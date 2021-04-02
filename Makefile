CC = g++
CE = -Wall -pedantic -Wextra -g -std=c++14
NAME = omraidav

# commands

# contruct output file
.PHONY:	main
main:	src/build/main.o	src/build/CFile.o	src/build/CFile.o	src/build/CController.o	src/build/CData.o	src/build/CAudio.o	src/build/CCompressed.o	src/build/CDatabase.o	src/build/CDiskMedia.o	src/build/CExe.o	src/build/CFolder.o	src/build/CLink.o	src/build/CPhoto.o	src/build/CProgramming.o	src/build/CText.o	src/build/CVideo.o	src/build/CUnknown.o

.PHONY: all
all: main

# construct binary file
.PHONY: compile
compile: $(NAME)

#	do nothing, documentation is already in doc/ file
.PHONY: doc

# clean all program data
.PHONY: clean
clean:
	rm -rf ./src/build 2>/dev/null
	rm -rf ./$(NAME) 2>/dev/null

# runs the program
.PHONY:	run
run:	$(NAME)
	./$(NAME)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
$(NAME): src/build/main.o	src/build/CFile.o	src/build/CFile.o src/build/CController.o src/build/CData.o src/build/CAudio.o src/build/CCompressed.o src/build/CDatabase.o src/build/CDiskMedia.o src/build/CExe.o src/build/CFolder.o src/build/CLink.o src/build/CPhoto.o src/build/CProgramming.o src/build/CText.o src/build/CVideo.o src/build/CUnknown.o
	$(CC) src/build/main.o src/build/CFile.o src/build/CController.o src/build/CData.o src/build/CAudio.o src/build/CCompressed.o src/build/CDatabase.o src/build/CDiskMedia.o src/build/CExe.o src/build/CFolder.o src/build/CLink.o src/build/CPhoto.o src/build/CProgramming.o src/build/CText.o src/build/CVideo.o src/build/CUnknown.o -o $(NAME)

src/build/main.o: src/main.cpp src/CController.hpp
	mkdir -p src/build
	$(CC) $(CE) -c src/main.cpp -o src/build/main.o

# Classes

# class CController
src/build/CController.o: src/CController.cpp	src/CController.hpp	src/CData.hpp
	$(CC) $(CE) -c src/CController.cpp -o src/build/CController.o

# class CFile
src/build/CFile.o:	src/CFile.cpp	src/CFile.hpp
	$(CC) $(CE) -c src/CFile.cpp -o src/build/CFile.o

# class CData
src/build/CData.o:	src/CData.cpp	src/CData.hpp	src/CAudio.hpp	src/CCompressed.hpp	src/CDatabase.hpp	src/CDiskMedia.hpp	src/CExe.hpp	src/CFolder.hpp	src/CLink.hpp	src/CPhoto.hpp	src/CProgramming.hpp	src/CText.hpp	src/CVideo.hpp	src/CUnknown.hpp
	$(CC) $(CE) -c src/CData.cpp -o src/build/CData.o

src/build/CAudio.o:	src/CAudio.cpp	src/CAudio.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CAudio.cpp -o src/build/CAudio.o

src/build/CCompressed.o:	src/CCompressed.cpp	src/CCompressed.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CCompressed.cpp -o src/build/CCompressed.o

src/build/CDatabase.o:	src/CDatabase.cpp	src/CDatabase.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CDatabase.cpp -o src/build/CDatabase.o

src/build/CDiskMedia.o:	src/CDiskMedia.cpp	src/CDiskMedia.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CDiskMedia.cpp -o src/build/CDiskMedia.o

src/build/CExe.o:	src/CExe.cpp	src/CExe.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CExe.cpp -o src/build/CExe.o

src/build/CFolder.o:	src/CFolder.cpp	src/CFolder.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CFolder.cpp -o src/build/CFolder.o

src/build/CLink.o: src/CLink.cpp	src/CLink.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CLink.cpp -o src/build/CLink.o

src/build/CPhoto.o:	src/CPhoto.cpp	src/CPhoto.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CPhoto.cpp -o src/build/CPhoto.o

src/build/CProgramming.o:	src/CProgramming.cpp	src/CProgramming.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CProgramming.cpp -o src/build/CProgramming.o

src/build/CText.o:	src/CText.cpp	src/CText.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CText.cpp -o src/build/CText.o

src/build/CVideo.o:	src/CVideo.cpp	src/CVideo.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CVideo.cpp -o src/build/CVideo.o

src/build/CUnknown.o:	src/CUnknown.cpp	src/CUnknown.hpp	src/CFile.hpp
	$(CC) $(CE) -c src/CUnknown.cpp -o src/build/CUnknown.o
