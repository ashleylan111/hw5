#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;



// Add prototypes of helper functions here

void wordFinder(const std::string current,
    std::string floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& results);

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> results;

    std::string current = in;
    wordFinder(current, floating, dict, results);

    return results;

}

// Define any helper functions here

void wordFinder(const std::string current,
    const std::string floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& results){

    //Base Case: If there are no blanks 
    if (current.find('-') == std::string::npos){

        if (floating.empty() && dict.count(current)){
            results.insert(current);
        }

        return;
        
    } 

    int blank_left = std::count(current.begin(), current.end(), '-');
    if (floating.size() > blank_left){
        return;
    }

    int idx = current.find('-');

    //Let the floating letters cover the blanks first 

    for (int i = 0; i < floating.size(); i++){
        char letter = floating[i];

        std::string nextWord = current;
        nextWord[idx] = letter;
        std::string nextFloating = floating;
        nextFloating.erase(i, 1); //Removing the float letter after attempted try

        wordFinder(nextWord, nextFloating, dict, results);

    }

    //Then let the rest of the blanks fill up 

    if (floating.size() <= blank_left - 1){
        for (char x = 'a'; x <= 'z'; x++){

            if (floating.find(x) != std::string::npos){
                continue;
            }

            std::string nextWord = current;
            nextWord[idx] = x;

            wordFinder(nextWord, floating, dict, results);

        }
    }


}
