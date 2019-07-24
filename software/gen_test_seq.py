InjectNoise = True
kPreambleLen = 20
kDataLen = 10 # Length in bytes
assert (kDataLen <= 0xF)
kParityBits = 1 # TODO change this out for a hamming code, or maybe a CRC https://www.w3.org/TR/PNG-CRCAppendix.html
kBitDuration_us = 50

testseq = 0xA235
print("input:\n0x{:0{l}X}\n".format(testseq, l=kDataLen))

# Generate bit sequence
data = "{:0{l}b}".format(testseq, l=kDataLen*8)
print("binary:\n{}\n".format(data))


# Calculate parity on just data segment
parity = str(data.count('1') % 2)

# Add preamble and start sequence
preamble = ""
for i in range(0,kPreambleLen):
	preamble += "1"	#Preamble is all 1's, relies on manchester encoding to generate edges

start_seq = "0"

length = "{:04b}".format(kDataLen)

# Assemble preamble, data, start sequence, and parity
bintext = preamble + start_seq + length + data + parity

print("Complete message (preamble, start, length, data, parity):\n{}\n{}".format(
	preamble + ' ' + start_seq + ' ' + length + ' ' + data + ' ' + parity,
	bintext))

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
# TODO: Add random noise in front of data
for x in bintext_manchester:
	
	# Add noise (random bit flips of duration << bit duration)
	line = "{}, {}".format(time, x) 
	output += line + "\r\n"
	print(line)
	time += kBitDuration_us / 1e6 # Write in seconds


with open('generated_packet.csv', 'w') as f:
	f.write(output)
