cmake_minimum_required(VERSION 3.13)
project(tic_tac_toe_gles)

set(CMAKE_CXX_STANDARD 14)

include_directories(boilerplate)
include_directories(Game)
include_directories(includes)
include_directories(includes/glm-trunk/glm)
include_directories(includes/glm-trunk/glm/detail)
include_directories(includes/glm-trunk/glm/gtc)
include_directories(includes/glm-trunk/glm/gtx)
include_directories(includes/glm-trunk/glm/simd)
include_directories(includes/glm-trunk/test/external/gli)
include_directories(includes/glm-trunk/test/external/gli/core)
include_directories(includes/glm-trunk/test/external/gli/gtx)
include_directories(SoundSystem)

add_executable(tic_tac_toe_gles
		boilerplate/CAnimation.cpp
		boilerplate/CAnimation.h
		boilerplate/GLES2Lesson.cpp
		boilerplate/GLES2Lesson.h
		boilerplate/glue.h
		boilerplate/main.cpp
		boilerplate/Material.cpp
		boilerplate/Material.h
		boilerplate/MaterialList.cpp
		boilerplate/MaterialList.h
		boilerplate/MeshObject.cpp
		boilerplate/MeshObject.h
		boilerplate/NativeBitmap.cpp
		boilerplate/NativeBitmap.h
		boilerplate/render.cpp
		boilerplate/Scene.cpp
		boilerplate/Scene.h
		boilerplate/Texture.cpp
		boilerplate/Texture.h
		boilerplate/Trig.cpp
		boilerplate/Trig.h
		boilerplate/TrigBatch.cpp
		boilerplate/TrigBatch.h
		boilerplate/WavefrontOBJReader.cpp
		boilerplate/WavefrontOBJReader.h
		boilerplate/x11.cpp
		boilerplate/x11_gcc.cpp
		Game/Game.cpp
		Game/Game.h
		Game/GameRenderListener.cpp
		Game/GameRenderListener.h
		SoundSystem/SoundClip.cpp
		SoundSystem/SoundClip.h
		SoundSystem/SoundEmitter.cpp
		SoundSystem/SoundEmitter.h
		SoundSystem/SoundListener.cpp
		SoundSystem/SoundListener.h
		SoundSystem/SoundUtils.cpp
		SoundSystem/SoundUtils.h)
