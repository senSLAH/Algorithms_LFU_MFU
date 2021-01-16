#ifndef SO_ALGORITHMS_H
#define SO_ALGORITHMS_H
#include <vector>
#include <deque>
#include "File_operation.h"

enum State : int {MENU = 0 , LRU = 1, LFU, MFU, WRITE ,STOP};//stan programu
enum Data_option : int {NOT_CHOSEN = 0, FROM_FILE = 1, _100_sets_of_100_elements = 2 };//opcji pobierania danych

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
    //"page" - przyjmuje strone, dalej funkcja sprawdza czy strona
    //znajduje się w tej strukruże która przechowuje struktura danych która
    //pamęta ile razy każdą ze stron użyli lub nie
    //1)jeżeli znajduje się -> zwiększa licznik
    //2)tworzy nowy obiekt w "freq" i przypisuje wartość

    int min_max_freq(int step, int free_element_of_frame, char option);
    //zwraca indeks strony o najmniejszej lub najwyższej
    //liczbie powtórzeń, to zależy od parametru option.
    //"option" - może przyjmować parametry "-" lub "+".
    //1) "-": zwraca index strony o najmniejszej liczbie powtórzeń(dla LFU)
    //2) "+": zwraca index strony o największej liczbie powtórzeń(dla MFU)

    void reserve_space(int option);
    //Ustawia liczbę ramek i długość cąga odłowań
    //wpisuje -1 do tablicy daltego żeby dalej sprawdacz czy w poraz pierwszy raz kożystamy z elementu w ramce

    std::vector<results_data>& get_results();

};


#endif
