/**
 * This file simply creates an instance of our server and runs.
 * It also does processing on any command line arguments
 */

#include <iostream>
#include "server.hpp"
#include "db.hpp"

int main(int argc, char **argv) {
  std::cout << "test" << std::endl;
  Db db("test.db");
  db.addUser("james", "password");
  db.addUser("brendjuan", "isuck");
  db.updateTaste("brendjuan", false);
  db.updateTaste("brendjuan", false);
  db.updateTaste("brendjuan", false);
  db.updateTaste("brendjuan", false);
  db.updateTaste("james", true);
  db.updateTaste("james", true);
  db.updateTaste("james", true);
  db.updateTaste("james", true);

  AudioServer server(&db);

  server.addSong("brendjuan","https://www.youtube.com/watch?v=JPVIgshtOag");
  server.addSong("brendjuan","https://www.youtube.com/watch?v=HHrMkAsGFlE");
  server.addSong("james", "https://www.youtube.com/watch?v=NT783hZIUXY");
  server.addSong("james", "https://www.youtube.com/watch?v=ZjajvMxji84");

  server.run();
}
