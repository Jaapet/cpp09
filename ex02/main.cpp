/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:30:45 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/07 04:39:27 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	std::deque<int>		deque;
	std::vector<int>	vector;
	int					val;

	clock_t				start, end, dtime, vtime;
	
	if (argc < 2)
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
		vector.push_back(val);
	}
	
	std::cout << "Before :";
	for (std::deque<int>::iterator ite = deque.begin(); ite != deque.end(); ++ite)
		std::cout << " " << *ite;
	std::cout << std::endl;

	
	start = clock();
	deque = sort_deque(&deque);
	end = clock();
	dtime = end - start;

	start = clock();
	vector = sort_vector(&vector);
	end = clock();
	vtime = end - start;


	std::cout << "After  :";
	for (std::deque<int>::iterator ite = deque.begin(); ite != deque.end(); ++ite)
		std::cout << " " << *ite;
	std::cout << std::endl;

	std::cout << "Time to process a range of " << deque.size() << " elements with std::deque  : " << dtime << " s" << std::endl;
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << vtime << " s" << std::endl;

	return (0);
}