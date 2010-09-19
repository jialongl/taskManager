class Parser{
public:
	Command *inputToCommand(char* input){
		return new Command();
	}
	string resultToOutput(Result *result){
		return string("Test");
	}
};

Parser *parser;
