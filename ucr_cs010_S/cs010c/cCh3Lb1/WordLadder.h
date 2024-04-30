#include <list>
#include <string>

using std::list;
using std::string;

class WordLadder {
    list<string> dict;
    bool letterChecker(const string& selectedWord, const string &newWord) const;

    public:
        WordLadder(const string &filename);
        void outputLadder(const string&start, const string& end, const string &outputFile);
};