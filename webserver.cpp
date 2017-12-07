#include "webserver.hpp"

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
Webserver::Webserver(const Wt::WEnvironment& env)
  : Wt::WApplication(env), pipeline(FIFO_NAME), db(new Db(DB_NAME))
{
  setTitle("Audio Server");                               // application title

  root()->addWidget(new Wt::WText("Username: "));  // show some text
  username = new Wt::WLineEdit(root());                     // allow text input
  username->setFocus();                                 // give focus

  //  root()->addWidget(new Wt::WBreak());

  root()->addWidget(new Wt::WText("Password: "));
  password = new Wt::WLineEdit(root());
  password->setEchoMode(Wt::WLineEdit::EchoMode::Password);
  password->setFocus();

  Wt::WPushButton *registerButton = new Wt::WPushButton("Register user", root());
  registerButton->setMargin(5, Wt::Left);

  root()->addWidget(new Wt::WBreak());

  root()->addWidget(new Wt::WText("URL: "));
  url = new Wt::WLineEdit(root());
  url->setFocus();

  root()->addWidget(new Wt::WBreak());

  Wt::WPushButton *linkButton
    = new Wt::WPushButton("Submit link", root());              // create a button
  linkButton->setMargin(5, Wt::Left);                            // add 5 pixels margin

  root()->addWidget(new Wt::WBreak());                       // insert a line break

  root()->addWidget(new Wt::WText("Upvote or downvote current song (login credentials needed): "));

  root()->addWidget(new Wt::WBreak());                       // insert a line break

  Wt::WPushButton *upvote = new Wt::WPushButton("Upvote", root());
  upvote->setMargin(5, Wt::Left);

  Wt::WPushButton *downvote = new Wt::WPushButton("Downvote", root());
  downvote->setMargin(5, Wt::Left);

  response = new Wt::WText(root());                         // empty text

  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  linkButton->clicked().connect(this, &Webserver::submitSong);

  upvote->clicked().connect(this, &Webserver::upvoteSong);

  downvote->clicked().connect(this, &Webserver::downvoteSong);

  registerButton->clicked().connect(this, &Webserver::createNewUser);
}

void Webserver::upvoteSong() {
  std::string uname = username->text().toUTF8();
  std::string pass = password->text().toUTF8();
  password->setText(Wt::WString());
  bool authed = authUser(uname, pass);
  if (authed) {
    // Write "upvote" to our fifo
    pipeline << "upvote" << std::endl;
    response->setText("Current song upvoted");
  }
}

void Webserver::downvoteSong() {
  std::string uname = username->text().toUTF8();
  std::string pass = password->text().toUTF8();
  password->setText(Wt::WString());
  bool authed = authUser(uname, pass);
  if (authed) {
    pipeline << "downvote" << std::endl;
    response->setText("Current song downvoted");
  }
}

void Webserver::submitSong() {
  std::string uname = username->text().toUTF8();
  std::string pass = password->text().toUTF8();
  std::string link = url->text().toUTF8();
  password->setText(Wt::WString());
  bool authed = authUser(uname, pass);
  if (authed) {
    // Write username and linke to our fifo
    pipeline << uname << ";" << link << std::endl;
    response->setText("Song submitted");
  }
}

bool Webserver::authUser(std::string username, std::string pass) {
  if (db->authUser(username, pass) == false) {
    response->setText("Username or Password incorrect, have you registered your username yet?");
    return false;
  }
  return true;
}

void Webserver::createNewUser(void) {
  std::string uname = username->text().toUTF8();
  std::string pass = password->text().toUTF8();
  password->setText(Wt::WString());
  createUser(uname, pass);
}

void Webserver::createUser(std::string username, std::string pass) {
  // Check if their password is acceptable
  bool strongPass = PassCheck::basic16Check(pass) || PassCheck::comprehensive8Check(pass);
  if (!strongPass) {
    response->setText("Password not strong enough, try new password");
    return;
  }
  int rc = db->addUser(username, pass);
  if (rc != SQLITE_OK) {
    response->setText("Username taken, try a new one");
  } else {
    response->setText("Successfully created user");
  }
  return;
}
