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
#include "HttpFactory.h"

class PlaceDescriptionService {
 public:
  PlaceDescriptionService(std::shared_ptr<HttpFactory> http_factory);
  virtual ~PlaceDescriptionService() {}

  std::string LocationSummary(const std::string& latitude, const std::string& longitude);

 private:
  std::string CreateRequestUrl(const std::string& latitude, const std::string& longitude) const;
  std::string LocationSummary(const std::string& json_response) const;
  std::string KeyValuePair(const std::string& key, const std::string& value) const;
  std::string Get(const std::string& request_url) const;

  std::shared_ptr<HttpFactory> http_factory_;
};

#endif  // TDD_CH5_PLACE_DESCRIPTION_SERVICE_H_
