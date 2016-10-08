//
// Created by monty on 04/10/16.
//

#ifndef TIC_TAC_TOE_GLES_CANIMATION_H
#define TIC_TAC_TOE_GLES_CANIMATION_H

namespace odb {

    class CAnimation {

        glm::mat4 mFrom;
        glm::mat4 mTo;
        long mRemainingTime;
        long mDuration;
    public:
        CAnimation(const glm::mat4 &aFrom, const glm::mat4 &aTo, long duration);

        glm::mat4 getCurrentState();
        glm::mat4 getTarget();
        void setNewTarget( glm::mat4 aTarget );
        bool isFinished();
        void update(long ms);
    };
}

#endif //TIC_TAC_TOE_GLES_CANIMATION_H
