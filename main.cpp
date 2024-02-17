/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:41:53 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/17 18:30:54 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIInterface.hpp"

#define RED "\033[1;31m"
#define RESET_RED "\033[0m"

int main() {
	std::string path = "./cgi-bin/cgi_tester";
	// std::string path = "./cgi-bin/script_env.py";
	// std::string path = "./cgi-bin/script_error.py";
	// std::string path = "./cgi-bin/script_error_exec.py";
	// std::string path = "./cgi-bin/script_print_request.py";
	std::string body_temp_path = "./cgi-bin/temp_body/.temp_cgi_tester";
	// std::string body_temp_path = "./cgi-bin/temp_body/.temp_body";
	// std::string body_temp_path = "./cgi-bin/temp_body/.temp_body_empty";
	// std::string body_temp_path = "./cgi-bin/temp_body/.temp_body_no_access";
	std::string header;
	std::string body_path; (void)body_path;
	int status = CGIInterface::executeCGI(header, body_path, path, body_temp_path);
	std::cout << "Return code: [" << status << "]" << std::endl
		// << "Response body: ->" << std::endl << header << "<-" << std::endl; 
		<< "Response body: ->" << std::endl << header.substr(0, header.find(DBL_CRLF)) + DBL_CRLF << "<-" << std::endl;
	return 0;
}
