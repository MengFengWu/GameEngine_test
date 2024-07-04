#include <stdio.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spiffs.h"

#include "../components/st7789/include/st7789.h"
#include "../components/fontx/include/fontx.h"
#include "../components/pngle/include/pngle.h"
#include "../components/decode_png/include/decode_png.h"

#include "../components/engine/include/Engine.h"

//#include "../files/people.h"

uint16_t *people;

//--Person class for testing--//
typedef struct person
{
    RenderObject mRenderObject;
    int attack;
    int HP;

    void (*new)(struct person*, RenderManager*);
}Person;

void personNew(struct person* obj, RenderManager* renderManager)
{
    obj->new = personNew;
    obj->attack = 10;
    obj->HP = 100;
    renderObjectNew(&(obj->mRenderObject), renderManager->findRenderResourceByName(renderManager, "person"), 50, 50, 1);
    printf("%s\n", "A person has been constructed.");
}
//----//

extern uint8_t testData[];

ResourceManager gResourceManager;
RenderManager gRenderManager;

void init()
{
    resourceManagerNew(&gResourceManager);
    renderManagerNew(&gRenderManager);
    printf("%s\n", "Manager initialization finished.");

    
    people = malloc(50*50*sizeof(uint16_t));
    for(uint16_t i = 0; i < 2500; i++)
    {
        people[i] = 30;
    }
    gRenderManager.addImage(&gRenderManager, &gResourceManager, "person", people, 50, 50);
    printf("%s\n", "Resource initialization finished.");
}

void app_main(void)
{
    init();
    Person John;
    personNew(&John, &gRenderManager);
    gRenderManager.addObject(&gRenderManager, &(John.mRenderObject));
    gRenderManager.renderAllObject(&gRenderManager);
    
    Person Mary;
    personNew(&Mary, &gRenderManager);
    gRenderManager.addObject(&gRenderManager, &(Mary.mRenderObject));
    gRenderManager.renderAllObject(&gRenderManager);

    Person Andy;
    personNew(&Andy, &gRenderManager);
    gRenderManager.addObject(&gRenderManager, &(Andy.mRenderObject));
    gRenderManager.renderAllObject(&gRenderManager);

    gRenderManager.removeObject(&gRenderManager, &(Mary.mRenderObject));
    gRenderManager.renderAllObject(&gRenderManager);

    gRenderManager.clear(&gRenderManager);
    gRenderManager.renderAllObject(&gRenderManager);
    /*
    while(1)
    {
        break;
    }
    */
    printf("%s\n", "Code finished.");
    //return 0;
}
