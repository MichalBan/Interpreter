def mean_square_dialog(timeline):
	print("calculating")
	while not mean_square(timeline):
		pass


def mean_square(timeline):
	metric_names = get_metric_names()
	for j in range(len(metric_names)):
		names = metric_names[j].split(',')
		if len(names) != 2:
			print("exactly 2 variables needed")
			return False
		for name in names:
			if name not in timeline[0]:
				print("variable " + name + " does not exist")
				return False
		var0 = [x[names[0]] for x in timeline]
		var1 = [x[names[1]] for x in timeline]
		result = calculate_mean_square(var0, var1)
		print(result)
	return True


def calculate_mean_square(var0, var1):
	result = 0
	for i in range(len(var0)):
		result = result + (var0[i] - var1[i]) ** 2
	return result


def get_metric_names():
	metric_names = input(
		"which variables to calculate mean square error from? (separate variables by coma and metrics by semicolon)\n")
	metric_names = metric_names.replace(' ', '')
	metric_names = metric_names.split(';')
	return metric_names
