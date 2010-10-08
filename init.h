/* Author: He Haocong */
void init(){
  cronManager = new CronManager();
  //shell = new Shell();	
  mainCommandExecutor = new MainCommandExecutor();
  parser = new Parser();
  mainTaskList = new TaskList();
  Command *cmd = new Command();
  cmd->method = IMPORT;
  mainCommandExecutor->executeCommand(cmd);
}
