class ImportCommandExecutor:public CommandExecutor{
public:
	Result *executeCommand(Command *command){
		if (command->method == IMPORT){
			delete mainTaskList();
			XMLNode taskListNode = XMLNode::openFileHelper("record.xml","taskList");
			XMLNode taskNode = taskListNode.getChildNode("task");
			XMLNode deadlineNode = taskNode.getChildNode("deadline");
			XMLNode priorityNode = taskNode.getChildNode("priority");
			XMLNode descriptionNode = taskNode.getChildNode("description");
			XMLNode cronFreqNode = taskNode.getChildNode("cronFreq");
			XMLNode isFinishedNode = taskNode.getChildNode("isFinished");
			XMLNode serialNumberNode = taskNode.getChildNode("serialNumber");
			XMLNode groupNode = taskNode.getChildNode("group");
			while(taskNode){
				Task* task = new Task();
				int taskNum = StringToNumber(serialNumberNode.getText());
				if (descriptionNode.getText() != "") mainTaskList->editTaskDescription(taskNum, descriptionNode.getText());
				if (StringToNumber(deadlineNode.getText()) != 0) mainTaskList->editTaskDeadline(taskNum, StringToNumber(deadlineNode.getText()));
				if (StringToNumber(priorityNode.getText()) != -100) mainTaskList->editTaskPriority(taskNum, StringToNumber(priorityNode.getText()));
				if (groupNode.getText() != "") mainTaskList->editTaskGroup(taskNum, groupNode.getText());
				if (StringToNumber(cronFreqNode.getText()) != -1) mainTaskList->editTaskCronFreq(taskNum,StringToNumber(cronFreqNode.getText()));
				mainTaskList->addTask(task);			
			}
			
		}
		return new Result();
	}
};

