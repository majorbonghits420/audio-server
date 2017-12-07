#include "PassCheck.hpp"

namespace PassCheck {

  bool basic16Check(std::string str) {
    return str.length() >= 16;
  }

  bool checkChars(std::string str) {
    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSymbol = false;
    for (char c : str) {
      hasLower = hasLower || islower(c);
      hasUpper = hasUpper || isupper(c);
      hasDigit = hasDigit || isdigit(c);
      hasSymbol = hasSymbol || ispunct(c);
    }
    return hasLower && hasUpper && hasDigit && hasSymbol;
  }

  std::string removeNonLetters(std::string str) {
    std::string toReturn("");
    for (unsigned int i = 0; i < str.length(); ++i) {
      if (isalpha(str[i])) {
        toReturn += tolower(str[i]);
      }
    }
    return toReturn;
  }

  bool dictCheck(std::string str) {
    // Check dictionary for word
    std::ifstream fid("words.txt");
    if(!fid) {
      std::cout << "Couldn't read file" << std::endl;
    }
    // While there is still words to check against
    while(fid) {
      std::string word;
      fid >> word;
      if (str.compare(word) == 0 && !word.empty()) {
        return false;
      }
    }
    return true;
  }

  bool comprehensive8Check(std::string str) {
    if (str.length() < 8) {
      return false;
    }
    if (checkChars(str) == false) {
      return false;
    }
    std::string lettersOnly = removeNonLetters(str);
    return dictCheck(lettersOnly);
  }

};
