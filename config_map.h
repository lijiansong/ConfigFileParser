#ifndef CONFIGMAP_H_
#define CONFIGMAP_H_
#include<string>
#include<list>
#inlcude<map>
#include<vector>

typedef std::pair<std::string,std::string> StringPair;
// Holds key value pairs used for configuration.
// The ConfigMap is the output of parsing a config file.
// Values can be obtained from the ConfigMap as different types (e.g.
// string, int, double, string list, double list, etc).
class ConfigMap
{
public:
	ConfigMap();
	~ConfigMap();
	
	static std::string RemoveQuotes(const std::string *s);
	static std::string PopLast(const std::string& key);
	static std::string PopFirst(const std::string& key);
	static std::string Last(const std::string& key);
	static std::string Push(const std::string& key,const std::string& s);
	
	std::string ToString();
	bool Contains(const std::string& key);
	std::string GetString(const std::string& key);
	void GetSection(const std::string& section, std::list<StringPair>& out);
	void GetStringList(const std::string& key,std::vector<std:string>& out);
	void GetDoubleList(const std::string& key,std::vector<double>& out);
	
	double GetDouble(const std::string& key);
	int GetInt(const std::string& key);
	
	void AddEntry(const std::string& key,const std::string value);
	void RemoveEntry(const std::string& key);
	
	ConfigMap* Copy();
	void GetContent(std::list<StringPair>& out);
	void Override(ConfigMap *other);
	
private:
	explicit ConfigMap(const ConfigMap& copy_from_me);
	void operator=(const ConfigMap&);
	std::map<std::string,std::string> data_;
}
#endif
