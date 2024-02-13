/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:47 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/13 18:16:35 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIINTERFACE_HPP
#define CGIINTERFACE_HPP

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

class CGIInterface {
	private:
		CGIInterface();
		~CGIInterface();

		static int		_checkFile(std::pair<int, std::string>& response,
			const std::string& path, const int& code);
		static int		_execute(std::pair<int, std::string>& response,
			const std::string& cgi_pass, const std::string& body_temp_path, const int& code);
		static char**	_initArgv(const std::string& cgi_pass);
		static char**	_initEnv(const std::string& cgi_pass, const std::string& body_temp_path);
		static int		_deleteServiceArgs(char**& argv, char**& envp, const int& status);
		static void		_deleteCharArray(char**& array);

	public:
		static void	executeCGI(std::pair<int, std::string>& response,
			const std::string& cgi_pass, const std::string& body_temp_path);

		struct CGIInterfaceError : public std::runtime_error {
			CGIInterfaceError(const std::string& message) : std::runtime_error(message) {}
		};
};

#endif
