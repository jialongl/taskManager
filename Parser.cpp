/* Author: Liu Jialong */
/* Author: He Haocong */

#include "Parser.h"

Parser::Parser() {
  cmd = new Command();
}

void Parser::tokenize_by_pipe (string s) {
  args.clear();

  int pos = 0;
  string buf = "";

  while (pos < s.size() && s[pos] == '|')
    pos++;

  while (pos < s.size()) {
    if ( s[pos] != '|')
      buf += s[pos];
      
    else {
      args.push_back(buf);
      buf = "";
    }
    pos++;
  }

  if (buf != "")
    args.push_back(buf); // push in the last argument
}

void Parser::tokenize_by_space (string s) {
  args.clear();
  int pos = 0;
  string buf = "";
  short inInvertedCommas = 0;

  while (pos < s.size() && s[pos] == ' ')
    pos++;

  while (pos < s.size()) {
    if ( s[pos] != ' ') {
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

}

void Parser::parse_date (string s, long *seconds) {
  int num_pos = 0; // to record the position in the string where it is a number (i.e '0' ~ '9')

  for (int j = 0; j < s.length(); j++) {
    if (s[j] == 'w') {
      *seconds += StringToNum( s.substr(num_pos, j-num_pos) ) * 604800;
      num_pos = j + 1;

    } else if (s[j] == 'd') {
      *seconds += StringToNum( s.substr(num_pos, j-num_pos) ) * 86400;
      num_pos = j + 1;

    } else if (s[j] == 'h') {
      *seconds += StringToNum( s.substr(num_pos, j-num_pos) ) * 3600;
      num_pos = j + 1;

    } else if (s[j] == 'm') {
      *seconds += StringToNum( s.substr(num_pos, j-num_pos) ) * 60;
      num_pos = j + 1;
    }
  }
}

void Parser::add_parse() {
  cmd->method = ADD;
  cmd->group = "default";

  for(iter = args.begin(); iter < args.end(); iter++ ) {
    if ( *iter == "-t" ) {
      string temp = *(++iter);
      long seconds = 0;

      parse_date(temp, &seconds);
      cmd->deadline = currentTime() + seconds;
    }

    else if ( *iter == "-p" ) {
      cmd->priority = StringToNum(*(++iter));
    }

    else if ( *iter == "-g" ) {
      string temp = *(++iter);
      if (temp[0] == '"' && temp[temp.length()-1] == '"')
	cmd->group = temp.substr(1, temp.length() - 2);
      else
	cmd->group = temp;
    }

    else if ( (*iter)[0] == '"' && *(iter - 1) != "-g") {
      string temp = *iter;
      cmd->taskDescription = temp.substr(1, temp.length() - 2);
    }

    /* else if ( *iter == "-c" ) */
  }
}

void Parser::edit_parse() {
  cmd->method = EDIT;

  if (args.size() >= 2)
    cmd->serialNumberList.push_back( StringToNum(args.at(1)) );

  for(iter = args.begin(); iter < args.end(); iter++ ) {
    if ( *iter == "-t" ) {
      string temp = *(++iter);
      long seconds = 0;

      parse_date(temp, &seconds);
      cmd->deadline = currentTime() + seconds;
    }

    else if ( *iter == "-p" ) {
      cmd->priority = StringToNum(*(++iter));
    }

    else if ( *iter == "-g" ) {
      string temp = *(++iter);
      if (temp[0] == '"' && temp[temp.length()-1] == '"')
	cmd->group = temp.substr(1, temp.length() - 2);
      else
	cmd->group = temp;
    }

    else if ( *iter == "-d" ) {
      string temp = *(++iter);
      if (temp[0] == '"' && temp[temp.length()-1] == '"')
	cmd->taskDescription = temp.substr(1, temp.length() - 2);
      else
	cmd->taskDescription= temp;
    }
  }
}

void Parser::rm_parse() {
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

void Parser::ls_parse() {
  cmd->method = LS;

  for(iter = args.begin(); iter < args.end(); iter++ ) {
    if ( *iter == "-g" ) {
      string temp = *(++iter);

      if (temp[0] == '"' && temp[temp.length()-1] == '"')
	cmd->group = temp.substr(1, temp.length() - 2);
      else
	cmd->group = temp; 
    }

    /* else if ( (*iter)[0] == '"' ) { //&& *(iter - 1) != "-g") { */
    /* 	string temp = *iter; */
    /* 	cmd->taskDescription = temp.substr(1, temp.length() - 2); */
    /* } */

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
      string temp = *(++iter);
      if (temp[0] == '"' && temp[temp.length()-1] == '"')
	cmd->keyword = temp.substr(1, temp.length() - 2);
      else
	cmd->keyword = temp;
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
}

void Parser::pri_parse() {
  cmd->method = PRI;

  if (args.size() == 2)
    cmd->priority = StringToNum(args.at(1));

  else if (args.size() == 3) {
    cmd->priority = StringToNum(args.at(2));
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
  }

}

void Parser::finish_parse() {
  cmd->method = FINISH;

  if (args.size() >= 2)
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
}

void Parser::export_parse() {
  cmd->method = EXPORT;
  if (args.size() == 2 && args[1] != "-html" )
    cmd->filename = args[1];
 
  else if (args.size() == 3 && args[1] == "-html")
    cmd->filename = args[2];
}

void Parser::import_parse() {
  cmd->method = IMPORT;
  if (args.size()!=1) cmd->filename = args[1];
}

void Parser::task_parse() {
  cmd->method = TASK;

  if (args.size() >= 2)
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
}

string Parser::matchAlias (string alias) {

  for ( iter2  = commandAliases.begin();
	iter2 != commandAliases.end();
	iter2++) {
    if (alias == (*iter2).first) {
      return (*iter2).second;
    }
    //(first token of "alias" is the same as the first token of iter2.first) {
    /* if (the number of args match) */
    /*   return iter2.second;  // return the key */
    /* else if (last token of iter2.first is "$0" and everything else matches) */
    /*   return iter2.second;  // return the key */
  }
  return "";
}

void Parser::map_parse() {

  string alias = trimHeadTailInvertedCommas( args.at(1) );
  string origin = trimHeadTailInvertedCommas( args.at(2) );

  /* cout << "a=" << alias << "o=" << origin << endl; */

  if (alias != "map")
    commandAliases[alias] = origin;
}

string Parser::trimHeadTailInvertedCommas(string s) {
  int start = 0;
  int end = s.length() - 1;

  while (start < s.size() && s[start] == ' ')
    start++;

  while (end > 0 && s[end] == ' ')
    end--;

  return s.substr(start+1, end-start-1); // the string has '"' at the beginning and the end.
}

Command Parser::*inputToCommand (string input) {

  tokenize_by_space(input);

  //------ check if this command has been alias-ed. -----

  string temp = matchAlias(args[0]);

  if (temp != "")
    tokenize_by_space(temp);

  //-----------------------------------------------------


  cmd = new Command();

  if (input.length() == 0) {

  }
  else if (args[0] == "exit")
    throw EXCEPTION_HALT;
    
  else if (args[0] == "help") {
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

  else if (args[0] == "tui"){
    TM_IOModule* newIO = new PdcIO();
    shell->changeIOModule(newIO);
    cmd->method = NULLCOMMAND;
  }

  else if (args[0] == "notui"){
    TM_IOModule* newIO = new KeyboardIOModule();
    shell->changeIOModule(newIO);
    cmd->method = NULLCOMMAND;
  }

  else if (args[0] == "map")
    map_parse();

  else {
    throw EXCEPTION_NO_SUCH_COMMAND;
  }

  return cmd;
}

CommandList Parser::inputToCommandList (string s) {
  IOModule->echo(s);
  vector <string> commands;
  CommandList cl;

  tokenize_by_pipe(s);
  commands = args;

  for (int i = 0; i < commands.size(); i++) {
    cl.push_back(inputToCommand(commands[i]));
  }

  return cl;
}

string Parser::resultToOutput(Result *result){
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
      ss << endl;
      for (unsigned i = 0; i < ret.size(); i++) {
	ss << "   Number:\t" << ret.at(i)->getSerialNumber() << "\t\tDeadline:\t" << formatTime(ret.at(i)->getDeadline()) ;
	ss << " Priority:\t"<< ret.at(i)->getPriority()<< "\t\t  Status:\t";

	if (ret.at(i)->getIsFinished())
	  ss<<"Finished"<<endl;	
	else
	  ss<<"Doing"<<endl;

	ss << "    Group:\t"<<ret.at(i)->getGroup()<<endl;
	ss << "  Details:" << endl;
	ss << "\t" << ret.at(i)->getDescription()<<endl;
      }
    }
    return ss.str();
  }
}

