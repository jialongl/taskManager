/* Author: Wang Xiangyu */
#include<fstream>

#include "ExportCommandExecutor.h"
string ExportCommandExecutor::distortString(string s){
	int i = 0;
	while (i != s.size()){
		if (s.at(i) == '<'){
			s.replace(i, 1, "&lt;");
		        i += 3;
		}else if(s.at(i) == '>'){
			s.replace(i, 1, "&gt;");
		        i += 3;
		}else if(s.at(i) == '&'){
			s.replace(i, 1, "&amp;");
			i += 4;
		}else if(s.at(i) == '\''){
			s.replace(i, 1, "&apos;");
			i += 4;
		}else if(s.at(i) == '\"'){
			s.replace(i, 1, "&quot;");
			i += 5;
		}
		i++;
	}
	return s;
}

Result* ExportCommandExecutor::executeCommand (TaskList* mainTaskList, Command* command){
	string filename;
	//export to file record.xml
	if (command->method == EXPORT){
		map<int, Task*> tasks = mainTaskList->getTaskMap();
		
		ofstream writeFile;
		if(command->filename == "")
		  command->filename = RECORDFILE;


		filename = command->filename;
		//writeFile.open((command->filename).c_str());
		writeFile.open(filename.c_str());

		//cout << command->filename << endl;

		if(command->html){
			//file head
			writeFile<<"<html>"<<endl;
			writeFile<<"<head>"<<endl;
			writeFile<<"<style type=\"text/css\">"<<endl;

            writeFile<<"body{font-family:\"Trebuchet MS\", Arial, Helvetica, sans-serif;border-collapse:collapse;}"<<endl;
            writeFile<<".taskMenu{opacity:0.9;font-weight:bold;font-size:1.1em;text-align:center;background-color:#A7C942;color:#ffffff;}"<<endl;
            writeFile<<".serialNumberMenu{position:fixed;border:solid;top:0;left:0px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".priorityMenu{position:fixed;border:solid;top:0;left:102px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".groupMenu{position:fixed;border:solid;top:0;left:204px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".isFinishedMenu{position:fixed;border:solid;top:0;left:306px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".DeadlineMenu{position:fixed;border:solid;top:0;left:408px;width:200px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".descriptionMenu{text-align:left;position:fixed;border:solid;top:0;padding-left:610px;width:100%;height:30px;padding-top:10px;background-color:#A7C942;z-index:-1;}"<<endl;
            writeFile<<"table{width:100%;border:0px;margin:0px;padding:0px;}"<<endl;
            writeFile<<"td{padding:5px 0px;margin:0px;border:0px;}"<<endl;
            writeFile<<".alt td{color:#000000;background-color:#EAF2D3;}"<<endl;
            writeFile<<".serialNumber{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".priority{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".isFinished{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".group{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".deadline{min-width:200px;width:150px;text-align:center;}"<<endl;
            writeFile<<".description{text-align:center;text-align:left;padding-left:10px;padding-right:10px;}"<<endl;
            writeFile<<".content{position:absolute;left:0px;top:45px;z-index:-100;}"<<endl;
/*
			writeFile<<"body{font-family:\"Trebuchet MS\", Arial, Helvetica, sans-serif;width:99%;border-collapse:collapse;}"<<endl;
			writeFile<<".taskMenu{opacity:0.9;font-weight:bold;font-size:1.1em;text-align:center;background-color:#A7C942;color:#ffffff;}"<<endl;
			writeFile<<".serialNumberMenu{position:fixed;border:solid;top:0;left:0;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
			writeFile<<".priorityMenu{position:fixed;border:solid;top:0;left:100px;width:96px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
			writeFile<<".groupMenu{position:fixed;border:solid;top:0;left:199px;width:96px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
			writeFile<<".isFinishedMenu{position:fixed;border:solid;top:0;left:298px;width:99px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
			writeFile<<".DeadlineMenu{position:fixed;border:solid;top:0;left:400px;width:139px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
			writeFile<<".descriptionMenu{position:fixed;border:solid;top:0;left:543px;width:715px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
			writeFile<<".alt td{color:#000000;background-color:#EAF2D3;}"<<endl;
			writeFile<<"td{width:101;text-align:center;}"<<endl;
			writeFile<<".deadline{width:150px;}"<<endl;
			writeFile<<".description{width:754;text-align:left;padding-left:10;padding-right:10;}"<<endl;
			writeFile<<".content{position:absolute;left:4px;top:40px;z-index:-100;};"<<endl;
*/

 			writeFile<<"</style>"<<endl;
			writeFile<<"</head>"<<endl;

			//task head
			writeFile<<"<div class='taskMenu'>"<<endl;

			//task body
			writeFile<<"	<div class='serialNumberMenu'>NUMBER</div>"<<endl;
			writeFile<<"	<div class='priorityMenu'>PRIORITY</div>"<<endl;
			//writeFile<<"	<div class='cronFreqMenu'>CRON</div>"<<endl;
			writeFile<<"	<div class='groupMenu'>GROUP</div>"<<endl;
			writeFile<<"	<div class='isFinishedMenu'>STATUS</div>"<<endl;
			writeFile<<"	<div class='deadlineMenu'>DEADLINE</div>"<<endl;
			writeFile<<"	<div class='descriptionMenu'>DETAILS</div>"<<endl;

			//task end
			writeFile<<"</div>"<<endl;
			
			writeFile<<"<table class='content'>"<<endl;
			
			int counter = 0;
			//file body
			for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++){
				string description = iter->second->getDescription();
				string group = iter->second->getGroup();

				string group_dist = distortString (group);
				string description_dist = distortString (description);
				//task head
				
				writeFile<<((counter++%2)? "<tr>":"<tr class='alt'>")<<endl;

				//task body
				writeFile<<"	<td class='serialNumber'>"<<iter->second->getSerialNumber()<<"</td>"<<endl;
				writeFile<<"	<td class='priority'>"<<iter->second->getPriority()<<"</td>"<<endl;
				//writeFile<<"	<td class='cronFreq'>"<<iter->second->getCronFreq()<<"</td>"<<endl;
				writeFile<<"	<td class='group'>"<<group_dist<<"</td>"<<endl;
				writeFile<<"	<td class='isFinished'>"<<(iter->second->getIsFinished()? "Finished":"Doing")<<"</td>"<<endl;
				writeFile<<"	<td class='deadline'>"<<formatTime(iter->second->getDeadline())<<"</td>"<<endl;
				writeFile<<"	<td class='description'>"<<description_dist<<"</td>"<<endl;

				//task end
				writeFile<<"</tr>"<<endl;
			}
		
			//file end
			writeFile<<"</table>"<<endl;
			writeFile<<"</html>"<<endl;
		}

		//xml file head
		writeFile<<"<!--<taskList>"<<endl;

		//file body
		for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++){
			string description = iter->second->getDescription();
			string group = iter->second->getGroup();

			string group_dist = distortString (group);
			string description_dist = distortString (description);
			//task head
			writeFile<<"	<task>"<<endl;

			//task body
			writeFile<<"		<serialNumber>"<<iter->second->getSerialNumber()<<"</serialNumber>"<<endl;
			writeFile<<"		<deadline>"<<iter->second->getDeadline()<<"</deadline>"<<endl;
			writeFile<<"		<priority>"<<iter->second->getPriority()<<"</priority>"<<endl;
			writeFile<<"		<description>"<<description_dist<<"</description>"<<endl;
			//writeFile<<"		<cronFreq>"<<iter->second->getCronFreq()<<"</cronFreq>"<<endl;
			writeFile<<"		<group>"<<group_dist<<"</group>"<<endl;
			writeFile<<"		<isFinished>"<<iter->second->getIsFinished()<<"</isFinished>"<<endl;

			//task end
			writeFile<<"	</task>"<<endl;
		}
	
		//file end
		writeFile<<"</taskList>-->"<<endl;

		writeFile.close();
	}
	return new Result();
}

Result* ExportCommandExecutor::executeCommand(TaskList* mainTaskList, Result* result, Command *command){
	string filename;
	if (command->method == EXPORT){
		map<int, Task*> tasks = result->getTaskMap();
		
		ofstream writeFile;
		if(command->filename == "")
		  command->filename = RECORDFILE;

		filename = command->filename;
		//writeFile.open((command->filename).c_str());
		writeFile.open(filename.c_str());

		if(command->html){
			//file head
			writeFile<<"<html>"<<endl;
			writeFile<<"<head>"<<endl;
			writeFile<<"<style type=\"text/css\">"<<endl;

            writeFile<<"body{font-family:\"Trebuchet MS\", Arial, Helvetica, sans-serif;border-collapse:collapse;}"<<endl;
            writeFile<<".taskMenu{opacity:0.9;font-weight:bold;font-size:1.1em;text-align:center;background-color:#A7C942;color:#ffffff;}"<<endl;
            writeFile<<".serialNumberMenu{position:fixed;border:solid;top:0;left:0px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".priorityMenu{position:fixed;border:solid;top:0;left:102px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".groupMenu{position:fixed;border:solid;top:0;left:204px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".isFinishedMenu{position:fixed;border:solid;top:0;left:306px;width:100px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".DeadlineMenu{position:fixed;border:solid;top:0;left:408px;width:200px;height:30px;padding-top:10px;background-color:#A7C942;}"<<endl;
            writeFile<<".descriptionMenu{text-align:left;position:fixed;border:solid;top:0;padding-left:610px;width:100%;height:30px;padding-top:10px;background-color:#A7C942;z-index:-1;}"<<endl;
            writeFile<<"table{width:100%;border:0px;margin:0px;padding:0px;}"<<endl;
            writeFile<<"td{padding:5px 0px;margin:0px;border:0px;}"<<endl;
            writeFile<<".alt td{color:#000000;background-color:#EAF2D3;}"<<endl;
            writeFile<<".serialNumber{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".priority{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".isFinished{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".group{min-width:100px;width:100px;text-align:center;}"<<endl;
            writeFile<<".deadline{min-width:200px;width:150px;text-align:center;}"<<endl;
            writeFile<<".description{text-align:center;text-align:left;padding-left:10px;padding-right:10px;}"<<endl;
            writeFile<<".content{position:absolute;left:0px;top:45px;z-index:-100;}"<<endl;
            writeFile<<"tr{padding-top:5px;padding-bottom:5px;}"<<endl;

 			writeFile<<"</style>"<<endl;
			writeFile<<"</head>"<<endl;

			//task head
			writeFile<<"<div class='taskMenu'>"<<endl;

			//task body
			writeFile<<"	<div class='serialNumberMenu'>NUMBER</div>"<<endl;
			writeFile<<"	<div class='priorityMenu'>PRIORITY</div>"<<endl;
			//writeFile<<"	<div class='cronFreqMenu'>CRON</div>"<<endl;
			writeFile<<"	<div class='isFinishedMenu'>STATUS</div>"<<endl;
			writeFile<<"	<div class='groupMenu'>GROUP</div>"<<endl;
			writeFile<<"	<div class='deadlineMenu'>DEADLINE</div>"<<endl;
			writeFile<<"	<div class='descriptionMenu'>DETAILS</div>"<<endl;

			//task end
			writeFile<<"</div>"<<endl;
			
			writeFile<<"<table class='content'>"<<endl;
			
			int counter = 0;
			//file body
			for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++){
				string description = iter->second->getDescription();
				string group = iter->second->getGroup();

				string group_dist = distortString (group);
				string description_dist = distortString (description);
				//task head
				
				writeFile<<((counter++%2)? "<tr>":"<tr class='alt'>")<<endl;

				//task body
				writeFile<<"	<td class='serialNumber'>"<<iter->second->getSerialNumber()<<"</td>"<<endl;
				writeFile<<"	<td class='priority'>"<<iter->second->getPriority()<<"</td>"<<endl;
				//writeFile<<"	<td class='cronFreq'>"<<iter->second->getCronFreq()<<"</td>"<<endl;
				writeFile<<"	<td class='group'>"<<group_dist<<"</td>"<<endl;
				writeFile<<"	<td class='isFinished'>"<<(iter->second->getIsFinished()? "Finished":"Doing")<<"</td>"<<endl;
				writeFile<<"	<td class='deadline'>"<<formatTime(iter->second->getDeadline())<<"</td>"<<endl;
				writeFile<<"	<td class='description'>"<<description_dist<<"</td>"<<endl;

				//task end
				writeFile<<"</tr>"<<endl;
			}
		
			//file end
			writeFile<<"</table>"<<endl;
			writeFile<<"</html>"<<endl;
		}

		//file head
		writeFile<<"<!--<taskList>"<<endl;

		//file body
		for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++){
			string description = iter->second->getDescription();
			string group = iter->second->getGroup();

			string group_dist = distortString (group);
			string description_dist = distortString (description);
			//task head
			writeFile<<"	<task>"<<endl;

			//task body
			writeFile<<"		<serialNumber>"<<iter->second->getSerialNumber()<<"</serialNumber>"<<endl;
			writeFile<<"		<deadline>"<<iter->second->getDeadline()<<"</deadline>"<<endl;
			writeFile<<"		<priority>"<<iter->second->getPriority()<<"</priority>"<<endl;
			writeFile<<"		<description>"<<description_dist<<"</description>"<<endl;
			//writeFile<<"		<cronFreq>"<<iter->second->getCronFreq()<<"</cronFreq>"<<endl;
			writeFile<<"		<isFinished>"<<iter->second->getIsFinished()<<"</isFinished>"<<endl;
			writeFile<<"		<group>"<<group_dist<<"</group>"<<endl;

			//task end
			writeFile<<"	</task>"<<endl;
		}
	
		//file end
		writeFile<<"</taskList>-->"<<endl;

		writeFile.close();
	}
	return new Result();
}

