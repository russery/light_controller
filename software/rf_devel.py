
import matplotlib.pyplot as plt
import numpy as np
import pandas
import pdb


#SOURCE_FILE_NAME = 'transmitted_data.csv'
#SOURCE_FILE_NAME = 'received_data.csv'
SOURCE_FILE_NAME = 'generated_packet.csv'


df = pandas.read_csv(SOURCE_FILE_NAME, header=None, names=['t', 'val'])
df['t'] = df['t'] * 1e6  # convert to us
df.sort_values('t', inplace=True)

#print(df)

def sample_rf_(t, df_):
	# In the real implementation, this will just be a periodic sample of the bus.
	# Here, it finds the current sample of the "bus" from the data file based on
	# current time increment.
	last_edge_row = df_[df_['t'].lt(t)].tail(1)
	if len(last_edge_row) > 0:
		#print('currently {} - last edge at {}'.format(t, last_edge_row['t'].values[0]))
		return last_edge_row['val'].values[0]
	else:
		return 0

class SampleBuffer:
	def __init__(self, length):
		self.vals = np.zeros(length)
		self.len = length
		self.cnt = 0

	def put(self, val):
		self.vals[self.cnt] = val;
		self.cnt += 1
		if self.cnt == self.len:
			pdb.set_trace()
			raise Exception('Overflowed sample buffer')

	def is_full(self):
		return self.cnt == (self.len - 1)

	def peek(self):
		if(self.cnt > 0):
			return self.vals[self.cnt-1]
		else:
			return -1

	def flush(self):
		self.vals = np.zeros(self.len)
		self.cnt = 0


def CheckBitCorrelation(samples, expected_bit):
	# TODO: find a better correlation algorithm. This rewards longer bits. Normalize to bit duration?
	c = 0
	for i in samples:
		if i == expected_bit:
			c += 1
	return c


def ProcessSample(samples):
	sym_len = int(len(samples) / 2)
	one_val = int(sym_len/2) + 1
	assert(sym_len*2 == len(samples)) # shouldn't be receiving an odd number of samples
	sym1 = sum(samples[0:sym_len-1]) >= one_val
	sym2 = sum(samples[sym_len:-1]) >= one_val
	if sym1 and not sym2: # 0b10
		return 0
	if not sym1 and sym2: # 0b01
		return 1
	pdb.set_trace()
	raise Exception("invalid manchester bit sequence from samples {}".format(samples))
	



kLoopDuration_us = 10.0
kMinBitDuration_us = 40.0
kMaxBitDuration_us = 60.0
kMinCorrelation = int(kMaxBitDuration_us/kLoopDuration_us*0.8)
kMaxSampleCnt = int(kMaxBitDuration_us/kLoopDuration_us * 5) # Need to store up to five bit periods of data
sb = SampleBuffer(kMaxSampleCnt+1)
kStates = ['kWaitRisingEdge', 'kSync', 'kAlign', 'kFinishPreamble', 'kData']
kPreambleLen = 20
kDataLen = 16
state_ = kStates[0]
samples_remaining_ = 0
bit_offset = 0
bit_dur = 1
bit_cnt = 0
data = 0
def DoRfReceive():	
	global state_, sb, samples_remaining_, bit_offset, bit_dur, bit_cnt, data
	#TODO Make sure interrupts are disabled when we're doing this for real to avoid conflicts on sample buffer
	if state_ == 'kWaitRisingEdge':
		if sb.peek() == 1:
			state_ = 'kSync'
		sb.flush()
	elif state_ == 'kSync':
		if sb.is_full():
			# Find bit offset and duration that maximizes correlation with [1,0]
			bit_correlation = 0
			bit_offset = 0
			bit_dur = 1
			for o in range(0,(int(kMaxBitDuration_us/kLoopDuration_us)*2)+1): # Offsets from 0 up to two bit periods
				for d in range(int(kMinBitDuration_us/kLoopDuration_us), int(kMaxBitDuration_us/kLoopDuration_us)+1): # Allow durations within valid range
					correlation = 0
					for b in range(0,6):
						correlation += CheckBitCorrelation(sb.vals[o+(d*b):o+(d*(b+1))], (b+1)%2)
					print('Correlation {} for offset {} and duration {}'.format(correlation, o, d))
					if correlation >= bit_correlation: # Better than last best
						bit_correlation = correlation
						bit_offset = o
						bit_dur = d

			if bit_correlation > (kMinCorrelation * 4):
				print('Found preamble sequence with best offset {} and duration {} and correlation {}'.format(bit_offset, bit_dur, bit_correlation))
				samples_remaining_ = bit_dur - ((kMaxSampleCnt - bit_offset) % bit_dur) - 1
				sb.flush() # TODO, ideally we wouldn't discard the samples we've received so far
				state_ = 'kAlign'
			else:
				print('Could not find good sync for edge')
				sb.flush() # TODO We should actually search the buffer for edges and try sync again, rather than just dropping these
				state_ = 'kWaitRisingEdge'
			
	elif state_ == 'kAlign':
		print('Aligning by receiving {} more bits'.format(samples_remaining_))
		samples_remaining_ -= 1
		if samples_remaining_ == 0:
			sb.flush() # TODO ideally we'd check this bit against an expected sample
			bit_cnt = 0
			state_ = 'kFinishPreamble'

	elif state_ == 'kFinishPreamble':
		if sb.cnt == bit_dur * 2:
			if ProcessSample(sb.vals[0:bit_dur*2]) == 0: # Received stop bit.
				print('Detected Start bit')
				bit_cnt = 0
				data = 0
				state_ = 'kData'
			else:
				bit_cnt += 1
				if bit_cnt > kPreambleLen:
					print('Preamble too long, restarting')
					state_ = 'kWaitRisingEdge'
			sb.flush()
		# TODO Periodically re-sync on edges? Depending on how well aligned we are this might not be necessary.

	elif state_ == 'kData':
		if sb.cnt == bit_dur * 2:
			bit_cnt += 1
			bit = ProcessSample(sb.vals[0:bit_dur*2])
			data = data << 1
			data += bit
			print("{} Got data bit 0b{:b}".format(bit_cnt, bit))
			if bit_cnt == (kDataLen + 1): # Received all data and parity bit
				# Check parity:
				p = 0
				d = data >> 1
				while d != 0:
					if d % 2:
						p += 1
					d = d >> 1
				p = p % 2
				if p != (data % 2):
					print('BAD PARITY {}'.format(p))
				# Process packet:
				print('Data received:\n0x{:X}'.format(data>>1))
				# Reset state machine
				state_ = 'kWaitRisingEdge'
			sb.flush()


for t in np.arange(min(df['t']), max(df['t']+kMaxBitDuration_us), kLoopDuration_us):
	sb.put(sample_rf_(t, df))
	#print(t)
	DoRfReceive()

