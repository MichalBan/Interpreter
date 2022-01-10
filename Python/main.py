import copy
import msvcrt
import serial
import sys
import traceback
from plot import *


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
	print("")
	request = port.read(1)
	with open("kod.txt") as f:
		while request == b'c':
			c = f.read(1)
			if not c:
				port.write(b'\0')
				port.write(b'\0')
				print("\n\nCode transmission complete")
				break
			print(c, end="")
			port.write(c.encode('ascii'))
			request = port.read(1)
			if request == b'$':
				handle_error(port)


def read_runtime_data(port):
	print("Press any key to interrupt")
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
			msvcrt.getch()
			print("interrupted")
			return timeline
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


def mean_square(timeline):
	names = input("which variables to calculate mean square error from? (separate variables by coma)\n")
	names = names.replace(' ', '')
	names = names.split(',')
	if len(names) != 2:
		print("exacly 2 variables needed")
		return False
	for name in names:
		if name not in timeline[0]:
			print("variable " + name + " does not exist")
			return False
	var0 = [x[names[0]] for x in timeline]
	var1 = [x[names[1]] for x in timeline]
	result = 0
	for i in range(len(var0)):
		result = result + (var0[i] - var1[i]) ** 2
	print(result)
	return True


def read_metadata_choice(port):
	message = "type 'm' to receive metadata or any other key to start interpretation.\n"
	choice = input(message)
	while choice == 'm':
		port.write(b'm')
		print(port.readline().decode("utf-8"))
		choice = input(message)
	port.write(b'r')


def main():
	sys.excepthook = show_exception_and_exit
	port = initialize_port()

	print("start / restart MCU")
	port.read(1)
	read_metadata_choice(port)

	print("sending code")
	transmit_code(port)

	print("executing code")
	timeline = read_runtime_data(port)

	print("plotting")
	while not plot(timeline):
		pass

	print("calculating")
	while not mean_square(timeline):
		pass

	print("press any key to close")
	msvcrt.getch()


if __name__ == '__main__':
	main()
