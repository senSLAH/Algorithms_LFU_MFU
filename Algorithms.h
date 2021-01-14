#ifndef SO_ALGORITHMS_H
#define SO_ALGORITHMS_H
#include <vector>
#include <deque>
#include "File_operation.h"

enum State : int {MENU = 0 , LRU = 1, LFU, WRITE ,STOP};
enum Data_option : int {NOT_CHOSEN = 0, FROM_FILE = 1, _100_sets_of_100_elements = 2 };

struct frequency
{
    int num;
    int repetitions;
};

struct repetitions_and_index
{
    int repetitions;
    int index;
};

class Algorithms
{
    std::deque<frequency> freq;//struktura danych która pamęta ile razy każdą ze stron użyli
    std::vector<std::deque<int>> table;
    std::vector<results_data> results;//struktura do której będziemy wpisyłacz wynniki algorytmów i zatem z niej będziemy zapisyłacz danne do pliku
    std::vector<Page>& data_storage;
    int number_of_frames;
    int reference_string_length;
    int hit;
    int fault;

public:
    explicit Algorithms(std::vector<Page>& data);
    void reserve_space();
    void run_algorithm(State algorithm_type, Data_option option);
    void LFU_MFU_algorithm(std::vector<Page> &arr_of_pages);
    void LRU_algorithm(std::vector<Page> &arr_of_pages);
    void check_frequency(int num);
    int min_max_freq(int step, char option);         //if step = 1 function will clear frequency
    void show_results();
    std::vector<results_data>& get_results();

};


#endif
