import serial


def initialize_port():
	ser = serial.Serial(
		port='COM4',
		baudrate=115200,
		bytesize=serial.EIGHTBITS,
		parity=serial.PARITY_NONE,
		stopbits=serial.STOPBITS_ONE,
		timeout=1000)
	return ser
