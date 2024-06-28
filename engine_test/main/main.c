#include <stdio.h>
#include <stdint.h>
#include "../components/engine/include/Engine.h"
#include "../files/data.h"

extern uint8_t testData[];

int main(void)
{
    uint8_t *testPtr = testData;
    
    ResourceManager sm1;
	resourceManagerNew(&sm1);
    sm1.load(&sm1);
    printf("%s\n", (sm1.findResourcebyID(&sm1, 0))->mFileName);
    printf("code finished successfully!/n");
    return 0;
    
    printf("%d\n", *(testPtr+3));
}