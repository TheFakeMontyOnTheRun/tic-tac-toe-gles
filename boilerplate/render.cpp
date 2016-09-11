#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <iterator>
#include <fstream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include <png.h>


#include <map>
#include "glm/glm.hpp"
#include "Game.h"
#include "glue.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include "GLES2Lesson.h"

odb::GLES2Lesson* gles2Lesson = nullptr;

extern void draw() {
	if ( gles2Lesson != nullptr ) {
		gles2Lesson->tick();
		gles2Lesson->render();
	}
}

/* new window size or exposure */
extern void reshape(int width, int height) {
}


static void
create_shaders(void) {
}

std::string readShaderFrom( std::string path ) {
    std::ifstream file( path );
    std::string toReturn((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    return toReturn;
}

//https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
int* loadPNG(const std::string filename, int width, int height)
{
    //header for testing if it is a png
    png_byte header[8];

    //open file as binary
    FILE *fp = fopen(filename.c_str(), "rb");

    //read the header
    fread(header, 1, 8, fp);


    //create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
                                                 NULL, NULL);

    //create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);

    //create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);

    //init png reading
    png_init_io(png_ptr, fp);

    //let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    //variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 twidth, theight;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
                 NULL, NULL, NULL);

    //update width and height based on png info
    width = twidth;
    height = theight;

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];

    //row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[height];
    // set the individual row_pointers to point at the correct offsets of image_data
    for (int i = 0; i < height; ++i)
        row_pointers[height - 1 - i] = image_data + i * rowbytes;

    //read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;
    fclose(fp);

    return (int*)image_data;
}

extern void init() {

	std::string gFragmentShader = readShaderFrom( "res/fragment.glsl" );
    std::string gVertexShader = readShaderFrom( "res/vertex.glsl" );

	gles2Lesson = new odb::GLES2Lesson();
    gles2Lesson->setTexture( loadPNG( "res/texture.png", 128, 128 ), loadPNG( "res/hexa.png", 128, 128 ), 128, 128, 1);
	gles2Lesson->init(300, 300, gVertexShader.c_str(), gFragmentShader.c_str());
}
