import random as r
import crc8

InjectNoise = False
AutoGenData = False

kPreambleLen = 20
kDataLenMax = 0xF
assert (kDataLenMax <= 0xF)
kCrcLen = 8
kBitDuration_us = 50


if AutoGenData:
	data_len = r.randrange(1,kDataLenMax, 1)
	data = r.randrange(0,0x100**data_len, 1)
else:
	data_len = 8
	data = 0x1234123412341234
print("data:\n0x{:0{l}X}\n".format(data, l=data_len))

# Calculate crc on just data segment
crc = int(crc8.crc8(data.to_bytes(data_len, 'big')).digest().hex(), 16)
print("CRC8 is 0x{:X}".format(crc))
crc = "{:0{l}b}".format(crc, l=8)

# Generate binary string
data = "{:0{l}b}".format(data, l=data_len*8)

# Add preamble and start sequence
preamble = ""
for i in range(0,kPreambleLen):
	preamble += "1"	#Preamble is all 1's, relies on manchester encoding to generate edges
start_seq = "0"
length = "{:04b}".format(data_len)

# Assemble preamble, data, start sequence, and crc
bintext = preamble + start_seq + length + data + crc

print("Complete message (preamble, start, length, data, crc):\n{}\n{}".format(
	preamble + ' ' + start_seq + ' ' + length + ' ' + data + ' ' + crc,
	bintext))

# Generate Manchester Encoding
bintext_manchester = ""
for b in bintext:
	if b == "0":
		bintext_manchester += "10"
	if b == "1":
		bintext_manchester += "01"

print("Encoded in Manchester Encoding:\n{}\n".format(bintext_manchester))


time = 0.0
output = ""

# Add random duration of random noise in front of data
noise_dur_s = 0.0
if InjectNoise:
	noise_dur_s = r.randrange(kBitDuration_us*10, kBitDuration_us*100, 1)/1e6
	print("Injecting {} sec of noise ahead of data".format(noise_dur_s))
	while time < noise_dur_s:
		output += "{}, {}, {}\r\n".format(time, r.choice(['0','1']), 'pre-noise')
		time += r.randrange(1,kBitDuration_us,1) / 1e6

# Add trailing 0's to bitstream (to make sure rx state machine keeps going, and as another opportunity for high freq noise)
bintext_manchester += "000000"

next_time = time
for x in bintext_manchester:
	#TODO - inject noise only *after* data bit, make it shorter in duration, and return to data bit value after injecting it	
	time = next_time
	next_time = time + (kBitDuration_us / 1e6)
	output += "{}, {}, {}\r\n".format(time, x, 'data')
	if InjectNoise:
		# Add noise (random number of bits of random duration < bit duration)
		noise_bit_count = r.randrange(0,10,1)
		for _ in range(0,noise_bit_count):
			time = time + (r.randrange(0,kBitDuration_us) / 1e6)
			end_time = time + (r.randrange(0,kBitDuration_us/5) / 1e6)
			if end_time >= next_time:
				break
			output += "{}, {}, {}\r\n".format(time, r.choice(['0','1']), 'noise')
			output += "{}, {}, {}\r\n".format(end_time, x, 'un-noise') # return to data value after noise bit

# Add random duration of random noise behind data
if InjectNoise:
	noise_dur_s = r.randrange(kBitDuration_us*10, kBitDuration_us*100, 1)/1e6
	end_time = time + noise_dur_s
	print("Injecting {} sec of noise behind data".format(noise_dur_s))
	while time < end_time:
		output += "{}, {}, {}\r\n".format(time, r.choice(['0','1']), 'post-noise')
		time += r.randrange(1,kBitDuration_us,1) / 1e6

#print(output)

with open('generated_packet.csv', 'w') as f:
	f.write(output)
