import serial
import time

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
	with open("kod.txt") as f:
		while True:
			request = ser.read(1)
			if not request == b'c':
				while True:
					message = ser.read(1)
					print(message)
			c = f.read(1)
			print("sending: ", c)
			ser.write(c.encode('ascii'))
			if not c:
				ser.write(b'\0')
				ser.write(b'\0')
				print("End of file")
				break

	print("It is done")
