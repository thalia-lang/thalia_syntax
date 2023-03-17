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

#ifndef THALIA_SYNTAX_EXPRS
#define THALIA_SYNTAX_EXPRS

#include "thalia/syntax/token.hpp"
#include "thalia/syntax/node.hpp"

namespace thalia::syntax {
	struct expression;

  struct literal_expression {
    token value;

		literal_expression(token value)
			: value(value) {}
  };

	struct grouping_expression {
    node<expression> value;

		grouping_expression(node<expression> value)
			: value(value) {}
  };

	struct call_expression {
		node<expression> target;
    nodes<expression> arguments;

		call_expression(node<expression> target, nodes<expression> args)
			: target(target), arguments(args) {}
	};

	struct unary_expression {
		token operation;
		node<expression> value;

		unary_expression(token op, node<expression> value)
			: operation(op), value(value) {}
  };

	struct binary_expression {
		token operation;
		node<expression> left;
		node<expression> right;

		binary_expression(token op, node<expression> left, node<expression> right)
			: operation(op), left(left), right(right) {}
	};

	struct assignment_expression {
		node<expression> lvalue;
		node<expression> rvalue;

		assignment_expression(node<expression> lvalue, node<expression> rvalue)
			: lvalue(lvalue), rvalue(rvalue) {}
	};

	struct identifier_expression {
		token name;

		identifier_expression(token name)
			: name(name) {}
	};
}

#endif // THALIA_SYNTAX_EXPRS
