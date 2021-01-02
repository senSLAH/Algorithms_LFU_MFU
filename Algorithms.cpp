#include "Algorithms.h"

Algorithms::Algorithms()
{
    number_of_frames = 3;
    reference_string_length = 20;
    std::vector<int> temp(3);
    hit = 0;
    fault = 0;

    for (int i = 0; i < reference_string_length; ++i)
    {
        table.push_back(temp);
    }
}

//std::vector<std::vector<float>> Algorithms::get_results()
//{
//    return results;
//}

void Algorithms::LFU_algorithm(std::vector<Page> &arr_of_pages)
{
    for (int i = 0; i < reference_string_length; ++i)
    {
        for (int j = 0; j < number_of_frames; ++j)
        {
            if (table[i][j] == 0)
            {
                table[i][j] = arr_of_pages[i].page;
                arr_of_pages[i].used += 1;
                fault += 1;
                break;
            }
            else if (table[i][j] == arr_of_pages[i].page)
            {
                hit += 1;
                break;
            }
            else if (j == 2)
            {
                //stosujemy FIFO
                table[i][0] = table[i][1];
                table[i][1] = table[i][2];
                table[i][2] = arr_of_pages[i].page;
                fault += 1;
            }
        }
        if ( i != reference_string_length)
        {
            table[i+1][0] = table[i][0];
            table[i+1][1] = table[i][1];
            table[i+1][2] = table[i][2];
        }
    }

    for (int i = 0; i < number_of_frames; ++i)
    {
        for (int j = 0; j < reference_string_length; ++j)
        {
            std::cout << table[j][i];
        }
        std::cout << "\n";
    }
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




