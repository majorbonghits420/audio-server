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

/**
 * Webserver that serves as the user interface
 */
class Webserver : public Wt::WApplication {

public:

  /**
   * Standard constructor interface for a Wt::WApplication
   */
  Webserver(const Wt::WEnvironment& env);

private:
  Wt::WLineEdit *username; /**< Field for username */
  Wt::WLineEdit *password; /**< Field for user's password */
  Wt::WLineEdit *url; /**< Field where user's enter a URL */
  Wt::WText *response; /**< Area for text response after user actions */

  std::ofstream pipeline; /**< FIFO we use to send commands to AudioServer */

  Db *db; /**< Database used for user registration and authentication */

  /**
   * Upvotes the current song with successful user auth
   */
  void upvoteSong();

  /**
   * Downvotes the current song with successful user auth
   */
  void downvoteSong();

  /**
   * Submits song with successful user auth
   */
  void submitSong();

  /**
   * Creates a new user if their password is strong enough
   */
  void createNewUser(void);

  /**
   * Authenticates the user is a valid user in the database
   * @param username username of user
   * @param pass password of the user
   *
   * @return true if user is authenticated, false otherwise
   */
  bool authUser(std::string username, std::string pass);

  /**
   * Creates a user in the database. Indicates to the user if the username is taken or if their
   * password is too weak
   *
   * @param username requested username to add
   * @param pass proposed password of the user
   */
  void createUser(std::string username, std::string pass);
};

#endif /* __WEBSERVER_HPP__ */
