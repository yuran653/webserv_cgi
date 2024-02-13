/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:44 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/13 18:45:47 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIInterface.hpp"

CGIInterface::CGIInterface() {
}

CGIInterface::~CGIInterface() {
}

void CGIInterface::_deleteCharArray(char**& array) {
	if (array != NULL) {
		for (size_t i = 0; array[i]; i++)
			delete[] array[i];
		delete[] array;
		array = NULL;
	}
}

int CGIInterface::_deleteServiceArgs(char**& argv, char**& envp, const int& status) {
	_deleteCharArray(argv);
	_deleteCharArray(envp);
	return status;
}

char** CGIInterface::_initEnv(const std::string& cgi_pass, const std::string& body_temp_path) {
	char** envp = new char*[2];
	envp[0] = new char[cgi_pass.size() + 1];
	std::strcpy(envp[0], (("PATH=" + cgi_pass).erase(5, 1)).c_str());
	std::cout << "ENVP -> " << envp[0] << std::endl;
	envp[1] = NULL;
	(void)body_temp_path;
	return envp;
}

char** CGIInterface::_initArgv(const std::string& cgi_pass) {
	char** argv = new char*[2];
	argv[0] = new char[cgi_pass.size()];
	std::string tmp_cgi_pass(cgi_pass);
	std::strcpy(argv[0], (tmp_cgi_pass.erase(0, 1)).c_str());
	std::cout << "ARGV ->" << argv[0] << std::endl;
	argv[1] = NULL;
	return argv;
}

int	CGIInterface::_execute(std::pair<int, std::string>& response,
	const std::string& cgi_pass, const std::string& body_temp_path,
	const int& code) {
	char** argv = _initArgv(cgi_pass);
	char** envp = _initEnv(cgi_pass, body_temp_path);
	if (argv == NULL || envp == NULL)
		return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
	response = std::make_pair(code, "OK");
	int fd[2];
	if (pipe(fd) == -1)
		return 1;
	pid_t pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0) {
		int file_fd = open(body_temp_path.c_str(), O_RDONLY);
		if (file_fd == -1)
			return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
		dup2 (file_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(file_fd);
		close(fd[1]);
		close(fd[0]);
		if (execve(argv[0], argv, envp) == -1)
			return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
	} else {
		close(fd[1]);
			
		
		
		int status;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) == false)
			return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
		response.first = 200;
	}
	return _deleteServiceArgs(argv, envp, EXIT_SUCCESS);
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
