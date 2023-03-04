/* Token - Thalia lexical tokens
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

#ifndef THALIA_SYNTAX_TOKEN
#define THALIA_SYNTAX_TOKEN

#include <cstddef>
#include <string>

namespace thalia::syntax {
	enum token_type {
		TknBegin,

		TknInt,
		TknId,

		TknProgram,
		TknFunc,
		TknLet,
		TknConst,
		TknReturn,
		TknEach,
		TknIn,
		TknWhile,
		TknIf,
		TknElse,

		TknPlus,
		TknMinus,
		TknStar,
		TknSlash,
		TknPercent,
		TknBang,
		TknEqual,
		TknAmpsAmps,
		TknPipePipe,
		TknEqlEqual,
		TknBngEqual,
		TknGreater,
		TknGrtEqual,
		TknLess,
		TknLssEqual,
		TknDot,
		TknComma,
		TknColon,
		TknSemi,
		TknOpnParen,
		TknClsParen,
		TknOpnBracket,
		TknClsBracket,
		TknOpnBrace,
		TknClsBrace,

		TknUnknown,
		TknEnd
	};

	struct token {
		token_type type;
		std::string target;
		std::size_t line;
		std::size_t position;

		token(token_type type, std::string target, std::size_t line, std::size_t pos)
			: type(type)
			, target(target)
			, line(line)
			, position(pos) {}

		token(token_type type, std::size_t line, std::size_t pos)
			: type(type)
			, target()
			, line(line)
			, position(pos) {}

		token(token_type type = TknBegin)
			: type(type)
			, target()
			, line(1)
			, position(0) {}
	};
}

#endif // THALIA_SYNTAX_TOKEN
