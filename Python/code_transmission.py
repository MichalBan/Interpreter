from exceptions_and_errors import handle_error


def transmit_code(port):
	print("sending code\n")
	request = get_request(port)
	with open("kod.txt") as f:
		while request == b'c':
			code_char = f.read(1)
			if not code_char:
				port.write(b'\0\0')
				print("\n\nCode transmission complete")
				return
			print(code_char, end="")
			port.write(code_char.encode('ascii'))
			request = get_request(port)


def get_request(port):
	request = port.read(1)
	if request == b'$':
		handle_error(port)
	return request
