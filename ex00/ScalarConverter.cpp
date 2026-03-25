/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 10:09:50 by jocalder          #+#    #+#             */
/*   Updated: 2026/03/25 12:17:46 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) {(void)other;}
ScalarConverter&	ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}
ScalarConverter::~ScalarConverter() {}

static bool		isPseudoFloat(const std::string &s)
{
	return (s == "nanf" || s == "+inff" || s == "-inff");	
}
static bool		isPseudoDouble(const std::string &s)
{
	return (s == "nan" || s == "+inf" || s == "-inf");
}
static bool		isCharLiteral(const std::string &s)
{
	return (s.length() == 3 && s[0] == '\'' && s[2] == '\'');
}
static bool		isIntLiteral(const std::string &s)
{
	if (s.empty())
		return false;
	size_t	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return false;
	while (i < s.length())
	{
		if (!std::isdigit(s[i]))
			return false;
		i++;
	}
	return true;
}
static bool		isFloatLiteral(const std::string &s)
{
	if (s.empty() || s[s.length() - 1] != 'f')
		return false;
	
	std::string f = s.substr(0, s.length() - 1);
	if (f.empty())
		return false;
	bool	dotFound = false;
	size_t	i = 0;
	if (f[i] == '+' || f[i] == '-')
		i++;
	if (i == f.length())
		return false;
	while (i < f.length())
	{
		if (f[i] == '.')
		{
			if (dotFound)
				return false;
			dotFound = true;
		}
		else if (!std::isdigit(f[i]))
			return false;
		i++;
	}
	return dotFound;
}
static bool		isDoubleLiteral(const std::string &s)
{
	if (s.empty())
		return false;
	bool	dotFound = false;
	size_t	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return false;
	while (i < s.length())
	{
		if (s[i] == '.')
		{
			if (dotFound)
				return false;
			dotFound = true;
		}
		else if (!std::isdigit(s[i]))
			return false;
		i++;
	}
	return dotFound;
}

static LiteralType	detectType(const std::string &literal)
{
	if (isPseudoFloat(literal))
		return TYPE_PSEUDO_FLOAT;
	if (isPseudoDouble(literal))
		return TYPE_PSEUDO_DOUBLE;
	if (isCharLiteral(literal))
		return TYPE_CHAR;
	if (isIntLiteral(literal))
		return TYPE_INT;
	if (isFloatLiteral(literal))
		return TYPE_FLOAT;
	if (isDoubleLiteral(literal))
		return TYPE_DOUBLE;
	return TYPE_INVALID;
}

static double	parseToDouble(const std::string &literal, LiteralType type)
{
	switch (type)
	{
		case TYPE_CHAR:
			return static_cast<double>(literal[1]);
		case TYPE_INT:
			return static_cast<double>(std::strtod(literal.c_str(), NULL));
		case TYPE_FLOAT:
			return static_cast<double>(std::strtod(literal.c_str(), NULL));
		case TYPE_DOUBLE:
			return std::atof(literal.c_str());
		case TYPE_PSEUDO_FLOAT:
			if (literal == "nanf")
				return std::numeric_limits<float>::quiet_NaN();
			if (literal == "+inff")
				return std::numeric_limits<float>::infinity();
			return -std::numeric_limits<float>::infinity();
		case TYPE_PSEUDO_DOUBLE:
			if (literal == "nan")
				return std::numeric_limits<double>::quiet_NaN();
			if (literal == "+inf")
				return std::numeric_limits<double>::infinity();
			return -std::numeric_limits<double>::infinity();
		default:
			return 0.0;
	}
}

static void		printChar(double value)
{
	std::cout << "char: ";
	if (value < 0 || value > 127
		|| std::isnan(value) || std::isinf(value))
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	char	c = static_cast<char>(value);
	if (!std::isprint(c))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;
}
static void		printInt(double value)
{
	std::cout << "int: ";
	if (value < INT_MIN || value > INT_MAX
		|| std::isnan(value) || std::isinf(value))
	{
		std::cout << "impossible" << std::endl;
		return;
	}
	std::cout << static_cast<int>(value) << std::endl;
}
static void		printFloat(double value)
{
	std::cout << "float: ";
	float	f = static_cast<float>(value);
	if (std::isnan(f))
	{
		std::cout << "nanf" << std::endl;
		return;
	}
	if (std::isinf(f))
	{
		if (f > 0)
			std::cout << "+inff" << std::endl;
		else
			std::cout << "-inff" << std::endl;
		return;
	}
	std::cout << f;
	//if (f == static_cast<int>(f))
	//	std::cout << ".0";
	std::cout << "f" << std::endl;
}
static void		printDouble(double value)
{
	std::cout << "double: ";
	if (std::isnan(value))
	{
		std::cout << "nan" << std::endl;
		return;
	}
	if (std::isinf(value))
	{
		if (value > 0)
			std::cout << "+inf" << std::endl;
		else
			std::cout << "-inf" << std::endl;
		return;
	}
	std::cout << value;
	//if (value == static_cast<int>(value))
	//	std::cout << ".0";
	std::cout << std::endl;
}

void	ScalarConverter::convert(std::string &literal)
{
	LiteralType type = detectType(literal);
	if (type == TYPE_INVALID)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	double value = parseToDouble(literal, type);
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}