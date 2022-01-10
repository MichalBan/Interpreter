import matplotlib.pyplot as plt


def plot(timeline):
	names = input("which variables to plot? (separate variables by coma and plots by semicolon)\n")
	names = names.replace(' ', '')
	plots_names = names.split(';')
	for i in range(len(plots_names)):
		names = plots_names[i].split(',')
		plt.figure(i+1)
		for name in names:
			if name not in timeline[0]:
				print("variable " + name + " does not exist")
				plt.close(1)
				return False
			signal = [x[name] for x in timeline]
			plt.plot(signal)
		plt.legend(names)
	plt.show()
	return True
