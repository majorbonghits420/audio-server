#ifndef __Q_HPP__
#define __Q_HPP__

#include "db.hpp"
#include "song.hpp"

#include <vector>

class Queue {
public:

  Queue();
  
  Queue(Db *database);

  void addSong(Song s);

  Song pop(void);

private:

  Db *db;
  void reorder(void);
  void updateTastes(void);
  std::vector<Song> songs;
};

#endif /* __Q_HPP___*/
