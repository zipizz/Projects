import sys
import fileinput

beforeStr = sys.argv[1]
afterStr = sys.argv[2]

for i, line in enumerate(fileinput.input(sys.argv[3], inplace=1)):
	sys.stdout.write(line.replace(beforeStr, afterStr))
