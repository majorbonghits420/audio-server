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

void AudioServer::addSong(std::string user, std::string url) {
    Song toAdd(url, user);
    toAdd.setTaste(database->getTaste(user));
    addSong(toAdd);
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
  if (!q.isEmpty()) {
    Song next = q.pop();
    currentSong = next;
    playSong(next);
  }
}

void AudioServer::run(void) {
  while (!q.isEmpty()) {
    if (!isPlaying()) {
      playNext();
    }
  }
}

void AudioServer::runForever(AudioServer *server) {
  while (true) {
    server->run();
  }
}
void AudioServer::run(std::string fname) {
  // start a thread to always be trying to pull stuff off of the queue
  std::thread playSongs(runForever, this);
  std::ifstream pipeline(fname);
  // We make this to ensure that the fifo is always open so that we can read from it
  std::ofstream hold(fname); // unused on purpose
  std::string line;
  do {
    // Check for any commands from the FIFO
    std::getline(pipeline, line);
    // Check if our line is a song submission
    std::size_t pos = line.find(";");
    if (pos != std::string::npos) {
      std::string user = line.substr(0, pos);
      std::string url = line.substr(pos + 1);
      Song newSong(url, user);
      addSong(newSong);
      // Upvote of the current song
    } else if (line.compare("upvote") == 0) {
      upvoteCurrentSong();
      // Downvote of the current song
    } else if (line.compare("downvote") == 0) {
      downvoteCurrentSong();
    }
  } while (!pipeline.fail());
}
