// Ruth Shiferaw
// RSHIFER1

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>
#include <map>

/** A function that stores the filenames within the .txt containing the list of files from the command line.
 * @param internal the vector the filenames are stored in
 * @param name the name of the file list in the command line
 * @param infile the file containing the other filenames */
int store_list_of_filenames(std::vector<std::string>& internal, std::string name, std::ifstream& infile);

/** A function that checks for valid filenames as content within the list of filenames, and
 * if valid, will store the contents of each file into a map.
 * @param filenames the vector storing the filenames in the list of files
 * @param trigram_destination the map the trigrams are stored within
 * @param tempword the word being stored within the map */
int saving_words_in_provided_files(std::vector<std::string>& filenames, std::map<std::vector<std::string>,int>& trigram_destination, std::string tempword);

/** A function that sorts and prints a list of trigrams into an ascending alphabetical order.
 * @param trigram_destination the map the trigrams are stored within */
int handle_A_command(std::map<std::vector<std::string>, int>& trigram_destination);

/** A function that sorts and prints a list of trigrams into a descending alphabetical order.
 * @param trigram_destination the map the trigrams are stored within */
int handle_D_command(std::map<std::vector<std::string>, int>& trigram_destination);

/** A function that sorts and prints a list of trigrams based on their frequency
 * in descending order.
 * @param trigram_destination the map the trigrams are stored within */
int handle_C_command(std::map<std::vector<std::string>, int>& trigram_destination);

/** A function that sorts and prints a list of trigrams based on the most
 * frequently occurring third word given two keywords for the first two 
 * words of the trigram.
 * @param trigram_destination the map the trigrams are stored within */
int handle_F_command(std::map<std::vector<std::string>, int>& trigram_destination, std::string firstword, std::string secondword);

