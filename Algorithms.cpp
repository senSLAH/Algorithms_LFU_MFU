#include "Algorithms.h"

Algorithms::Algorithms()
{
    number_of_frames = 3; //ramki
    reference_string_length = 13;
    hit = 0;
    fault = 0;

    //wpisuje -1 daltego żeby sprawdacz czy w pirwszy raz kożystamy z tej ramki
    std::deque<int> temp(number_of_frames,-1);
    for (int i = 0; i < reference_string_length; ++i)
    {
       table.push_back(temp);
    }
}


void Algorithms::LRU_algorithm(std::vector<Page> &arr_of_pages)
{
    bool swap = false;
    for (int i = 0; i < reference_string_length; ++i)
    {
        for (int j = 0; j < number_of_frames; ++j)
        {
            // jeżeli równa -1, w takiem razie wiemy że jeszcze nie stosowaliśmy tego pola
            if (table[i][j] == -1)
            {
                fault += 1;//o ile zamieniamy wartość w 'table' mamy zwiekszyć fault (zasada dziłania algorymu)
                swap = true;
            }
            //jeżeli w ramcę już znajduje się liczba która jest następna w ciągu:
            //zwiększymy wartość hit
            //zmienimy kolejność numerów w taki sposób żebty ta liczba była na pirszem mejscu
            else if (table[i][j] == arr_of_pages[i].page)
            {
                hit += 1;// zwiększamy hit tylki
                swap = true;
            }
            //w przypadku kiędy jesteśmy na ostatniej ramce i nie znalazliśmy liczby w ramce
            //??????????????????
            else if (table[i][j] != arr_of_pages[i].page && j == number_of_frames-1)
            {
                fault += 1;
                swap = true;
            }

            if (swap)
            {
                int temp = arr_of_pages[i].page;
                table[i].erase(table[i].begin() + j);
                table[i].push_front(temp);
                swap = false;
                break;
            }
        }
        //wpisujemy do następnej ramki stan aktualnej ramki
        if ( i < reference_string_length-1)
        {
            for (int j = 0; j < number_of_frames; ++j)
                table[i+1][j] = table[i][j];
        }
    }

//    for (int i = 0; i < number_of_frames; ++i)
//    {
//        for (int j = 0; j < reference_string_length; ++j)
//        {
//            std::cout << table[j][i];
//        }
//        std::cout << "\n";
//    }
    results_data temp_res;
    temp_res.fault = fault;
    temp_res.hit = hit;
    // zapisujemy w vector dlatego żeby w przyszłości łatwo
    //zapisacz wynniki do pliku
    results.push_back(temp_res);
}

void Algorithms::LFU_algorithm(std::vector<Page> &arr_of_pages)
{
    bool swap = false;
    bool delete_element = false;
    for (int i = 0; i < reference_string_length; ++i)
    {
        for (int j = 0; j < number_of_frames; ++j)
        {
            // jeżeli równa -1, w takiem razie wiemy że jeszcze nie stosowaliśmy tego pola
            if (table[i][j] == -1)
            {
                fault += 1;//o ile zamieniamy wartość w 'table' mamy zwiekszyć fault (zasada dziłania algorymu)
                swap = true;
                check_frequency(arr_of_pages[i].page);
            }
            else if (table[i][j] == arr_of_pages[i].page)
            {
                hit += 1;
                swap = true;
                check_frequency(arr_of_pages[i].page);
            }
            else if (table[i][j] != arr_of_pages[i].page && j == number_of_frames-1)
            {
                fault += 1;
                swap = true;
            }

            if (swap)
            {
                int temp = arr_of_pages[i].page;
                // мы должны удалить нужный елемент
                table[i].erase(table[i].begin() + minimal_freq());
                table[i].push_front(temp);
                swap = false;
                break;
            }
        }
        if ( i < reference_string_length-1)
        {
            for (int j = 0; j < number_of_frames; ++j)
                table[i+1][j] = table[i][j];
        }
    }
    std::cout << "LFU\nFault: " << fault << "\tHit: " << hit << "\n";
    results_data temp_res;
    temp_res.fault = fault;
    temp_res.hit = hit;
    results.push_back(temp_res);
}

int Algorithms::minimal_freq(int option)
{
    frequency freq_temp;
    freq_temp = freq[0];
    int temp_index = 0;

    for (int i = 1; i < freq.size(); ++i)
    {
        if (freq_temp.repetitions <= freq[i].repetitions)
        {
            freq_temp = freq[i];
            temp_index = i;
        }
    }
    if (option == 1)
        check_frequency(freq_temp.num);
    return temp_index;
}

void Algorithms::check_frequency(int num)
{
    //iterujemy się po wszyskim elementam i szukamy liczby "num",
    //zwiększamy "repetitions" jeżeli znajdujemy i wychodzimy z funkcji
    //jeżeli nie ma takiego elementu - twożymy go
    for (int i = 0; i < freq.size(); ++i)
    {
        if (freq[i].num == num)
        {
            freq[i].repetitions += 1;
            return;//
        }
    }
    frequency temp;
    temp.num = num;
    temp.repetitions = 1;
    freq.push_front(temp);
}

void Algorithms::show_results()
{
    for (int i = 0; i < results.size(); ++i)
    {
        std::cout << "Hit: " << results[i].hit << "\n";
        std::cout << "Faults: " << results[i].fault << "\n";
    }
}

std::vector<results_data>& Algorithms::get_results()
{
    return results;
}



