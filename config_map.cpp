#include"config_map.h"
#include<cstdlib>
#include<list>
#include<string>
#include<set>
#include<sstream>

ConfigMap::ConfigMap() 
{}

ConfigMap::~ConfigMap() 
{}

ConfigMap * ConfigMap::Copy() 
{
	ConfigMap *result = new ConfigMap();
	std::map<std::string, std::string>::iterator it;
	it = data_.begin();
	while (it != data_.end()) 
	{
		result->AddEntry(it->first, it->second);
		it++;
	}
	return result;
}

std::string ConfigMap::RemoveQuotes(const std::string *s) 
{
	int n = s->length();
	if (n >= 2) 
	{
		if (s->at(0) == '"' && s->at(n-1) == '"') 
		{
			return s->substr(1, n - 2);
		}
	}
	return std::string(*s);
}
std::string ConfigMap::Last(const std::string& key) 
{
	int pos = key.find_last_of(".");
	if (pos == -1) 
	{
		return "";
	}
	return key.substr(pos + 1);
}

std::string ConfigMap::PopLast(const std::string& key) 
{
	int pos = key.find_last_of(".");
	if (pos == -1) 
	{
		return "";
	}
	return key.substr(0, pos);
}

std::string ConfigMap::PopFirst(const std::string& key) 
{
	int pos = key.find_first_of(".");
	if (pos == -1) 
	{
		return "";
	}
	return key.substr(pos + 1);
}

std::string ConfigMap::Push(const std::string& key, const std::string& s) 
{
	if (key == "") 
	{
		return s;
	}

	return key + "." + s;
}

bool ConfigMap::Contains(const std::string& key) 
{
	std::map<std::string, std::string>::iterator it = data_.find(key);
	return it != data_.end();
}

void ConfigMap::GetStringList(const std::string& key,
    std::vector<std::string>& out) 
{
	std::map<std::string, std::string>::iterator it = data_.find(key);

	if (it == data_.end()) 
	{
		return;
	}

	std::string parts[1024];
	int n = Tokenize(it->second, ',', parts);
	for (int i = 0; i < n; i++) 
	{
		out.push_back(parts[i]);
	}
}

void ConfigMap::AddEntry(const std::string& key, const std::string value) 
{
	data_[key] = value;
}

void ConfigMap::RemoveEntry(const std::string& key) 
{
	data_.erase(key);
}

void ConfigMap::GetDoubleList(const std::string& key,
    std::vector<double>& out) 
{
	std::map<std::string, std::string>::iterator it = data_.find(key);

	if (it == data_.end()) 
	{
		return;
	}

	std::string parts[1024];
	int n = Tokenize(it->second, ',', parts);
	for (int i = 0; i < n; i++) 
	{
		double d = atof(parts[i].c_str());
		out.push_back(d);
	}
}

double ConfigMap::GetDouble(const std::string& key) 
{
	std::map<std::string, std::string>::iterator it = data_.find(key);
	if (it == data_.end()) 
	{
		return 0;
	}
	std::string val = it->second;
	double d = atof(val.c_str());
	return d;
}

int ConfigMap::GetInt(const std::string& key) 
{
	std::map<std::string, std::string>::iterator it = data_.find(key);
	if (it == data_.end()) 
	{
		return 0;
	}
	std::string val = it->second;
	int i = atoi(val.c_str());
	return i;
}

std::string ConfigMap::GetString(const std::string& key) 
{
	std::map<std::string, std::string>::iterator it = data_.find(key);
	if (it == data_.end()) 
	{
		return "";
	}
	return it->second;
}

void ConfigMap::GetSection(const std::string& section,
    std::list<StringPair>& out) 
{
	std::string prefix = section + ".";
	std::map<std::string, std::string>::iterator it =
      data_.lower_bound(prefix);

	if (it == data_.end()) 
	{
		return;
	}

	while (it != data_.end()) 
	{
		std::string key = it->first;
		std::string sec = key.substr(0, prefix.length());

		if (sec != prefix) 
		{
			break;
		}

		out.push_back(StringPair(it->first, it->second));
		it++;
	}
}

void ConfigMap::GetContent(std::list<StringPair>& out) 
{
	std::map<std::string, std::string>::iterator it;
	it = data_.begin();
	while (it != data_.end()) 
	{
		out.push_back(StringPair(it->first, it->second));
		it++;
	}
}

void ConfigMap::Override(ConfigMap *other) 
{
	std::list<StringPair> l;
	other->GetContent(l);
	std::list<StringPair>::iterator it = l.begin();
	while (it != l.end()) 
	{
		AddEntry(ConfigMap::PopFirst(it->first), it->second);
		it++;
	}
}

std::string ConfigMap::ToString()
{
	std::stringstream stream;

	std::map<std::string, std::string>::iterator it;
	it = data_.begin();
	stream << "Config: \n";
	while (it != data_.end()) 
	{
		stream << it->first << ":" << it->second << "\n";
		it++;
	}
	return stream.str();
}

