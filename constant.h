#ifndef CONSTANT_H_
#define CONSTANT_H_
#include<string>
class Constant
{
public:
	Constant(int type,const std::string *svalue);
	~Constant();
	int GetInt();
	float GetFloat();
	std::string GetString();
	int GetType();

	std::string ToString();

private:
	explicit Constant(const Constant& copy_from_me);
	void operator=(const Constant&);

	int type_;
	int ivalue_;
	float fvalue_;
	std::string svalue_;
}
#endif
