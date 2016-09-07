CXXFLAGS = -O2 -g -c -std=c++0x
#LDFLAGS = -lX11 -lGLESv2 -lEGL
CXX = em++
OBJS = main.o render.o x11.o GLES2Lesson.o

TARGET = demo.html

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
