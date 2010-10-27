/* Author: He Haocong */
#ifndef enumH
#define enumH
enum commandMethod {
	ADD,
	EDIT,
	RM,
	LS, // deprecated, replaced by "select"
	SELECT,
	TASK,
	PRI,
	CRON,
	FINISH,
	EXPORT,
	IMPORT,
	SORT,
	RUN,
	NULLCOMMAND,
	WRITE,
	READ,
	TUI,
	NOTUI,
};

enum sortKeyword_e{
	DEADLINE,
	PRIORITY,
	SERIAL_NUMBER
};

enum filterType{
	K_FILTER,
	S_FILTER,
	F_FILTER,
	G_FILTER,
	OVERDUE_FILTER
};

enum exception_e{
	EXCEPTION_NOT_A_NUMBER,
	EXCEPTION_HALT,
	EXCEPTION_NO_SUCH_TASK,
	EXCEPTION_NO_SUCH_COMMAND,
	EXCEPTION_TASK_EXIST,
	EXCEPTION_ILLEGAL_EXPRESSION,
    EXCEPTION_CANCEL,
	EXCEPTION_HELP
};

enum finishFlag_e{
	YES,
	NO,
	ALL
};

enum displayElementType{
    LIST_DE,
    EDIT_DE,
    CMD_DE,
    CONFIRM_DE
};
#endif
