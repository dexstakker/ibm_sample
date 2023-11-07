#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
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

vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
    for (string w : words) {
        word_set.insert(w);
    }
    vector<string> answer;
    for  (string word: words) {
        if (dfs(word, word_set)) {
            answer.push_back(word);
        }
    }
    return answer;
}

int main() {
    vector<string> overallDict;
    
    
    cout << "TEST" << endl;
    // Build the word list
    ifstream file("/Users/dex/test.txt");
    //ifstream file("/Users/dex/wordsforproblem.txt");
    
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
    
    vector<string> ans = findAllConcatenatedWordsInADict(overallDict);
    cout << endl << "For question #1: Number of concatenated words = " << ans.size() << endl;

    return 0;
}

