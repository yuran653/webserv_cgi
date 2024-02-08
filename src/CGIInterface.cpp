/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIInterface.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:40:44 by jgoldste          #+#    #+#             */
/*   Updated: 2024/02/08 16:50:44 by jgoldste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGIInterface.hpp"

CGIInterface::CGIInterface() {
}

CGIInterface::~CGIInterface() {
}

// char** CGIInterface::_initEnv() {

// }

void CGIInterface::_checkPath(const std::string& path) {
	std::ofstream os(path, std::ios::out | std::ios::trunc);
	if (os.is_open() == false)
		throw CGIInterfaceError("Failed to open: [" + path + "] file");
}

// char** CGIInterface::_initCGIArgv(const std::string& cgi_pass, const std::string& body_temp_path) {
	
// }

std::string	CGIInterface::executeCGI(const std::string& cgi_pass, const std::string& body_temp_path) {
	_checkPath(cgi_pass);
	_checkPath(body_temp_path);
	
}
