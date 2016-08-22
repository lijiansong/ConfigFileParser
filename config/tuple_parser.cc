#include "config/tuple_parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <map>
#include <string>

//#include <glog/logging.h>

#include "config/config_map_builder.h"
#include "config/config_loader.h"

// External functions defined by bison/flex
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyparse(ConfigMapBuilder *);
extern YY_BUFFER_STATE yy_scan_string(const char *);
extern void yy_switch_to_buffer(YY_BUFFER_STATE);
extern void yy_delete_buffer(YY_BUFFER_STATE);

ConfigMap *parse_config_string(const std::string& input_string) {
  YY_BUFFER_STATE buf_state = yy_scan_string(input_string.c_str());
  yy_switch_to_buffer(buf_state);

  ConfigMapBuilder builder;
  int result = yyparse(&builder);

  yy_delete_buffer(buf_state);

  if (result == 0) {
    return builder.GetMap();
  }

  std::cout << "could not parse config";
  exit(1);
}

ConfigMap *parse_config_file(const std::string& input_file) {
  ConfigLoader loader;
  StringList lines;
  loader.Load(input_file, lines);

  std::string s;
  s.reserve(100000);
  StringList::iterator it = lines.begin();
  while (it != lines.end()) {
    s.append(*it).append("\n");
    it++;
  }

  return parse_config_string(s.c_str());
}
