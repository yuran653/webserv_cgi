/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:44 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/12 18:58:26 by jgoldste         ###   ########.fr       */
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
	std::strcpy(envp[0], ("PATH=" + cgi_pass.erase(0,2)).c_str());
	envp[1] = NULL;
	(void)body_temp_path;
	return NULL;
}

char** CGIInterface::_initArgv(const std::string& cgi_pass, const std::string& body_temp_path) {
	char** argv = new char*[3];
	argv[0] = new char[cgi_pass.size() + 1];
	std::strcpy(argv[0], cgi_pass.c_str());
	argv[1] = new char[body_temp_path.size() + 1];
	std::strcpy(argv[1], body_temp_path.c_str());
	argv[2] = NULL;
	return argv;
}

int	CGIInterface::_execute(std::pair<int, std::string>& response,
	const std::string& cgi_pass, const std::string& body_temp_path,
	const int& code) {
	char** argv = _initArgv(cgi_pass, body_temp_path);
	char** envp = _initEnv(cgi_pass, body_temp_path);
	std::cout << "argv: " << argv << std::endl;
	std::cout << "argv[0]" << argv[0] << std::endl;
	std::cout << "argv[1]" << argv[1] << std::endl;
	std::cout << "argv[2]" << &argv[2] << std::endl;
	// if (argv == NULL || envp == NULL)
	// 	return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
	std::cout << "--- OK ---" << std::endl;
	response = std::make_pair(code, "OK");
	// int fd[2];
	// if (pipe(fd) == -1)
	// 	return 1;
	// pid_t pid = fork();
	// if (pid == -1)
	// 	return 1;
	// if (pid == 0) {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	if (execve(argv[0], argv, envp) == -1)
	// 		return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
	// } else {
	// 	close(fd[1]);

	
		
	// 	int status;
	// 	waitpid(-1, &status, 0);
	// 	if (WIFEXITED(status) == 0)
	// 		return _deleteServiceArgs(argv, envp, EXIT_FAILURE);
	// 	response.first = 200;
	// }
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
