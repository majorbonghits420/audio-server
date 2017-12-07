#ifndef __SONG_HPP__
#define __SONG_HPP__

#include <string>

/**
 * Object that represents a Song in our system.
 * A Song contains the URL of the song, along with who submitted the song, and thier taste value
 */
class Song {

public:

  /**
   * Default constructor. Creates an object with 0 taste, a user of Rick Astley, with a URL to his #1 hit song
   */
  Song()
    : url("https://www.youtube.com/watch?v=dQw4w9WgXcQ"), // Defualt URL is a rick roll
      user("Rick Astley"),
      taste(0.0)
  {}

  /**
   * Creates a song with the given URL assiciated with the given user
   *
   * @param url the URL of the song
   * @param user The user who submitted the URL
   */
  Song(std::string url, std::string user)
    : url(url), user(user)
  {}

  /**
   * Returns the URL of the song
   */
  std::string getUrl(void) { return url; }

  /**
   * Returns the user assiciated with the song
   */
  std::string getUser(void) { return user; }

  /**
   * Returns the taste of the user associated with this song.
   * This taste may be a stale value, as it may not be the current value in the database and is only periodically updated
   *
   * @return taste of the associated user
   */
  int getTaste(void) { return taste; }

  /**
   * Sets the taste of the user associated with this song
   *
   * @param t The taste value of the user
   */
  void setTaste(int t) { taste = t; }

private:
  std::string url; /**< The submitted url */
  std::string user; /**< The username of person who submitted the url*/
  int taste; /**< Taste number for the user who submitted the song */
};

#endif /* __SONG_HPP__ */
