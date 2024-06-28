/*
    ResourceManager.h

    Class Resource and ResourceManager.
*/

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <stdint.h>
#define MAX_OBJECT_COUNT 200

//Enum to indicate resource type
typedef enum{
    RESOURCE_NULL = 0,
    RESOURCE_GRAPHIC = 1,
    RESOURCE_TEXT = 2,
    //RESOURCE_AUDIO = 3,
}RESOURCE_TYPE; 

/*
    Resource class, indicate a resource object.
*/
typedef struct
{
    uint8_t mResourceID;
    char mFileName[64];
    RESOURCE_TYPE mType;
    void (*new)(Resource*, uint8_t, char[], RESOURCE_TYPE);
    /*
        The following function is required for each derived class.:
        void (*load)(TYPE*);
        void (*unload)(TYPE*);
    */
}Resource;

void resourceNew(Resource*, uint8_t, char[], RESOURCE_TYPE);

/*
    ResourceManager class, manages resource objects.
*/
typedef struct
{
    uint8_t mResourceCount;
    void (*new)(ResourceManager*);

    //TO-DO: use a good data structure (name mResources) to store mResource.
    //Currently I use array of length 200, so it might overflow.
    Resource mResources[MAX_OBJECT_COUNT];

    //Finds resource by its ID, return NULL if not found.
    Resource* (*findResourcebyID)(ResourceManager*, uint8_t); 

    //Clears all resource objects. Not used as there's nothing to be allowcated or to be free.
    //void (*clear)(struct ResourceManager*);

    //Add resource.
    void (*load)(ResourceManager*);
}ResourceManager;

void resourceManagerNew(ResourceManager*);
Resource* resourceManagerFindResourcebyID(ResourceManager*, uint8_t); 
void resourceManagerLoad(ResourceManager*);

#endif /* _RESOURCEMANAGER_H_ */