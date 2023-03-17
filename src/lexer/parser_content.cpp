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

#include "thalia/syntax/parser_content.hpp"

namespace thalia::syntax {
	extern void parser_content::advance(std::size_t size) {
		if (_index + size < _target.size()) {
			_index += size;
		} else {
			_index = _target.size();
		}
	}

	extern bool parser_content::match(std::vector<token_type> types) {
		for (token_type type: types) {
			if (check(type)) {
				advance();
				return true;
			}
		}
		return false;
	}
}
