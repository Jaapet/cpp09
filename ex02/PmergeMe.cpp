/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:28:49 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/07 18:24:03 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Iterator>
Iterator	uplow(Iterator ite, char c)
{
	if (c == '+')
		++ite;
	else if (c == '-')
		--ite;
	return (ite);
}

template <typename T>
void	pair(T *c, T *S, T *low)
{
	if (c->size() == 2)
	{
		low->push_back(std::min(*c->begin(), *(uplow(c->end(), '-'))));
		S->push_back(std::max(*c->begin(), *(uplow(c->end(), '-'))));
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
	if (size == 1)
	{
		if (*ite < *mid && mid == c->begin())
			c->insert(mid, *ite);
		else if (*ite < *mid && *ite > *(uplow(mid, '-')))
			c->insert(mid, *ite);
		else if (*ite > *mid)
			binary_search(c, ite, uplow(mid, '+'), size);
		else if (*ite < *(uplow(mid, '-')))
			binary_search(c, ite, uplow(mid, '-'), size);
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

std::deque<int>	ford_johnson_deque(std::deque<int> *c)
{
	std::deque<int> S, low;

	pair(c, &S, &low);
	std::sort(S.begin(), S.end());
	c = &S;

	typename std::deque<int>::iterator mid = c->begin();
    std::advance(mid, c->size() / 2);

	for (typename std::deque<int>::iterator ite = low.begin(); ite != low.end(); ++ite)
		binary_search(c, ite, mid, c->size());

	return (*c);
}

std::list<int>	ford_johnson_list(std::list<int> *c)
{
	std::list<int> S, low;

	pair(c, &S, &low);
	S.sort();
	c = &S;

	typename std::list<int>::iterator mid = c->begin();
    std::advance(mid, c->size() / 2);

	for (typename std::list<int>::iterator ite = low.begin(); ite != low.end(); ++ite)
		binary_search(c, ite, mid, c->size());

	return (*c);
}

std::deque<int>	sort_deque(std::deque<int> *deque)
{
	return (ford_johnson_deque(deque));
}

std::list<int>	sort_list(std::list<int> *list)
{
	return (ford_johnson_list(list));
}