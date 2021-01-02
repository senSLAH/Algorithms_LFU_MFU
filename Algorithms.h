#ifndef SO_ALGORITHMS_H
#define SO_ALGORITHMS_H
#include "vector"
#include "File_operation.h"

enum State : int {MENU = 0 , LFU = 1, MFU, WRITE ,STOP};
enum Data_option : int {NOT_CHOSEN = 0, FROM_FILE = 1, _100_sets_of_100_elements = 2 };

struct frequency
{
    int num;
    int repetitions;
};

class Algorithms
{
    std::vector<frequency> freq;
    std::vector<std::vector<int>> table;
    int number_of_frames;
    int reference_string_length;
    int hit;
    int fault;

public:
    Algorithms();
    void run_algorithm(State algorithm_type, Data_option option);
    void LFU_algorithm(std::vector<Page> &arr_of_pages);
    void check_frequency(int num);
    void FCFS_algorithm_two_measures(std::vector<std::vector<Page>> &arr_of_proces);
    void SJF_algorith(std::vector<Page> &arr_of_proces);
    void average_TAT_WT(std::vector<Page> &arr_of_proces);
    std::vector<std::vector<float>> get_results();
    void bubble_sort(std::vector<Page> &arr_of_proces, std::string str = "arrival");
};


#endif
