// argv - Print command line arguments
// Copyright (C) 2022 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_SHELL_ESCAPE_HPP
#define HEADER_SHELL_ESCAPE_HPP

#include <iosfwd>

class ShellEscape
{
private:
  enum QuoteState
  {
    INITIAL,
    REGULAR,
    ANSIC,
  };

public:
  ShellEscape(std::ostream& out);

  void print_quoted(char* const text_cstr);

private:
  void emit(char c);
  bool requires_ansic(char c);
  void print_char(char c);

  void open_regular_quote();
  void open_ansic_quote();
  void close_quote();

private:
  std::ostream& m_out;
  QuoteState m_quote_state;

public:
  ShellEscape(ShellEscape const&) = delete;
  ShellEscape& operator=(ShellEscape const&) = delete;
};

#endif

/* EOF */
