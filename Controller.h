#ifndef SO_CONTROLLER_H
#define SO_CONTROLLER_H

#include "vector"
#include "Algorithms.h"
#include "File_operation.h"




class Controller
{
    Algorithms &algorithms;
    File_operation &file;
    State current_state;
    State last_state;
    Data_option data_option;

public:
    Controller(Algorithms &a, File_operation &f);
    void set_state(State s);
    State get_state() const;
    void draw();
};


#endif
