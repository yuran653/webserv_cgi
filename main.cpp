/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:41:53 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/14 16:49:14 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIInterface.hpp"

#define RED "\033[1;31m"
#define RESET_RED "\033[0m"

int main() {
	// std::string path = "./cgi-bin/cgi_tester";
	std::string path = "./cgi-bin/script_env.py";
	std::string body_temp_path = "./cgi-bin/temp_body/.temp_body";
	std::pair<int, std::string> response;
	CGIInterface::executeCGI(response, path, body_temp_path);
	std::cout << "Return code: [" << response.first << "]" << std::endl
		<< "Response body: ->[" << response.second << "]<-" << std::endl; 
	return 0;
}
