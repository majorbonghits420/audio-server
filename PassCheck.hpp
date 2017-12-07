#ifndef __PASSCHECK_HPP__
#define __PASSCHECK_HPP__

#include <string.h>
#include <string>
#include <iostream>
#include <cctype>
#include <fstream>

/**
 * Library used to check the strength of passwords and characteristics of strings
 */
namespace PassCheck {

  /**
   * Checks if the password passes a basic16check.
   *
   * @param str string of password to check
   * @return true if the password passes the check, false otherwise
   */
  bool basic16Check(std::string str);

  /**
   * Checks if the given string has a lowercase, uppercase, digit, and symbol character.
   *
   * @param str The string to check
   * @return True is the string has each type of character, false otherwise.
   */
  bool checkChars(std::string str);

  /**
   * Removes all nonaphabetic characters from the string
   *
   * @param str string to remove non letters from
   * @return the inputted string with non letters removed
   */
  std::string removeNonLetters(std::string str);

  /**
   * Checks if the string matches any words in our dictionary located at "words.txt"
   *
   * @param str string to compare to words in the dictionary
   * @return true if the string matches a word in the dictionary, false otherwise
   */
  bool dictCheck(std::string str);

  /**
   * Checks if the string passes a comprehensive8 check
   *
   * @param str the password to check
   * @return true if it passes the checkm, false otherwise
   */
  bool comprehensive8Check(std::string str);
};

#endif /* __PASSCHECK_HPP__ */
