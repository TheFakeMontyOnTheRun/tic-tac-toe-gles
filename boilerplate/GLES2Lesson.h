//
// Created by monty on 23/11/15.
//

#ifndef LESSON02_GLES2LESSON_H
#define LESSON02_GLES2LESSON_H

namespace odb {

	class GLES2Lesson {

		void fetchShaderLocations();

		void setPerspective();

		void prepareShaderProgram();

		void clearBuffers();

		void printVerboseDriverInformation();

		void createVBOs();

		void deleteVBOs();

		GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);

		GLuint loadShader(GLenum shaderType, const char *pSource);

		const static float cubeVertices[6 * 4 * 12];
		const static unsigned short cubeIndices[6 * 6];

		const static glm::vec4 ambientLightFullColor;

		glm::mat4 projectionMatrix{};

		GLint tangentVectorShaderPosition{};

		GLint vertexAttributePosition{};
		GLint modelMatrixAttributePosition{};
		GLint samplerUniformPosition{};
		GLint normalMapUniformPosition{};
		GLint textureCoordinatesAttributePosition{};
		GLint projectionMatrixAttributePosition{};
		GLint normalAttributePosition{};

		GLint diffuseLightPosition{};
		GLuint gProgram{};

		//VBO stuff
		GLuint vboCubeVertexDataIndex{};
		GLuint vboCubeVertexIndicesIndex{};


		GLuint currentFilter{};
		float cubeRotationAngleYZ{};
		float cubeRotationAngleXZ{};

		glm::vec4 diffuseLightWorldPosition{};
		glm::vec4 diffuseLightColor{};
		glm::vec4 ambientLightColor{};

		GLuint diffuseLightColorShaderLocation{};
		GLuint ambientLightColorShaderLocation{};

		float rotationXZSpeed{};
		float rotationYZSpeed{};

		std::vector<std::shared_ptr<NativeBitmap>> mBitmaps{};
		std::vector<std::shared_ptr<Texture>> mTextures{};

	public:
		GLES2Lesson();

		~GLES2Lesson();

		bool init(float w, float h, const std::string &vertexShader,
				  const std::string &fragmentShader);

		void setTexture(std::vector<std::shared_ptr<NativeBitmap>> textures);

		void render();

		void tick();

		void reset();

		void setSpeeds(const glm::vec2 &param);

		void drawTrigBatch(odb::TrigBatch &batch, glm::mat4 transform, int textureIndex, int normalIndex);
	};
}
#endif //LESSON02_GLES2LESSON_H
