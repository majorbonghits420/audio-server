#ifndef __SONG_HPP__
#define __SONG_HPP__

#include <string>

class Song {

public:

  Song()
    : url("https://www.youtube.com/watch?v=dQw4w9WgXcQ"), // Defualt URL is a rick roll
      user("Rick Astley"),
      taste(0.0)
  {}

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

#endif /* __SONG_HPP__ */
