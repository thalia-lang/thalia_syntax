/* Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of ThaliaSyntax.
 *
 * ThaliaSyntax is free software: you can redistribute it and/or modify
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

#include "thalia/syntax/token.hpp"
#include "thalia/syntax/lexer_content.hpp"

namespace thalia::syntax {
	class lexer {
		public:
			enum signal_type {
				SgnUnexpChr
			};

			struct signal {
				signal_type type;
				token target;
				std::size_t index;

				signal(token token, std::size_t index = 0)
					: type(SgnUnexpChr), target(token), index(index) {}

				signal(token token, signal_type type, std::size_t index = 0)
					: type(type), target(token), index(index) {}
			};

		public:
			lexer(const std::string& code)
				: _code(code), _tokens(), _signals() {}

			std::pair<std::vector<token>, std::vector<signal>> scan();

		private:
			lexer_content _code;
			std::vector<token> _tokens;
			std::vector<signal> _signals;

		private:
			void scan_next();
			void scan_keyword_or_id();
			void scan_number();

			void scan_with_choice(char, token_type, token_type);
			void scan_with_assertion(char, token_type);

			void push_token(token_type type);
			void push_signal(signal_type type);
	};
}

#endif // THALIA_SYNTAX_LEXER
