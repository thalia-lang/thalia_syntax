#include <iostream>
#include <memory>

#include "thalia/syntax/ast.hpp"
#include "thalia/syntax/exprs.hpp"
#include "thalia/syntax/node.hpp"

#include "termcolor.hpp"
#include "ast_expr_view.hpp"

extern int main() {
	std::cout << termcolor::white;

	using namespace thalia::syntax;
	demo::ast_expr_view view(std::cout);
	view.visit(
		std::make_shared<expression>(expression {
			assignment_expression {
				std::make_shared<expression>(expression {
					identifier_expression {
						token(TknId,	"x", 1, 0)
					}
				}),
				std::make_shared<expression>(expression {
					binary_expression {
						token(TknPlus, "+", 1, 0),
						std::make_shared<expression>(expression {
							literal_expression {
								token(TknInt, "21", 1, 0)
							}
						}),
						std::make_shared<expression>(expression {
							unary_expression {
								token(TknMinus, "-", 1, 0),
								std::make_shared<expression>(expression {
									call_expression {
										std::make_shared<expression>(expression {
											identifier_expression {
												token(TknId, "rand_int", 1, 0)
											}
										}),
										std::vector<std::shared_ptr<expression>> {
											std::make_shared<expression>(expression {
												literal_expression {
													token(TknInt, "0", 1, 0)
												}
											}),
											std::make_shared<expression>(expression {
												literal_expression {
													token(TknInt, "10", 1, 0)
												}
											})
										}
									}
								})
							}
						})
					}
				})
			}
		})
	);

	std::cout << '\n';
	return 0;
}
