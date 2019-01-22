from ._dutyroll import __rollduty_fixed, __rollduty_variable


def rollduty(*args):
	if len(args) == 3:
		return __rollduty_fixed(*args)
	elif len(args) == 4:
		return __rollduty_variable(*args)
	else:
		raise Exception('Invalid function call.')
