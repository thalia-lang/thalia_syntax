#ifndef THALIA_DEMO_AST_EXPR_VIEW
#define THALIA_DEMO_AST_EXPR_VIEW

#include <cstddef>
#include <ostream>
#include <string>
#include <functional>

#include "thalia/syntax/ast.hpp"
#include "thalia/syntax/exprs.hpp"
#include "thalia/syntax/node.hpp"

namespace demo {
	class ast_expr_view {
		private:
			using expr_node = thalia::syntax::node<thalia::syntax::expression>;
			using literal_expression = thalia::syntax::literal_expression;
			using grouping_expression = thalia::syntax::grouping_expression;
			using call_expression = thalia::syntax::call_expression;
			using unary_expression = thalia::syntax::unary_expression;
			using binary_expression = thalia::syntax::binary_expression;
			using assignment_expression = thalia::syntax::assignment_expression;
			using identifier_expression = thalia::syntax::identifier_expression;

		public:
			ast_expr_view(std::ostream& out): _out(out) {}

			void visit(expr_node node, std::size_t deep = 0);

		private:
			std::ostream& _out;

		private:
			void visit_literal(const literal_expression&, std::size_t = 0);
			void visit_grouping(const grouping_expression&, std::size_t = 0);
			void visit_call(const call_expression&, std::size_t = 0);
			void visit_unary(const unary_expression&, std::size_t = 0);
			void visit_binary(const binary_expression&, std::size_t = 0);
			void visit_assignment(const assignment_expression&, std::size_t = 0);
			void visit_identifier(const identifier_expression&, std::size_t = 0);

			void print_node(const char*, std::size_t, bool, std::function<void()>);

			std::string tab(std::size_t size = 0) { return std::string(2 * size, ' '); }
	};
}

#endif // THALIA_DEMO_AST_EXPR_VIEW
