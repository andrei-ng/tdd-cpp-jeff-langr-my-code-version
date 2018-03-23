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

class APlaceDescriptionService_WithHttpTemplateMock : public APlaceDescriptionService {
 public:
  PlaceDescriptionServiceTemplate<HttpStub> place_description_service;
};

TEST_F(APlaceDescriptionService_WithHttpTemplateMock, MakesHttpRequestToObtainAddress) {
  InSequence force_expectation_order;
  HttpStub http_stub;

  std::string url_start("http://open.mapquestapi.com/nominatim/v1/reverse?key=");
  std::string url_end("&format=json&lat=" + APlaceDescriptionService::latitude + "&lon=" +
                      APlaceDescriptionService::longitude);

  auto expected_url = url_start + "KEY" + url_end;
  EXPECT_CALL(place_description_service.GetHttpInUse(), Initialize());
  EXPECT_CALL(place_description_service.GetHttpInUse(), Get(expected_url));

  auto description = place_description_service.LocationSummary(latitude, longitude);
}

class APlaceDescriptionService_WithNiceHttpMock : public APlaceDescriptionService {
 public:
  PlaceDescriptionServiceTemplate<NiceMock<HttpStub>> place_description_service;
};

TEST_F(APlaceDescriptionService_WithNiceHttpMock, FormatsRetrievedAddressIntoSummaryDescription) {
  //  HttpStub http_stub;
  NiceMock<HttpStub> http_stub;
  //  StrictMock<HttpStub> http_stub;

  EXPECT_CALL(place_description_service.GetHttpInUse(), Get(_))
      .WillOnce(Return(R"({ "address": {"road":"Drury Ln",
                                        "city":"Fountain",
                                        "state":"CO",
                                        "country":"US" }})"));

  auto description = place_description_service.LocationSummary(latitude, longitude);

  ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
