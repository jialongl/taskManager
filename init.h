void init(){
  cronManager = new CronManager();
  shell = new Shell();	
  mainCommandExecutor = new MainCommandExecutor();
  parser = new Parser();
  mainTaskList = new TaskList();
}
