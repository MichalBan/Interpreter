import traceback
import msvcrt
import sys


def set_up_exception_handler():
	sys.excepthook = show_exception_and_exit


def check_for_error_message(line, port):
	if line[0] == b'$':
		handle_error(port)


def show_exception_and_exit(exc_type, exc_value, tb):
	traceback.print_exception(exc_type, exc_value, tb)
	print("Press any key to exit")
	msvcrt.getch()
	sys.exit(-1)


def handle_error(port):
	while True:
		print("")
		message = port.readline()
		print(message, end="")
