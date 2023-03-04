/* Content - Content for the lexical analyzer
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

#ifndef THALIA_SYNTAX_CONTENT
#define THALIA_SYNTAX_CONTENT

#include <cstddef>
#include <string>

namespace thalia::syntax {
	class content {
		public:
			content(const std::string& target)
				: _target(target), _line(1), _start(0), _index(0) {}

			void skip_whitespaces();

			bool is_eof() const { return _target[_index] == '\0'; }
			bool is_eol() const { return _target[_index] == '\n'; }

			std::size_t line() const { return _line; }
			std::size_t position() const { return _index; }
			std::string value() const { return _target.substr(_start, _index - _start); }

			void start() { _start = _index; }
			void advance(std::size_t size = 1) { _index += size; }
			void shift(std::size_t size = 1) { _start += size; }

			char operator*() const { return _target[_index]; }
			char operator[](std::size_t index) const { return _target[_index + index]; }

		private:
			const std::string& _target;
			std::size_t _line;
			std::size_t _start;
			std::size_t _index;
	};
}

#endif // THALIA_SYNTAX_CONTENT
