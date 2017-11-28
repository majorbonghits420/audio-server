#ifndef __WEBSERVER_HPP__
#define __WEBSERVER_HPP__

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <iostream>
#include <string>
#include <fstream>
#include <sqlite3.h>
#include <thread>

#include "db.hpp"
#include "PassCheck.hpp"
#include "Globals.hpp"

class Webserver : public Wt::WApplication {

public:
  //  Webserver(Db *databse, std::string fifo, const Wt::WEnvironment &env);
  Webserver(const Wt::WEnvironment& env);

private:
  Wt::WLineEdit *username;
  Wt::WLineEdit *password;
  Wt::WLineEdit *url;
  Wt::WText *response;

  std::ofstream pipeline;

  Db *db;

  void greet();

  void upvoteSong();

  void downvoteSong();

  void submitSong();

  void createNewUser(void);

  bool authUser(std::string username, std::string pass);

  void createUser(std::string username, std::string pass);
};

#endif /* __WEBSERVER_HPP__ */
