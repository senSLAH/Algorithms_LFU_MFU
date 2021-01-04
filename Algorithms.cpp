#include "Algorithms.h"

Algorithms::Algorithms()
{
    number_of_frames = 3;
    reference_string_length = 13;
    hit = 0;
    fault = 0;

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
            if (table[i][j] == -1)
            {
                fault += 1;
                swap = true;
            }
            else if (table[i][j] == arr_of_pages[i].page)
            {
                hit += 1;
                swap = true;
            }
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

            if (table[i][j] == -1)
            {
                fault += 1;
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
                delete_element = true;
            }

            if (swap)
            {
                if (delete_element)
                {
                    delete_element_func(1);
                    check_frequency(arr_of_pages[i].page);
                }


                int temp = arr_of_pages[i].page;
                table[i].erase(table[i].begin() + delete_element_func());
                table[i].push_front(temp);
                swap = false;
                delete_element = false;
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

int Algorithms::delete_element_func(int option)
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
        check_frequency(freq_temp.num, "Delete");
    return temp_index;
}

void Algorithms::check_frequency(int num, std::string option)
{
    for (int i = 0; i < freq.size(); ++i)
    {
        if (freq[i].num == num && option == "Delete")
        {
            freq.erase(freq.begin() + i);
            return;
        }
        if (freq[i].num == num && option == "Pass")
        {
            freq[i].repetitions += 1;
            return;
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



