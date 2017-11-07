/**
 * James Cassell (jcc384) jcc384@cornell.edu
 * Creation date: 06/11/17
 * Description: This class is meant to be the application class for the web application.
 */

#include "server.hpp"

void AudioServer::playVideo(std::string url) {
  system(("cvlc -Vdummy " + url).c_str());
}

void AudioServer::routePath(const std::string &internalPath) {
  if (internalPath == "/vote") {
    // Display voting options
  } else if (internalPath == "/user") {
    // Display logged in user information
  } else if (internalPath == "/login") {
    // Take user to login page
  } else if (internalPath == "/submit") {
    // Take user to lin submission page
  } else {
    // If all else fails, take to login page
  }
}
