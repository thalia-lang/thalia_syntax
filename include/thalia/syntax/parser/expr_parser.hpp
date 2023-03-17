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

#ifndef THALIA_SYNTAX_EXPR_PARSER
#define THALIA_SYNTAX_EXPR_PARSER

#include <utility>
#include <vector>

#include "thalia/syntax/ast.hpp"
#include "thalia/syntax/node.hpp"
#include "thalia/syntax/parser/parser_content.hpp"

namespace thalia::syntax {
	class expr_parser {
		public:
			enum signal_type {
				SgnExpectId
			};

			struct signal {
				signal_type type;
				token target;

				signal(token token)
					: type(SgnExpectId), target(token) {}

				signal(token token, signal_type type)
					: type(type), target(token) {}
			};

		public:
			expr_parser(parser_content& content)
				: _content(content) {}

			std::pair<node<expression>, std::vector<signal>> parse();

		private:
			parser_content& _content;
			std::vector<signal> _signals;

		private:
			node<expression> parse_assignment();
			node<expression> parse_logic_or();
			node<expression> parse_literal();
			node<expression> parse_grouping();
			node<expression> parse_term();
			node<expression> parse_factor();
			node<expression> parse_unary();
			node<expression> parse_primary();
			node<expression> parse_call();
			node<expression> parse_identifier();
	};
}

#endif // THALIA_SYNTAX_EXPR_PARSER
