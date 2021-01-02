#include <string>

#include "Algorithms.h"
#include "Controller.h"
#include "File_operation.h"


int main()
{
    srand(time(0));

    File_operation file;
    Algorithms algorithms;
    Controller ctrl(algorithms,file);


    while (ctrl.get_state() != STOP)
    {
        ctrl.draw();
    }

    return 0;
}
