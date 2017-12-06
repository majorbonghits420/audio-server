#include "queue.hpp"

Queue::Queue()
  : db(nullptr)
{
  songs = std::vector<Song>();
}

Queue::Queue(Db *database)
  : db(database) {
  songs = std::vector<Song>();
}

void Queue::addSong(Song s) {
  songs.insert(songs.end(), s);
  reorder();
}

Song Queue::pop(void) {
  Song toReturn =  songs.back();
  songs.pop_back();
  return toReturn;
}

void Queue::updateTastes(void) {
  for (Song s : songs) {
    int currentTaste = db->getTaste(s.getUser());
    s.setTaste(currentTaste);
  }
}

void Queue::reorder(void) {
    updateTastes();
    std::sort(songs.begin(), songs.end(),
              [](Song a, Song b) -> bool {
                  return (a.getTaste() > b.getTaste());
              });
}
