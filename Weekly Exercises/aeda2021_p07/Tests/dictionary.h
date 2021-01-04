#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
        bool operator == (const WordMeaning &wm1) const;
        friend ostream& operator<<(ostream& os, const WordMeaning& wm);
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;

};


//TODO
class WordInexistent
{
    string wordBefore;
    string wordBeforeMeaning;
    string wordAfter;
    string wordAfterMeaning;
public:
    WordInexistent(string wordBefore,string wordBeforeMeaning,string wordAfter,string wordAfterMeaning):wordBefore(wordBefore),wordBeforeMeaning(wordBeforeMeaning),
    wordAfter(wordAfter),wordAfterMeaning(wordAfterMeaning){}
    string getWordBefore() const;
    string getMeaningBefore() const;
    string getWordAfter() const;
    string getMeaningAfter() const;
};

#endif