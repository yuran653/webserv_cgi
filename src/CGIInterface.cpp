/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:44 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/18 19:31:10 by jgoldste         ###   ########.fr       */
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

char** CGIInterface::_initEnv() {
	char** envp = new char*[4];
	envp[0] = new char[std::strlen("REQUEST_METHOD=POST") + 1];
	std::strcpy(envp[0], "REQUEST_METHOD=POST");
	envp[1] = new char[std::strlen("SERVER_PROTOCOL=HTTP/1.1") + 1];
	std::strcpy(envp[1], "SERVER_PROTOCOL=HTTP/1.1");
	envp[2] = new char[std::strlen("PATH_INFO=/directory/youpi.bla") + 1];
	std::strcpy(envp[2], "PATH_INFO=/directory/youpi.bla");
	envp[3] = NULL;
	return envp;
}

char** CGIInterface::_initArgv(const std::string& cgi_pass) {
	char** argv = new char*[2];
	argv[0] = new char[cgi_pass.size()];
	std::strcpy(argv[0], cgi_pass.c_str());
	argv[1] = NULL;
	return argv;
}

size_t CGIInterface::_setBufSize() {
	size_t buff_size = BUFF_SIZE > sizeof(DBL_CRLF) - 1 ? BUFF_SIZE : sizeof(DBL_CRLF) - 1;
	buff_size = buff_size > MAX_HTTP_HDR - 1 ? MAX_HTTP_HDR : buff_size;
	return (buff_size);
}

int CGIInterface::_execute(std::string& header, std::string& body_path,
		const std::string& cgi_pass, const int& file_fd) {
	body_path = "./response_tmp";
	int exit_status = 502;
	char** argv = _initArgv(cgi_pass);
	char** envp = _initEnv();
	if (argv == NULL || envp == NULL)
		return _deleteServiceArgs(argv, envp, exit_status);
	if (dup2(file_fd, STDIN_FILENO) == -1)
		return _deleteServiceArgs(argv, envp, exit_status);
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
		return _deleteServiceArgs(argv, envp, exit_status);
	pid_t pid = fork();
	if (pid == -1)
		return _deleteServiceArgs(argv, envp, exit_status);
	else if (pid == 0) {
		close(pipe_fd[0]);
		dup2(pipe_fd[1],STDOUT_FILENO);
		if (execve(argv[0], argv, envp) == -1)
			exit(_deleteServiceArgs(argv, envp, exit_status));
	} else if (pid > 0) {
		close(pipe_fd[1]);
		int response_fd = open(body_path.c_str(), O_WRONLY | O_CREAT | O_EXCL | O_APPEND, 0644);
		if (response_fd == -1)
			return (_deleteServiceArgs(argv, envp, 500));
		if (fcntl(response_fd, F_SETFL, O_NONBLOCK) == -1) {
			close(response_fd);
			return (_deleteServiceArgs(argv, envp, 413));
		}
		size_t buff_size = _setBufSize();
		char* buff = new char[buff_size + 1];
		std::memset(buff, '\0', buff_size + 1);
		size_t pos = std::string::npos;
		while (read(pipe_fd[0], buff, buff_size)) {
			if (header.size() > MAX_HTTP_HDR) {
				header.clear();
				delete[] buff;
				close(response_fd);
				std::remove(body_path.c_str());
				return (_deleteServiceArgs(argv, envp, 431));
			}
			std::string buff_read(buff);
			header += buff_read;
			pos = header.find(DBL_CRLF);
			if (pos != std::string::npos) {
				header.erase(pos + sizeof(DBL_CRLF) - 1);
				if (header.size() > MAX_HTTP_HDR) {
					header.clear();
					delete[] buff;
					close(response_fd);
					std::remove(body_path.c_str());
					return (_deleteServiceArgs(argv, envp, 431));
				}
				write(response_fd, buff + pos + sizeof(DBL_CRLF), pos + sizeof(DBL_CRLF));
				std::memset(buff, '\0', buff_size + 1);
				break;
			}
			std::memset(buff, '\0', buff_size + 1);
		}
		size_t read_size;
		while ((read_size = read(pipe_fd[0], buff, buff_size))) {
			write(response_fd, buff, read_size);
			std::memset(buff, '\0', buff_size + 1);
		}
		close(pipe_fd[0]);
		close(response_fd);
		delete[] buff;
		int status;
		while (waitpid(-1, &status, WUNTRACED) == -1)
			;
		if (WEXITSTATUS(status) != EXIT_FAILURE || WIFEXITED(status) == EXIT_SUCCESS) // <---
			exit_status = 200;
	}
	(void)body_path;
	return _deleteServiceArgs(argv, envp, exit_status);
}

int	CGIInterface::executeCGI(std::string& header, std::string& body_path,
			const std::string& cgi_pass, const std::string& body_temp_path) {
	int code;
	int file_fd;
	file_fd = open(cgi_pass.c_str(), O_RDONLY);
	if (file_fd == -1)
		return 502;
	close(file_fd);
	file_fd = open(body_temp_path.c_str(), O_RDONLY);
	if (file_fd == -1)
		return 500;
	if (fcntl(file_fd, F_SETFL, O_NONBLOCK) == -1) {
		close(file_fd);
		return 413;
	}
	code = _execute(header, body_path, cgi_pass, file_fd);
	close(file_fd);
	return code;
}
