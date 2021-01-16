#ifndef SO_FILE_OPERATION_H
#define SO_FILE_OPERATION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>


struct Page //dla algorytmu LFU i MFU tworzymy strukturu która może przechowywać strone(page) i liczbe zastowań(used)
{
    int page;
    int used;
};

struct results_data//dla zapisu wynników
{
    int fault;
    int hit;
};

class File_operation
{
    std::ifstream input_file;
    std::ofstream output_results_data_file;
    std::ofstream output_tested_data_file;
    std::vector<Page> data_storage;//zawiera dane jeżeli  zdecydowaliśmy kożystać z jednego cągu odwołań
    std::vector<std::vector<Page>> data_storage_two_measures;//zawiera dane jeżeli  zdecydowaliśmy kożystać ze 100 różnych cągów odwołań
    int data_option;// zawiera 1 lub 2 w zależności od tego czy zdecydowaliśmy kożystać z odczytu pliku czy generacji stu różnych ciągach odwołań
    int process;//zawiera liczbę stron zajmowanych przez proces

public:
    File_operation();
    //1)otwieramy pliki i sprawdzamy czy udało ich się otwożycz
    //dalej wypisujemy otpowidni komunikaty.
    //2)rezerwujemy mejsce na stu różnych ciągów w wektoże
    //3)przypisuje zmiennej "procesu" ilość stron zajmowanych przez proces

    void data_settings(int option);
    //w zależności od "data_option" wywołuje funkcję która generuje cągi lub czyta dane z plika

    void read_file();
    //wczytuje danne z pliku Test_data.txt
    //możemy zmienicz "data_option" jeżeli plik zawira 10000 elementów


    void write_results(std::vector<results_data> &results);
    //zapisuje wynniki do pliku Results.txt;


    void write_tested_data_to_file();
    //zapisuje dane użyte przy ostatnim testowaniu do pliku Tested_data.txt z takim
    //formatowaniem aby móc skopiować te dane do pliku Test_data.txt i skożystać z tych samych
    //dannych przy następnych badaniach za pomocą opcji odczytu z pliku


    void generate_100_sets_of_100_elements();
    //generuje sto cągów w każdym 100 odwołań do procesów z zakresu [1-20]

    int get_data_option();
    std::vector<Page>& get_data_storage();
    std::vector<std::vector<Page>>& get_data_storage_two_measures();

    ~File_operation();
    //zamyka pliki i wypisuje odpowidni komunikat
};


#endif
