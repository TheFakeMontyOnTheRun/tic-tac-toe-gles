#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <memory>
#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <iterator>
#include <fstream>
#include <map>
#include "glm/glm.hpp"

#include <png.h>
#include "CAnimation.h"
#include "GameRenderListener.h"

#include "Game.h"
#include "glue.h"
#include "glm/gtc/matrix_transform.hpp"

#include "NativeBitmap.h"
#include "Texture.h"
#include "Material.h"
#include "Trig.h"
#include "TrigBatch.h"
#include "MeshObject.h"
#include "MaterialList.h"
#include "Scene.h"

#include "GLES2Lesson.h"
#include "WavefrontOBJReader.h"


odb::GLES2Lesson* gles2Lesson = nullptr;



std::shared_ptr<odb::Scene> cube;
std::shared_ptr<odb::Scene> choice;
std::shared_ptr<odb::Scene> drawOutcome;
std::shared_ptr<odb::Scene> victoryXOutcome;
std::shared_ptr<odb::Scene> victoryOOutcome;
std::shared_ptr<odb::Scene> press;
std::shared_ptr<odb::Scene> title;


std::shared_ptr<odb::GameRenderListener> renderListener = std::make_shared<odb::GameRenderListener>();

odb::Game::EPieces playerPiece = odb::Game::EPieces::kBlank;

void drawSceneAt(std::shared_ptr<odb::Scene> scene, glm::mat4 transform, int textureIndex, int normalIndex ) {
    if ( scene != nullptr ) {
        for ( auto& mesh : scene->meshObjects ) {
            for ( auto& batch : mesh->trigBatches ) {
                gles2Lesson->drawTrigBatch( batch, transform, textureIndex, normalIndex );
            }
        }
    }
}


std::string extractTexturefrom( std::shared_ptr<odb::Scene> scene ) {
    if ( scene != nullptr ) {
        for ( auto& mesh : scene->meshObjects ) {
            return mesh->trigBatches[ 0 ].getMaterial()->diffuseMapFilename;
        }
    }

    return "res/hexa.png";
}



extern void draw(odb::Game& game) {

	if ( gles2Lesson != nullptr ) {

		gles2Lesson->tick();
        renderListener->update( 200 );
		gles2Lesson->render();
        game.setListener( renderListener );


        switch ( renderListener->currentVisual ) {
            case odb::GameRenderListener::EVisuals::kTitleScreen:
                drawSceneAt( title, glm::translate( glm::mat4(1.0f), glm::vec3( 0.0f, 0.0f, -5.0f ) ), 2, 4 );
                drawSceneAt( press, glm::translate( glm::mat4(1.0f), glm::vec3( 0.0f, -1.0f, -5.0f ) ), 3, 4 );
                break;

            case odb::GameRenderListener::EVisuals::kPieceSelection:
                drawSceneAt( choice, glm::translate( glm::mat4(1.0f), glm::vec3( 0.0f, 1.0f, -5.0f ) ), 2, 4 );


                drawSceneAt( cube, renderListener->getStateFor( 0, 1 ), 0, 1 );
                drawSceneAt( cube, renderListener->getStateFor( 2, 1 ), 0, 1 );
                break;

            case odb::GameRenderListener::EVisuals::kOutcome: {

                std::shared_ptr<odb::Scene> meshes[] = {drawOutcome, victoryOOutcome, victoryXOutcome};
                drawSceneAt(meshes[static_cast<int>(game.getWinner())], renderListener->getOutcomeState(), 2, 4);
                drawSceneAt( press, glm::translate( glm::mat4(1.0f), glm::vec3( 0.0f, -1.0f, -5.0f ) ), 3, 4 );
            }

            case odb::GameRenderListener::EVisuals::kGame:
                for ( int y = 0; y < 3; ++y ) {
                    for ( int x = 0; x < 3; ++x ) {
                        drawSceneAt( cube, renderListener->getStateFor( x, y ), 0, 1 );
                    }
                }
                break;
        }

    }
}

/* new window size or exposure */
extern void reshape(int width, int height) {
}


static void
create_shaders(void) {
}

std::string readTextFrom(std::string path) {
    std::ifstream file( path );
    std::string toReturn((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());

    return toReturn;
}

//https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
std::shared_ptr<odb::NativeBitmap> loadPNG(const std::string filename ) {
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
    int width = twidth;
    int height = theight;

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
        row_pointers[ i] = image_data + i * rowbytes;

    //read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;
    fclose(fp);

    std::shared_ptr<odb::NativeBitmap> toReturn = std::make_shared<odb::NativeBitmap>( width, height, (int*)image_data );

    return toReturn;
}

extern void init() {

	std::string gFragmentShader = readTextFrom("res/fragment.glsl");
    std::string gVertexShader = readTextFrom("res/vertex.glsl");

    cube = readScene( readTextFrom("res/cubonormal.obj"), readTextFrom("res/cubonormal.mtl"));
    choice  = readScene( readTextFrom("res/choice.obj"), readTextFrom("res/choice.mtl"));
    drawOutcome = readScene( readTextFrom("res/draw.obj"), readTextFrom("res/draw.mtl"));
    victoryXOutcome = readScene( readTextFrom("res/x_victory.obj"), readTextFrom("res/x_victory.mtl"));
    victoryOOutcome = readScene( readTextFrom("res/o_victory.obj"), readTextFrom("res/o_victory.mtl"));
    press = readScene( readTextFrom("res/press.obj"), readTextFrom("res/press.mtl"));
    title = readScene( readTextFrom("res/title.obj"), readTextFrom("res/title.mtl"));


    std::vector< std::shared_ptr<odb::NativeBitmap>> textures;

    textures.push_back( loadPNG( "res/cubecolours.png" ) ); //0
    textures.push_back( loadPNG( "res/cubenormals.png" ) ); //1
    textures.push_back( loadPNG( "res/image1.png" ) ); //2
    textures.push_back( loadPNG( "res/image2.png" ) ); //4
    textures.push_back( loadPNG( "res/image3.png" ) ); //6

    gles2Lesson = new odb::GLES2Lesson();
    gles2Lesson->setTexture( textures );
    gles2Lesson->setSpeeds( glm::vec2( 1.0f * (3.14159f / 180.0f), 0.0f * (3.14159f / 180.0f)) );
	gles2Lesson->init(640, 480, gVertexShader.c_str(), gFragmentShader.c_str());
}
