#include "Algorithms.h"

Algorithms::Algorithms(std::vector<Page>& data): data_storage(data)
{
    hit = 0;
    fault = 0;
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

void Algorithms::LFU_MFU_algorithm(std::vector<Page> &arr_of_pages)
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
                swap = false;
                check_frequency(arr_of_pages[i].page);
                break;
            }
            else if (table[i][j] != arr_of_pages[i].page && j == number_of_frames-1)
            {
                fault += 1;
                swap = true;
                check_frequency(arr_of_pages[i].page);
            }

            if (swap)
            {
                int temp = arr_of_pages[i].page;
                // мы должны удалить нужный елемент
                table[i].erase(table[i].begin() + min_max_freq(i, '+'));// "-"LFU, +"MFU"
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

// trzeba zwrócicz index elementa z najmniejdzym "repetitions"
int Algorithms::min_max_freq(int step, char option)
{
    if (step < 3)
        return step;

    std:: vector<repetitions_and_index> r_i;
    int index = 0;
    for (int i = 0; i < table[step].size(); ++i)
    {
        //находим какая у него частота
        for (int j = 0; j < freq.size(); ++j) // итерируемся по всем частотам и нахил частоту для этого числа
        {
            if (freq[j].num == table[step][i]) //нашли
            {
                repetitions_and_index temp_r;
                temp_r.repetitions = freq[j].repetitions;  //записываем частоту в перемунную что бы потом сравнить
                temp_r.index = i;//запоминаем индекс что бы если частота будем наименьшей удалить это число
                r_i.push_back(temp_r);
                break;
            }
        }
    }
    int temp_rep = r_i[0].repetitions;
    if (option == '-')
    {
        for (int j = 0; j < r_i.size()-1; ++j)
        {
            if (temp_rep >= r_i[j+1].repetitions)
                index = j+1;
        }
    }
    else
    {
        for (int j = 0; j < r_i.size()-1; ++j)
        {
            if (temp_rep <= r_i[j+1].repetitions)
                index = j+1;
        }
    }
    return r_i[index].index;
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

void Algorithms::reserve_space()
{
    number_of_frames = 3; //ramki
    reference_string_length = data_storage.size();


    //wpisuje -1 daltego żeby dalej sprawdacz czy w pirwszy raz kożystamy z tej ramki lub nie
    std::deque<int> temp(number_of_frames,-1);
    for (int i = 0; i < reference_string_length; ++i)
    {
        table.push_back(temp);
    }
}



