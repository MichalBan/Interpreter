import matplotlib.pyplot as plt


def plot(timeline):
	identifiers = timeline[0].keys()
	for name in identifiers:
		signal = [x[name] for x in timeline]
		plt.plot(signal)
	plt.legend(identifiers)
	plt.show()
