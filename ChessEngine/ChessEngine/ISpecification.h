#pragma once

template <typename T> class ISpecification 
{
public:
	virtual bool isSatisfiedBy(T* item) = 0;
};