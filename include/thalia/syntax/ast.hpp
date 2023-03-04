/* AST - Thalia abstract syntax tree nodes
 * Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
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

#ifndef THALIA_SYNTAX_AST
#define THALIA_SYNTAX_AST

#include <variant>

#include "thalia/syntax/exprs.hpp"

namespace thalia::syntax {
	enum expr_type {
		ExprLiteral,
		ExprGrouping,
		ExprCall,
		ExprUnary,
		ExprBinary,
		ExprAssignment,
		ExprIdentifier
	};

	struct expression {
		expr_type type;
		std::variant<
			literal_expression,
			grouping_expression,
			call_expression,
			unary_expression,
			binary_expression,
			assignment_expression,
			identifier_expression
		> target;

		expression(literal_expression value)
			: type(ExprLiteral), target(value) {}

		expression(grouping_expression value)
			: type(ExprGrouping), target(value) {}

		expression(call_expression value)
			: type(ExprCall), target(value) {}

		expression(unary_expression value)
			: type(ExprUnary), target(value) {}

		expression(binary_expression value)
			: type(ExprBinary), target(value) {}

		expression(assignment_expression value)
			: type(ExprAssignment), target(value) {}

		expression(identifier_expression value)
			: type(ExprIdentifier), target(value) {}
	};
}

#endif // THALIA_SYNTAX_AST
