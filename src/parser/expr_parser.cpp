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

#include <utility>

#include "thalia/syntax/ast.hpp"
#include "thalia/syntax/exprs.hpp"
#include "thalia/syntax/node.hpp"
#include "thalia/syntax/token.hpp"
#include "thalia/syntax/parser/expr_parser.hpp"

namespace thalia::syntax {
	static inline bool is_lvalue(const node<expression>& node) {
		return node != nullptr && node->type == ExprIdentifier;
	}

	extern std::pair<node<expression>, std::vector<expr_parser::signal>> expr_parser::parse() {
		node<expression> value(parse_assignment());
		return std::make_pair(value, _signals);
	}

	extern node<expression> expr_parser::parse_assignment() {
		node<expression> value(parse_primary());
		if (!(_content.check(TknEqual) && is_lvalue(value))) {
			return value;
		}

		_content.advance();
		node<expression> rvalue(parse_logic_or());
		return std::make_shared<expression>(
			expression(assignment_expression(value, rvalue))
		);
	}

	extern node<expression> expr_parser::parse_identifier() {
		token token = *_content;
		if (token.type != TknId) {
			_signals.push_back({ token, SgnExpectId });
			return nullptr;
		}

		return std::make_shared<expression>(
			expression(identifier_expression(token))
		);
	}
}
