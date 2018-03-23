/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/
#include "AddressExtractor.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "gmock/gmock.h"

using namespace testing;

class AnAddressExtractor : public Test {
 public:
  AddressExtractor addr_extractor;
};

/** Renamed IsEmpty from book example to IsEmptyJson, as the former is reserved by GoogleTest Framework */
MATCHER(IsEmptyJson, "") { return arg.road.empty() && arg.city.empty() && arg.state.empty() && arg.country.empty(); }

MATCHER(IsNotEmptyJson, "") {
  return !arg.road.empty() && !arg.city.empty() && !arg.state.empty() && !arg.country.empty();
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressOnAFailedParse) {
  auto address = addr_extractor.AddressFrom("not a valid json input");

  ASSERT_THAT(address, IsEmptyJson());
}

TEST_F(AnAddressExtractor, ReturnsAnEmptyAddressWhenNoAddressFound) {
  auto json = R"({ "place_id":"15331615" })";
  auto address = addr_extractor.AddressFrom(json);

  ASSERT_THAT(address, IsEmptyJson());
}

TEST_F(AnAddressExtractor, ReturnsPopulatedAddressForValidJsonResult) {
  auto json = R"({
         "place_id":"15331615",
         "address":{
         "road":"War Eagle Court",
         "city":"Colorado Springs",
         "state":"Colorado",
         "country":"United States of America",
         }
      })";

  auto address = addr_extractor.AddressFrom(json);

  ASSERT_THAT(address.road, Eq("War Eagle Court"));
  ASSERT_THAT(address.city, Eq("Colorado Springs"));
  ASSERT_THAT(address.state, Eq("Colorado"));
  ASSERT_THAT(address.country, Eq("United States of America"));
}

TEST_F(AnAddressExtractor, DefaultsNonexistentFieldsToEmpty) {
  auto json = R"({
         "address":{
         "road":"War Eagle Court",
         "city":"Colorado Springs",
         "country":"United States of America" }})";

  auto address = addr_extractor.AddressFrom(json);

  ASSERT_THAT(address.state, Eq(""));
}
