#ifndef __Q_HPP__
#define __Q_HPP__

#include "db.hpp"
#include "song.hpp"

#include <algorithm>
#include <vector>

/**
 * A priority queue that contains Song objects sorted by user tastes found in a database.
 */
class Queue {
public:

  /**
   * Creates a Queue object with an empty queue and no database reference.
   * This object will not be able to function as it does not have a Db to get taste values from
   */
  Queue();

  /**
   * Creates a Queue object that weights Songs based on taste values from a database
   *
   * @param databae Pointer to a Db object
   */
  Queue(Db *database);

  /**
   * Adds a Song into the queue
   *
   * @param s Song to add
   */
  void addSong(Song s);

  /**
   * Gets the Song at the front of the queue
   *
   * @return Song at the front of the queue
   */
  Song pop(void);

  /**
   * Checks if the queue is empty
   *
   * @return true if empty, else otherwise
   */
  bool isEmpty(void) { return songs.empty(); }

private:

  Db *db; /**< Pointer to Db object used for taste values */

  /**
   * Reorders all of the Songs in queue based on the tastes of the associated users
   */
  void reorder(void);

  /**
   * Updates the associated taste of each Song in the queue with values in the database
   */
  void updateTastes(void);
  std::vector<Song> songs; /**< Our queue of songs */
};

#endif /* __Q_HPP___*/
