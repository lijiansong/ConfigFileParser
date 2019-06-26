#ifndef _CONFIG_MAP_BUILDER_H_
#define _CONFIG_MAP_BUILDER_H_

#include <string>

#include "config/config_map.h"
#include "config/constant.h"

using StringPair = std::pair<std::string, std::string>;

// Builds a ConfigMap. Used by the parser (lang.yy) to build a config map
// from a config file.
class ConfigMapBuilder {
public:
  ConfigMapBuilder();
  ~ConfigMapBuilder();

  // Handles the start of a new section.
  void StartSection(std::string *section, std::string *parent);

  // Hanldes the end of a section.
  void EndSection(std::string *section);

  // Handles a key value pair in a section
  void AddKeyValue(std::string *key, Constant * node);

  // Returns the ConfigMap
  ConfigMap *GetMap();
private:
  // Current section
  std::string section_;

  // Map with key value pairs
  ConfigMap config_map_;
};

#endif /* _CONFIG_MAP_BUILDER_H_ */
