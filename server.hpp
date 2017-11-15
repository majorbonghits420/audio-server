#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "db.hpp"
#include "queue.hpp"
#include "song.hpp"

#include <stdlib.h>
#include <string>
#include <fstream>
#include <thread>

class AudioServer {

public:

  AudioServer(Db *db);

  static void playVideo(std::string url);

  Song getCurrentSong(void) { return currentSong; }

  bool isPlaying(void);

  void playSong(Song s);

  void upvoteCurrentSong(void);

  void downvoteCurrentSong(void);

  void playNext(void);

  void addSong(Song s) { q.addSong(s); }

  void addSong(std::string user, std::string url) { q.addSong(Song(url, user)); }

  /**
   * This starts the server up and does not return until there is nothing in the
   * song queue. It asssumes that a number of songs has already been added to the
   * queue.
   */
  void run(void);

  /**
   * This starts the server which then runs until told to stop. Commands for adding songs, voting,
   * and quiting are sent via the fifo, which its name is passed as an argument to this function.
   *
   */
  void run(std::string fname);

private:
  Db *database;
  Queue q;
  Song currentSong;

  static void runForever(AudioServer *server);
};


#endif /* __SERVER_HPP__ */
