#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "db.hpp"
#include "queue.hpp"
#include "song.hpp"

#include <stdlib.h>
#include <string>

class AudioServer {

public:

  AudioServer(std::string dbFilename);

  static void playVideo(std::string url);

  Song getCurrentSong(void) { return currentSong; }

  bool isPlaying(void);

  void playSong(Song s);

  void upvoteCurrentSong(void);

  void downvotCurrentSong(void);

  void playNext(void);

  void addSong(Song s) { q.addSong(s); }

  void addSong(std::string user, std::string url) { q.addSong(Song(url, user)); }

private:
  Db database;
  Queue q;
  Song currentSong;
};


#endif /* __SERVER_HPP__ */
