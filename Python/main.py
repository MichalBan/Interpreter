import copy

import matplotlib.pyplot as plt
import serial

if __name__ == '__main__':
	ser = serial.Serial(
		port='COM4',
		baudrate=115200,
		bytesize=serial.EIGHTBITS,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		timeout=1000)

	print("Let us begin")
	print("waiting...")
	request = ser.read(1)
	with open("kod.txt") as f:
		while request == b'c':
			c = f.read(1)
			if not c:
				ser.write(b'\0')
				ser.write(b'\0')
				print("End of file")
				break
			print("sending: ", c)
			ser.write(c.encode('ascii'))
			request = ser.read(1)

	if request == b'$':
		while True:
			message = ser.read(1)
			print(message)

	result = {}
	timeline = []
	identifiers = []
	ser.readline()
	line = ser.readline()
	while not line == b'fin\n':
		iterator = 0
		name = ""
		value = ""
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
		line = ser.readline()

	if line[0] == b'$':
		while True:
			message = ser.read(1)
			print(message)

	for name in identifiers:
		signal = [x[name] for x in timeline]
		plt.plot(signal)
	plt.legend(identifiers)
	plt.show()

	print("It is done")
