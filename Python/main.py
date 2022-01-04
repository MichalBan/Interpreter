import copy
import msvcrt
import serial
import sys
import traceback
from plot import plot


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


def transmit_code(port):
	print("waiting for MCU")
	request = port.read(1)
	print("sending code")
	with open("kod.txt") as f:
		while request == b'c':
			c = f.read(1)
			if not c:
				port.write(b'\0')
				port.write(b'\0')
				print("\nCode transmission complete")
				break
			print(c, end="")
			port.write(c.encode('ascii'))
			request = port.read(1)
			if request == b'$':
				handle_error(port)


def read_runtime_data(port):
	result = {}
	timeline = []
	identifiers = []
	port.readline()
	line = port.readline()
	while not line == b'fin\n':
		iterator = 0
		name = ""
		value = ""
		if line[0] == b'$':
			handle_error(port)
		while line[iterator] != 10:
			while line[iterator] != 61:
				name = name + chr(line[iterator])
				iterator = iterator + 1
			if len(timeline) == 0:
				identifiers.append(name)
			iterator = iterator + 1

			while 45 <= line[iterator] <= 57:
				value = value + chr(line[iterator])
				iterator = iterator + 1
			iterator = iterator + 1

			result[name] = float(value)
			name = ""
			value = ""
		timeline.append(copy.deepcopy(result))
		if msvcrt.kbhit():
			port.write(b'e')
			print("interrupted")
		line = port.readline()
	return timeline


def initialize_port():
	ser = serial.Serial(
		port='COM4',
		baudrate=115200,
		bytesize=serial.EIGHTBITS,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		timeout=1000)
	return ser


def main():
	sys.excepthook = show_exception_and_exit
	port = initialize_port()

	print("Press any key to start")
#	msvcrt.getch()
	transmit_code(port)

	print("Executing code. Press any key to interrupt")
	timeline = read_runtime_data(port)

	print("plotting")
	plot(timeline)


if __name__ == '__main__':
	main()
