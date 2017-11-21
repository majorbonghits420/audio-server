#ifndef __PASSCHECK_HPP__
#define __PASSCHECK_HPP__

#include <string.h>
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>

namespace PassCheck {

  bool basic16Check(std::string str);

  bool checkChars(std::string str);

  std::string removeNonLetters(std::string str);

  bool dictCheck(std::string str);

  bool comprehensive8Check(std::string str);
};

#endif /* __PASSCHECK_HPP__ */
