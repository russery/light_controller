
kPreambleLen = 20
kDataLen = 16
kParityBits = 1 # TODO change this out for a hamming code, or maybe a CRC https://www.w3.org/TR/PNG-CRCAppendix.html
kBitDuration_us = 50

testseq = 0x1234
print("input:\n0x{0:X}\n".format(testseq))

# Generate bit sequence
bintext = "{:016b}".format(testseq)
print("binary:\n{}\n".format(bintext))


# Calculate parity on just data segment
parity = str(bintext.count('1') % 2)

# Add preamble and start sequence
preamble = ""
for i in range(0,kPreambleLen):
	preamble += "1"	#Preamble is all 1's, relies on manchester encoding to generate edges

start_seq = "0"

# Assemble preamble, data, start sequence, and parity
bintext = preamble + start_seq + bintext + parity

print("Complete message (preamble, start, data, parity):\n{}".format(bintext))

# Generate Manchester Encoding
bintext_manchester = ""
for b in bintext:
	if b == "0":
		bintext_manchester += "10"
	if b == "1":
		bintext_manchester += "01"

print("Encoded in Manchester Encoding:\n{}\n".format(bintext_manchester))

# Generate nominal timing
time = 0.0
output = ""
for x in bintext_manchester:
	# Add random noise in front of data
	# Add noise (random bit flips of duration << bit duration)
	line = "{}, {}".format(time, x) 
	output += line + "\r\n"
	print(line)
	time += kBitDuration_us / 1e6 # Write in seconds


with open('generated_packet.csv', 'w') as f:
	f.write(output)
