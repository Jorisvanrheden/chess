#pragma once

#include "ISpecification.h"

template <typename T> class AndSpecification : public ISpecification<T>
{
public:
	AndSpecification(ISpecification<T>& first, ISpecification<T>& second)
		: first(first),
		  second(second)
	{
	}
	~AndSpecification() {}

	bool isSatisfiedBy(T* piece)
	{
		return first.isSatisfiedBy(piece) && second.isSatisfiedBy(piece);
	}

private:
	ISpecification<T>& first;
	ISpecification<T>& second;
};