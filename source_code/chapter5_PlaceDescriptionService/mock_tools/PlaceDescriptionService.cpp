/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "PlaceDescriptionService.h"

#include "AddressExtractor.h"

std::string PlaceDescriptionService::LocationSummary(const std::string& latitude, const std::string& longitude) {
  std::string server{"http://open.mapquestapi.com/"};
  std::string service{"nominatim/v1/reverse?"};
  std::string url_request = server + service + KeyValuePair("key", "KEY") + "&" + KeyValuePair("format", "json") + "&" +
                            KeyValuePair("lat", latitude) + "&" + KeyValuePair("lon", longitude);

  http_->Get(url_request);
  return "";
}

std::string PlaceDescriptionService::KeyValuePair(const std::string& key, const std::string& value) const {
  return key + "=" + value;
}
