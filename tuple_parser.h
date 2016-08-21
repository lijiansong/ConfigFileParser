#ifndef TUPLEPARSER_H_
#define TUPLEPARSER_H_
#include <map>
#include <string>
#include "config_map_builder.h"
#include "config_map.h"
// Example config file:
// a {
//  k1 = 10;
//  k2 = "a string";
//  a1 {
//    k1 = 30;
//  }
// }
//
// // b inherits from a
// b:a {
//   k1 = 11;
//   k2 = NULL;
//   k3 = 12;
// }
//
// Resulting map:
// a.k1 = 10
// a.k2 = 20
// a.a1.k1 = 30
// b.k1 = 11
// b.k3 = 12
// b.a1.k1 = 30
//
// You can also include files as follows:
// #include "file_name"
// Parses from a string. Does not handle includes.
ConfigMap *parse_config_string(const std::string& input_string);

// Parses from a file. Handles includes.
ConfigMap *parse_config_file(const std::string& input_file);

#endif
