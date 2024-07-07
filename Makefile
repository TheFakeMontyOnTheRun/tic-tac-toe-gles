CXXFLAGS = -O2 -g -c -std=c++14 -Iincludes -Iincludes/glm-trunk -IGame -Iboilerplate -ISoundSystem
LDFLAGS = -lX11 -lGLESv2 -lEGL -lpng -lopenal

OBJS = boilerplate/main.o boilerplate/render.o boilerplate/x11_gcc.o boilerplate/GLES2Lesson.o Game/Game.o \
    boilerplate/Material.o boilerplate/MaterialList.o boilerplate/MeshObject.o boilerplate/NativeBitmap.o \
    boilerplate/Scene.o boilerplate/Trig.o boilerplate/TrigBatch.o boilerplate/Texture.o \
    boilerplate/WavefrontOBJReader.o boilerplate/CAnimation.o Game/GameRenderListener.o \
    SoundSystem/SoundClip.o SoundSystem/SoundEmitter.o SoundSystem/SoundListener.o SoundSystem/SoundUtils.o

TARGET = game

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
