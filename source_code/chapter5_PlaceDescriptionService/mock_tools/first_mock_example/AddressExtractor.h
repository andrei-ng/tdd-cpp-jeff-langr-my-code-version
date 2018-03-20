/***
 * Excerpted from "Modern C++ Programming with Test-Driven Development",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material,
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose.
 * Visit http://www.pragmaticprogrammer.com/titles/lotdd for more book information.
***/

#ifndef TDD_CH5_ADDRESS_EXTRACTOR_H_
#define TDD_CH5_ADDRESS_EXTRACTOR_H_

#include <string>

#include <json/reader.h>
#include <json/value.h>

#include "Address.h"

class AddressExtractor {
 public:
  using Value = Json::Value;
  Address AddressFrom(const std::string& json) const;

 private:
  Json::Value JsonAddressFrom(const std::string& json) const;
  void Populate(Address& address, Value& jsonAddress) const;
  Json::Value Parse(const std::string& json) const;
  std::string GetString(Value& result, const std::string& name) const;
};

#endif
