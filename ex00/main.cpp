/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:09:52 by jocalder          #+#    #+#             */
/*   Updated: 2026/03/25 11:53:10 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Usage ./Scalarconvert <literal>" << std::endl;
		return 1;
	}
	std::string literal = argv[1];
	ScalarConverter::convert(literal);
	return 0;
}