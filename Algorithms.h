#ifndef SO_ALGORITHMS_H
#define SO_ALGORITHMS_H
#include <vector>
#include <deque>
#include "File_operation.h"

enum State : int {MENU = 0 , LRU = 1, LFU, MFU, WRITE ,STOP};
enum Data_option : int {NOT_CHOSEN = 0, FROM_FILE = 1, _100_sets_of_100_elements = 2 };

struct frequency
{
    int page;
    int used;
};

struct repetitions_and_index
{
    int used;
    int index;
};

class Algorithms
{
    std::deque<frequency> freq;//struktura danych która pamęta ile razy każdą ze stron użyli
    std::vector<std::deque<int>> table;
    std::vector<results_data> results;//struktura do której będziemy wpisyłacz wynniki algorytmów i zatem z niej będziemy zapisyłacz danne do pliku
    std::vector<Page>& data_storage;
    std::vector<std::vector<Page>>& data_storage_two_measures;
    int number_of_frames;
    int reference_string_length;

public:
    Algorithms(std::vector<Page>& data, std::vector<std::vector<Page>>& data_two_measures);

    void LFU_MFU_algorithm(std::vector<Page> &arr_of_pages, char option);
    void LFU_MFU_algorithm(std::vector<std::vector<Page>> &arr_of_pages, char option);

    void LRU_algorithm(std::vector<Page> &arr_of_pages);
    void LRU_algorithm(std::vector<std::vector<Page>> &arr_of_pages);

    void check_frequency(int page);
    //Zarządza strukturą danych "std::deque<frequency> freq"
    //"page" - przyjmuje numer, dalej funkcja sprawdza czy ten numer
    //znajduje się w tej strukruże lub nie
    //1) jeżeli znajduje się -> zwiększa licznik

    int min_max_freq(int step, char option);
    //zwraca indeks strony o najmniejszej lub najwyższej
    //liczbie powtórzeń, to zależy od parametru option.
    //"option" - może przyjmować parametry "-" lub "+".
    //1) "-": zwraca index strony o najmniejszej liczbie powtórzeń
    //2) "+": zwraca index strony o największej liczbie powtórzeń

    void reserve_space(int option);
    //

    void show_results();
    std::vector<results_data>& get_results();

};


#endif
