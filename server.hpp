#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "db.hpp"
#include "queue.hpp"
#include "song.hpp"

#include <stdlib.h>
#include <string>
#include <fstream>
#include <thread>

/**
 * Class used play songs from a sorted queue and take commmands over FIFO
 */
class AudioServer {

public:

  /**
   * Creates an audioserver with a database used to get/modify data for songs
   *
   * @param db reference to a Db object for modifying/querying tastes
   */
  AudioServer(Db *db);

  /**
   *
   *
   * @param url the URL to stream audio from
   */
  static void playVideo(std::string url);

  /**
   * Returns a copy of the Song object currently playing
   */
  Song getCurrentSong(void) { return currentSong; }

  /**
   * Checks if there is an instance of VLC playing a song
   *
   * @return true if there is a song playing, false otherwise
   */
  bool isPlaying(void);

  /**
   * Plays the URL contained in the given Song
   *
   * @param s Song to play audio from
   */
  void playSong(Song s);

  /**
   * Increments the taste value of the user who submitted the current song in the database
   */
  void upvoteCurrentSong(void);

  /**
   * Decrements the taste value of the user who submitted the current song in the database
   */
  void downvoteCurrentSong(void);

  /**
   * Plays the audio of the next Song in the queue
   */
  void playNext(void);

  /**
   * Adds a Song to the queue of songs to play
   *
   * @param s The Song to add
   */
  void addSong(Song s) { q.addSong(s); }

  /**
   * Creates and adds a Song to the queue
   *
   * @param user The person who submitted the song
   * @param url The URL of the song
   */
  void addSong(std::string user, std::string url);

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
   * @param fname the name of the FIFO to read commands from
   */
  void run(std::string fname);

private:
  Db *database; /**< Database used to update user information */
  Queue q; /**< The Queue of our Songs to be played*/
  Song currentSong; /**< The Song currently playing */

  /**
   * Takes a server and makes it so the server is always trying to play songs from the song queue
   *
   * @param server that will constantly be trying to play songs from its queue
   */
  static void runForever(AudioServer *server);
};


#endif /* __SERVER_HPP__ */
