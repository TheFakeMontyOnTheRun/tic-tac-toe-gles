//
// Created by monty on 10/10/16.
//

#ifndef TIC_TAC_TOE_GLES_SOUNDEMITTER_H
#define TIC_TAC_TOE_GLES_SOUNDEMITTER_H

namespace odb {
    class SoundEmitter {
        std::shared_ptr<SoundClip> mSample = nullptr;
        unsigned int mEmitterHandle{};
    public:
        glm::vec3 mPosition{0, 0, 0};

        SoundEmitter(std::shared_ptr<SoundClip> aSample);

        void play(std::shared_ptr<SoundListener> listener);
    };
}

#endif //TIC_TAC_TOE_GLES_SOUNDEMITTER_H
