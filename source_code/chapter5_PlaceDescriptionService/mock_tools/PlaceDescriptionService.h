/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#ifndef TDD_CH5_PLACE_DESCRIPTION_SERVICE_H_
#define TDD_CH5_PLACE_DESCRIPTION_SERVICE_H_

#include <string>
#include "Address.h"
#include "Http.h"

class Http;

class PlaceDescriptionService {
 public:
  PlaceDescriptionService(Http* http) : http_(http) {}

  std::string LocationSummary(const std::string& latitude, const std::string& longitude);

 private:
  std::string CreateRequestUrl(const std::string& latitude, const std::string& longitude) const;
  std::string LocationSummary(const Address& address) const;
  std::string LocationSummary(const std::string json_response) const;
  std::string KeyValuePair(const std::string& key, const std::string& value) const;
  std::string Get(const std::string& requestUrl) const;

  Http* http_;
};

#endif  // TDD_CH5_PLACE_DESCRIPTION_SERVICE_H_
