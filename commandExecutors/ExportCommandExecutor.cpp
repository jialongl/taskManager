#include "commandExecutors/ExportCommandExecutor.h"

Result* ExportCommandExecutor::executeCommand (Command* command)
{
    string filename;
    //export to file record.xml
    if (command->method == EXPORT)
    {
        map<int, Task*> tasks = mainTaskList->getTaskMap();
        
        ofstream writeFile;
        if (command->filename == "")
            writeFile.open("record.xml");
        else{
            filename = command->filename;
            //writeFile.open((command->filename).c_str());
            writeFile.open(filename.c_str());
        }

        if(command->html){
            //file head
            writeFile<<"<html>"<<endl;

            //file body
            for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++)
            {
                string description = iter->second->getDescription();
                string group = iter->second->getGroup();

                string group_dist = distortString (group);
                string description_dist = distortString (description);
                //task head
                writeFile<<"	<div class='task'>"<<endl;

                //task body
                writeFile<<"		<div class='serialNumber'>"<<iter->second->getSerialNumber()<<"</div>"<<endl;
                writeFile<<"		<div class='deadline'>"<<iter->second->getDeadline()<<"</div>"<<endl;
                writeFile<<"		<div class='priority'>"<<iter->second->getPriority()<<"</div>"<<endl;
                writeFile<<"		<div class='description'>"<<description_dist<<"</div>"<<endl;
                writeFile<<"		<div class='cronFreq'>"<<iter->second->getCronFreq()<<"</div>"<<endl;
                writeFile<<"		<div class='isFinished'>"<<iter->second->getIsFinished()<<"</div>"<<endl;
                writeFile<<"		<div class='group'>"<<group_dist<<"</div>"<<endl;

                //task end
                writeFile<<"	</div>"<<endl;
            }
        
            //file end
            writeFile<<"</html>"<<endl;

        }else{
            //file head
            writeFile<<"<taskList>"<<endl;

            //file body
            for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++)
            {
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
                writeFile<<"		<cronFreq>"<<iter->second->getCronFreq()<<"</cronFreq>"<<endl;
                writeFile<<"		<isFinished>"<<iter->second->getIsFinished()<<"</isFinished>"<<endl;
                writeFile<<"		<group>"<<group_dist<<"</group>"<<endl;

                //task end
                writeFile<<"	</task>"<<endl;
            }
        
            //file end
            writeFile<<"</taskList>"<<endl;
        }

        writeFile.close();
    }
    return new Result();
}

Result* ExportCommandExecutor::executeCommand(Result* result, Command *command){
    string filename;
    if (command->method == EXPORT){
        map<int, Task*> tasks = result->getTaskMap();
        
        ofstream writeFile;
        if (command->filename == "")
            writeFile.open("record.xml");
        else{
            filename = command->filename;
            //writeFile.open((command->filename).c_str());
            writeFile.open(filename.c_str());
        }

        if(command->html){
            //file head
            writeFile<<"<html>"<<endl;

            //file body
            for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++)
            {
                string description = iter->second->getDescription();
                string group = iter->second->getGroup();

                string group_dist = distortString (group);
                string description_dist = distortString (description);
                //task head
                writeFile<<"	<div class='task'>"<<endl;

                //task body
                writeFile<<"		<div class='serialNumber'>"<<iter->second->getSerialNumber()<<"</div>"<<endl;
                writeFile<<"		<div class='deadline'>"<<iter->second->getDeadline()<<"</div>"<<endl;
                writeFile<<"		<div class='priority'>"<<iter->second->getPriority()<<"</div>"<<endl;
                writeFile<<"		<div class='description'>"<<description_dist<<"</div>"<<endl;
                writeFile<<"		<div class='cronFreq'>"<<iter->second->getCronFreq()<<"</div>"<<endl;
                writeFile<<"		<div class='isFinished'>"<<iter->second->getIsFinished()<<"</div>"<<endl;
                writeFile<<"		<div class='group'>"<<group_dist<<"</div>"<<endl;

                //task end
                writeFile<<"	</div>"<<endl;
            }
        
            //file end
            writeFile<<"</html>"<<endl;

        }else{
            //file head
            writeFile<<"<taskList>"<<endl;

            //file body
            for (map<int, Task*>::iterator iter = tasks.begin(); iter!=tasks.end(); iter++)
            {
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
                writeFile<<"		<cronFreq>"<<iter->second->getCronFreq()<<"</cronFreq>"<<endl;
                writeFile<<"		<isFinished>"<<iter->second->getIsFinished()<<"</isFinished>"<<endl;
                writeFile<<"		<group>"<<group_dist<<"</group>"<<endl;

                //task end
                writeFile<<"	</task>"<<endl;
            }
        
            //file end
            writeFile<<"</taskList>"<<endl;
        }

        writeFile.close();
    }
    return new Result();
}
string ExportCommandExecutor::distortString (string s)
{
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
