#ifndef _CONFIG_CONFIG_LOADER_H_
#define _CONFIG_CONFIG_LOADER_H_

#include <fstream>
#include <string>
#include <list>
#include <map>

using StringList = std::list<std::string>;

// Loads a config file from disk, recursively loading included files.
class ConfigLoader {
public:
  ConfigLoader();
  ~ConfigLoader();

  void Load(const std::string& file_name, StringList& out);

private:
  // Disallow copy and assign
  explicit ConfigLoader(const ConfigLoader& copy_from_me);
  void operator=(const ConfigLoader&);

  StringList::iterator LoadInternal(const std::string& file_name,
      StringList& lines, StringList::iterator it);

  std::string ExtractInclude(const std::string& line);
  int CleanLine(std::string& line, char *out);
};

#endif /* _CONFIG_CONFIG_LOADER_H_ */
