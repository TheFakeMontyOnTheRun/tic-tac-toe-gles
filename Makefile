CXXFLAGS = -O2 -g -c -std=c++0x -Iincludes -Iincludes/glm-trunk -IGame
LDFLAGS = -lX11 -lGLESv2 -lEGL -lpng
CXX = clang++
OBJS = boilerplate/main.o boilerplate/render.o boilerplate/x11_gcc.o boilerplate/GLES2Lesson.o Game/Game.o \
    boilerplate/Material.o boilerplate/MaterialList.o boilerplate/MeshObject.o boilerplate/NativeBitmap.o \
    boilerplate/Scene.o boilerplate/Trig.o boilerplate/TrigBatch.o boilerplate/Texture.o \
    boilerplate/WavefrontOBJReader.o

TARGET = game

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
