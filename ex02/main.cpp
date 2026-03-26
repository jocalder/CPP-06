/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:59:04 by jocalder          #+#    #+#             */
/*   Updated: 2026/03/26 10:01:10 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main()
{
    std::srand(std::time(0));

    Base* ptr = generate();

    std::cout << "identify(Base*): ";
    identify(ptr);

    std::cout << "identify(Base&): ";
    identify(*ptr);

    delete ptr;
    return 0;
}