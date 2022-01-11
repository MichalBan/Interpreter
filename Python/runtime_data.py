import copy
import msvcrt
from exceptions_and_errors import check_for_error_message


def read_runtime_data(port):
	print("executing code\nPress any key to interrupt")
	timeline = []
	port.read(1)
	line = port.readline()
	while not line == b'fin\n':
		result = read_loop_data(line, port)
		timeline.append(copy.deepcopy(result))
		if msvcrt.kbhit():
			return interrupt(port, timeline)
		line = port.readline()
	return timeline


def read_loop_data(line, port):
	check_for_error_message(line, port)
	result = {}
	iterator = 0
	while line[iterator] != ord('\n'):
		iterator, name = build_name(iterator, line)
		iterator, value = build_value(iterator, line)
		result[name] = float(value)
	return result


def build_value(iterator, line):
	value = ""
	while ord('-') <= line[iterator] <= ord('9'):
		value = value + chr(line[iterator])
		iterator = iterator + 1
	iterator = iterator + 1
	return iterator, value


def build_name(iterator, line):
	name = ""
	while line[iterator] != ord('='):
		name = name + chr(line[iterator])
		iterator = iterator + 1
	iterator = iterator + 1
	return iterator, name


def interrupt(port, timeline):
	port.write(b'e')
	msvcrt.getch()
	print("interrupted")
	return timeline
