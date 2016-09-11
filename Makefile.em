CXXFLAGS = -O2 -g -c -std=c++0x -Iincludes -Iincludes/glm-trunk -IGame -s USE_ZLIB=1 -s USE_LIBPNG=1 -s FULL_ES2=1
LDFLAGS =  -O2 -s EXPORTED_FUNCTIONS="['_main', '_int_sqrt']" -s USE_ZLIB=1 -s USE_LIBPNG=1 -s FULL_ES2=1 --preload-file res --use-preload-plugins
CXX = em++
CC = emcc
OBJS = boilerplate/main.o boilerplate/render.o boilerplate/x11.o boilerplate/GLES2Lesson.o Game/Game.o

TARGET = game.html

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
	rm *.js
