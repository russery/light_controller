
import textwrap

testseq = 0xF0000aa123456789ABCDEFF123456789A

print("input: {0:X}\n".format(testseq))

bintext = "{:0b}\n".format(testseq)
print("binary: {}\n".format(bintext))

outbin = ""
for b in bintext:
	if b == "0":
		outbin += "00000"
	else:
		outbin += "11111"

outbin = int(outbin, 2)
print("output binary: {0:b}\n".format(outbin))

outhex = "{0:X}".format(outbin)
print("output hex: {}\n".format(outhex))

print("output array: {}".format(', 0x'.join(textwrap.wrap(outhex, 2))))



