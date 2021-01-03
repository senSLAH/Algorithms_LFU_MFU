#include "Algorithms.h"

Algorithms::Algorithms()
{
    number_of_frames = 3;
    reference_string_length = 20;
    hit = 0;
    fault = 0;

    std::deque<int> temp(3,-1);
    for (int i = 0; i < reference_string_length; ++i)
    {
       table.push_back(temp);
    }
}

//std::vector<std::vector<float>> Algorithms::get_results()
//{
//    return results;
//}

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
    std::cout << fault << " " << hit << "\n";
}

void Algorithms::check_frequency(int num)
{
    for (int i = 0; i < freq.size(); ++i)
    {
        if (freq[i].num == num)
        {
            freq[i].repetitions += 1;
        }
        return;
    }
    frequency temp;
    temp.num = num;
    temp.repetitions = 1;
    freq.push_back(temp);
}




