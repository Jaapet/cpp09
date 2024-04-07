/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:28:49 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/07 04:42:26 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
void	pair(T *c, T *S, T *low)
{
	if (c->size() == 2)
	{
		low->push_back(std::min(*c->begin(), *(c->end() - 1)));
		S->push_back(std::max(*c->begin(), *(c->end() - 1)));
	}
	else if (c->size() == 1)
		low->push_back(*c->begin());
	else
	{
		typename T::iterator mid = c->begin();
    	std::advance(mid, c->size() / 2);

		T l(c->begin(), mid);
		T r(mid, c->end());
		c->clear();
		pair(&l, S, low);
		pair(&r, S, low);
	}
	
}

template <typename T>
void	binary_search(T *c, typename T::iterator ite, typename T::iterator mid, int size)
{
	if (size == 1)//
	{
		if (*ite < *mid && mid == c->begin())
			c->insert(mid, *ite);
		else if (*ite < *mid && *ite > *(mid - 1))
			c->insert(mid, *ite);
		else if (*ite > *mid)
			binary_search(c, ite, mid + 1, size);
		else if (*ite < *(mid - 1))
			binary_search(c, ite, mid - 1, size);
	}
	else
	{
		size /= 2;
		if (*ite < *mid)
			std::advance(mid, -size);
		else
			std::advance(mid, size);
		binary_search(c, ite, mid, size);
	}
}

template <typename T>
T	ford_johnson(T *c)
{
	T S, low;

	pair(c, &S, &low);
	std::sort(S.begin(), S.end());
	c = &S;
	
	for (typename T::iterator ite = low.begin(); ite != low.end(); ++ite)
		std::cout << " " << *ite;
	std::cout << std::endl;

	typename T::iterator mid = c->begin();
    std::advance(mid, c->size() / 2);

	for (typename T::iterator ite = low.begin(); ite != low.end(); ++ite)
		binary_search(c, ite, mid, c->size());

	return (*c);
}

std::deque<int>	sort_deque(std::deque<int> *deque)
{
	return (ford_johnson(deque));
}

std::vector<int>	sort_vector(std::vector<int> *vector)
{
	return (ford_johnson(vector));
}