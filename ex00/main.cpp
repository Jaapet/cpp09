/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndesprez <ndesprez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:50:43 by ndesprez          #+#    #+#             */
/*   Updated: 2024/04/04 20:11:27 by ndesprez         ###   ########.fr       */
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
				break ;
			} case 1:{
				if (word != "|")
					return (std::cerr << "Bad input => " << line << std::endl, false);
				break ;
			} case 2:{
				if (!check_value(word))
					return (false);
				std::istringstream	conv(word);
				if (!(conv >> val))
					return (std::cerr << "Invalid value => " << word << std::endl, false);
				break ;
			} default:{
				return (std::cerr << "Bad input => " << line << std::endl, false);
				break ;
			}
		}
	}
	if (val == -1)
		return (std::cerr << "Bad input => " << line << std::endl, false);
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (std::cerr << "Invalid number of args." << std::endl, 1);

	std::ifstream	file(argv[1]);
	std::ifstream	db("data.csv");
	std::multimap<std::string, float>	values;

	if (!file.is_open() || !db.is_open())
		return (std::cerr << "File error." << std::endl, 1);

	std::string	line;
	std::getline(file, line);
	parse_btc(db, values);

	while (std::getline(file, line))
	{
		if (parse_line(line))
		{
			std::istringstream	iss(line);
			std::string			date, sep;
			float				val;

			if (!(iss >> date >> sep >> val))
			{
				file.close();
				db.close();
				return (std::cerr << "Invalid line." << std::endl, 1);
			}

			std::multimap<std::string, float>::const_iterator ite = values.lower_bound(date);
			float	rate, res;

			if (ite != values.begin())
			{
				if (ite == values.end() || ite->first != date)
					ite--;
				rate = ite->second;
				res = rate * val;
				std::cout << date << " => " << val << " = " << res << std::endl;
			}
			else
			{
				file.close();
				db.close();
				return (std::cerr << "No data for date " << date << std::endl, 1);
			}
		}
	}
	file.close();
	db.close();
	return (0);
}