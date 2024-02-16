/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:47 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/16 23:52:32 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIINTERFACE_HPP
#define CGIINTERFACE_HPP

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_HTTP_HDR 4096
#define EOF_STR "\0xEOF"

class CGIInterface {
	private:
		CGIInterface();
		~CGIInterface();

		static int		_openFile(const char* path, int& response_code, const int& code);
		static int		_execute(std::string& header, std::string& body_path,
			const std::string& cgi_pass, const int& file_fd);
		static char**	_initArgv(const std::string& cgi_pass);
		static char**	_initEnv();
		static int		_deleteServiceArgs(char**& argv, char**& envp, const int& status);
		static void		_deleteCharArray(char**& array);

	public:
		static int	executeCGI(std::string& header, std::string& body_path,
			const std::string& cgi_pass, const std::string& body_temp_path);

		struct CGIInterfaceError : public std::runtime_error {
			CGIInterfaceError(const std::string& message) : std::runtime_error(message) {}
		};
};

#endif
