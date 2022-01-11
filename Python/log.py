from os import mkdir


def log(timeline):
	try:
		mkdir("logs")
	except FileExistsError:
		pass
	for name in timeline[0].keys():
		log_name = "logs/" + name + ".log"
		log_handle = open(log_name, 'w')
		for data in timeline:
			log_handle.write(str(data[name]) + '\n')
		log_handle.close()
