cls
del game.htmp game.js
em++ -std=c++0x EXPORTED_FUNCTIONS="['_main', '_int_sqrt']" -s USE_ZLIB=1 -s USE_LIBPNG=1 -s FULL_ES2=1 --preload-file res --use-preload-plugins -Iincludes -IGame -Iincludes/glm-trunk boilerplate/main.cpp boilerplate/render.cpp boilerplate/x11.cpp boilerplate/GLES2Lesson.cpp  boilerplate/Material.cpp boilerplate/MaterialList.cpp boilerplate/MeshObject.cpp boilerplate/NativeBitmap.cpp boilerplate/Scene.cpp boilerplate/Trig.cpp boilerplate/TrigBatch.cpp boilerplate/Texture.cpp boilerplate/WavefrontOBJReader.cpp Game/Game.cpp -o game.html
