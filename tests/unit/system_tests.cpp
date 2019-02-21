#include <fsciolib/fscio.hpp>
#include <fscio/native/tester.hpp>

using namespace fscio::native;

FSCIO_TEST_BEGIN(system_test)
   silence_output(true);
   auto test_check1 = [](bool b) { fscio::check(b, "asserted"); }; 
   test_check1(true);
   CHECK_ASSERT("asserted", test_check1, false);

   auto test_check2 = [](bool b) { std::string s="asserted"; fscio::check(b, s); }; 
   test_check2(true);
   REQUIRE_ASSERT("asserted", test_check2, false);

   auto test_check3 = [](bool b) { fscio::check(b, "asserted with more text", 8); }; 
   test_check3(true);
   REQUIRE_ASSERT("asserted", test_check3, false);

   auto test_check4 = [](bool b) { std::string s="asserted with more text"; fscio::check(b, s, 8); }; 
   test_check4(true);
   REQUIRE_ASSERT("asserted", test_check4, false);

   auto test_check5 = [](bool b) { fscio::check(b, 13); }; 
   test_check5(true);
   REQUIRE_ASSERT("13", test_check5, false);
   silence_output(false);
FSCIO_TEST_END

int main(int argc, char** argv) {
   FSCIO_TEST(system_test);
   return has_failed();
}
