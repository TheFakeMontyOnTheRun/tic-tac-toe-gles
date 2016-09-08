CXXFLAGS = -O2 -g -c -std=c++0x -Iincludes
#LDFLAGS = -lX11 -lGLESv2 -lEGL
CXX = em++
OBJS = boilerplate/main.o boilerplate/render.o boilerplate/x11.o boilerplate/GLES2Lesson.o

TARGET = game.html

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
	rm *.js
