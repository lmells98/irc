/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmells <lmells@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:00:31 by lmells            #+#    #+#             */
/*   Updated: 2024/02/04 18:00:35 by lmells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

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
	static int	ERROR_CODE;
	
	const int	ERROR_NONE = 0;
	const int	ERROR_USAGE = 1;

	class LogConfig
	{
		private:
			enum FieldWidth { ACTION = 80, RESULT = 21 };

			const std::string	c_prefix;
			const std::string	c_fillLine;

			LogConfig(void) {}
			LogConfig(const std::string &name) : c_prefix(centerStringInTextField(name.size() + 4, "[" + name + "]")),
												 c_fillLine(std::string(ACTION + RESULT, PAD_WITH_CHAR)) { }

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

	};
}


#endif
