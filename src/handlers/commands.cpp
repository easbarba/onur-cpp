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

#include <filesystem>
#include <format>
#include <iostream>
#include <ostream>
#include <string>

#include "../include/commands.hpp"
#include "../include/globals.hpp"
#include "../include/helpers.hpp"

using std::cout;
using std::endl;
using std::filesystem::exists;
using std::filesystem::path;

Commands::Commands () {}

auto
Commands::grab (void) -> void
{
  for (auto singleConfig : parse.multi ())
    {
      cout << "\n " << singleConfig.name << ":" << endl;

      for (auto topic : singleConfig.topics)
        {
          cout << "  + " << topic.first << endl;
          for (auto project : topic.second)
            {
              auto finalpath{ path (globals.projectsDir / singleConfig.name
                                    / topic.first / project.Name ()) };

              printProjectInfo (project);

              if (exists (finalpath / ".git" / "config"))
                actions.pull (finalpath);
              else
                actions.klone (project, finalpath);
            }

          cout << endl;
        }
    }
}

auto
Commands::backup (void) -> void
{
  cout << "Backing up" << endl;
}

auto
Commands::config (std::string name, ConfigEntries entries) -> void
{
  std::string _name{ name };
  std::optional<std::string> _topic;

  if (name.contains ("."))
    {
      std::size_t dot_positon{ name.find (".") };
      _name = { name.substr (0, dot_positon) };
      _topic = { name.substr (dot_positon + 1) };
    }

  if (_topic.has_value ())
    parse.save (_name, _topic.value (), entries);

  // if (!parse.exist (_name))
  //   {
  //     if (!_topic.has_value ())
  //       {
  //         cout << "Provide a topic, exiting!";
  //       }

  //     cout << std::format ("Config does not exists: {}, imma creating it!",
  //                          name);

  //     parse.save (_name, _topic.value (), entries);

  //     return;
  //   }

  for (auto singleConfig : parse.multi ())
    {
      if (_name == singleConfig.name)
        {
          cout << "\n" << singleConfig.name << ":" << endl;
          for (auto topic : singleConfig.topics)
            {
              if (_topic.has_value () && _topic.value () != topic.first)
                continue;

              cout << " + " << topic.first << endl;

              for (auto project : topic.second)
                printProjectInfo (project);
            }
        }

      std::string m{ std::format ("{} {} {} {}", name,
                                  entries.name.has_value (),
                                  entries.url.has_value (), entries.branch) };
    }
}
