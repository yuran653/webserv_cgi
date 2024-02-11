/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:44 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/12 02:53:14 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIInterface.hpp"

CGIInterface::CGIInterface() {
}

CGIInterface::~CGIInterface() {
}

int	CGIInterface::_execute(std::pair<int, std::string>& response,
	const std::string& cgi_pass, const std::string& body_temp_path,
	const int& code) {
	(void)cgi_pass;
	(void)body_temp_path;
	response = std::make_pair(code, "OK");
	int fd[2];
	if (pipe(fd) == -1)
		return 1;
	pid_t pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0) {
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		if (execl(cgi_pass.c_str(), body_temp_path.c_str(), NULL) == -1)
			return 1;
	} else {
		close(fd[1]);

	
		
		int status;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) == -1)
			return 1;
			response.first = 200;
	}
	return 0;
}

int CGIInterface::_checkFile(std::pair<int, std::string>& response,
	const std::string& path, const int& code) {
	std::ofstream os(path);
	if (os.is_open() == false) {
		response = std::make_pair(code, "");
		return 1;
	}
	return 0;
}

void CGIInterface::executeCGI(std::pair<int, std::string>& response,
			const std::string& cgi_pass, const std::string& body_temp_path) {
	if (_checkFile(response, cgi_pass, 502))
		return;
	if (_checkFile(response, body_temp_path, 500))
		return;
	_execute(response, cgi_pass, body_temp_path, 502);
}
