/*
 * Onur is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Onur is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Onur. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "actions.hpp"
#include "globals.hpp"
#include "project.hpp"
#include "repository.hpp"

class Commands
{
public:
  Commands ();

  Globals globals;
  Actions actions;
  Repository repository;

  auto grab (void) -> void;
  auto backup (void) -> void;
  auto printProjectInfo (Project projekt) -> void;
};

#endif // COMMANDS_H_
