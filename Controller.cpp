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
    int temp_choice;
    if (current_state == MENU)
    {
        temp_choice = 0;
        std::cout << "\nAlgoritms:\n";
        std::cout << "1) LRU\n";
        std::cout << "2) LFU\n";
        std::cout << "3) MFU\n";
        std::cout << "\nYour choice:\n";

        std::cin >> temp_choice;
        if (temp_choice < 4 && temp_choice > 0)
            current_state = static_cast<State>(temp_choice);
        else
            std::cout << "Plese chose 1,2 or 3";
    }

    if ((current_state == LRU || current_state == LFU || current_state == MFU) && data_option == NOT_CHOSEN)
    {
        temp_choice = 0;
        std::cout << "\n1) Use data from file\n";
        std::cout << "2) Generate 100 sets of 100 elements each\n";
        std::cout << "Chose option:\n";

        std::cin >> temp_choice;
        file.data_settings(temp_choice);//wywołuje funkcję która w zależności od "temp_choice" wywołuje funkcję do wczytywania pliku lub generacji cągów
        data_option = static_cast<Data_option>(file.get_data_option());//sprawdzamy czy stan "data_option" po odczytu z plika nie zmienił się
        file.write_tested_data_to_file();//kiedy już mamy dane na których będziemy testować algorym wpisujemy ich do "Tested_data.txt"
        algorithms.reserve_space(data_option);//Ustawia liczbę ramek i długość cąga odłowań
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
        file.write_results(algorithms.get_results());
        current_state = STOP;
    }
}

