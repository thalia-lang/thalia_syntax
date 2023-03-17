#include <cstddef>
#include <functional>
#include <variant>

#include "thalia/syntax/ast.hpp"
#include "thalia/syntax/exprs.hpp"
#include "thalia/syntax/node.hpp"

#include "termcolor.hpp"
#include "ast_expr_view.hpp"

namespace demo {
	using namespace thalia::syntax;

	extern void ast_expr_view::visit(node<expression> node, std::size_t deep) {
		switch (node->type) {
			case ExprLiteral:
				return visit_literal(std::get<literal_expression>(node->target), deep);
			case ExprGrouping:
				return visit_grouping(std::get<grouping_expression>(node->target), deep);
			case ExprCall:
				return visit_call(std::get<call_expression>(node->target), deep);
			case ExprUnary:
				return visit_unary(std::get<unary_expression>(node->target), deep);
			case ExprBinary:
				return visit_binary(std::get<binary_expression>(node->target), deep);
			case ExprAssignment:
				return visit_assignment(std::get<assignment_expression>(node->target), deep);
			case ExprIdentifier:
				return visit_identifier(std::get<identifier_expression>(node->target), deep);
		}
	}

	extern void ast_expr_view::visit_literal(const literal_expression& node, std::size_t deep) {
		return print_node(
			"Literal", deep, false,
			[&]() -> void { _out << '\'' << node.value.target << '\''; }
		);
	}

	extern void ast_expr_view::visit_identifier(const identifier_expression& node, std::size_t deep) {
		return print_node(
			"Identifier", deep, false,
			[&]() -> void { _out << '\'' << node.name.target << '\''; }
		);
	}

	extern void ast_expr_view::visit_grouping(const grouping_expression& node, std::size_t deep) {
		return print_node(
			"Grouping", deep, true,
			[&]() -> void { visit(node.value, deep + 1); }
		);
	}

	extern void ast_expr_view::visit_call(const call_expression& node, std::size_t deep) {
		return print_node(
			"Call", deep, true,
			[&]() -> void {
				visit(node.target, deep + 1);
				for (const auto& argument: node.arguments) {
					_out << '\n';
					visit(argument, deep + 1);
				}
			}
		);
	}

	extern void ast_expr_view::visit_unary(const unary_expression& node, std::size_t deep) {
		return print_node(
			"Unary", deep, true,
			[&]() -> void {
				_out << tab(deep + 1) << "'" << node.operation.target << "'\n";
				visit(node.value, deep + 1);
			}
		);
	}

	extern void ast_expr_view::visit_binary(const binary_expression& node, std::size_t deep) {
		return print_node(
			"Binary", deep, true,
			[&]() -> void {
				_out << tab(deep + 1) << "'" << node.operation.target << "'\n";
				visit(node.left, deep + 1);
				_out << '\n';
				visit(node.right, deep + 1);
			}
		);
	}

	extern void ast_expr_view::visit_assignment(const assignment_expression& node, std::size_t deep) {
		return print_node(
			"Assignment", deep, true,
			[&]() -> void {
				visit(node.lvalue, deep + 1);
				_out << '\n';
				visit(node.rvalue, deep + 1);
			}
		);
	}

	extern void ast_expr_view::print_node(const char* name, std::size_t deep, bool expand, std::function<void()> print_children) {
		_out << tab(deep);
		_out << termcolor::bright_blue << "Expression";
		_out << termcolor::white << "::";
		_out << termcolor::bright_green << name;
		_out << termcolor::white << " { ";

		if (expand) {
			_out << '\n';
			print_children();
			_out << termcolor::white << '\n' << tab(deep) << '}';
		} else {
			print_children();
			_out << termcolor::white << " }";
		}
	}
}
