
def print_args(arguments):

	for i in arguments:
		print(i)


if __name__ == "__main__":

	from sys import argv

	print_args(argv[1:])

	random_array = ["hello", "salut", "こんにちは"]

	print_args(random_array)

