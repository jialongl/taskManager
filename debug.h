void print(){
	        map<int, Task*> theMap = mainTaskList->getTaskMap();
		        for (map<int, Task*>::iterator it = theMap.begin();it!=theMap.end();it++){
				                cout << it->first <<"   "<< it->second->getDescription() <<endl;
						        }
			        if (theMap.find(10) != theMap.end()) cout<< theMap.find(10)->first<<"aaa!"<<endl;
}

