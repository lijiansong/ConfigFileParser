#include "src/config/constant.h"

Constant::Constant(int type, const std::string *svalue) {
  type_ = type;

  if (svalue == NULL) {
    svalue_ = "";
  } else {
    svalue_ = *svalue;
  }
}

Constant::~Constant() {
}

int Constant::GetInt() {
  return ivalue_;
}

float Constant::GetFloat() {
  return fvalue_;
}

std::string Constant::GetString() {
  return svalue_;
}

std::string Constant::ToString() {
  return svalue_;
}

int Constant::GetType() {
  return type_;
}
