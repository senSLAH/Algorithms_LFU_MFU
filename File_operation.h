#ifndef SO_FILE_OPERATION_H
#define SO_FILE_OPERATION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>

struct Page
{
    int page;
    int used;
};

class File_operation
{
    std::ifstream input_file;
    std::ofstream output_file;
    std::vector<Page> data_storage;
    std::vector<std::vector<Page>> data_storage_two_measures;
    int data_option;

public:
    File_operation();
    void data_settings(int option);
    void read_file();
    void generate_100_sets_of_100_elements();
    std::vector<Page>& get_data_storage();
    std::vector<std::vector<Page>>& get_data_storage_two_measures();
    void draw_processes() const;
    void write_to_file(std::vector<std::vector<float>> res);
    ~File_operation();
};


#endif
