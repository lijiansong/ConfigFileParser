#include <stdlib.h>

#include <iostream>

#include "config_map.h"
#include "config_map_builder.h"
#include "tuple_parser.h"
#include "util.h"
int main(int argc,char** argv)
{
	if (argc != 2) 
	{
		std::cout << "usage config file\n";
		exit(1);
	}
	std::string s = argv[1];
	ConfigMap *map = parse_config_file(s);

	if (map == NULL) 
	{
		std::cout << "error parsing " << s << "\n";
	} 
	else 
	{
		std::cout << map->ToString();
	}
	return 0;
}
