#include "File_operation.h"


File_operation::File_operation()
{
    data_option = 0;
    input_file.open("../Test_data.txt");
    if (!input_file.is_open())
    {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    output_file.open("../Results.txt");
    if (!output_file.is_open())
    {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    std::cout << "File input file opened successfully!\n";
    std::cout << "File output file opened successfully!\n";

    data_storage_two_measures.resize(100);
    for (auto & data_storage_two_measure : data_storage_two_measures)
    {
        data_storage_two_measure.resize(100);
    }

}

void File_operation::data_settings(int option)
{
    data_option = option;
    if (option == 1)
    {
        read_file();
    }

    if (option == 2)
    {

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

File_operation::~File_operation()
{
    input_file.close();
    output_file.close();
    std::cout << "Files successfully closed!\n";
}

std::vector<Page> &File_operation::get_data_storage()
{
    return data_storage;
}
