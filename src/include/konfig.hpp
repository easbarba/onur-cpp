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

#pragma once

#include <list>
#include <map>

#include <nlohmann/json.hpp>

#include "project.hpp"

class Konfig
{
public:
  Konfig ();

  Konfig (std::string name, std::map<std::string, std::list<Project>> topics)
      : name (name), topics (topics) {};

  std::string name;
  std::map<std::string, std::list<Project>> topics;

  void
  to_json (nlohmann::json &j, const Konfig &k)
  {
    j = nlohmann::json { { "name", k.name }, { "topics", k.topics } };
  }
};
