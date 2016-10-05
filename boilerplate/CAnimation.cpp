//
// Created by monty on 04/10/16.
//
#include "glm/glm.hpp"
#include "CAnimation.h"

namespace odb {
    CAnimation::CAnimation(const glm::mat4 &aFrom, const glm::mat4 &aTo, long duration):
    mFrom( aFrom ), mTo( aTo ), mRemainingTime( duration ), mDuration( duration ) {
    }

    glm::mat4 CAnimation::getCurrentState() {
        if ( isFinished()) {
            return mTo;
        } else {
            float delta = (static_cast<float>(mDuration - mRemainingTime) / static_cast<float>(mDuration) );
            return mFrom + ( delta * ( mTo - mFrom ) );
        }
    }

    void CAnimation::update(long ms) {
        mRemainingTime -= ms;
    }

    glm::mat4 CAnimation::getTarget() {
        return mTo;
    }

    void CAnimation::setNewTarget( glm::mat4 aTarget ) {
        mTo = aTarget;
    }

    bool CAnimation::isFinished() {
        return mRemainingTime < 0;
    }
}