/* Exception - Thalia syntax exceptions
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

#ifndef THALIA_SYNTAX_EXCEPTION
#define THALIA_SYNTAX_EXCEPTION

#include <stdexcept>

#include "thalia/syntax/token.hpp"

namespace thalia::syntax {
	class exception: public std::runtime_error {
		public:
		  exception(const char* message, const token token)
				: std::runtime_error(message), _target(token) {}

			token where() const noexcept { return _target; }

		private:
			const token _target;
	};

	class unexpected_character: public exception {
		public:
			unexpected_character(const token token)
				: exception("Unexpected character.", token) {}
	};
}

#endif // THALIA_SYNTAX_EXCEPTION
