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

#include <string>

#include "CLI/Option.hpp"
#include <CLI/CLI.hpp>

#include "include/commands.hpp"
#include "include/misc.hpp"

using std::string;

auto
main (int argc, char *argv[]) -> int
{
  CLI::App app{ "Easily manage multiple FLOSS repositories." };
  app.require_subcommand (1);
  argv = { app.ensure_utf8 (argv) };

  string filename{ "default" };
  app.add_option ("-f,--file", filename, "A help string");
  app.set_version_flag ("--version", string ("0.2.0"));

  CLI::App *grab_cmd{ app.add_subcommand ("grab", "grab all projects") };
  CLI::App *backup_cmd{ app.add_subcommand (
      "backup", "compress all selected projects") };

  CLI::App *config_cmd{ app.add_subcommand ("config",
                                            "manage configurations") };
  std::string config_edit;
  ConfigEntries edit;
  config_cmd
      ->add_option ("config", config_edit, "Configuration name and topic")
      ->required (true);
  config_cmd->add_option ("name", edit.name, "Project name");
  config_cmd->add_option ("url", edit.url, "Project url");
  config_cmd->add_option ("branch", edit.branch, "Project branch");

  CLI11_PARSE (app, argc, argv);

  Commands commands;

  if (*grab_cmd)
    commands.grab ();

  if (*backup_cmd)
    commands.backup ();

  if (*config_cmd)
    commands.config (config_edit, edit);

  return 0;
}
