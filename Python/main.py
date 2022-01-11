import msvcrt
from port_init import initialize_port
from metrics import mean_square_dialog
from plots import plot_dialog
from runtime_data import read_runtime_data
from code_transmission import transmit_code
from exceptions_and_errors import set_up_exception_handler
from log import log


def main():
	set_up_exception_handler()
	port = initialize_port()
	wait_for_MCU(port)
	read_metadata_dialog(port)
	transmit_code(port)
	timeline = read_runtime_data(port)
	log(timeline)
	plot_dialog(timeline)
	mean_square_dialog(timeline)
	wait_for_any_key()


def read_metadata_dialog(port):
	message = "type 'm' to receive metadata or any other key to start interpretation.\n"
	choice = input(message)
	while choice == 'm':
		port.write(b'm')
		print(port.readline().decode("utf-8"))
		choice = input(message)
	port.write(b'r')


def wait_for_any_key():
	print("press any key to close")
	msvcrt.getch()


def wait_for_MCU(port):
	print("start / restart MCU")
	port.read(1)


if __name__ == '__main__':
	main()
