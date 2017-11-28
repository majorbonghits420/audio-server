/**
 * This file simply creates an instance of our server and runs.
 * It also does processing on any command line arguments
 */

#include "Globals.hpp"
#include "server.hpp"
#include "webserver.hpp"

void runServer(AudioServer *server) {
  server->run(FIFO_NAME);
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new Webserver(env);
}

int main(int argc, char **argv)
{
  Db db(DB_NAME);
  AudioServer server(&db);
  std::cout << "server created" << std::endl;
  std::thread serverThread(runServer, &server);
  std::cout << "Started server thread" << std::endl;

  /*
   * Your main method may set up some shared resources, but should then
   * start the server application (FastCGI or httpd) that starts listening
   * for requests, and handles all of the application life cycles.
   *
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */
  return Wt::WRun(argc, argv, &createApplication);
}
