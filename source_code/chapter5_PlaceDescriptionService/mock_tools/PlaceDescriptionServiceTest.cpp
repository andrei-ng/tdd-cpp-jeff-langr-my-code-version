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
  MOCK_METHOD0(Initialize, void());
  MOCK_CONST_METHOD1(Get, std::string(const std::string&));
};

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
  HttpStub http_stub;

  std::string url_start("http://open.mapquestapi.com/nominatim/v1/reverse?key=");
  std::string url_end("&format=json&lat=" + APlaceDescriptionService::latitude + "&lon=" +
                      APlaceDescriptionService::longitude);

  auto expected_url = url_start + "KEY" + url_end;

  EXPECT_CALL(http_stub, Get(expected_url));

  PlaceDescriptionService place_descr_service{&http_stub};
  auto description = place_descr_service.LocationSummary(latitude, longitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
  HttpStub http_stub;

  EXPECT_CALL(http_stub, Get(_))
      .WillOnce(Return(R"({ "address": {"road":"Drury Ln",
                                        "city":"Fountain",
                                        "state":"CO",
                                        "country":"US" }})"));

  PlaceDescriptionService place_descr_service{&http_stub};
  auto description = place_descr_service.LocationSummary(latitude, longitude);

  ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
