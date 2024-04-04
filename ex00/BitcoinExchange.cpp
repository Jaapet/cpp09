/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:40:34 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/04 19:02:47 by ndesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool	check_date(std::string const &date)
{
	int	m, d;

	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i != 4 && i != 7 && !isdigit(date[i]))
			return (false);
	}
	
	m = std::atoi(date.substr(5, 2).c_str());
	d = std::atoi(date.substr(8, 2).c_str());

	if (m < 1 || m > 12 || d < 1 || d > 31)
		return (false);

	return (true);
}

bool	check_value(std::string const &val)
{
	float value;

	if (val.empty())
		return (std::cerr << "Empty value." << std::endl, false);
	if (val[0] == '-')
		return (std::cerr << "Negative value." << std::endl, false);
	for (size_t i = 0; i < val.size(); i++)
	{
		if (!isdigit(val[i]) && val[i] != '.')
			return (std::cerr << "Non numeric value." << std::endl, false);
	}
	std::istringstream iss(val);
	iss >> value;
	if (value > 1000)
		return (std::cerr << "Too large value." << std::endl, false);
	return (true);
}

void	parse_btc(std::ifstream &db, std::multimap<std::string, float> &values)
{
	std::string	line, date;
	float		val;
	size_t		p;

	while (std::getline(db, line))
	{
		p = line.find(',');
		if (p != std::string::npos)
			line.replace(p, 1, " ");

		std::istringstream iss(line);

		if (iss >> date >> val)
			values.insert(std::make_pair(date, val));
	}
	
}