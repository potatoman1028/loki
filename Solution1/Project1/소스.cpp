#include<iostream>
#include "loki_object.h"

int main()
{
	loki::object_container<int> container;

	container.reserve(50);
	for (int i = 0; i < 50; i++)
	{
		auto obj = container.at(i);
		*obj->memory = i;
	}

	container.realloc(100);
	for (int i = 0; i < 150; i++)
	{
		auto obj = container.at(i);
		*obj->memory = i;
	}
	return 0;
}
