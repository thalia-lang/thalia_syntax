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

#include "thalia/syntax/lexer/lexer_content.hpp"

namespace thalia::syntax {
	extern void lexer_content::skip_whitespaces() {
		while (true) {
			switch (*(*this)) {
				case ' ':
				case '\r':
				case '\t': {
					++_index;
					break;
				}
				case '\n': {
					++_line;
					++_index;
					break;
				}
				default: return;
			}
		}
	}
}
