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

#include <memory>
#include <string>

#include "Address.h"
#include "AddressExtractor.h"
#include "Http.h"

template <typename HTTP>
class PlaceDescriptionServiceTemplate {
 public:
  HTTP& GetHttpInUse() { return http_; }  // mocks in tests need the reference
  std::string LocationSummary(const std::string& latitude, const std::string& longitude) {
    auto requested_url = CreateRequestUrl(latitude, longitude);
    auto json_response = Get(requested_url);

    return LocationSummary(json_response);
  }

 private:
  std::string CreateRequestUrl(const std::string& latitude, const std::string& longitude) const {
    std::string server{"http://open.mapquestapi.com/"};
    std::string service{"nominatim/v1/reverse?"};
    return server + service + KeyValuePair("key", "KEY") + "&" + KeyValuePair("format", "json") + "&" +
           KeyValuePair("lat", latitude) + "&" + KeyValuePair("lon", longitude);
  }

  std::string LocationSummary(const std::string& json_response) const {
    AddressExtractor extractor;
    auto address = extractor.AddressFrom(json_response);
    return address.Summary();
  }
  std::string KeyValuePair(const std::string& key, const std::string& value) const { return key + "=" + value; }

  std::string Get(const std::string& request_url) {
    http_.Initialize();
    return http_.Get(request_url);
  }
  HTTP http_;
};

class Http;
typedef PlaceDescriptionServiceTemplate<Http> PlaceDescriptionService;

#endif  // TDD_CH5_PLACE_DESCRIPTION_SERVICE_H_
