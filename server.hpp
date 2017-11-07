#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <stdlib.h>
#include <string>
#include <Wt/WApplication>

class AudioServer : public Wt::WApplication {

public:
  AudioServer(const Wt::WEnvironment &env);

  void routePath(const std::string &interalPath);

  static void playVideo(std::string url);
};


#endif /* __SERVER_HPP__ */
