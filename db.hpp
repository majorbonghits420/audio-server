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
   * Returns the return code of the SQL query.
   */
  int addUser(std::string username, std::string password);

  bool authUser(std::string username, std::string password);

  int updateTaste(std::string username, int taste);

  void closeDatabase(void);

private:
  const int MAX_STATEMENT_SIZE = 500;
  sqlite3* database;
  std::mt19937 rng;
  void createDb(std::string filename);
  std::string computeHash(std::string toHash);

  // Values that auth callback function sets
};

#endif /* __DB_HPP__ */
