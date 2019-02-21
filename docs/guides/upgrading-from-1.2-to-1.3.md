## Version 1.3

### fsciolib C API
- Removed the following typedefs to `uint64_t`:
  - `account_name`
  - `permission_name`
  - `scope_name`
  - `table_name`
  - `action_name`
- Added a `uint64_t` typedef called `capi_name` to replace the removed typedefs above:
    - These have been replaced by `capi_name` and as a practice should not be used when writing C++ contract code. Instead, the new version of the `fscio::name` type from the fsciolib C++ API should be used to replace these instances. This decision was made because of bad implicit casting issues with `uint64_t` and the new pattern should allow for better type safety.
- Removed `symbol_name` typedef:
    - This has no C equivalent to replace it. When writing C++ contract code, the `fscio::symbol_code` struct should be used instead. As with the previously mentioned named types, this was removed and replaced with `fscio::symbol_code` to allow for better type safety in contracts.  To use a symbol, i.e. symbol name and precision, use the `fscio::symbol` class.
- Removed `time` and `weight_type` typedefs.
- Removed the `transaction_id_type` and `block_id_type` typedefs.
- Removed the `account_permission` struct.
- Renamed the following typedefs:
  - `checksum160` -> `capi_checksum160`
  - `checksum256` -> `capi_checksum256`
  - `checksum512` -> `capi_checksum512`
  - `public_key`  -> `capi_public_key`
  - `signature`   -> `capi_signature`
- Removed the non-existent intrinsics declarations `require_write_lock` and `require_read_lock`.

### fsciolib C++ API
- Removed fsciolib/vector.hpp:
  - Removed alias `fscio::vector` and typedef `bytes`.
  - Going forward contract writers should include `<vector>` from the STL and use `std::vector<char>` instead of bytes.
- Removed fsciolib/types.hpp.
- Removed fsciolib/optional.hpp. Use `std::optional` as a replacement.
- Removed fsciolib/core_symbol.hpp. The contract writer should explicitly specify the symbol.
- Added fsciolib/name.hpp.

#### fsciolib/types.hpp
- Moved the typedef `fscio::extensions_types` to fsciolib/transaction.hpp.
- Removed comparison functions for `checksum` structs.
- Removal of `fscio::char_to_symbol`, `fscio::string_to_name`, `fscio::name_suffix` functions
- Removal of the `N` macro. The `""_n` operator or the `name` constructor should be used as a type safe replacement. Example: `N(foo)` -> `"foo"_n`, or `N(foo)` -> `name("foo")`.
- Moved `fscio::name` struct definition and `""_n` operator to fsciolib/name.hpp.

#### fsciolib/name.hpp
- Removed implicit and explicit conversions to `uint64_t`.
- Added `enum class` `fscio::name::raw` which is implicitly converted from an `fscio::name` (used for template non-type parameters).
- Added `bool` conversion operator for conditionally testing if a name is empty.
- All constructors are now `constexpr`. These take either a `uint64_t`, an `fscio::name::raw` or a `std::string_view`.
- Added `constexpr` methods `fscio::name::length` and `fscio::name::suffix`.
- Added equivalence, inverted equivalence and less than operators to `fscio::name`.

#### fsciolib/symbol.hpp
- Removed `fscio::symbol_type` struct and replaced with `fscio::symbol` class.
- Added struct `fscio::symbol_code`:
  - Added two `constexpr` constructors that take either a raw `uint64_t` or an `std::string_view`.
  - Added `constexpr` methods `is_valid`, `length` and `raw`.
  - Added a print method.
  - Added `bool` conversion operator to test is `symbol_code` is empty.
- Removed `fscio::string_to_symbol`, `fscio::is_valid_symbol`, `fscio::symbol_name_length` functions.
- Removed the `S` macro. The symbol constructor should be used as a type safe replacement. Example: `S(4,SYS)` -> `symbol(symbol_code("SYS"), 4)` (or simply `symbol("SYS", 4)` as of v1.3.1).
- Added struct `fscio::symbol`:
  - Added three `constexpr` constructors that take either a raw `uint64_t`, `symbol_code` and a `uint8_t` precision or an `std::string_view` and a `uint8_t` precision.
  - Added `constexpr` methods `is_valid`, `precision`, `code`, and `raw`. These, respectively, check if the `symbol` is valid, get the `uint8_t` precision, get the `symbol_code` part of the `symbol`, and get the raw `uint64_t` representation of `symbol`.
  - Added equivalence, inverted equivalence and less than operators to `fscio::symbol`.
- Modified struct `fscio::extended_symbol`:
  - Restricted fields to private.
  - Added `constexpr` constructor that takes a `fscio::symbol` and an `fscio::name`.
  - Added `constexpr` methods `get_symbol` and `get_contract`.
  - Made existing comparison operators `constexpr`.

