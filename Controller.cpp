#include "Controller.h"


Controller::Controller(Algorithms &a, File_operation &f):algorithms(a), file(f)
{
    current_state = MENU;
    data_option = NOT_CHOSEN;
}


State Controller::get_state() const
{
    return current_state;
}

void Controller::draw()
{
    int temp;
    if (current_state == MENU)
    {
        temp = 0;
        std::cout << "\nAlgoritms:\n";
        std::cout << "1) LRU\n";
        std::cout << "2) LFU\n";
        std::cout << "3) MFU\n";
        std::cout << "\nYour choice:\n";

        std::cin >> temp;
        if (temp < 4 && temp > 0)
            current_state = static_cast<State>(temp);
        else
            std::cout << "Plese chose 1,2 or 3";
    }

    if ((current_state == LRU || current_state == LFU || current_state == MFU) && data_option == NOT_CHOSEN)
    {
        temp = 0;
        std::cout << "\n1) Use data from file\n";
        std::cout << "2) Generate 100 sets of 100 elements each\n";
        std::cout << "Chose option:\n";

        std::cin >> temp;
        data_option = static_cast<Data_option>(temp);
        file.data_settings(temp);
        file.write_tested_data_to_file();
        algorithms.reserve_space(data_option);
    }

    if (current_state == LRU)
    {
        if (data_option == FROM_FILE)
            algorithms.LRU_algorithm(file.get_data_storage());
        else
            algorithms.LRU_algorithm(file.get_data_storage_two_measures());
        current_state = WRITE;
    }
    if (current_state == LFU)
    {
        if (data_option == FROM_FILE)
            algorithms.LFU_MFU_algorithm(file.get_data_storage(), '-');
        else
            algorithms.LFU_MFU_algorithm(file.get_data_storage_two_measures(), '-');
        current_state = WRITE;
    }
    if (current_state == MFU)
    {
        if (data_option == FROM_FILE)
            algorithms.LFU_MFU_algorithm(file.get_data_storage(), '+');
        else
            algorithms.LFU_MFU_algorithm(file.get_data_storage_two_measures(), '+');
        current_state = WRITE;
    }
    if (current_state == WRITE)
    {
        // функция для записи в файл результатов
        file.write_results(algorithms.get_results());
        current_state = STOP;
    }
}

void Controller::set_state(State s)
{
    current_state = s;
}
