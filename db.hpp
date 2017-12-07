#ifndef __DB_HPP__
#define __DB_HPP__

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <chrono>
#include <random>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

/**
 * Db class is for all sqlite3 database interactions
 */
class Db {

public:

  Db(std::string filename);

  /**
   * Attempts to add a username with the given password to the database.
   * @param username username of the new user
   * @param password the password of the new user
   *
   * @return the return code of the SQL query.
   */
  int addUser(std::string username, std::string password);

  /**
   * Authenticates a user based on their username and password
   * @param username of the user to authernticate
   * @param password password of the given user
   *
   * @return true if the user is authenticated, false otherwise
   */
  bool authUser(std::string username, std::string password);

  /**
   * Updates the taste for the given user depending on a given vote
   *
   * @param username - username of taste to update
   * @param vote - true for an upvote, false for a downvote
   *
   * @return int - the return code of the database query
   */
  int updateTaste(std::string username, bool vote);

  /**
   * Gets the taste of a given user from the database
   *
   * @param uname username of the user
   * @return taste of the user
   */
  int getTaste(std::string uname);

  /**
   * Closes the sqlite3 database object
   */
  void closeDatabase(void);

private:
  const int MAX_STATEMENT_SIZE = 500; /**< Max size that statements issued to the database should be */
  sqlite3* database; /**< Pointer to the sqlite3 database we are interacting with */
  std::mt19937 rng; /**< The rng we use to generate salts */

  /**
   * Creates a sqlite3 database with the given filename
   * @param filename string for the file location to make the database
   */
  void createDb(std::string filename);

  /**
   * Computes the SHA256 hash of a given string
   *
   * @param toHash the string to hash
   * @return the SHA256 hash of the inputted string
   */
  std::string computeHash(std::string toHash);
};

#endif /* __DB_HPP__ */
