#ifndef SRC_DIALOG_HANDLER_H_
#define SRC_DIALOG_HANDLER_H_

#include "Function_handler.h"

class Dialog_handler
{
	SINGLETON(Dialog_handler);
public:
	static Dialog_handler& get_instance();
	static void metadata_dialog();
};

#endif
