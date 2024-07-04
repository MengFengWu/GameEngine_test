/*
    ResourceManager.c

    Functions of RenderManager.h.
*/

#ifndef _RENDERMANAGER_C_
#define _RENDERMANAGER_C_

#include <string.h>
#include <stdio.h>
#include "../include/ResourceManager.h"
#include "../include/RenderManager.h"

//include library "st7789"
#include "../../st7789/include/st7789.h"
#include "../../fontx/include/fontx.h"
#include "../../pngle/include/pngle.h"
#include "../../decode_png/include/decode_png.h"

#define MAX_OBJECT_COUNT 200

/*
    RenderResource class
*/
void renderResourceNew(RenderResource* obj, uint8_t ID, Resource* resource)
{
    obj->new = renderResourceNew;
    obj->mRenderResourceID = ID;
    obj->loadImage = renderResourceLoadImage;
    obj->loadFont = renderResourceLoadFont;
    //obj->unload = renderResourceUnload;
    obj->baseResource = resource;
    return;
}

void renderResourceLoadImage(RenderResource* obj, uint16_t* image, uint16_t width, uint16_t height)
{
    obj->mWidth = width;
    obj->mHeight = height;
    obj->mImage = image;
}

void renderResourceLoadFont(RenderResource* obj)
{
    if(obj->baseResource->mType == RESOURCE_TEXT)
    {
        InitFontx(obj->mFont, obj->baseResource->mFileName, "");
    }
    return;
}

/*
void renderResourceUnload(RenderResource* obj)
{
    if(obj->mImage != NULL) obj->mImage = NULL;
    return;
}
*/

/*
    RenderObject class
*/
void renderObjectNew(RenderObject* obj, RenderResource* renderResource, int16_t posX, int16_t posY, uint8_t visible)
{
    obj->mRenderResource = renderResource;
    obj->mPosX = posX;
    obj->mPosY = posY;
    obj->mColor = WHITE;
    obj->mVisible = visible;
    //obj->mScale = scale;
    obj->new = renderObjectNew;
    obj->setPos = renderObjectSetPos;
    obj->setColor = renderObjectSetColor;
    obj->setText = renderObjectSetText;
    obj->render = renderObjectRender;
    return;
}

void renderObjectSetPos(RenderObject* obj, int16_t posX, int16_t posY)
{
    obj->mPrePosX = obj->mPosX;
    obj->mPrePosY = obj->mPosY;
    obj->mPosX = posX;
    obj->mPosY = posY;
}

void renderObjectSetColor(RenderObject* obj, uint16_t color)
{
    obj->mPrePosX = obj->mPosX;
    obj->mPrePosY = obj->mPosY;
    obj->mColor = color;
    return;
}

void renderObjectSetText(RenderObject* obj, char text[])
{
    obj->mPrePosX = obj->mPosX;
    obj->mPrePosY = obj->mPosY;    
    if(obj->mRenderResource->baseResource->mType == RESOURCE_TEXT) strcpy((char*)(obj->mText), text);
    return;
}

void renderObjectRender(RenderObject* obj, TFT_t* TFT_t)
{
    if(obj->mRenderResource->baseResource->mType == RESOURCE_GRAPHIC)
    {
        lcdShowPNG(TFT_t, obj->mPosX, obj->mPosY, obj->mRenderResource->baseResource->mFileName,
                    obj->mRenderResource->mWidth, obj->mRenderResource->mHeight);
    }
    else if (obj->mRenderResource->baseResource->mType == RESOURCE_TEXT)
    {
        if(strlen((char*)(obj->mText)) > 0)
        {
            lcdDrawString(TFT_t, obj->mRenderResource->mFont,
                            obj->mPosX, obj->mPosY, obj->mText, obj->mColor);
        }
    }
    return;
}

