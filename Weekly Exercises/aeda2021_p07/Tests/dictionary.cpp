#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word<wm1.getWord();
}

ostream &operator<<(ostream &os, const WordMeaning &wm) {
    os << wm.getWord() << '\n' << wm.getMeaning();
    return os;
}

bool WordMeaning::operator==(const WordMeaning &wm1) const {
    return (word==wm1.getWord() && meaning==wm1.getMeaning());
}

//TODO
void Dictionary::readDictionary(ifstream &f)
{
    string word,meaning;
    while (getline(f,word)){
        getline(f,meaning);
        words.insert(WordMeaning(word,meaning));
    }
}

//TODO
string Dictionary::searchFor(string word) const
{
    string wordBefore,wordBeforeMeaning,wordAfter,wordAfterMeaning;
    BSTItrIn<WordMeaning> it1(words);
    while (!it1.isAtEnd()){
        wordBefore=it1.retrieve().getWord();
        wordBeforeMeaning=it1.retrieve().getMeaning();
        if (it1.retrieve().getWord()==word) return it1.retrieve().getMeaning();
        it1.advance();
        if (it1.isAtEnd()) break;
        wordAfter=it1.retrieve().getWord();
        wordAfterMeaning=it1.retrieve().getMeaning();
        if (it1.retrieve().getWord()==word) return it1.retrieve().getMeaning();
        else if (it1.retrieve().getWord()>word) break;
    }
    throw WordInexistent(wordBefore,wordBeforeMeaning, wordAfter,wordAfterMeaning);

}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    if (words.remove(WordMeaning(word,""))){
        words.insert(WordMeaning(word,newMeaning));
        return true;
    }else{
        words.insert(WordMeaning(word,newMeaning));
        return false;
    }
}

//TODO
void Dictionary::print() const
{
    words.printTree();
}

string WordInexistent::getWordBefore() const {
    return wordBefore;
}

string WordInexistent::getMeaningBefore() const {
    return wordBeforeMeaning;
}

string WordInexistent::getWordAfter() const {
    return wordAfter;
}

string WordInexistent::getMeaningAfter() const {
    return wordAfterMeaning;
}
