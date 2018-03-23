/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "CurlHttp.h"

#include <string>

using namespace std;

string CurlHttp::response_;

CurlHttp::CurlHttp() : curl(NULL) {}

CurlHttp::~CurlHttp() { curl_global_cleanup(); }

void CurlHttp::Initialize() {
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &CurlHttp::WriteCallback);
}

string CurlHttp::Get(const string& url) const {
  response_ = "invalid request";  // TODO test
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  return CurlHttp::Response();
}

string CurlHttp::Response() { return response_; }

size_t CurlHttp::WriteCallback(const char* buf, size_t size, size_t n_memb, void*) {
  for (auto i = 0u; i < size * n_memb; i++) response_.push_back(buf[i]);
  return size * n_memb;
}
