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

#ifndef THALIA_SYNTAX_PARSER_CONTENT
#define THALIA_SYNTAX_PARSER_CONTENT

#include <cstddef>
#include <vector>

#include "thalia/syntax/token.hpp"

namespace thalia::syntax {
	class parser_content {
		public:
			parser_content(const std::vector<token>& target)
				: _target(target), _index(0) {}

			bool at_end() const { return _target[_index].type == TknEnd; }
			bool check(token_type type) const { return !at_end() && _target[_index].type == type; }

			const token& operator*() const { return _target[_index]; }

			bool match(std::vector<token_type> types);
			void advance(std::size_t size = 1);

		private:
			const std::vector<token>& _target;
			std::size_t _index;
	};
}

#endif // THALIA_SYNTAX_PARSER_CONTENT
