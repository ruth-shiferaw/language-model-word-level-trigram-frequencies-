// Ruth Shiferaw
// RSHIFER1

#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include "language_model.h"
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::pair;
using std::make_pair;
using std::cerr; // default error output stream


int store_list_of_filenames(vector<string>& internal, string name, ifstream& infile) {
  if (!infile.is_open()) {
        cerr << "Invalid file list: " << name << endl;
        return 1;
    } else { //read into input file and verify specified files within can be opened too
        while (infile >> name) { //storing contents of input file into a vector
            internal.push_back(name);
        }
        return 0;
    }
}

 int saving_words_in_provided_files(vector<string>& filenames, map<vector<string>, int>& trigram_destination, string tempword) {
     for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
         std::ifstream testing_files(*it);
         if (!testing_files.is_open()) {
             cerr << "Invalid file: " << *it << endl;
             continue;
         } else {
             vector<string> temp_storing_vector;
             temp_storing_vector.push_back("<START_1>");
             temp_storing_vector.push_back("<START_2>");
             while (testing_files >> tempword) {
                 temp_storing_vector.push_back(tempword);
                 if (temp_storing_vector.size() == 4) {
                     vector<string> temp_storing_word;
                     temp_storing_word.push_back(temp_storing_vector[0]);
                     temp_storing_word.push_back(temp_storing_vector[1]);
                     temp_storing_word.push_back(temp_storing_vector[2]);
                     trigram_destination[temp_storing_word]++;
                     temp_storing_vector.erase(temp_storing_vector.begin());
                     //temp_storing_vector.clear();
                 }
             }
             //tempstoringvector.clear();
             temp_storing_vector.push_back("<END_1>");
             temp_storing_vector.push_back("<END_2>");
             vector<string> temp_storing_word;
             temp_storing_word.push_back(temp_storing_vector[0]);
             temp_storing_word.push_back(temp_storing_vector[1]);
             temp_storing_word.push_back(temp_storing_vector[2]);
             trigram_destination[temp_storing_word]++;
             //trigram_destination[temp_storing_word + " <END_1> <END_2>"]++;
         }
     }
     return 0;
 }


int handle_A_command(map<vector<string>, int>& trigram_destination) {
    //making a temp vector to compare the orig to
    vector<pair<vector<string>, int>> trigrams;
    
    //copying into temp
    for (map<vector<string>, int>::iterator it = trigram_destination.begin(); it != trigram_destination.end(); it++) {
        trigrams.push_back(make_pair(it->first, it->second));
    }
    
    //using sort algo to sort the temp
    sort(trigrams.begin(), trigrams.end());
    
    int num_frequencies = 0;
    for (vector<pair<vector<string>, int>>::iterator it = trigrams.begin(); it != trigrams.end(); it++) {
        num_frequencies = it -> second;
        cout << num_frequencies << " - [";
        for (unsigned i = 0; i < it->first.size(); i++) {
            if (i == 2) {
                cout << it->first[i];
            } else {
                cout << it->first[i] << " ";
            }
        }
        cout << "]" << endl;
    }
  return 0;
}

int handle_D_command(map<vector<string>, int>& trigram_destination) {
    //this code is recycled from handleAcommand, so same comments apply !
    vector<pair<vector<string>, int>> trigrams;
    
    for (map<vector<string>, int>::iterator it = trigram_destination.begin(); it != trigram_destination.end(); it++) {
        trigrams.push_back(make_pair(it->first, it->second));
    }
    
    // sorting it backwards so it ends up in descending order
    sort(trigrams.rbegin(), trigrams.rend());
    
    int num_frequencies = 0;
    for (vector<pair<vector<string>, int>>::iterator it = trigrams.begin(); it != trigrams.end(); it++) {
        num_frequencies = it->second;
        cout << num_frequencies << " - [";
        for (unsigned i = 0; i < it->first.size(); i++) {
            if (i == 2) {
                cout << it->first[i];
            } else {
                cout << it->first[i] << " ";
            }
        }
        cout << "]" << endl;
    }
    
    return 0;
}

int handle_C_command(map<vector<string>, int>& trigram_destination) {
    //making a different vecotor that will hold the trigrams and their freq
    vector<pair<vector<string>, int>> tempvector;

    //copying contents of original map holding trigrams to the new tempvector
    for (map<vector<string>, int>::iterator it = trigram_destination.begin(); it != trigram_destination.end(); ++it) {
        tempvector.push_back(make_pair(it->first, it->second)); // Use make_pair to add elements to the vector.
    }

    // sort the vector in descending order by count
    for (unsigned i = 0; i < tempvector.size() - 1; ++i) {
        for (unsigned j = i + 1; j < tempvector.size(); ++j) {
            if (tempvector[i].second < tempvector[j].second) {
                swap(tempvector[i], tempvector[j]);
            } else if (tempvector[i].first[0] == tempvector[j].first[0]) { //// if counts are the same, sort by alphabetical order of first, second, and third words
                if (tempvector[i].first[1] == tempvector[j].first[1]) {
                    if (tempvector[i].first[2] > tempvector[j].first[2]) {
                        swap(tempvector[i], tempvector[j]);
                    }
                } else if (tempvector[i].first[1] > tempvector[j].first[1]) {
                    swap(tempvector[i], tempvector[j]);
                }
            }
        }
    }

    // print the sorted trigrams and their counts
    for (unsigned i = 0; i < tempvector.size(); ++i) {
        cout << tempvector[i].second << " - [" << tempvector[i].first[0] << " " << tempvector[i].first[1] << " " << tempvector[i].first[2] << "]" << endl;
    }

    return 0;
}

int handle_F_command(map<vector<string>, int>& trigram_destination, string firstword, string secondword){
    //making a temp vector to store the matching occurrances
    vector<pair<vector<string>, int>> list_of_matches;

    //iterating through the original trigram_destination map and checking for matches to the keywords
    for (map<vector<string>, int>::iterator i = trigram_destination.begin(); i != trigram_destination.end(); ++i) {
        vector<string> temp_trigram = i->first; //stores the first trigram in parameter map into a vector of strings
        //checking for matches
        if ((temp_trigram[0] == firstword) && (temp_trigram[1] == secondword)) {
            list_of_matches.push_back(*i);
        }
    }

    //checking if no matches were found
    if (list_of_matches.empty() == true) {
        cerr << "No trigrams of the form [" << firstword << " " << secondword << " ?]." << endl;
        return 1;
    }

    //sorting the list_of_matches array in alphabetical order and by count
    sort(list_of_matches.begin(), list_of_matches.end());

    cout << list_of_matches[0].second << " - [" << list_of_matches[0].first[0] << " " << list_of_matches[0].first[1] << " " << list_of_matches[0].first[2] << "]" << endl;

    return 0;
}
  

