// Ruth Shiferaw
// RSHIFER1

#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include "language_model.h"

using std::cin;
using std::cout;
using std::endl; // end of line, flushes buffer
using std::cerr; // default error output stream
using std::vector;
using std::string;
using std::map;

int main(int argc, char* argv[]) {
    if (argc < 2) { //if no input filename argument was provided
        cerr << "Invalid file list: " << argv[1] << endl;
        return 1;
    }

    if ((*argv[2] == 'f')) {
        if (argc != 5) {
            cerr << "Invalid argument list: f requires two additional command-line arguments" << endl;
            return 1;
        }
    }

    vector <string> internal_files;
    string filename; 

    //checking if argv[1] filename can be opened 
    std::ifstream input_file(argv[1]); 
    string command_inputfile = argv[1];
    store_list_of_filenames(internal_files, command_inputfile, input_file); //stores the specified filenames within a vector

    map<vector<string>,int> store_trigrams;
    string temp_file_contents;
    
    //saving the available words from specified txt files into a map
    saving_words_in_provided_files(internal_files, store_trigrams, temp_file_contents);

    switch (*argv[2]) {
        case 'a':
            handle_A_command(store_trigrams);
            break;
        case 'd':
            handle_D_command(store_trigrams);
            break;
        case 'c':
            handle_C_command(store_trigrams);
            break;
        case 'f':
            if (handle_F_command(store_trigrams, argv[3], argv[4]) == 1) {
                return 1;
            }
            break;
        default:
            cerr << "Invalid command: valid options are a, d, c, and f" << endl;
            break;
    }
    
    return 0;
}
