/* Author: Liu Jialong */

#ifndef ParserH
#define ParserH

#include "includes.h"
#include "Command.h"

class Parser{

 private:
  vector <string> args;
  vector <string>::iterator iter;

  map <string, string> commandAliases;
  map <string, string>::iterator iter2;

  Command *cmd;

  void parse_date (string s, long *seconds);
  string matchAlias(string alias);
  string trimHeadTailInvertedCommas(string s);

 public:
  void tokenize_by_pipe(string s);
  void tokenize_by_space (string s);
  void add_parse();
  void edit_parse();
  void rm_parse();
  void ls_parse();
  void pri_parse();
  void finish_parse();
  void export_parse();
  void import_parse();
  void task_parse();
  void map_parse();
  Command *inputToCommand (string input);
  CommandList inputToCommandList (string input);
  string resultToOutput(Result *result);
};

Parser *parser;

#endif