#### fsciolib/asset.hpp
- The main constructor now requires a `int64_t` (quantity) and `fscio::symbol` explicitly.
- The default constructor no longer initializes the instance to a valid zero quantity asset with a symbol equivalent to "core symbol". Instead the default constructed `fscio::asset` is a bit representation of all zeros (which will cause `is_valid` to fail) so that check is bypassed to allow for `multi_index` and `datastream` to work.
- Old contracts that use `fscio::asset()` should be changed to either use the core symbol of the specific chain they are targeting i.e. `fscio::asset(0, symbol(symbol_code("SYS"),4))`. To reduce writing `symbol(symbol_code("SYS"),4)` over and over, a `constexpr` function to return the symbol or `constexpr` global variable should be used.

#### fsciolib/contract.hpp
- The constructor for `fscio::contract` now takes an `fscio::name` for the receiver, an `fscio::name` for the code, and a `fscio::datastream<const char*>` for the datastream used for the contract.  The last argument is for manually unpacking an action, see the section on `fscio::ignore` for a more indepth usage.

#### fsciolib/dispatcher.hpp
- Renamed the macro `FSCIO_ABI` to `FSCIO_DISPATCH` as this is more descriptive of what this macro actually does.
- Modified the definition of `FSCIO_DISPATCH` to work with the new constructor for `fscio::contract`.

#### fsciolib/multi_index.hpp
- The first template parameter for `indexed_by` now requires the argument be convertible to `fscio::name::raw` (replacing `uint64_t`).
- The first template parameter for `multi_index` now requires the argument be convertible to `fscio::name::raw` (replacing `uint64_t`).
- The constructor now takes an `fscio::name` type for the code (replacing `uint64_t`). Scope is still `uint64_t`.
- Various other replacements of `uint64_t` to `fscio::name`.

#### fsciolib/singleton.hpp
- The first template parameter for `fscio::singleton` now requires the argument be convertible to `fscio::name::raw` (replacing `uint64_t`).
- The constructor now takes an `fscio::name` type for the code.
- In the methods `get_or_create` and `set`, the argument `bill_to_account` is now of type `fscio::name` (replacing `uint64_t`).

#### fsciolib/action.hpp
- Added C++ function `fscio::require_auth`.
- Added C++ function `fscio::has_auth`.
- Added C++ function `fscio::is_account`.
- Redefined `fscio::permission_level` to use `fscio::name` in place of `uint64_t`.
- Removed the macro `ACTION`. (The identifier `ACTION` has been reused for another macro described below in the Macros section.)

#### fsciolib/permission.hpp
 - The optional provided_keys argument of the function `fscio::check_transaction_authorization` is now of the type `std::set<fscio::public_key>` rather than the type `std::set<capi_public_key>`. C++ contract code should most likely be using the `fscio::public_key` struct (defined in "fsciolib/public_key.hpp") if they need to deal with FSCIO-compatible public keys rather than the `capi_public_key` struct (now renamed from its original name of `::public_key`) from the fsciolib C API. Note that existing contract code that just referred to the type `public_key` without namespace qualification may have accidentally been using the `capi_public_key` struct and therefore should ideally be modified to use the `fscio::public_key` C++ type.
 - The `account` and `permission` arguments of `fscio::check_permission_authorization` are both `fscio::name` now instead of `uint64_t`.

#### fsciolib/ignore.hpp
- Added new type `ignore`:
  - This type acts as a placeholder for actions that don't want to deserialize their fields but want the types to be reflected in the ABI.
    ```
    ACTION action(ignore<some_type>) { some_type st; _ds >> st; }
    ```
- Added new type `ignore_wrapper`:
  - This allows for calling `SEND_INLINE_ACTION` with `ignore_wrapper(some_value)` against an action with an `ignore` of matching types.

### Macros
- Added `ACTION` macro which is simply a shortcut for `[[fscio::action]] void`.
- Added `TABLE` macro which is simply a shortcut for `struct [[fscio::table]]`.
- Added `CONTRACT` macro which is simply a shortcut for `class [[fscio::contract]]`.

### CMake
- Added `fscio.cdt-config.cmake` to allow for `find_package(fscio.cdt)`. See fscio.cdt/examples/hello or fscio.cdt/examples/template for an example.
- Added new macro `add_contract`. This new contract takes a contract name, cmake target, then any normal arguments you would give to `add_executable`. See fscio.cdt/examples/hello or fscio.cdt/examples/template.
- New version checking mechanism is included. See fscio.contracts/CMakeLists.txt to see this in use.

### libc
- Replaced `printf`, `sprintf`, and `snprintf` with new minimal variants. This allows contracts to use these functions without causing stack overflow issues.

### libcxx
- Removed `sstream` with the intent to return this after more has been done.
- Added `__cxa_pure_virtual` to allow for pure virtual methods in contract classes.
- `std::to_string` now works without the issues of stack overflows.

