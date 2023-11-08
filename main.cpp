#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

unordered_set<string> word_set;


bool dfs(string word, unordered_set<string> &word_set) {
    for (int i = 0; i < word.size();i++) {
        string prefix = word.substr(0, i+1);
        string suffix = word.substr(i+1);
        if (word_set.find(prefix) != word_set.end() && 
            (word_set.find(suffix) != word_set.end() || dfs(suffix, word_set))) {
            return true;
        }
    }
    return false;
}

map<int,vector<string>> findAllConcatenatedWordsInADict(vector<string>& words, set<int, greater<int>>& word_length_counts) {
    word_set = unordered_set<string>();
    map<int,vector<string>> result;
    for (string w : words) {
        word_set.insert(w);
    }
    
    //vector<string> answer;
    for  (string word: words) {
        if (dfs(word, word_set)) {
            int len = (int)word.length();
            
            //answer.push_back(word);
            // 1. Add word to vector for that length
            if (result.find(len) == result.end()) {
                vector<string> val;
                val.push_back(word);
                result[len] = val;
            } else {
                result[len].push_back(word);
            }
            // 2. Add that length to that set of lengths
            word_length_counts.insert(len);
        }
    }
    

    return result;
}

int main() {
    vector<string> overallDict;
    set<int, greater<int>> len_set;
    map<int,vector<string>> tally;
    
    
    cout << "TEST" << endl;
    // Build the word list
    //ifstream file("/Users/dex/test.txt");
    ifstream file("/Users/dex/wordsforproblem.txt");
    
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            // note that the newline character is not included
            // in the getline() function
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            overallDict.push_back(line);
        }
    }
    cout << "Number of entries in Dictionary = " << overallDict.size() << endl;
    
    tally = findAllConcatenatedWordsInADict(overallDict, len_set);
    int final_count = 0;
    for (int num : len_set) {
        final_count += tally[num].size();
    }
    cout << "For question #2 the answer is " << final_count;
    cout << endl << "For question #2: Number of concatenated words = " << final_count << endl;

    // Sort that set of lengths
    int longest = *len_set.begin();
    cout << "For question #1a, the length of the longest word is " << longest << endl;
    cout << "The matching word(s): " << endl;
    for (string v : tally[longest]) {
        cout << v << endl;
    }
    cout << endl;
    
    set<int>::iterator iter = len_set.begin();
    iter++;
    int second_place = *iter;
    cout << "For question #1b, the length of the 2nd-longest word is " << second_place << endl;
    cout << "The matching word(s): " << endl;
    for (string v : tally[second_place]) {
        cout << v << endl;
    }
    cout << endl;

    
    return 0;
}
