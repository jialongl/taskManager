#include <sstream>

class Parser{

 private:
  vector <string> args;
  vector <string>::iterator iter;
  Command *cmd;

 public:

  Parser() {
    cmd = new Command();
  }

  void tokenize(string s) {
    int pos = 0;
    string buf = "";
    short inInvertedCommas = 0;

    while (pos < s.size() && isspace(s[pos]))
      pos++;

    while (pos < s.size()) {
      if (!isspace(s[pos])) {
	buf += s[pos];

	if (s[pos] == '"') {
	  if(inInvertedCommas == 0)
	    inInvertedCommas = 1;

	  else {
	    inInvertedCommas = 0;
	    args.push_back(buf);
	    buf = "";
	  }
	}
      }

      else {
	if (inInvertedCommas == 1)
	  buf += s[pos];
	else if (buf != "") {
	  args.push_back(buf);
	  buf = "";
	}
      }

      pos++;
    }

    if (buf != "")
      args.push_back(buf); // push in the last argument

    /* for(vector <string>::iterator i = args.begin(); i < args.end(); i++ ) */
    /*   cout << "args[" << *i << "] = " << *i << endl; */
  }

  void add_parse() {
    cmd->method = ADD;
    cmd->group = "\"default\"";

    for(iter = args.begin(); iter < args.end(); iter++ ) {
      if ( *iter == "-t" ) {
	cmd->deadline = currentTime() + StringToNum(*(++iter));
      }

      else if ( *iter == "-p" ) {
	cmd->priority = StringToNum(*(++iter));
      }

      else if ( *iter == "-g" ) {
	cmd->group = *(++iter);
      }

      else if ( (*iter)[0] == '"' && *(iter - 1) != "-g") {
      	cmd->taskDescription = *iter;
      }

      /* else if ( *iter == "-c" ) */
    }
  }

  void edit_parse() {
    cmd->method = EDIT;
    cmd->serialNumberList.push_back( StringToNum(args.at(1)) );

    for(iter = args.begin(); iter < args.end(); iter++ ) {
      if ( *iter == "-t" ) {
	cmd->deadline = currentTime() + StringToNum(*(++iter));
      }

      else if ( *iter == "-p" ) {
	cmd->priority = StringToNum(*(++iter));
      }

      else if ( *iter == "-g" ) {
	cmd->group = *(++iter);
      }

      else if ( *iter == "-d" ) {
      	cmd->taskDescription = *(++iter);
      }
    }
  }

  void rm_parse() {
    cmd->method = RM;

    for(iter = args.begin(); iter < args.end(); iter++ ) {
      if ( *iter == "-g" ) {
	cmd->group = *(++iter);

      } else {
	if ( *iter != "rm")
	  cmd->serialNumberList.push_back( StringToNum(*iter) );
      }
    }
  }

  void ls_parse() {
    cmd->method = LS;

    for(iter = args.begin(); iter < args.end(); iter++ ) {
      if ( *iter == "-g" ) {
	cmd->group = *(++iter);
      }

      else if ( (*iter)[0] == '"' ) { //&& *(iter - 1) != "-g") {
      	cmd->taskDescription = *iter;
      }

      else if ( *iter == "-f" ) {
	string s = *(++iter);

	if (s == "yes" || s == "YES" || s == "Yes" || s == "y" || s == "Y")
	  cmd->finishFlag = YES;
	else if (s == "no"|| s == "NO" || s == "No" || s == "n" || s == "N")
	  cmd->finishFlag = NO;
	else
	  cmd->finishFlag = ALL;
      }

      else if ( *iter == "-k") { // got to change later so this "-k" is not necessary
	cmd->keyword = *(++iter);
      }

      else if ( *iter == "-s" ) {
	string keywords = *(++iter);
	string buf;
	stringstream ss(keywords.substr(1, keywords.length() - 2));

	string deadline = "deadline";
	string serialnumber = "serialnumber";
	string priority = "priority";

	while ( ss >> buf ) {
	  if( deadline.find(buf) != string::npos )
	    cmd->sortKeyword.push_back(DEADLINE);
	  else if( serialnumber.find(buf) != string::npos )
	    cmd->sortKeyword.push_back(SERIAL_NUMBER);
	  else if( priority.find(buf) != string::npos )
	    cmd->sortKeyword.push_back(PRIORITY);
	}
      }
    }

    /* cmd->serialNumberList.push_back(StringToNum(args.at(1))); */
  }

  void pri_parse() {
    cmd->method = PRI;
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
    cmd->priority = StringToNum(args.at(2));
  }

  void finish_parse() {
    cmd->method = FINISH;
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
  }

  void export_parse() {
    cmd->method = EXPORT;
    if (args.size()!=1) cmd->filename = args[1];
  }

  void import_parse() {
    cmd->method = IMPORT;
    if (args.size()!=1) cmd->filename = args[1];
  }

  void task_parse() {
    cmd->method = TASK;
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
  }


  Command *inputToCommand (char *input) {
    string s = string(input);
    tokenize(s);

    delete cmd;
    cmd = new Command();

    if (args[0] == "exit" || args[0] =="")
      throw EXCEPTION_HALT;
    
    else if (args[0] == "help") {
      args.clear();
      throw EXCEPTION_HELP;
    }

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

    else {
      args.clear();
      throw EXCEPTION_NO_SUCH_COMMAND;
    }

    args.clear();
    return cmd;
  }

  string resultToOutput(Result *result){
    if (result->isNull == true)
      return string("");

    else {
      vector<Task *> ret = result->sort(result->comparer);
      stringstream ss("");

      if (result->detailed == false) {
	for (unsigned i = 0; i < ret.size(); i++){
	  ss << endl << ret.at(i)-> getSerialNumber();
	  if (ret.at(i)->getIsFinished()) ss<<" f";
	  string s = ret.at(i)->getDescription();
	  if (s.length()>50) s = s.substr(0,50) + "...";
       	  ss<< "\t" << s;
	}

	ss<< endl;

      } else {
//	ss << endl << "No.\tfinished?\tdeadline\tpriority\tdetails" << endl;
	ss << endl;
	for (unsigned i = 0; i < ret.size(); i++) {
		ss << " Serial Number:\t" << ret.at(i)->getSerialNumber() << "\t\tDeadline:\t" << formatTime(ret.at(i)->getDeadline()) ;
		ss << "      Priority:\t"<< ret.at(i)->getPriority()<< "\t\t  Status:\t";
		if (ret.at(i)->getIsFinished()) ss<<"Finished"<<endl;	
		else ss<<"Doing"<<endl;
		ss << " Details: " << endl;
		ss << "\t" << ret.at(i)->getDescription()<<endl;
//	  ss << ret.at(i)->getSerialNumber()  << "\t" << (ret.at(i)->getIsFinished() ? "yes" : "no") << "\t\t" << formatTime(ret.at(i)->getDeadline()) << "\t" << ret.at(i)->getPriority() << "\t\t" << ret.at(i)->getDescription() << endl;
	}
      }
      return ss.str();
    }
  }
};

Parser *parser;
