#include <stdlib.h>
#include <list>
#include <string>
#include <set>
#include <iostream>

#include "src/config/config_loader.h"
#include "src/config/config_map.h"
#include "src/util/util.h"

ConfigLoader::ConfigLoader() {
}

ConfigLoader::~ConfigLoader() {
}

void print_lines(StringList & lines) {
  StringList::iterator it = lines.begin();
  int i=0;
  while (it != lines.end()) {
    std::cout << i++ << ": " << (*it);
    it++;
  }
}

void ConfigLoader::Load(const std::string& file_name, StringList& lines) {
  // Load the main file
  LoadInternal(file_name, lines, lines.begin());

  // Set of already loaded includes
  std::set<std::string> loaded;

  // Load includes
  StringList::iterator it = lines.begin();
  while (it != lines.end()) {
    std::string line = (*it);

    std::string f = ExtractInclude(line);

    if (!f.empty()) {
      if (loaded.find(f) != loaded.end()) {
        // Already loaded this include, there is a loop
        std::cout << "loop in includes " << f;
        exit(1);
      }

      loaded.insert(f);

      it = lines.erase(it);
      it = LoadInternal(f, lines, it);
    } else {
      it++;
    }
  }
}

std::string ConfigLoader::ExtractInclude(const std::string& line) {
  if (line.substr(0, 8) == "#include") {
    std::string s = line.substr(9);
    return ConfigMap::RemoveQuotes(&s);
  }
  return "";
}

StringList::iterator ConfigLoader::LoadInternal(
    const std::string& file_name, StringList& lines,
    StringList::iterator it) {

  std::fstream fin;

  std::cout << "loading file " << file_name << '\n';

  fin.open(file_name.c_str(), std::ios::in);

  if (!fin.good()) {
    std::cout << "could not open " << file_name << '\n';
    exit(1);
  }

  StringList::iterator first_it = it;

  bool first = true;

  std::string line;
  while (!fin.eof()) {
    getline(fin, line);

    StringList::iterator itx = lines.insert(it, line);
    if (first) {
      first = false;
      first_it = itx;
    }
  }
  fin.close();

  return first_it;
}
