#include <fsciolib/fscio.hpp>
#include <fscio/native/tester.hpp>

using namespace fscio::native;

FSCIO_TEST_BEGIN(name_test)
   //silence_output(true);
   fscio_assert( fscio::name{"azaa34"}.value == "azaa34"_n.value, "fscio::name != azaa34" );
   fscio_assert( fscio::name{0}.value == 0, "fscio::name != 0" );
   fscio_assert( fscio::name{"aa11"}.value == "aa11"_n.value, "fscio::name != aa11" );
   fscio_assert( fscio::name{"z11"}.value == "z11"_n.value, "fscio::name != z11" );
   
   auto testa = []() {
      fscio_assert( fscio::name{"bb"}.value == "aa"_n.value, "bb != aa" );
   };
   REQUIRE_ASSERT("bb != aa", testa);
   REQUIRE_ASSERT("character is not in allowed character set for names",
         ([]() {
            fscio::name{"!"}.value;
         }));
   silence_output(false);
FSCIO_TEST_END

FSCIO_TEST_BEGIN(is_account_test)
   intrinsics::set_intrinsic<intrinsics::is_account>([](uint64_t a) { 
         if (a == 3)
            return true;
         if (a == 4)
            return true;
         return false;
         });

   CHECK_ASSERT("is not an account", ([]() {
      fscio_assert(is_account(5), "is not an account");
      }));
   CHECK_EQUAL(is_account(3), true);
   CHECK_EQUAL(is_account(4), true);
   CHECK_EQUAL(is_account(6), true);
   REQUIRE_EQUAL(is_account(7), true);

FSCIO_TEST_END

int main(int argc, char** argv) {
   FSCIO_TEST(name_test);
   FSCIO_TEST(is_account_test);
   return has_failed();
}
