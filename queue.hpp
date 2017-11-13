#include "db.hpp"
#include "song.hpp"

#include <vector>

class Queue {
public:
  
  Queue(Db *database);

  void addSong(Song s);

  Song pop(void);

private:

  Db *db;
  void reorder(void);
  void updateTastes(void);
  std::vector<Song> songs;
};
