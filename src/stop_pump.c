#include "pump.h"

int main(void)
{
    if(init_pump())
        return 1;
    stop_pump();
    return 0;   
}
