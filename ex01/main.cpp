/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:52:53 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/04 23:30:44 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cerr << "Invalid number of arguments." << std::endl, 1);

	std::istringstream	iss(argv[1]);
	std::stack<float>	list;
	std::string			str;

	while (iss >> str)
	{
		if (isdigit(str[0]))
			list.push(std::atof(str.c_str()));
		else
		{
			if (list.size() < 2)
				return (std::cerr << "Invalid expression." << std::endl, 1);

			float	a = list.top();
			list.pop();
			float	b = list.top();
			list.pop();

			switch (str[0]) {
                case '+':{
					list.push(b + a);
					break ;
				}
                case '-':{
					list.push(b - a);
					break ;
				}
				case '/':{
					list.push(b / a);
					break ;
				}
                case '*':{
					list.push(b * a);
					break ;
				}
                default:
                    return (std::cerr << "Invalid operator." << std::endl, 1);
			}
		}
	}
	
	if (list.size() != 1)
		return (std::cerr << "Invalid expression." << std::endl, 1);
	std::cout << list.top() << std::endl;
	return (0);
}