#include <string>

#include "Algorithms.h"
#include "Controller.h"
#include "File_operation.h"
#include "time.h"


int main()
{
    srand(time(0));

    File_operation file;
    Algorithms algorithms(file.get_data_storage());
    Controller ctrl(algorithms,file);


    while (ctrl.get_state() != STOP)
    {
        ctrl.draw();
    }

    return 0;
}
