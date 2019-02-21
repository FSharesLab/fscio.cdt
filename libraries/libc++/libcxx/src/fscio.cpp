#pragma once

/**
 * Define specific things for the fscio system
 */

extern "C" {
   void fscio_assert(unsigned int, const char*);
   void __cxa_pure_virtual() { fscio_assert(false, "pure virtual method called"); }
}
