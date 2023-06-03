CXXFLAGS = -O2 -g -c -std=c++14 -Iincludes -Iincludes/glm-trunk -IGame -Iboilerplate -ISoundSystem -DX11_GLUE
LDFLAGS =  -O2 -s EXPORTED_FUNCTIONS="['_main', '_int_sqrt']" -s USE_ZLIB=1 -s USE_LIBPNG=1 -s FULL_ES2=1 --preload-file res --use-preload-plugins  -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0 --shell-file ./minimal.html
CXX = em++
CC = emcc
OBJS = boilerplate/main.o boilerplate/render.o boilerplate/x11.o boilerplate/GLES2Lesson.o Game/Game.o \
    boilerplate/Material.o boilerplate/MaterialList.o boilerplate/MeshObject.o boilerplate/NativeBitmap.o \
    boilerplate/Scene.o boilerplate/Trig.o boilerplate/TrigBatch.o boilerplate/Texture.o \
    boilerplate/WavefrontOBJReader.o boilerplate/CAnimation.o Game/GameRenderListener.o \
    SoundSystem/SoundClip.o SoundSystem/SoundEmitter.o SoundSystem/SoundListener.o SoundSystem/SoundUtils.o


TARGET = index.html

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

all:	$(TARGET)

serve: $(TARGET)
	python3 -m http.server

dist: $(TARGET)
	zip dist.zip index.html index.data index.js index.wasm

clean:
	rm -f $(OBJS) $(TARGET)
	rm *~
	rm *.js
