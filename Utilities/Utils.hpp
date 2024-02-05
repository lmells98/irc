/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:00:31 by lmells            #+#    #+#             */
/*   Updated: 2024/02/05 12:04:20 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string.h>
# include <stdio.h>

# include <exception>
# include <string>

# define PAD_WITH_CHAR '='

static std::string	centerStringInTextField(size_t fieldWidth, const std::string &str, const char padWithChar = PAD_WITH_CHAR)
{
	size_t	stringLength = str.size();
	if (fieldWidth <= stringLength)
		return (str);

	size_t	difference = fieldWidth - stringLength;
	size_t	paddingLeft = difference / 2;
	size_t	paddingRight = difference - paddingLeft;
	return (std::string(paddingLeft, padWithChar) + str + std::string(paddingRight, padWithChar));
}

namespace IRC
{
	static int	ExitCode;

	class LogConfig
	{
		private:
			enum FieldWidth { ACTION = 80, RESULT = 21, DIVIDER = 2 };

			const std::string	c_prefix;
			const std::string	c_fillLine;

			LogConfig(void) {}
			LogConfig(const std::string &name) : c_prefix(centerStringInTextField(name.size() + 4, "[" + name + "]")),
												 c_fillLine(std::string(ACTION + DIVIDER + RESULT, PAD_WITH_CHAR)) { }

		public:			
			~LogConfig(void) {}

			static LogConfig	initialise(void) { return LogConfig(); }
			static LogConfig	initialise(const std::string &prefixContent) { return (LogConfig(prefixContent)); }

			inline std::string	getPrefix(void) const { return c_prefix; };
			inline std::string	fillLine(const char padWithChar = PAD_WITH_CHAR) const
			{
				if (padWithChar == PAD_WITH_CHAR)
					return (c_fillLine);
				return (std::string(ACTION + RESULT, padWithChar));
			};

			inline size_t		getLineLength(void) const { return (ACTION + DIVIDER + RESULT); }
			inline size_t		getActionFieldWidth(void) const { return (ACTION); }
			inline size_t		getResultFieldWidth(void) const { return (RESULT); }

	};


	inline static std::runtime_error	RuntimeError(int exitCode, const std::string &message, bool printErrnoMessage = false)
	{
		IRC::ExitCode = exitCode;
		std::string	outputBuffer = "Runtime Error! " + message;

		if (printErrnoMessage)
		{
			char *errnoMessage = NULL;
			switch (errno != 0)
			{
				case 1:
					sprintf(errnoMessage, "(%d) %s", errno, strerror(errno));
					outputBuffer.append(errnoMessage);
					break;
			
				default:
					outputBuffer.append("Cannot print errno message because errno value was not set!");
					break;
			}
		}
		return (std::runtime_error(outputBuffer));
	}
}

#endif
