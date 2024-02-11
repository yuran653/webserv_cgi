/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:47 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/12 02:49:50 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIINTERFACE_HPP
#define CGIINTERFACE_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

class CGIInterface {
	private:
		CGIInterface();
		~CGIInterface();

		static int	_checkFile(std::pair<int, std::string>& response,
			const std::string& path, const int& code);
		static int	_execute(std::pair<int, std::string>& response,
			const std::string& cgi_pass, const std::string& body_temp_path, const int& code);

	public:
		static void	executeCGI(std::pair<int, std::string>& response,
			const std::string& cgi_pass, const std::string& body_temp_path);

		struct CGIInterfaceError : public std::runtime_error {
			CGIInterfaceError(const std::string& message) : std::runtime_error(message) {}
		};
};

#endif
