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
#include "HttpFactory.h"
#include "PlaceDescriptionService.h"

using namespace testing;

class HttpStub : public Http {
 public:
  MOCK_METHOD0(Initialize, void());
  MOCK_CONST_METHOD1(Get, std::string(const std::string&));
};

class APlaceDescriptionService : public Test {
 public:
  void SetUp() override {
    http_factory = std::make_shared<HttpFactory>();
    place_description_service = std::make_shared<PlaceDescriptionService>(http_factory);
  }

  void TearDown() override {
    http_factory.reset();
    place_description_service.reset();
  }

  static const std::string latitude;
  static const std::string longitude;

  std::shared_ptr<HttpStub> http_stub;
  std::shared_ptr<HttpFactory> http_factory;
  std::shared_ptr<PlaceDescriptionService> place_description_service;
};

const std::string APlaceDescriptionService::latitude("38.005");
const std::string APlaceDescriptionService::longitude("-104.44");

class APlaceDescriptionService_WithHttpFactory : public APlaceDescriptionService {
 public:
  void SetUp() override {
    APlaceDescriptionService::SetUp();
    http_stub = std::make_shared<HttpStub>();
    http_factory->SetInstance(http_stub);
  }
};

TEST_F(APlaceDescriptionService_WithHttpFactory, MakesHttpRequestToObtainAddress) {
  InSequence force_expectation_order;

  std::string url_start("http://open.mapquestapi.com/nominatim/v1/reverse?key=");
  std::string url_end("&format=json&lat=" + APlaceDescriptionService::latitude + "&lon=" +
                      APlaceDescriptionService::longitude);

  auto expected_url = url_start + "KEY" + url_end;
  EXPECT_CALL(*http_stub, Initialize());
  EXPECT_CALL(*http_stub, Get(expected_url));

  auto description = place_description_service->LocationSummary(latitude, longitude);
}

class APlaceDescriptionService_WithNiceHttpMock : public APlaceDescriptionService {
 public:
  void SetUp() override {
    APlaceDescriptionService::SetUp();
    http_stub = std::make_shared<NiceMock<HttpStub>>();
    http_factory->SetInstance(http_stub);
  }
};

TEST_F(APlaceDescriptionService_WithNiceHttpMock, FormatsRetrievedAddressIntoSummaryDescription) {
  EXPECT_CALL(*http_stub, Get(_))
      .WillOnce(Return(R"({ "address": {"road":"Drury Ln",
                                        "city":"Fountain",
                                        "state":"CO",
                                        "country":"US" }})"));

  auto description = place_description_service->LocationSummary(latitude, longitude);

  //  Mock::VerifyAndClearExpectations(http_stub.Get()));
  ASSERT_THAT(description, Eq("Drury Ln, Fountain, CO, US"));
}
