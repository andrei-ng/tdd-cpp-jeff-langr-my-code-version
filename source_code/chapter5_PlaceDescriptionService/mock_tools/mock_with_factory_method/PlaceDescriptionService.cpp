/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "PlaceDescriptionService.h"
#include "CurlHttp.h"

std::string PlaceDescriptionService::LocationSummary(const std::string& latitude, const std::string& longitude) {
  auto requested_url = CreateRequestUrl(latitude, longitude);
  auto json_response = Get(requested_url);

  return LocationSummary(json_response);
}

std::string PlaceDescriptionService::LocationSummary(const std::string& json_response) const {
  AddressExtractor extractor;
  auto address = extractor.AddressFrom(json_response);
  return address.Summary();
}

std::string PlaceDescriptionService::CreateRequestUrl(const std::string& latitude, const std::string& longitude) const {
  std::string server{"http://open.mapquestapi.com/"};
  std::string service{"nominatim/v1/reverse?"};
  return server + service + KeyValuePair("key", "KEY") + "&" + KeyValuePair("format", "json") + "&" +
         KeyValuePair("lat", latitude) + "&" + KeyValuePair("lon", longitude);
}

std::string PlaceDescriptionService::Get(const std::string& request_url) const {
  std::shared_ptr<Http> http = GetHttpService();
  http->Initialize();
  return http->Get(request_url);
}

std::string PlaceDescriptionService::KeyValuePair(const std::string& key, const std::string& value) const {
  return key + "=" + value;
}

std::shared_ptr<Http> PlaceDescriptionService::GetHttpService() const { return std::make_shared<CurlHttp>(); }
