/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#include "WavReader.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  cout << "argc = " << argc << endl;
  if (argc != 3) {
    cout << "USAGE:" << endl << "\tSnippetPublisher [sourceDir] [destDir]" << endl;
    return 1;
  }

  auto source = argv[1];
  auto dest = argv[2];

  WavReader reader(source, dest);
  reader.PublishSnippets();
}