/*
    RenderManager class
*/
void renderManagerNew(RenderManager* obj)
{
    spi_master_init(&(obj->TFT_t), CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO, CONFIG_BL_GPIO);
    lcdInit(&(obj->TFT_t), CONFIG_WIDTH, CONFIG_HEIGHT, CONFIG_OFFSETX, CONFIG_OFFSETY);
    
    obj->new = renderManagerNew;

    obj->mScreen = malloc(SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(uint8_t));

    obj->mRenderResourceCount = 0;
    obj->mRenderObjectCount = 0;

    obj->mInitRenderObject.mRenderResource = NULL;
    obj->mInitRenderObject.nextObj = &(obj->mInitRenderObject);
    obj->mInitRenderObject.prevObj = &(obj->mInitRenderObject);

    obj->findRenderResourceByID = renderManagerFindRenderResourceByID;
    obj->findRenderResourceByName = renderManagerFindRenderResourceByName;
    obj->addImage = renderManagerAddImage;
    obj->addFont = renderManagerAddFont;
    obj->addObject = renderManagerAddObject;
    obj->removeObject = renderManagerRemoveObject;
    obj->copy = renderManagerCopy;
    obj->readDown = renderManagerReadDown;
    obj->readUp = renderManagerReadUp;
    obj->clear = renderManagerClear;
    obj->update = renderManagerUpdate;
    obj->renderAllText = renderManagerRenderAllText;
    obj->renderAllObject = renderManagerRenderAllObject;
    return;
}

RenderResource* renderManagerFindRenderResourceByID(RenderManager* obj, uint8_t ID)
{
    if(ID < obj->mRenderResourceCount)
    {
        return &(obj->mRenderResources[ID]);
    }
    else return NULL;
} 

RenderResource* renderManagerFindRenderResourceByName(RenderManager* obj, char name[])
{
    for(uint8_t i = 0; i < obj->mRenderResourceCount; i++)
    {
        if(strcmp(((obj->mRenderResources[i]).baseResource)->mFileName, name) == 0)
        {
            return &(obj->mRenderResources[i]);
        }
    }
    return NULL;
}

void renderManagerAddImage(RenderManager* obj, ResourceManager* resourceManager, char name[], uint16_t* image, uint16_t width, uint16_t height)
{
    resourceManager->addResource(resourceManager, name, RESOURCE_GRAPHIC);
    RenderResource newRenderResource;
    renderResourceNew(&newRenderResource, obj->mRenderResourceCount, resourceManager->findResourceByID(resourceManager, (resourceManager->mResourceCount) - 1));
    renderResourceLoadImage(&newRenderResource, image, width, height);

    obj->mRenderResources[obj->mRenderResourceCount] = newRenderResource;
    obj->mRenderResourceCount++;
    return;
}

void renderManagerAddFont(RenderManager* obj, ResourceManager* resourceManager, char name[])
{
    resourceManager->addResource(resourceManager, name, RESOURCE_TEXT);
    RenderResource newRenderResource;
    renderResourceNew(&newRenderResource, obj->mRenderResourceCount, resourceManager->findResourceByID(resourceManager, (resourceManager->mResourceCount) - 1));
    renderResourceLoadFont(&newRenderResource);

    obj->mRenderResources[obj->mRenderResourceCount] = newRenderResource;
    obj->mRenderResourceCount++;
    return;
}

void renderManagerAddObject(RenderManager* obj, RenderObject* renderObject)
{
    renderObject->prevObj = obj->mInitRenderObject.prevObj;
    (obj->mInitRenderObject.prevObj)->nextObj = renderObject;
    renderObject->nextObj = &(obj->mInitRenderObject);
    obj->mInitRenderObject.prevObj = renderObject;
}

void renderManagerRemoveObject(RenderManager* obj, RenderObject* renderObject)
{
    renderObject->prevObj->nextObj = renderObject->nextObj;
    renderObject->nextObj->prevObj = renderObject->prevObj;
    renderObject->prevObj = NULL;
    renderObject->nextObj = NULL;
    printf("%s", "Revome an object, named ");
    printf("%s\n", renderObject->mRenderResource->baseResource->mFileName);
}

