/*
    ResourceManager.c

    Functions of RenderManager.h.
*/

#ifndef _RENDERMANAGER_C_
#define _RENDERMANAGER_C_

#include <string.h>
#include "../include/ResourceManager.h"
#include "../include/RenderManager.h"

/*
    RenderResource class
*/
void renderResourceNew(RenderResource* obj, ResourceManager* mResourceManager, uint8_t ID)
{
    obj->new = renderResourceNew;
    obj->load = renderResourceLoad;
    obj->unload = renderResourceUnload;
    obj->baseResource = mResourceManager->findResourcebyID(mResourceManager, ID);
}

void renderResourceLoad(RenderResource* obj, uint16_t width, uint16_t height, uint8_t* image);
{
    obj->mWidth = width;
    obj->mHeight = height;
    obj->mImage = image;
}

void renderResourceUnload(RenderResource* obj)
{
    if(obj->mImage != NULL) obj->mImage = NULL;
}

/*
    RenderObject class
*/
void renderObjectNew(RenderObject* obj, RenderResource* renderResource, int16_t posX, int16_t posY, uint8_t visible)
{
    obj->mRenderResource = renderResource;
    obj->mPosX = posX;
    obj->mPosY = posY;
    obj->mVisible = visible;
    obj->new = renderObjectNew;
}

/*
    RenderManager class
*/

#endif /* _RENDERMANAGER_C_ */