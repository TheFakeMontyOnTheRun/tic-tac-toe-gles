//
// Created by monty on 04/10/16.
//
#include <array>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "CAnimation.h"
#include "GameRenderListener.h"

static const float rad = 3.14159f / 180.0f;
static const long animationTime = 2000;
static const float zNear = -8;
static const float zFar = -10;
static const float degreesForX = 90.0f;
static const float degreesForO = 270.0f;
static const float degreesForBlank = 180.0f;

namespace odb {

    glm::mat4 makeTransform( glm::vec3 translate, float rotationXZ, float rotationYZ  ) {
        glm::mat4 identity = glm::mat4(1.0f);
        glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::mat4 translated = glm::translate(identity, translate);
        glm::mat4 rotatedAroundXAxis = glm::rotate(translated, rotationYZ, xAxis);
        glm::mat4 rotatedAroundYAxis = glm::rotate(rotatedAroundXAxis, rotationXZ, yAxis);

        return rotatedAroundYAxis;
    }

    void GameRenderListener::update( long delta ) {
        timeEllapsed += 200;

        for ( auto& animationLine : animations ) {
            for ( auto& animation : animationLine ) {
                if ( animation != nullptr ) {
                    animation->update(200);
                }
            }
        }
    }

    glm::mat4 GameRenderListener::getStateFor( int x, int y ) {

        if ( animations[ y ][ x ] == nullptr ) {
            glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForBlank * rad, 0 );
            animations[ y ][ x ] = std::make_shared<odb::CAnimation>( transform0, transform0, animationTime );
        }

        return animations[ y ][ x ]->getCurrentState();
    }


    void GameRenderListener::onPieceSelectedIsX( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForBlank * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForX * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceSelectedIsO( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForBlank * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForO * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceFocusedIsX( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForX * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForX * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceFocusedIsBlank( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForBlank * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForBlank * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceFocusedIsO( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForO * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear), degreesForO * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceDefocusedIsX( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForX * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForX * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceDefocusedIsO( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear ), degreesForO * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForO * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::onPieceDefocusedIsBlank( int x, int y ) {
        glm::mat4 transform0 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zNear), degreesForBlank * rad, 0 );
        glm::mat4 transform1 = makeTransform( glm::vec3( -3 + (3 * x), 3 + (-3 * y), zFar ), degreesForBlank * rad, 0 );
        compoundAnimation( x, y, std::make_shared<odb::CAnimation>( transform0, transform1, animationTime ) );
    }

    void GameRenderListener::compoundAnimation( int x, int y, std::shared_ptr<odb::CAnimation> animation ) {

        if ( animations[ y ][ x ]  != nullptr && !animations[ y ][ x ]->isFinished() ) {
            animations[ y ][ x ]->setNewTarget( animation->getTarget() );
        } else {
            animations[ y ][ x ] = animation;
        }
    }
}