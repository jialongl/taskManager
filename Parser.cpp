/* Author: Liu Jialong */
/* Author: He Haocong */

#include "Parser.h"

Parser::Parser() {
  //cmd = new Command();
}

void Parser::tokenize_by_pipe (string s) {
  args.clear();

  int pos = 0;
  string buf = "";
  bool inInvertedCommas = false;
  int tmp = s.size();

  while (pos < tmp && s[pos] == '|')
    pos++;

  while (pos < tmp) {
    if ( s[pos] != '|') {
      if ( s[pos] == '"')
    	  inInvertedCommas = !inInvertedCommas;

      buf += s[pos];
    }

    else if (inInvertedCommas == false) {
      args.push_back(buf);
      buf = "";
    }

    else { // s[pos] == '|' and inInvertedCommas == true
      buf += s[pos];
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
  bool inInvertedCommas = false;

  int tmp = s.size();

  while (pos < tmp && s[pos] == ' ')
    pos++;

  while (pos < tmp) {
	  if ( s[pos] != ' ') {
	    buf += s[pos];
		if (s[pos] == '\\' && s[pos+1] == '\\')
	      pos++;

	    if (s[pos] == '"') {
	      if (pos > 0 && s[pos-1] == '\\') {
		buf = buf.substr(0, buf.length() - 2);
		buf += '"';
	      } else {
		// this '"' is not escaped
		if (inInvertedCommas == true) {
		  args.push_back(buf);
		  buf = "";
		}
		inInvertedCommas = !inInvertedCommas;
	      }
		}
	  }

	  else {
		  if (inInvertedCommas == true)
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

void Parser::parse_date (string s, time_t *seconds) {
  int digit_pos = 0; // to record the position in the string where it is a digit (i.e '0' ~ '9')
  int this_number;

  if (isNumber(s))
    *seconds = StringToNum(s);

  else if (isDigit(s[0]) || s[0] == '-') {
	  for (int j = 0; j < s.length(); j++) {
		  this_number = StringToNum( s.substr(digit_pos, j - digit_pos) );
		  if (s[j] == 'w') {
			  *seconds += this_number * 604800;
			  digit_pos = j + 1;

		  } else if (s[j] == 'd') {
			  *seconds += this_number * 86400;
			  digit_pos = j + 1;

		  } else if (s[j] == 'h') {
			  *seconds += this_number * 3600;
			  digit_pos = j + 1;

		  } else if (s[j] == 'm') {
			  *seconds += this_number * 60;
			  digit_pos = j + 1;
		  }
	  }
	  *seconds += currentTime();

  } else if (s[0] == 'b') {
	  int j=1;

	  time_t now;
	  time_t temp = 0;
	  struct tm *now_tm;
	  time(&now);
	  now_tm = localtime(&now);

	  while( j < s.length()) {
		  if (!(isDigit(s[j])) && s[j] != '-') { //s[j] is (at least) a letter
			  break;
		  }
		  j++;
	  }

	  now_tm->tm_sec = 0;
	  now_tm->tm_min = 0;
	  now_tm->tm_hour = 0;

	  if (s[j] == 'w')
		  now_tm->tm_mday -= now_tm->tm_wday ;

	  parse_date(s.substr(1, s.length()-1), &temp);
	  temp -= currentTime();
	  *seconds = mktime(now_tm);
	  *seconds += temp;
  }
}

void Parser::add_parse() {
  cmd->method = ADD;
  cmd->group = "default";
  cmd->deadline = NO_SPECIFIC_DEADLINE;

  for(iter = args.begin(); iter < args.end(); iter++ ) {
    if ( *iter == "-t" ) {
      string temp = *(++iter);
      time_t seconds = 0;

      if (temp.length() >= 2) {
    	  parse_date(temp, &seconds);
    	  cmd->deadline = seconds;
      }
    }

    else if ( *iter == "-p" ) {
      cmd->priority = StringToNum(*(++iter));
    }

    else if ( *iter == "-g" ) {
      string temp = *(++iter);
      cmd->group = trimInvertedCommas(temp);
    }

    else if ( (*iter)[0] == '"' && *(iter - 1) != "-g") {
      string temp = *iter;
      cmd->taskDescription = trimInvertedCommas(temp);
    }

  }
}

void Parser::edit_parse() {

  if (args.size() >= 2) {
    cmd->method = EDIT;
    cmd->serialNumberList.push_back( StringToNum(args.at(1)) );
    cmd->priority = NO_CHANGE;

  } else
    return ;

  for(iter = args.begin(); iter < args.end(); iter++ ) {
    if ( *iter == "-t" ) {
      string temp = *(++iter);
      time_t seconds = 0;

      if (temp.length() >= 2) {
    	  parse_date(temp, &seconds);
    	  cmd->deadline = seconds;
      }
    }

    else if ( *iter == "-p" ) {
      cmd->priority = StringToNum(*(++iter));
    }

    else if ( *iter == "-f" ) {
      string s = *(++iter);

      if (s == "yes" || s == "YES" || s == "Yes" || s == "y" || s == "Y")
	cmd->finishFlag = YES;
      else if (s == "no"|| s == "NO" || s == "No" || s == "n" || s == "N")
	cmd->finishFlag = NO;
    }

    else if ( *iter == "-g" ) {
      string temp = *(++iter);
      cmd->group = trimInvertedCommas(temp);
    }

    else if ( *iter == "-d" ) {
      string temp = *(++iter);
      cmd->taskDescription = trimInvertedCommas(temp);
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
      cmd->group = trimInvertedCommas(temp);
    }

    /* else if ( (*iter)[0] == '"' ) { //&& *(iter - 1) != "-g") { */
    /* 	string temp = *iter; */
    /* 	cmd->taskDescription = temp.substr(1, temp.length() - 2); */
    /* } */

    else if ( *iter == "-f" ) {

      if (args.size() < 3)
	return ;

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
      cmd->group = trimInvertedCommas(temp);
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

    else if (* iter == "-i" && (iter + 1 != args.end())){
      string times = *(++iter);
      int pos = 0;
      for (int i=0;i<times.length();i++){
          if (times[i] == ':') {
              pos = i;
              break;
          }
      }
      if (pos < times.size() && times[pos] == ':'){
          time_t d0;
          time_t d1;
          parse_date(times.substr(0,pos),&d0);
          parse_date(times.substr(pos+1,times.size() - pos - 1),&d1);
          cmd->deadline = d0;
          cmd->deadline2 = d1;
      }
    }
  }
}

void Parser::pri_parse() {
  cmd->method = PRI;

  if (args.size() == 2) {
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
    cmd->priority = 20; // elevate the priority directly to 20

  } else if (args.size() == 3) {
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
    cmd->priority = StringToNum(args.at(2));
  }

}

void Parser::finish_parse() {
  cmd->method = FINISH;
  for(iter = args.begin(); iter < args.end(); iter++ ) {
    if ( *iter == "-g" ) {
      cmd->group = *(++iter);

    } else {
      if ( *iter != "finish")
	cmd->serialNumberList.push_back( StringToNum(*iter) );
    }
  }
}

void Parser::sort_parse(){
    if (args.size() != 2) return;
    cmd->method = SORT;
    string keywords = args.at(1);
    string buf;
    stringstream ss(trimInvertedCommas(keywords));//keywords.substr(1, keywords.length() - 2));

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

void Parser::export_parse() {
  cmd->method = EXPORT;
  if (args.size() == 2) {
    if ( args[1] == "-html" ) {
      cmd->filename = "record.html";
      cmd->html = true;
    }
    else
      cmd->filename = trimInvertedCommas(args[1]);
  }

  else if (args.size() == 3 && args[1] == "-html") {
    cmd->filename = trimInvertedCommas(args[2]);
    cmd->html = true;
  }
}

void Parser::write_parse() {
  cmd->method = WRITE;
  if (args.size() == 2 && args[1] != "-html" )
    cmd->filename = args[1];

  else if (args.size() == 3 && args[1] == "-html") {
    cmd->filename = args[2];
    cmd->html = 1;
  }
}

void Parser::import_parse() {
  cmd->method = IMPORT;
  if (args.size()!=1) cmd->filename = args[1];
}

void Parser::read_parse() {
  cmd->method = READ;
  if (args.size()!=1) cmd->filename = args[1];
}

void Parser::task_parse() {
  cmd->method = TASK;

  if (args.size() >= 2)
    cmd->serialNumberList.push_back(StringToNum(args.at(1)));
}

void Parser::run_parse() {
  cmd->method = RUN;
  if (args.size()!=1) cmd->filename = trimInvertedCommas(args[1]);
}

void Parser::undo_parse(){
  cmd->method = UNDO;
}

void Parser::redo_parse(){
  cmd->method = REDO;
}

void Parser::map_parse() {

    if (args.size()!=3) return;

  string alias  = trimInvertedCommas( args.at(1) );
  string origin = trimInvertedCommas( args.at(2) );

  if (alias != "map") {
    commandAliases.push_back(alias);
    commandOriginals.push_back(origin);
  }
}

string Parser::trimInvertedCommas(string s) {
  int start = 0;
  int end = s.length() - 1;
  int tmp = s.size();

  while (start < tmp && s[start] == ' ')
    start++;

  while (end > 0 && s[end] == ' ')
    end--;

  if (s[start] == '"' && s[end] == '"') // the string has '"' at the beginning and the end.
    return s.substr(start+1, end-start-1);
  else
    return s.substr(start, end-start+1);
}

string Parser::matchAlias (string s) {
  string alias;
  string origin;
  string token_to_insert;
  size_t found;
  int dollar_number;
  vector<string> args_input;

  tokenize_by_space(s);
  if (args.size()>0 && args[0] == "map") return s;
  args_input = args;

    for ( int i = commandAliases.size()-1; i>=0; i--) {
        alias  = commandAliases[i];
        origin = commandOriginals[i];

        if (s == alias)
            return origin; // a perfect match should return straightaway -- it happens mostly there are no $ signs in the alias.

        tokenize_by_space(alias); // now think of "args" as "args_alias"

        for (int i = 0; i < args.size(); i++) {
            if (i >= args_input.size())
                break;

            if ( args_input[i] != args[i]) {
                if ( args[i][0] == '$' ) {
                    dollar_number = StringToNum( args[i].substr(1, args[i].length()-1) );

                    if (dollar_number == 0) {
                        found = origin.find(args[i]);
                        if (found != string::npos) {
		  // args[i] == "$0" at this moment,
		  // so replace $0 with all the remaining tokens
                            string string_dollar_0 = "";
                            while (i < args_input.size()) {
                                string_dollar_0 += (args_input[i] + " ");
                                i++;
                            }
                            origin.replace( int(found),  2, string_dollar_0 );
                            return origin;
                        }

                    } else {
                    // args[i] != "$0"
                    // then find string '${dollar_number}' in string "origin" and replace it with THIS (the current one) token in "s"
                        found = origin.find(args[i]);

                        if (found != string::npos) {
                            origin.replace( int(found),  2, args_input[i] );
                        }
                    }

	            } else { // not a variable ( denoted by $0, $1, $2...) used in "map" command
	                break;
	            }
	        }

	        if (i == args_input.size()-1 && i == args.size()-1) { // all tokens match -- Yes, it MATCHes!
	            return origin;
	        }
	    }
    }

    return "";
}

Command* Parser::inputToCommand (string input) {

  if (input[0] != '\\') {
    //------ check if this command has been alias-ed. -----
    string temp = matchAlias(input);

    if (temp != "")
      tokenize_by_space(temp);
    else
      tokenize_by_space(input);
    //-----------------------------------------------------
  }

  else
    tokenize_by_space(input.substr(1, input.length()-1));

  cmd = new Command();

  if (input.length() == 0) {

  }
  else if (args[0] == "exit" || args[0] == "quit"){
      delete cmd;
    throw EXCEPTION_HALT;
  }
    
  else if (args[0] == "help" || args[0] == "--help") {
      delete cmd;
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
    cmd->method = TUI;
  }

  else if (args[0] == "notui"){
    cmd->method = NOTUI;
  }

  else if (args[0] == "map")
    map_parse();
  
  else if (args[0] == "read")
    read_parse();
  
  else if (args[0] == "write")
    write_parse();

  else if (args[0] == "run")
    run_parse();

  else if (args[0] == "undo")
    undo_parse();

  else if (args[0] == "redo")
    redo_parse();

  else if (args[0] == "sort")
      sort_parse();

  else {
      delete cmd;
    throw EXCEPTION_NO_SUCH_COMMAND;
  }

  return cmd;
}

CommandList Parser::inputToCommandList (string s) {
//  IOModule->echo(s);
  vector <string> commands;
  CommandList cl;

  tokenize_by_pipe(s);
  commands = args;

  for (int i = 0; i < commands.size(); i++) {
    cl.push_back(inputToCommand(commands[i]));
  }

  if (cl.size() != 0) cl[0]->originalCommand = s;
  return cl;
}

string Parser::resultToOutput(Result *result){
  if (result->isNull == true) {
    // delete result;
    return string("");
  }

  else {
    vector<Task *> ret = result->sort(result->comparer);
    stringstream ss("");

    if (result->detailed == false) {

      for (unsigned i = 0; i < ret.size(); i++) {
	ss << endl << ret.at(i)-> getSerialNumber();

	if (ret.at(i)->getIsFinished())
	  ss<<" f";

	string s = ret.at(i)->getDescription();

	if (s.length() > 50)
	  s = s.substr(0,50) + "...";
	else
	  s.append( 50-s.length(), ' ');

	ss<< "\t" << s;

	for (unsigned j=0; j < result->comparer->keywords.size(); j++) {
	  if (result->comparer->keywords.at(j) == DEADLINE) {
	    string s2 = formatTime ( ret.at(i)->getDeadline() );
	    ss<< "\t" << s2;
	  }

	  else if (result->comparer->keywords.at(j) == PRIORITY)
	    ss<< "\t" << ret.at(i)->getPriority();

	  // else if (result->comparer->keywords.at(i) == serialNumber)
	  //   ss<< "\t" << ret.at(i)->getSerialNumber;
	}
      }

      ss<< endl;

    } else {
      ss << endl;
      for (unsigned i = 0; i < ret.size(); i++) {
	ss << "   Number:\t" << ret.at(i)->getSerialNumber() << "\t\tDeadline:\t" << formatTime(ret.at(i)->getDeadline()) <<endl;
	ss << " Priority:\t"<< ret.at(i)->getPriority()<< "\t\t  Status:\t";

    string fts = formatTime(ret.at(i)->getFinishTime());
    if (fts.size() > 13) fts = fts.substr(13,11);
	if (ret.at(i)->getIsFinished())
	  ss<<"Finished on "+fts<<endl;	
	else
	  ss<<"Doing"<<endl;

	ss << "    Group:\t"<<ret.at(i)->getGroup()<<endl;
	ss << "  Details:" << endl;
	ss << "\t" << ret.at(i)->getDescription()<<endl;
      }
    }

    // delete result;
    return ss.str();
  }
}
