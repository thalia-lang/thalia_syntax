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
#include <vector>
#include <algorithm>

#include "thalia/syntax/token.hpp"
#include "thalia/syntax/lexer/lexer.hpp"

namespace thalia::syntax {
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

	static inline bool is_digit(char ch) {
		return ch >= '0' && ch <= '9';
	}

	static inline bool is_alpha(char ch) {
		return ch == '_' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
	}

	static inline bool is_alphanum(char ch) {
		return is_alpha(ch) || is_digit(ch);
	}

	extern std::pair<std::vector<token>, std::vector<lexer::signal>> lexer::scan() {
		if (!_tokens.empty() || !_signals.empty()) {
			return std::make_pair(_tokens, _signals);
		}

		do {
			scan_next();
		} while(!_code.is_eof());
		return std::make_pair(_tokens, _signals);
	}

	extern void lexer::scan_next() {
		_code.skip_whitespaces();
		_code.start();

		if (_code.is_eof()) {
			return push_token(TknEnd);
		}

		const char ch = *_code;
		_code.advance();

		if (is_alpha(ch)) {
			return scan_keyword_or_id();
		}

		if (is_digit(ch)) {
			return scan_number();
		}

		switch (ch) {
			case '(': return push_token(TknOpnParen);
			case ')': return push_token(TknClsParen);
			case '{': return push_token(TknOpnBrace);
			case '}': return push_token(TknClsBrace);
			case '[': return push_token(TknOpnBracket);
			case ']': return push_token(TknClsBracket);
			case ',': return push_token(TknComma);
			case '.': return push_token(TknDot);
			case ':': return push_token(TknColon);
			case ';': return push_token(TknSemi);
			case '-': return push_token(TknMinus);
			case '+': return push_token(TknPlus);
			case '/': return push_token(TknSlash);
			case '*': return push_token(TknStar);
			case '%': return push_token(TknPercent);
			case '=': return scan_with_choice('=', TknEqlEqual, TknEqual);
			case '!': return scan_with_choice('=', TknBngEqual, TknBang);
			case '<': return scan_with_choice('=', TknLssEqual, TknLess);
			case '>': return scan_with_choice('=', TknGrtEqual, TknGreater);
			case '&': return scan_with_assertion('&', TknAmpsAmps);
			case '|': return scan_with_assertion('|', TknPipePipe);
		}

		return push_signal(SgnUnexpChr);
	}

	extern void lexer::scan_with_choice(char expected, token_type first, token_type second) {
		if (*_code != expected) {
			return push_token(second);
		}

		_code.advance();
		return push_token(first);
	}

	extern void lexer::scan_with_assertion(char expected, token_type type) {
		char ch = *_code;
		_code.advance();

		if (ch != expected) {
			return push_signal(SgnUnexpChr);
		}

		return push_token(type);
	}

	extern void lexer::scan_number() {
		while (is_digit(*_code)) _code.advance();
		return push_token(TknInt);
	}

	extern void lexer::scan_keyword_or_id() {
		while (is_alphanum(*_code)) _code.advance();

		std::string value = _code.value();
		const keyword* result = std::find_if(
			std::begin(keywords), std::end(keywords),
			[&](const keyword& target) -> bool { return value == target.value; }
		);

		_tokens.push_back({
			result == std::end(keywords) ? TknId : result->type,
			value, _code.line(), _code.position()
		});
	}

	extern void lexer::push_token(token_type type) {
		_tokens.push_back({ type, _code.value(), _code.line(), _code.position() });
	}

	extern void lexer::push_signal(lexer::signal_type type) {
		token token(TknError, _code.value(), _code.line(), _code.position());
		_signals.push_back({ token, type, _tokens.size() });
	}
}
