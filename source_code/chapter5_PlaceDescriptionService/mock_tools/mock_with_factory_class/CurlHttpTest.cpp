#include <string>

#include "gmock/gmock.h"

#include "CurlHttp.h"

using namespace ::testing;
using namespace std;

TEST(CurlHttp, WriteCallback) {
  string buffer("123456789012");
  size_t size(12);
  size_t number_of_members(1);
  CurlHttp::WriteCallback("123456789012", size, number_of_members, NULL);
  ASSERT_THAT(CurlHttp::Response(), Eq("123456789012"));
}

TEST(CurlHttpIntegration, DISABLED_Get) {
  CurlHttp http;
  http.Initialize();
  auto response = http.Get("http://langrsoft.com");
  ASSERT_THAT(response, HasSubstr("Jeff Langr"));
}
