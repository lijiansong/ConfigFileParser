#include"config_map_builder.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include"config_map.h"
ConfigMapBuilder::ConfigMapBuilder() 
{}

ConfigMapBuilder::~ConfigMapBuilder() 
{}

void ConfigMapBuilder::StartSection(std::string *section, std::string *parent) 
{
	section_ = ConfigMap::Push(section_, *section);

	if (parent != NULL && !parent->empty()) 
	{
		// Inherit entries from parent section
		std::list<StringPair> l;
		config_map_.GetSection(*parent, l);

		int n = parent->length() + 1;

		std::list<StringPair>::iterator itx = l.begin();
		while (itx != l.end()) 
		{
			std::string key = section_ + "." + itx->first.substr(n);

			config_map_.AddEntry(key, itx->second);
			itx++;
		}
	}
}
void ConfigMapBuilder::EndSection(std::string *section) 
{
	section_ = ConfigMap::PopLast(section_);
}

void ConfigMapBuilder::AddKeyValue(std::string *key, Constant * node) 
{
	if (node->GetType() == 3) 
	{
		// Erase the value
		config_map_.RemoveEntry(section_ + "." +  *key);
	} 
	else 
	{
		config_map_.AddEntry(section_ + "." + (*key), node->GetString());
	}
}
ConfigMap *ConfigMapBuilder::GetMap() 
{
	// Return a copy of the config map.
	return config_map_.Copy();
}


