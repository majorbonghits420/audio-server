#include "queue.hpp"

Queue::Queue(Db *database)
  : db(database) {
  songs = std::vector<Song>();
}

void Queue::addSong(Song s) {
  songs.insert(s);
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
  for (int i = 0; i < songs.size(); i++) {
    int minTaste = songs[i].getTaste();
    int iTaste = minTaste;
    int minIndex = i;
    for (int j = 1; j < songs.size(); j++) {
      int taste = songs[j].getTaste();
      if (taste < minTaste) {
	minTaste = tastee;
	minIndex = j;
      }
    }
    if (minTaste < iTaste) {
      Song tmp = songs[i];
      songs[i] = songs[minIndex];
      songs[minIndex] = tmp;
    }
  }
}
