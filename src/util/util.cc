#include "src/util/util.h"

#include <math.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

double Elapsed(time_t start, time_t finish) {
  return ((double) (finish - start) / (double) CLOCKS_PER_SEC);
}

char * ReadFile(const char *name, int &size) {
  // Get the file size
  struct stat filestatus;
  stat(name, &filestatus);
  size = filestatus.st_size;

  std::fstream fin;
  fin.open(name, std::ios::in | std::ios::binary);

  if (!fin.good()) {
    std::cout << "could not open file " << name;
    exit(1);
  }

  // Read the contents into a buffer
  char *buf = new char[size];
  fin.read(buf, size);
  return buf;
}

bool SameContent(const char* actual_file, const char* expected_file) {
  int size1, size2;
  char *actual = ReadFile(actual_file, size1);
  char *expected = ReadFile(expected_file, size2);

  if (size1 != size2) {
    return false;
  }

  bool ok = true;
  for (int i = 0; i < size1; i++) {
    if (expected[i] != actual[i]) {
      ok = false;
      break;
    }
  }

  delete[] actual;
  delete[] expected;

  return ok;
}

std::string Trim(const std::string& line) {
  int n = line.length();
  int start = 0;
  const char *buf = line.c_str();

  // trim left
  while (start < n && buf[start] == ' ') {
    start++;
  }

  if (start >= n) {
    return "";
  }

  // trim right
  int end = n - 1;
  while (end >= 0 && buf[end] == ' ') {
    end--;
  }

  if (end < 0) {
    return "";
  }

  return line.substr(start, end - start + 1);
}

int Tokenize(const std::string& line, char sep, std::string *out) {
  int n = line.length();
  const char* s = line.c_str();

  int pos = 0;
  int start = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == sep) {
      out[pos] = line.substr(start, i - start);

      start = i + 1;
      pos++;
    }
  }

  if (start <= n - 1) {
    out[pos++] = line.substr(start, n - start);
  }

  return pos;
}
