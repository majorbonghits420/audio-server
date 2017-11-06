/**
 * James Cassell (jcc384) jcc384@cornell.edu
 * Creation date: 06/11/17
 * Description: This class is meant to be the application class for the web application.
 */

#include <stdlib.h>
#include <string>
#include <Wt/WApplication>

class AudioServer : public Wt::WApplication {

public:
  AudioServer(const Wt::WEnvironment &env);

  static void playVideo(std::string url);
};

void AudioServer::playVideo(std::string url) {
  system(("cvlc -Vdummy " + url).c_str());
}

int main(int argc, char **argv) {}
