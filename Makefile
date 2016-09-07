CXXFLAGS = -O2 -g -c -std=c++0x
LDFLAGS = -lX11 -lGLESv2 -lEGL
CXX = clang++
OBJS = main.o render.o x11_gcc.o GLES2Lesson.o

TARGET = demo

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
