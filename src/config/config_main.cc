#include <stdlib.h>
#include <iostream>

#include "src/config/config_map.h"
#include "src/config/config_map_builder.h"
#include "src/config/tuple_parser.h"
#include "src/util/util.h"

int main(int argc, char** argv) {
  //google::InitGoogleLogging(argv[0]);

  if (argc != 2) {
    std::cout << "usage tuple file\n";
    exit(1);
  }

  std::string s = argv[1];
  ConfigMap *map = parse_config_file(s);

  if (map == NULL) {
    std::cout << "error parsing " << s << "\n";
  } else {
    std::cout << map->ToString();
  }
  return 0;
}
