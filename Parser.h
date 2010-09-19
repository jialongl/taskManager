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


  /* Command ls_parse (vector<string> args) { */

  /* } */

  void add_parse (vector<string> args) {
    cmd->commandMethod = "add";
    cmd->taskDescription = args[1];
  }

  Command *inputToCommand (char *input){
    string s = string(input);
    tokenize(s);

    if (args[0] == "add")
      add_parse();

    /* else if (args[0] == "edit") */
    /*   return edit_parse(); */

    /* else if (args[0] == "rm") */
    /*   return rm_parse(); */

    /* else if (args[0] == "ls") */
    /*   return ls_parse(); */

    /* else if (args[0] == "pri") */
    /*   return pri_parse(); */

    /* else if (args[0] == "finish") */
    /*   return finish_parse(); */

    /* else if (args[0] == "export") */
    /*   return export_parse(); */

    /* else if (args[0] == "import") */
    /*   return import_parse(); */

    /* else if (args[0] == "task") */
    /*   return task_parse(); */

    return cmd;
  }
  string resultToOutput(Result *result){
    return string("Test");
  }
};

Parser *parser;
