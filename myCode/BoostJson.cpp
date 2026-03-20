/**
 * @file BoostJson.cpp
 * @brief Boost.JSON Library Implementation Wrapper
 *
 * Reference link:
 * https://www.boost.org/doc/libs/latest/libs/json/doc/html/index.html
 *
 * WHY THIS FILE EXISTS:
 * 1. Boost.JSON is normally provided as a compiled library
 *    that requires linker flags.
 *
 * 2. Including <boost/json/src.hpp>
 *    switches it into a header-only usage mode.
 *
 * 3. That causes the JSON library implementation
 *    to be compiled directly into this project.
 *
 * 4.  Keeping this include in a
 *     separate source file avoids recompiling the large JSON code
 */

#include <boost/json/src.hpp>
