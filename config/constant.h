#ifndef CONFIG_CONSTANT_H_
#define CONFIG_CONSTANT_H_

#include <string>

// Contains a string, float, or int constant from a config file. Used
// by the config parser: tuple.y
class Constant {
public:
  Constant(int type, const std::string *svalue);
  ~Constant();

  int GetInt();
  float GetFloat();
  std::string GetString();
  int GetType();

  std::string ToString();
private:
  // Disallow copy and assign
  explicit Constant(const Constant& copy_from_me);
  void operator=(const Constant&);

  int type_;
  int ivalue_;
  float fvalue_;
  std::string svalue_;
};

#endif /* CONFIG_CONSTANT_H_ */
