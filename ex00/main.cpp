/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:50:43 by ndesprez          #+#    #+#             */
/*   Updated: 2024/03/26 16:56:47 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	parse_line(std::string &line)
{
	std::istringstream	iss(line);
	std::string			word;
	std::string			date;
	float				val = -1;

	for (int i = 0; iss >> word; i++)
	{
		switch (i) {
			case 0:{
				if (!check_date(word))
					return (std::cerr << "Bad input => " << line << std::endl, false);
				date = word;
			} case 1:{
				if (word != "|")
					return (std::cerr << "Bad input => " << line << std::endl, false);
			} case 2:{
				if (!check_value(word))
					return (false);
				std::istringstream	conv(word);
				if (!(conv >> val))
					return (std::cerr << "Invalid value => " << word << std::endl, false);
			} default:{
				return (std::cerr << "Bad input => " << line << std::endl, false);
			}
		}
	}
	if (val == -1)
		return (std::cerr << "Bad input => " << line << std::endl, false);
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cerr << "Invalid number of args." << std::endl, 1);

	std::ifstream	file(argv[1]);
	std::ifstream	db("data.csv");
	std::multimap<std::string, float>	values;

	if (!file.is_open() || !db.is_open())
		return (std::cerr << "File error." << std::endl, 1);

	std::string	line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (!parse_line(line))
			return (1);
	}
}