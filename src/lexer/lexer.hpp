/* Lexer - Thalia lexical analyzer
 * Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Thalia.
 *
 * Thalia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef THALIA_SYNTAX_LEXER
#define THALIA_SYNTAX_LEXER

#include <cstddef>
#include <string>
#include <vector>
#include <utility>

#include "thalia/syntax/token.hpp"
#include "thalia/syntax/exception.hpp"

#include "content.hpp"

namespace thalia::syntax {
	class lexer {
		public:
			using tokens = std::vector<token>;
			using exceptions = std::vector<exception>;

		public:
			lexer(const std::string& code)
				: _code(code), _errors() {}

			std::pair<tokens, exceptions> scan();

		private:
			content _code;
			std::vector<exception> _errors;

		private:
			token next_token();

			token make_keyword_or_id();
			token make_number();
			token choose_token(char, token_type, token_type);
			token assert_token(char, token_type);

			bool is_digit(char ch) const {
				return ch >= '0' && ch <= '9';
			}

			bool is_alphanum(char ch) const {
				return is_alpha(ch) || is_digit(ch);
			}

			bool is_alpha(char ch) const {
				return ch == '_' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
			}

			token make_token(token_type type) const {
				return token(type, _code.line(), _code.position());
			}
	};
}

#endif // THALIA_SYNTAX_LEXER
