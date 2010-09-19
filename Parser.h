#include <sstream>

class Parser{

 private:
  vector <string> args;
  Command *cmd;

 public:

  Parser() {
    cmd = new Command();
  }

  void tokenize(string s) {
    stringstream ss(s);
    string buf;
    while ( ss >> buf ) {
      args.push_back(buf);
    }
  }


  void add_parse() {
    cmd->method = ADD;
    cmd->taskDescription = args[1];
  }

  void edit_parse() {
    cmd->method = EDIT;
  }

  void rm_parse() {
    cmd->method = RM;
  }

  void ls_parse() {
    cmd->method = LS;
    /* cmd->sortKeyword.push_back(); */
  }

  void pri_parse() {
    cmd->method = PRI;
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

    return cmd;
  }

  string resultToOutput(Result *result){
    return string("Test");
  }
};

Parser *parser;
