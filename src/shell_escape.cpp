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

#include "shell_escape.hpp"

#include <ios>
#include <iomanip>
#include <ostream>


ShellEscape::ShellEscape(std::ostream& out) :
  m_out(out),
  m_quote_state(QuoteState::INITIAL)
{}

void
ShellEscape::print_quoted(char* const text_cstr)
{
  for (int i = 0; text_cstr[i] != '\0'; ++i) {
    emit(text_cstr[i]);
  }
  close_quote();
}

void
ShellEscape::emit(char c)
{
  if (requires_ansic(c)) {
    open_regular_quote();
    print_char(c);
  } else {
    open_ansic_quote();
    print_char(c);
  }
}

bool
ShellEscape::requires_ansic(char c)
{
  return isprint(c) && c != '\\' && c != '\'';
}

void
ShellEscape::print_char(char c)
{
  if (c == '\\') {
    m_out << "\\\\";
  } else if (c == '\'') {
    m_out << "\\'";
  } else if (c == '\a') {
    m_out << "\\a";
  } else if (c == '\b') {
    m_out << "\\b";
  } else if (c == '\e') {
    m_out << "\\e";
  } else if (c == '\f') {
    m_out << "\\f";
  } else if (c == '\n') {
    m_out << "\\n";
  } else if (c == '\r') {
    m_out << "\\r";
  } else if (c == '\t') {
    m_out << "\\t";
  } else if (c == '\v') {
    m_out << "\\v";
  } else if (isprint(c)) {
    m_out << c;
  } else {
    m_out << '\\' << std::oct << std::setfill('0') << std::setw(3) << static_cast<int>(static_cast<unsigned char>(c));
  }
}

void
ShellEscape::open_regular_quote()
{
  switch (m_quote_state)
  {
    case QuoteState::INITIAL:
      m_out << '\'';
      m_quote_state = QuoteState::REGULAR;
      break;

    case QuoteState::REGULAR:
      // do nothing
      break;

    case QuoteState::ANSIC:
      m_out << '\'';
      m_out << '\'';
      m_quote_state = QuoteState::REGULAR;
      break;
  }
}

void
ShellEscape::open_ansic_quote()
{
  switch (m_quote_state)
  {
    case QuoteState::INITIAL:
      m_out << "$'";
      m_quote_state = QuoteState::ANSIC;
      break;

    case QuoteState::REGULAR:
      m_out << '\'';
      m_out << "$'";
      m_quote_state = QuoteState::ANSIC;
      break;

    case QuoteState::ANSIC:
      // do nothing
      break;
  }
}

void
ShellEscape::close_quote()
{
  switch (m_quote_state)
  {
    case QuoteState::INITIAL:
      m_out << "''";
      break;

    case QuoteState::REGULAR:
      m_out << '\'';
      m_quote_state = QuoteState::INITIAL;
      break;

    case QuoteState::ANSIC:
      m_out << '\'';
      m_quote_state = QuoteState::INITIAL;
      break;
  }
}

/* EOF */
