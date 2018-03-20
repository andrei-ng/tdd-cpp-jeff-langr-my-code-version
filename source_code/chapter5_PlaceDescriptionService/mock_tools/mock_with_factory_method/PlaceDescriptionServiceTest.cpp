/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include <memory>

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

class PlaceDescriptionService_StubHttpService : public PlaceDescriptionService {
 public:
  PlaceDescriptionService_StubHttpService(std::shared_ptr<HttpStub> http_stub) : http_stub_{http_stub} {}
  std::shared_ptr<Http> GetHttpService() const override { return http_stub_; }
  std::shared_ptr<Http> http_stub_;
};

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
  InSequence force_expectation_order;
  std::shared_ptr<HttpStub> http_stub{new HttpStub};

  std::string url_start("http://open.mapquestapi.com/nominatim/v1/reverse?key=");
  std::string url_end("&format=json&lat=" + APlaceDescriptionService::latitude + "&lon=" +
                      APlaceDescriptionService::longitude);

  auto expected_url = url_start + "KEY" + url_end;
  EXPECT_CALL(*http_stub, Initialize());
  EXPECT_CALL(*http_stub, Get(expected_url));

  PlaceDescriptionService_StubHttpService place_descr_service{http_stub};
  auto description = place_descr_service.LocationSummary(latitude, longitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription) {
  std::shared_ptr<HttpStub> http_stub{new NiceMock<HttpStub>};
  //  std::shared_ptr<HttpStub> http_stub{new StrictMock<HttpStub>};
  //  std::shared_ptr<HttpStub> http_stub{new HttpStub};

  EXPECT_CALL(*http_stub, Get(_))
      .WillOnce(Return(R"({ "address": {"road":"Drury Ln",
                                        "city":"Fountain",
                                        "state":"CO",
                                        "country":"US" }})"));

  PlaceDescriptionService_StubHttpService place_descr_service{http_stub};
  auto description = place_descr_service.LocationSummary(latitude, longitude);

  ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
