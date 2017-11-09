#include "db.hpp"

Db::Db(std::string filename)
  : rng(std::chrono::system_clock::now().time_since_epoch().count()){
  int rc;

  // Open the database
  rc = sqlite3_open_v2(filename.c_str(),
		       &database,
		       SQLITE_OPEN_READWRITE,
		       nullptr
		       );

  // If our database has not been created, we initialize it
  if (rc != 0) {
    createDb(filename);
  }
}

void Db::closeDatabase(void) {
  sqlite3_close(database);
}

void Db::createDb(std::string filename) {
  int rc;
  std::cerr << "Database with name " << filename  << " not found, creating database " << std::endl;
  // Create the database
  rc = sqlite3_open_v2(filename.c_str(),
		       &database,
		       SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
		       nullptr
		       );
  // Create our table for users (this databse only uses one table since info is simple)
  if (rc != 0) {
    std::cerr << "Unable to create database" << std::endl;
    return;
  }
  std::string sql =
    "CREATE TABLE users(uname TEXT PRIMARY KEY UNIQUE," 
    "salt INT," 
    "hash TEXT," 
    "taste INT" 
    "); ";
  // Exceute above sql statement
  char *errMsg = 0;
  rc = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL Error: %s\n", errMsg);
  } else {
    std::cerr << "Successfully created new database and table" << std::endl;
  }
}

int Db::addUser(std::string username, std::string pass) {
  // Setup values to insert
  int taste = 0;
  int salt = rng();
  // Generate hash of salt + password
  CryptoPP::SHA256 hash;
  byte digest[CryptoPP::SHA256::DIGESTSIZE];
  std::string toHash = std::to_string(salt) + pass;
  hash.CalculateDigest(digest, (byte*) toHash.c_str(), toHash.length());

  // Convert to Hex string that we can enter as text into db
  CryptoPP::HexEncoder encoder;
  std::string hashedPass;
  encoder.Attach(new CryptoPP::StringSink(hashedPass));
  encoder.Put(digest, sizeof(digest));
  encoder.MessageEnd();

  // Build query
  std::string query = "INSERT INTO users (uname, salt, hash, taste) VALUES"
    "('" + username + "', " + std::to_string(salt) + ",'" + hashedPass + "'," +
    std::to_string(taste) + ");";
  int rc = sqlite3_exec(database, query.c_str(), nullptr, nullptr, nullptr);
  return rc;  
}
