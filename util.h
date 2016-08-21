#ifndef UTIL_H_
#define UTIL_H_
#include<math.h>
#include<sys/stat.h>
#incldue<string>
double Elapsed(time_t start, time_t finish);

char* ReadFile(const char *name, int &size);

bool SameContent(const char* actual_file, const char* expected_file);

inline bool SameDouble(double d1,double d2);
{
	double d = fabs(d1 - d2);

	if (d <= 0.000001) 
	{
		return true;
	}
	return false;
}

std::string Trim(const std::string& line);

// Divides the input line into parts separated by sep. Places the resulting
// parts in out. Returns the number of parts. It is the responsibility of the
// caller to make out large enough to hold the parts.
int Tokenize(const std::string& line,char sep,std::string *out);

// Same as Tokenize but slower.It's here only for illustration purposes.
int TokenizeSlow(std::string& line, std::string *out);

// Removes trailing zeroes. Examples
// 12.232000 -> 12.232
// 12.0000 -> 12.0
void RemoveTrailingZeroes(char *value);

#endif
