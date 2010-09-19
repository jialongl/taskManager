#include <sstream>

class Parser{

 private:
  vector <string> args;
  vector <string>::iterator iter;
  Command *cmd;

 public:

  /* Parser() { */
  /* } */

  void tokenize(string s) {
    stringstream ss(s);
    string buf;
    while ( ss >> buf ) {
      if (buf[0] == '"')
	continue;

      args.push_back(buf);
    }
  }


  void add_parse() {
    cmd->method = ADD;
    cmd->taskDescription = args[1];

    for(iter = args.begin(); iter < args.end(); iter++ ) {
      if ( *iter == "-t" ) {
	cmd->deadline = StringToNum(*(iter + 1));
      }

      else if ( *iter == "-p" ) {
	cmd->priority = StringToNum(*(iter + 1));
      }

      else if ( *iter == "-g" ) {
	cmd->group = *(iter + 1);
      }

      /* else if ( *iter == "-c" ) */
    }
  }

  void edit_parse() {
    cmd->method = EDIT;
  }

  void rm_parse() {
    cmd->method = RM;
  }

  void ls_parse() {
    cmd->method = LS;
    cmd->serialNumberList.push_back(StringToNum(args[1]));
  }

  void pri_parse() {
    cmd->method = PRI;
    cmd->serialNumberList.push_back(StringToNum(args[1]));
    cmd->priority = StringToNum(args[2]);
  }

  void finish_parse() {
    cmd->method = FINISH;
  }

  void export_parse() {
    cmd->method = EXPORT;
  }

  void import_parse() {
    cmd->method = IMPORT;
  }

  void task_parse() {
    cmd->method = TASK;
    cmd->serialNumberList.push_back(StringToNum(args[1]));
  }


  Command *inputToCommand (char *input) {
    string s = string(input);
    tokenize(s);

    delete cmd;
    cmd = new Command();

    if (args[0] == "exit")
      throw EXCEPTION_HALT;

    else if (args[0] == "add")
      add_parse();

    else if (args[0] == "edit")
      edit_parse();

    else if (args[0] == "rm")
      rm_parse();

    else if (args[0] == "ls")
      ls_parse();

    else if (args[0] == "pri")
      pri_parse();

    else if (args[0] == "finish")
      finish_parse();

    else if (args[0] == "export")
      export_parse();

    else if (args[0] == "import")
      import_parse();

    else if (args[0] == "task")
      task_parse();

    args.clear();
    return cmd;
  }

  string resultToOutput(Result *result){
    return string("Test");
  }
};

Parser *parser;
