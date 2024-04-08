/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:30:45 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/08 17:37:29 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	std::deque<int>		deque;
	std::list<int>		list;
	int					val;

	clock_t				start, end;
	double				dtime, ltime;
	
	if (argc < 3)
		return (std::cerr << "Invalid number of arguments." << std::endl, 1);
	
	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (!isdigit(argv[i][j]))
				return (std::cerr << "Non numeric value." << std::endl, 1);
		}
		val = std::atoi(argv[i]);
		if (val < 0)
			return (std::cerr << "Negative value." << std::endl, 1);
		for (std::deque<int>::iterator ite = deque.begin(); ite != deque.end(); ++ite)
		{
			if (val == *ite)
				return (std::cerr << "Duplicated value." << std::endl, 1);
		}
		deque.push_back(val);
		list.push_back(val);
	}
	
	std::cout << "Before :";
	for (std::deque<int>::iterator ite = deque.begin(); ite != deque.end(); ++ite)
		std::cout << " " << *ite;
	std::cout << std::endl;

	
	start = clock();
	deque = sort_deque(&deque);
	end = clock();
	dtime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;

	start = clock();
	list = sort_list(&list);
	end = clock();
	ltime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;


	std::cout << "After  :";
	for (std::deque<int>::iterator ite = deque.begin(); ite != deque.end(); ++ite)
		std::cout << " " << *ite;
	std::cout << std::endl;

	std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << dtime << " µs" << std::endl;
	std::cout << "Time to process a range of " << list.size() << " elements with std::list  : " << ltime << " µs" << std::endl;

	return (0);
}