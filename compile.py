import sys
from optparse import OptionParser

def readOptions () :
	parser = OptionParser()
	parser.add_option("-i", "--input", dest="input", help="read latex layout from FILE", metavar="FILE")
	parser.add_option("-o", "--output", dest="output", help="write output latex to FILE", metavar="FILE")

	return parser.parse_args()

def getStyle (filename) :
	ext = filename.lower().split('.')[-1].strip()
	if ext in ['c', 'cc', 'cpp'] :
		return 'cpp'
	if ext in ['java'] :
		return 'java'
	if ext in ['py'] :
		return 'py'
	else :
		return 'txt'

def getTex (input) :
	tex = ''

	with open('./' + input) as inputFile :
		for line in inputFile :
			if len(line) > 3 and line[0:3] == ' - ':
				tex += "\section{%s}\n" % line[3:].strip()
			elif len(line) > 1 :
				tokens = line.split("/")
				tex += "\subsection{%s}\n" % tokens[1].strip().replace("_", "\\_")
				tex += "\lstinputlisting[style=%s]{%s}\n" %(getStyle(line), line.strip()	)

	return tex

def writeOutput (output, tex) :
	with open('./' + output, "w") as outputFile :
		outputFile.write(tex)

if __name__ == "__main__":
	args = readOptions()
	input = args[0].input or "content.txt"
	output = args[0].output or "content.tex"

	tex = getTex(input)
	writeOutput(output, tex)