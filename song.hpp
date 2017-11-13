#include <string>

class Song {

  Song(std::string url, std::string user)
    : url(url), user(user)
  {}

  std::string getUrl(void) { return url; }

  std::string getUser(void) { return user; }

  int getTaste(void) { return taste; }

  void setTaste(int t) { taste = t; }
  
private:
  std::string url; /**< The submitted url */
  std::string user; /**< The username of person who submitted the url*/
  int taste; /**< Taste number for the user who submitted the song */
};
