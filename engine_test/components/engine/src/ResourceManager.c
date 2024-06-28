/*
    ResourceManager.c

    Functions of ResourceManager.h.
*/

#ifndef _RESOURCEMANAGER_C_
#define _RESOURCEMANAGER_C_

#include <string.h>
#include "../include/ResourceManager.h"

/*
    Resource class
*/
void resourceNew(Resource* obj, uint8_t ID, char name[], RESOURCE_TYPE type)
{
    obj->new = resourceNew;
    obj->mResourceID = ID;
    obj->mType = type;
    strcpy(obj->mFileName, name);
}

/*
    ResourceManager class
*/
void resourceManagerNew(ResourceManager* obj)
{
    obj->new = resourceManagerNew;
    obj->mResourceCount = 0;
    obj->findResourcebyID = resourceManagerFindResourcebyID;
    obj->load = resourceManagerLoad;
    return;
}

Resource* resourceManagerFindResourcebyID(ResourceManager* obj, uint8_t ID)
{
    if(ID < obj->mResourceCount)
    {
        return &(obj->mResources[ID]);
    }
    else return NULL;
}

void resourceManagerLoad(ResourceManager* obj)
{
    Resource newResource;
    resourceNew(&newResource, obj->mResourceCount, "Test", RESOURCE_GRAPHIC);
    obj->mResources[obj->mResourceCount] = newResource;
    obj->mResourceCount++;
    return;
}

#endif /* _RESOURCEMANAGER_C_ */