#include <fsciolib/fscio.hpp>
#include <fscio/native/tester.hpp>

using namespace fscio::native;

FSCIO_TEST_BEGIN(print_test)
   silence_output(true);
   CHECK_PRINT("27", [](){ fscio::print((uint8_t)27); });
   CHECK_PRINT("34", [](){ fscio::print((int)34); });
   CHECK_PRINT([](std::string s){return s[0] == 'a';},  [](){ fscio::print((char)'a'); });
   CHECK_PRINT([](std::string s){return s[0] == 'b';},  [](){ fscio::print((int8_t)'b'); });
   CHECK_PRINT("202", [](){ fscio::print((unsigned int)202); });
   CHECK_PRINT("-202", [](){ fscio::print((int)-202); });
   CHECK_PRINT("707", [](){ fscio::print((unsigned long)707); });
   CHECK_PRINT("-707", [](){ fscio::print((long)-707); });
   CHECK_PRINT("909", [](){ fscio::print((unsigned long long)909); });
   CHECK_PRINT("-909", [](){ fscio::print((long long)-909); });
   CHECK_PRINT("404", [](){ fscio::print((uint32_t)404); });
   CHECK_PRINT("-404", [](){ fscio::print((int32_t)-404); });
   CHECK_PRINT("404000000", [](){ fscio::print((uint64_t)404000000); });
   CHECK_PRINT("-404000000", [](){ fscio::print((int64_t)-404000000); });
   CHECK_PRINT("0x0066000000000000", [](){ fscio::print((uint128_t)102); });
   CHECK_PRINT("0xffffff9affffffffffffffffffffffff", [](){ fscio::print((int128_t)-102); });
   silence_output(false);
FSCIO_TEST_END

int main(int argc, char** argv) {
   FSCIO_TEST(print_test);
   return has_failed();
}