### attributes
- Added `[[fscio::ignore]]` attribute to flag a type as being ignored by the deserializer. This attribute is primarily only used for internal use within fsciolib.
- Added `[[fscio::contract]]` attribute. This new attribute is used to mark a contract class as "contract" with the name being either the C++ name of the class or a user specified name (i.e. `[[fscio::contract("somecontract")]]`). This attribute can also be used in conjunction with the `fscio::action` and `fscio::table` attributes for tables that you would like to define outside of the `fscio::contract` class.  This is used in conjunction with either the raw `fscio-cpp` option `--contract <name>`, `-o <name>.wasm` or with CMake `add_contract`.  It acts as a filter enabling contract developers to include a header file with attributes from another contract (e.g. fscio.token) while generating an ABI devoid of those actions and tables.
  ```c++
  #include <fsciolib/fscio.hpp>
  using namespace fscio;
  CONTRACT test : public fscio::contract {
  public:
     using contract::contract;
     ACTION acta(){}
     TABLE taba {
        uint64_t a;
        float b;
        uint64_t primary_key() const { return a; }
     };
  };
  struct [[fscio::table, fscio::contract("test")]]
  tabb {
     uint64_t a;
     int b;
  };
  typedef fscio::multi_index<"testtaba"_n, test::taba> table_a;
  typedef fscio::multi_index<"testtabb"_n, tabb> table_b;
  FSCIO_DISPATCH( test, (acta) )
  ```
  The above code will produce the tables `testtaba` and `testtabb` in your ABI. Example: `fscio-cpp -abigen test.cpp -o test.wasm` will mark this compilation and ABI generation for the `fscio::contract` `test`. The same thing can be done with `fscio-cpp -abigen test.cpp -o test_contract.wasm --contract test` or with the CMake command `add_contract( test, test_contract, test.cpp )`. Either of the previous two approaches will produce a test_contract.wasm and test_contract.abi generated under the context of the contract name of `test`.

### Boost
- Boost is now part of the library. No more external dependence on Boost and all system inclusion are within it's `sysroot`. (Boost will be removed in a future release.)


## ABI generator attributes
Unlike the old ABI generator tool, the new tool uses C++11 or GNU style attributes to mark ```actions``` and ```tables```.
#### [[fscio::action]]
This attribute marks either a struct or a method as an action.
Example (four ways to declare an action for ABI generation):
```c++
// this is the C++11 and greater style attribute
[[fscio::action]]
void testa( name n ) {
   // do something
}

// this is the GNU style attribute, this can be used in C code and prior to C++ 11
__attribute__((fscio_action))
void testa( name n ){
   // do something
}

struct [[fscio::action]] testa {
   name n;
   FSCLIB_SERIALIZE( testa, (n) )
};

struct __attribute__((fscio_action)) testa {
   name n;
   FSCLIB_SERIALIZE( testa, (n) )
};
```
If your action name is not a valid [FSCIO name](https://developers.fsc.io/fscio-cpp/docs/naming-conventions) you can explicitly specify the name in the attribute ```c++ [[fscio::action("<valid action name>")]]```

Example (two ways to declare a table for ABI generation):
```
struct [[fscio::table]] testtable {
   uint64_t owner;
   /* all other fields */
};

struct __attribute__((fscio_table)) testtable {
   uint64_t owner;
   /* all other fields */
};

typedef fscio::multi_index<"tablename"_n, testtable> testtable_t;
```
If you don't want to use the multi-index you can explicitly specify the name in the attribute ```c++ [[fscio::table("<valid action name>")]]```.

For an example contract of ABI generation please see the file ./examples/abigen_test/test.cpp. You can generate the ABI for this file with `fscio-abigen test.cpp --output=test.abi`.

### Fixing an ABI or Writing an ABI Manually
- The sections to the ABI are pretty simple to understand and the syntax is purely JSON, so it is reasonable to write an ABI file manually.
- The ABI generation will never be completely perfect for every contract written. Advanced features of the newest version of the ABI will require manual construction of the ABI, and odd and advanced C++ patterns could capsize the generators type deductions. So having a good knowledge of how to write an ABI should be an essential piece of knowledge of a smart contract writer.
- Please refer to [developers.fsc.io "How to Write an ABI File"](https://developers.fsc.io/fscio-cpp/docs/how-to-write-an-abi) to learn about the different sections of an ABI.

### Adding Ricardian Contracts and Clauses to ABI
- As of FSCIO.CDT v1.4.0 the ABI generator will try to automatically import contracts and clauses into the generated ABI.  There are a few caveats to this, one is a strict naming policy of the files and an HTML tag used to mark each Ricardian contract and each clause.
- The Ricardian contracts should be housed in a file with the name <contract name>.contracts.md and the clauses should be in a file named <contract name>.clauses.md.
 - For each Ricardian contract the header `<h1 class="contract">ActionName</h1>` should be used, as this directs the ABI generator to attach this Ricardian contract to the specified action.
 - For each Ricardian clause the header `<h1 class="clause">ClauseID</h1>` should be used, as this directs the ABI generator to the clause id and the subsequent body.
 - The option `-R` has been added to fscio-cpp and fscio-abigen to add "resource" paths to search from, so you can place these files in any directory structure you like and use `-R<path to file>` in the same vein as `-I` for include paths.
 - To see these in use please see ./examples/hello/hello.contracts.md and ./examples/hello/hello.clauses.md.



License
----

MIT
