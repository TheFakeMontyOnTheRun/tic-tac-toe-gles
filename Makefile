CXXFLAGS = -O2 -g -c -std=c++0x -Iincludes
LDFLAGS = -lX11 -lGLESv2 -lEGL
CXX = clang++
OBJS = boilerplate/main.o boilerplate/render.o boilerplate/x11_gcc.o boilerplate/GLES2Lesson.o

TARGET = game

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
