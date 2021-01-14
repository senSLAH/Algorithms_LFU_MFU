#include "File_operation.h"


File_operation::File_operation()
{
    data_option = 0;

    process = 20;//proces zawira 20 stron

    input_file.open("../Test_data.txt");
    if (!input_file.is_open())
    {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    output_tested_data_file.open("../Tested_data.txt");
    if (!output_tested_data_file.is_open())
    {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    output_results_data_file.open("../Results.txt");
    if (!output_results_data_file.is_open())
    {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    std::cout << "File input file opened successfully!\n";
    std::cout << "File output file opened successfully!\n";

    data_storage_two_measures.resize(100);
    for (auto & data_storage_two_measure : data_storage_two_measures)
        data_storage_two_measure.resize(100);

}

void File_operation::data_settings(int option)
{
    data_option = option;
    if (option == 1)
        read_file();
    if (option == 2)
    {
        generate_100_sets_of_100_elements();
    }
}

void File_operation::read_file()
{
    char ch;
    std::string data_form_file;
    std::string save_value;
    Page temp;

    // zapisujemy cało zawartość plika do data_form_file
    while (input_file.get(ch))
        data_form_file += ch;

    for (int i = 0; i < data_form_file.size(); ++i)
    {
        save_value = "";

        if (data_form_file[i] != ' ')
        {
            save_value += data_form_file[i];
            temp.page = stoi(save_value);
            temp.used = 0;
            data_storage.push_back(temp);
        }
    }
}

std::vector<Page> &File_operation::get_data_storage()
{
    return data_storage;
}

void File_operation::generate_100_sets_of_100_elements()
{
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            data_storage_two_measures[i][j].page = rand() % process + 1 ;
            data_storage_two_measures[i][j].used = 0 ;
        }
    }
    std::cout << "";
}

void File_operation::write_results(std::vector<results_data> &results)
{
    for (int i = 0; i < results.size(); ++i)
    {
        output_results_data_file << "Hit: " << results[i].hit;
        output_results_data_file << "\nFault: " << results[i].fault << "\n";
    }
}

void File_operation::write_tested_data_to_file()
{
    if (data_option == 1)
        for (auto &i : data_storage)
            output_tested_data_file << i.page;
    else
        for (int i = 0; i < data_storage_two_measures.size(); ++i)
            for (int j = 0; j < data_storage_two_measures[i].size(); ++j)
                output_tested_data_file << data_storage_two_measures[i][j].page << " ";

}

std::vector<std::vector<Page>> &File_operation::get_data_storage_two_measures()
{
    return data_storage_two_measures;
}

File_operation::~File_operation()
{
    input_file.close();
    output_results_data_file.close();
    std::cout << "Files successfully closed!\n";
}
