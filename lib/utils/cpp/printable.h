#ifndef HLIB_PRINTER_H_
#define HLIB_PRINTER_H_

#include <ostream>
#include <vector>
#include <array>

// member pointer pattern?

struct streamable_tag {};

struct container_streamable_tag : streamable_tag {};
struct sequence_streamable_tag : streamable_tag {};
struct sequence_streamable_tag {};


struct container_printible_tag {};

struct sequence_printable_tag : container_printible_tag{};
struct associative_printable_tag : container_printible_tag{};
struct unordered_assosiative_printible_tag : container_printible_tag{};

struct streamable_traits

#endif