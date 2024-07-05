#include <stdio.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spiffs.h"

#include "st7789.h"
#include "fontx.h"
#include "pngle.h"
#include "decode_png.h"

#include "Engine.h"

#include "../files/people.h"

//--Person class for testing--//
typedef struct person
{
    RenderObject mRenderObject;
    int attack;
    int HP;
    int oriX;
    int oriY;

    void (*new)(struct person*, RenderManager*, int16_t, int16_t);
    void (*move)(struct person*);
}Person;

void personMove(Person* obj)
{
    if(obj->mRenderObject.mPosX <= 0 || obj->mRenderObject.mPosX + 50 >= 240) obj->oriX *= -1;
    if(obj->mRenderObject.mPosY <= 0 || obj->mRenderObject.mPosY + 50 >= 320) obj->oriY *= -1;
    obj->mRenderObject.setPos(&obj->mRenderObject, obj->mRenderObject.mPosX + (5 * obj->oriX), obj->mRenderObject.mPosY + (5 * obj->oriY));
}

void personNew(Person* obj, RenderManager* renderManager, int16_t posX, int16_t posY)
{
    obj->new = personNew;
    obj->move = personMove;
    obj->oriX = 1;
    obj->oriY = 1;
    obj->attack = 10;
    obj->HP = 100;
    renderObjectNew(&(obj->mRenderObject), renderManager->findRenderResourceByName(renderManager, "person"), posX, posY, 1);
}
//----//

//--Declare Managers and objects--//
ResourceManager gResourceManager;
RenderManager gRenderManager;

Person group[1];
//----//

//--Init Function--//
void init()
{   
    resourceManagerNew(&gResourceManager);
    renderManagerNew(&gRenderManager);
    printf("%s\n", "Manager initialization finished.");

    gRenderManager.addImage(&gRenderManager, &gResourceManager, "person", loadPeople, 50, 50);
    printf("%s\n", "Resource initialization finished.");
}
//----//

void app_main(void)
{   
    init();

    for(int i = 0; i < 1; i++)
    {
        personNew(&group[i], &gRenderManager, 6 * i + 1, 6 * i + 1);
        gRenderManager.addObject(&gRenderManager, &(group[i].mRenderObject));
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);

    gRenderManager.removeObject(&gRenderManager, &(group[0].mRenderObject));
    vTaskDelay(1000/portTICK_PERIOD_MS);

    gRenderManager.addObject(&gRenderManager, &(group[0].mRenderObject));
    vTaskDelay(1000/portTICK_PERIOD_MS);

    gRenderManager.clear(&gRenderManager);
    vTaskDelay(1000/portTICK_PERIOD_MS);

    for(int i = 0; i < 1; i++)
    {
        gRenderManager.addObject(&gRenderManager, &(group[i].mRenderObject));
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
    
    while(1)
    {
        for(int i = 0; i < 1; i++)
        {
            group[i].move(&(group[i]));
        }
        for(int i = 0; i < 1; i++)
        {
            gRenderManager.update(&gRenderManager, &(group[i].mRenderObject));
        }
        //vTaskDelay(60/portTICK_PERIOD_MS);
    }
    
    printf("%s\n", "Code finished.");
    //return 0;
}
