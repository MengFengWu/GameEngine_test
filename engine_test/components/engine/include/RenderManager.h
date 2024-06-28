/*
    RenderManager.h

    Class RenderResource, RenderObject and RenderManager.
*/

#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_

#include <stdint.h>
#include "./RenderManager.h"

/*
    RenderResource class (derived from Resource), indicate a resource which is to be rendered.
*/
typedef struct
{
    Resource* baseResource;
    uint16_t mWidth;
    uint16_t mHeight;
    uint8_t *mImage;
    void (*new)(RenderResource*, ResourceManager*, uint8_t);
    
    //load function, load image and parameters.
    void (*load)(RenderResource*);

    //unload function, set the image pointer to NULL.
    void (*unload)(RenderResource*);
}RenderResource;

void renderResourceNew(RenderResource*, ResourceManager*, uint8_t);
void renderResourceLoad(RenderResource*, uint16_t, uint16_t, uint8_t*);
void renderResourceUnload(RenderResource*);

/*
    RenderObject class, includes a RenderResource and parameters for rendering.
*/
typedef struct
{
    RenderResource* mRenderResource;

    int16_t mPosX;
    int16_t mPosY;
    uint8_t mVisible;

    void (*new)(RenderObject*, RenderResource, int16_t, int16_t, uint8_t)
}RenderObject;

void renderObjectNew(RenderObject*, RenderResource, int16_t, int16_t, uint8_t)

/*
    RenderManager class, manages RenderObject objects.
*/
typedef struct
{
    uint16_t mRenderObjectCount;
    void (*new)(struct ResourceManager*);

    Resource mResources[200];

    //Finds resource by its ID, return NULL if not found.
    Resource* (*findResourcebyID)(ResourceManager*, uint8_t); 

    //Clears all resource objects. Not used as there's nothing to be allowcated or to be free.
    //void (*clear)(struct ResourceManager*);

    //Add resource.
    void (*load)(ResourceManager*);


    void (*update)(ResourceManager*);
    void (*renderAllObject)();
}ResourceManager;

#endif /* _RENDERMANAGER_H_ */