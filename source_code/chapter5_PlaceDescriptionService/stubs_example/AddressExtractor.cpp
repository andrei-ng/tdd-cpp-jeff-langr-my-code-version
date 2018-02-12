/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#include "AddressExtractor.h"

#include <string>

Address AddressExtractor::AddressFrom(const  std::string& json) const {
  Address address;
  Json::Value json_address{JsonAddressFrom(json)};
  Populate(address, json_address);
  return address;
}

Json::Value AddressExtractor::JsonAddressFrom(const  std::string& json) const {
  auto location_data = Parse(json);
  return location_data.get("address", Value::null);
}

void AddressExtractor::Populate(Address& address, Value& json_address) const {
  address.road = GetString(json_address, "road");
  address.city = GetString(json_address, "city");
  address.state = GetString(json_address, "state");
  address.country = GetString(json_address, "country");
}

Json::Value AddressExtractor::Parse(const  std::string& json) const {
  Value root;
  /** Reader is deprecated, but did not find a quick example of how to use CharReader*/
  Json::Reader reader;
  reader.parse(json, root);
  return root;
}

std::string AddressExtractor::GetString(Value& result, const  std::string& name) const { return result.get(name, "").asString(); }
