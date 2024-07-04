/*
    AudioManager.h

    Class AudioResource, AudioPlayer and AudioManager.
*/

#ifndef _AUDIOMANAGER_H_
#define _AUDIOMANAGER_H_

#include <stdint.h>
#include "./ResourceManager.h"

//include library 

#define MAX_OBJECT_COUNT 200

/*
    AudioResource class (derived from Resource), indicate an audio resource.
*/
typedef struct audioResource
{
    Resource* baseResource;

    //constructor for AudioResource
    void (*new)(struct audioResource*, Resource*);
}AudioResource;

//constructor for AudioResource
void audioResourceNew(AudioResource*, Resource*);

/*
    AudioPlayer class, encapsulate information about the media that will be played.
*/
typedef struct audioPlayer
{
    AudioResource* mAudioResource;

    //number of repetitions (0: play once, 1: repeat one time, etc.)
    uint8_t mNumRepeats;
    //counter used to track current repetitions
    uint8_t mRepeatCount;

    //constructor for AudioPlayer
    void (*new)(struct audioPlayer*, AudioResource*, uint8_t);

    //function that will be call when the repetition finished
    void (*onMediaComplete)(struct audioPlayer*);
}AudioPlayer;

//constructor for AudioPlayer
void audioPlayerNew(AudioPlayer*, AudioResource*, uint8_t);
void audioPlayerOnMediaCompleteDefault(AudioPlayer*);

/*
    AudioManager class, manages AudioResource and AudioObject objects.
*/
typedef struct audioManager
{
    uint8_t mAudioResourceCount;
    uint8_t mAudioPlayerCount;
    void (*new)(struct audioManager*);

    AudioResource mAudioResources[MAX_OBJECT_COUNT];
    AudioPlayer mAudioPlayers[MAX_OBJECT_COUNT];

    //Finds AudioResource by its ID, returns NULL if not found.
    AudioResource* (*findAudioResourceByID)(struct audioManager*, uint8_t);
    //Finds AudioResource by its name, returns NULL if not found.
    AudioResource* (*findAudioResourceByName)(struct audioManager*, char[]); 

}AudioManager;

#endif /* _AUDIOMANAGER_H_ */