void renderManagerCopy(RenderManager* obj, RenderObject* renderObject, int16_t posX, int16_t posY, uint16_t width, uint16_t height)
{
    if(renderObject->mRenderResource->baseResource->mType == RESOURCE_GRAPHIC)
    {
        if((posX <= renderObject->mPosX && renderObject->mPosX < (posX + width)) &&
            (posY <= renderObject->mPosY && renderObject->mPosY < (posY + height)))
        {
            for(uint16_t i = 0; i < (renderObject->mRenderResource->mWidth); i++)
            {
                for(uint16_t j = 0; j < (renderObject->mRenderResource->mHeight); j++)
                {
                    if(renderObject->mRenderResource->mImage[i * renderObject->mRenderResource->mWidth + j] != TRANSPARENT)
                    {
                        obj->mScreen[(renderObject->mPosX + i) + (renderObject->mPosY + j)] = renderObject->mRenderResource->mImage[i * renderObject->mRenderResource->mWidth + j];
                    }
                    if(renderObject->mPosY + j >= posY + height) break;
                }
                if(renderObject->mPosX + i >= posX + width) break;
            }
        }
    }
    return;
}

void renderManagerReadDown(RenderManager* obj, RenderObject* renderObject)
{
    RenderObject currentNode = obj->mInitRenderObject;
    while(currentNode.nextObj->mRenderResource != NULL)
    {
        if(currentNode.nextObj->mVisible == 1) obj->copy(obj, currentNode.nextObj, renderObject->mPrePosX, renderObject->mPrePosY, renderObject->mRenderResource->mWidth, renderObject->mRenderResource->mHeight);
        currentNode = *(currentNode.nextObj);
    }
    lcdDrawPNG(&(obj->TFT_t), renderObject->mPrePosX, renderObject->mPrePosY, (obj->mScreen + (renderObject->mPrePosX * SCREEN_WIDTH + renderObject->mPrePosY)), renderObject->mRenderResource->mWidth, renderObject->mRenderResource->mHeight);
    return;
}

void renderManagerReadUp(RenderManager* obj, RenderObject* renderObject)
{
    RenderObject currentNode = obj->mInitRenderObject;
    while(currentNode.nextObj->mRenderResource != NULL)
    {
        if(currentNode.nextObj->mVisible == 1) obj->copy(obj, currentNode.nextObj, renderObject->mPosX, renderObject->mPosY, renderObject->mRenderResource->mWidth, renderObject->mRenderResource->mHeight);
        currentNode = *(currentNode.nextObj);
    }
    lcdDrawPNG(&(obj->TFT_t), renderObject->mPosX, renderObject->mPosY, (obj->mScreen + (renderObject->mPosX * SCREEN_WIDTH + renderObject->mPosY)), renderObject->mRenderResource->mWidth, renderObject->mRenderResource->mHeight);
    return;
}

void renderManagerClear(RenderManager* obj)
{
    while(obj->mInitRenderObject.nextObj->mRenderResource != NULL)
    {
        obj->removeObject(obj, obj->mInitRenderObject.nextObj);
    }
    printf("%s\n", "Finish clearing.");
    return;
}

void renderManagerUpdate(RenderManager* obj, RenderObject* renderObject)
{
    uint8_t tempVisible = renderObject->mVisible;
    obj->readUp(obj, renderObject);
    renderObject->setVisible(renderObject, 0);
    obj->readDown(obj, renderObject);
    renderObject->setVisible(renderObject, tempVisible);
    return;
}

void renderManagerRenderAllText(RenderManager* obj)
{
    RenderObject currentNode = obj->mInitRenderObject;
    while(currentNode.nextObj->mRenderResource != NULL)
    {
        currentNode = *(currentNode.nextObj);
        if(currentNode.mRenderResource->baseResource->mType == RESOURCE_TEXT) currentNode.render(&currentNode, &(obj->TFT_t));
    }
    return;
}

void renderManagerRenderAllObject(RenderManager* obj)
{
    RenderObject currentNode = obj->mInitRenderObject;
    while(currentNode.nextObj->mRenderResource != NULL)
    {
        printf("%s", "Rendered an object, named ");
        printf("%s\n", currentNode.nextObj->mRenderResource->baseResource->mFileName);
        currentNode = *(currentNode.nextObj);
        currentNode.render(&currentNode, &(obj->TFT_t));
    }
    printf("%s\n", "Finish rendering.");
    return;
}

#endif /* _RENDERMANAGER_C_ */