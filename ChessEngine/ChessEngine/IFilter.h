#pragma once

#include "ISpecification.h"

template <typename T> class IFilter 
{
public:
	virtual std::vector<T*> filter(std::vector<T*> items, ISpecification<T>& specification) = 0;
};