/* Lexer - Thalia lexical analyzer
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

#include <utility>
#include <vector>
#include <algorithm>

#include "thalia/syntax/token.hpp"
#include "thalia/syntax/exception.hpp"

#include "lexer.hpp"

namespace thalia::syntax {
	using tokens = std::vector<token>;
	using exceptions = std::vector<exception>;

	struct keyword {
		token_type type;
		std::string value;
	};

	static const keyword keywords[10] = {
		{ TknProgram, "program" },
		{ TknFunc, "function" },
		{ TknLet, "let" },
		{ TknConst, "const"},
		{ TknReturn, "return" },
		{ TknEach, "each"},
		{ TknIn, "in" },
		{ TknWhile, "while" },
		{ TknIf, "if" },
		{ TknElse, "else" }
	};

	extern std::pair<tokens, exceptions> lexer::scan() {
		token current;
		std::vector<token> result;

		_errors.clear();
		result.push_back(current);
		do {
			current = next_token();
			result.push_back(current);
		} while(current.type != TknEnd);

		return std::make_pair(result, _errors);
	}

	extern token lexer::next_token() {
		_code.skip_whitespaces();
		_code.start();

		if (_code.is_eof()) {
			return make_token(TknEnd);
		}

		const char ch = *_code;
		_code.advance();

		if (is_alpha(ch)) {
			return make_keyword_or_id();
		}

		if (is_digit(ch)) {
			return make_number();
		}

		switch (ch) {
			case '(': return make_token(TknOpnParen);
			case ')': return make_token(TknClsParen);
			case '{': return make_token(TknOpnBrace);
			case '}': return make_token(TknClsBrace);
			case '[': return make_token(TknOpnBracket);
			case ']': return make_token(TknClsBracket);
			case ',': return make_token(TknComma);
			case '.': return make_token(TknDot);
			case ':': return make_token(TknColon);
			case ';': return make_token(TknSemi);
			case '-': return make_token(TknMinus);
			case '+': return make_token(TknPlus);
			case '/': return make_token(TknSlash);
			case '*': return make_token(TknStar);
			case '%': return make_token(TknPercent);
			case '=': return choose_token('=', TknEqlEqual, TknEqual);
			case '!': return choose_token('=', TknBngEqual, TknBang);
			case '<': return choose_token('=', TknLssEqual, TknLess);
			case '>': return choose_token('=', TknGrtEqual, TknGreater);
			case '&': return assert_token('&', TknAmpsAmps);
			case '|': return assert_token('|', TknPipePipe);
		}

		token result = make_token(TknUnknown);
		_errors.push_back(unexpected_character(result));
		return result;
	}

	extern token lexer::choose_token(char expected, token_type first, token_type second) {
		if (*_code != expected) {
			return make_token(second);
		}

		_code.advance();
		return make_token(first);
	}

	extern token lexer::assert_token(char expected, token_type type) {
		char ch = *_code;
		_code.advance();

		if (ch != expected) {
			token result = make_token(TknUnknown);
			_errors.push_back(unexpected_character(result));
			return result;
		}

		return make_token(type);
	}

	extern token lexer::make_number() {
		while (is_digit(*_code)) _code.advance();
		return make_token(TknInt);
	}

	extern token lexer::make_keyword_or_id() {
		while (is_alphanum(*_code)) _code.advance();

		std::string value = _code.value();
		const keyword* result = std::find_if(
			std::begin(keywords), std::end(keywords),
			[&](const keyword& target) { return value == target.value; }
		);

		return token(
			result == std::end(keywords) ? TknId : result->type,
			value, _code.line(), _code.position()
		);
	}
}
