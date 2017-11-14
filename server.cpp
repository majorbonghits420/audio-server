/**
 * James Cassell (jcc384) jcc384@cornell.edu
 * Creation date: 06/11/17
 * Description: This class is meant to be the application class for the web application.
 */

#include "server.hpp"

AudioServer::AudioServer(Db *db)
  : database(db)
{
  q = Queue(database);
}

void AudioServer::playVideo(std::string url) {
  system(("cvlc -Vdummy " + url + " --play-and-exit &").c_str());
}

bool AudioServer::isPlaying(void) {
  std:: string cmd("ps -u pi");
  std::string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return (data.find("vlc") != std::string::npos);
}

void AudioServer::playSong(Song s) {
  playVideo(s.getUrl());
}

void AudioServer::upvoteCurrentSong(void) {
  database->updateTaste(currentSong.getUser(), true);
}

void AudioServer::downvoteCurrentSong(void) {
  database->updateTaste(currentSong.getUser(), false);
}

void AudioServer::playNext(void) {
  Song next = q.pop();
  currentSong = next;
  playSong(next);
}

void AudioServer::run(void) {
  while (!q.isEmpty()) {
    if (!isPlaying()) {
      playNext();
    }
  }
}
