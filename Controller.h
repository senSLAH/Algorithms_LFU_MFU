#ifndef SO_CONTROLLER_H
#define SO_CONTROLLER_H

#include "vector"
#include "Algorithms.h"
#include "File_operation.h"




class Controller
{
    Algorithms &algorithms;
    File_operation &file;
    State current_state;//stan programu
    Data_option data_option;// zawiera 1 lub 2 w zależności od tego czy zdecydowaliśmy kożystać z odczytu pliku czy generacji stu różnych ciągach odwołań

public:
    Controller(Algorithms &a, File_operation &f);
    //wartości domyślne dla current_state data_option

    void draw();
    //wyświetla Menu, zarządza stanem programu(current_state) i wywołaniem algorytmów

    State get_state() const;
};


#endif
