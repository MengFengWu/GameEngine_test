/*
    AudioManager.c

    Functions of AudioManager.h.
*/

#ifndef _AUDIOMANAGER_C_
#define _AUDIOMANAGER_C_

#include "../include/AudioManager.h"

/*
    AudioResource class
*/
void audioResourceNew(AudioResource* obj, Resource* resource)
{
    obj->new = audioResourceNew;
    obj->baseResource = resource;
}

/*
    AudioPlayer class
*/
void audioPlayerNew(AudioPlayer* obj, AudioResource* audioResource, uint8_t numRepeats)
{
    obj->mAudioResource = audioResource;
    obj->mNumRepeats = numRepeats;
    obj->mRepeatCount = 0;
    obj->new = audioPlayerNew;
    obj->onMediaComplete = audioPlayerOnMediaCompleteDefault;
}

void audioPlayerOnMediaCompleteDefault(AudioPlayer*)
{
    return;
}

#endif /* _AUDIOMANAGER_C_ */