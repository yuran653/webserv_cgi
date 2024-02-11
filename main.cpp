/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:41:53 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/11 15:39:59 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIInterface.hpp"

#define RED "\033[1;31m"
#define RESET_RED "\033[0m"

int main() {
	std::string path = "./cgi-bin/cgi-tester";
	std::string body_temp_path = "./cgi-bin/temp_body";
	std::pair<int, std::string> response;
	CGIInterface::executeCGI(response, path, body_temp_path);
		std::cout << "Return code: [" << response.first << "]" << std::endl
			<< "Response body: [" << response.second << "]" << std::endl; 
	// std::string cgi_response = "./.response";
	// std::ofstream output_file(cgi_response, std::ios::out | std::ios::trunc);
	// if (output_file.is_open() == false) {
	// 	std::cerr << RED "Error: " RESET_RED "failed to open: [" + cgi_response + "] file" << std::endl;
	// 	return 1;
	// }
	// try {
	// 	output_file << CGIInterface::executeCGI(path, body_temp_path);
	// } catch (const CGIInterface::CGIInterfaceError& e) {
	// 	std::cerr << RED "Error: " RESET_RED << e.what() << std::endl;
	// 	return 1;
	// }
	return 0;
}
