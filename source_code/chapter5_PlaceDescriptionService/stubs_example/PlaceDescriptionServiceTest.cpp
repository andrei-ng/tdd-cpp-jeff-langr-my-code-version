/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "gmock/gmock.h"

#include "Http.h"
#include "PlaceDescriptionService.h"

using namespace testing;

class APlaceDescriptionService : public Test {
 public:
  static const std::string latitude;
  static const std::string longitude;
};

const std::string APlaceDescriptionService::latitude("38.005");
const std::string APlaceDescriptionService::longitude("-104.44");

class HttpStub : public Http {
 public:
  virtual ~HttpStub() {}
  void Initialize() override {}
  std::string Get(const std::string& url) const override {
    Verify(url);
    return R"({ "address": {
                "road":"Drury Ln",
                "city":"Fountain",
                "state":"CO",
                "country":"US" }})";
  }

  void Verify(const std::string& url) const {
    auto expected_args("lat=" + APlaceDescriptionService::latitude + "&lon=" + APlaceDescriptionService::longitude);

    ASSERT_THAT(url, EndsWith(expected_args));
  }
};

TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation) {
  HttpStub http_stub;
  PlaceDescriptionService place_descr_service{&http_stub};

  auto description = place_descr_service.LocationSummary(latitude, longitude);

  ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
