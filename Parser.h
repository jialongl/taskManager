/* Author: Liu Jialong */

#ifndef ParserH
#define ParserH

#include "includes.h"
#include "Command.h"
#include "Result.h"

class Parser{

 private:
  vector <string> args;
  vector <string>::iterator iter;

  vector <string> commandAliases;
  vector <string> commandOriginals;

  Command *cmd;

  void parse_date (string s, time_t *seconds);
  string matchAlias(string alias);
  string trimInvertedCommas(string s);

 public:
  Parser();
  void tokenize_by_pipe(string s);
  void tokenize_by_space (string s);
  void add_parse();
  void edit_parse();
  void rm_parse();
  void ls_parse();
  void pri_parse();
  void finish_parse();
  void export_parse();
  void write_parse();
  void import_parse();
  void read_parse();
  void task_parse();
  void map_parse();
  void run_parse();
  void undo_parse();
  void redo_parse();
  void sort_parse();
  Command *inputToCommand (string input);
  CommandList inputToCommandList (string input);
  string resultToOutput(Result *result);
};
#endif
