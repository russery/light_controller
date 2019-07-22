
import matplotlib.pyplot as plt
import numpy as np
import pandas
import pdb


SOURCE_FILE_NAME = 'transmitted_data.csv'
#SOURCE_FILE_NAME = 'received_data.csv'


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
		if self.cnt > self.len:
			pdb.set_trace()
			raise Exception('Overflowed sample buffer')

	def flush(self):
		self.vals = np.zeros(self.len)
		self.cnt = 0


kMinCorrelation = 4
def CheckBitCorrelation(samples, expected_bit):
	# TODO: find a better correlation algorithm. This rewards longer bits. Normalize to bit duration?
	c = 0
	for i in samples:
		if i == expected_bit:
			c += 1
	return c


def ProcessSample(sample):
	#TODO: Decode Manchester encoding on data segment
	pass


kLoopDuration_us = 1000.0
kMinBitDuration_us = 4000.0
kMaxBitDuration_us = 6000.0
kMaxSampleCnt = int(kMaxBitDuration_us/kLoopDuration_us * 5) # Need to store up to five bit periods of data
sb = SampleBuffer(kMaxSampleCnt)
kStates = ['kWaitRisingEdge', 'kSync', 'kAlign', 'kFinishPreamble', 'kData']
state_ = kStates[0]
samples_remaining_ = 0
def DoRfReceive(sample, time):	
	global state_, sb, samples_remaining_
	print("{}, {}, {}".format(state_, time, sample))
	if state_ == 'kWaitRisingEdge':
		if sample != 0:
			state_ = 'kSync'
			sb.put(sample)
			print('Found edge at {}'.format(time))
	elif state_ == 'kSync':
		sb.put(sample)
		if sb.cnt == kMaxSampleCnt:
			# Find bit offset and duration that maximizes correlation with [1,0]
			bit_correlation = 0
			bit_offset = 0
			bit_dur = 1
			for o in range(0,(int(kMaxBitDuration_us/kLoopDuration_us)*2)+1): # Offsets from 0 up to a two bit periods
				for d in range(int(kMinBitDuration_us/kLoopDuration_us), int(kMaxBitDuration_us/kLoopDuration_us)+1): # Allow durations within valid range
					correlation = CheckBitCorrelation(sb.vals[o:o+d], 1)
					correlation += CheckBitCorrelation(sb.vals[o+d:o+(d*2)], 0)
					correlation += CheckBitCorrelation(sb.vals[o+(d*2):o+(d*3)], 1)
					print('Correlation {} for offset {} and duration {}'.format(correlation, o, d))
					if correlation >= bit_correlation: # Better than last best
						bit_correlation = correlation
						bit_offset = o
						bit_dur = d

			if bit_correlation > (kMinCorrelation * 2):
				print('Found 0b10 sequence with best offset {} and duration {} and correlation {}'.format(bit_offset, bit_dur, bit_correlation))
				samples_remaining_ = bit_dur - ((kMaxSampleCnt - bit_offset) % bit_dur)
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
			state_ = 'kFinishPreamble'
		# TODO ideally we'd check this bit against an expected sample

	elif state_ == 'kFinishPreamble':
		pdb.set_trace()
		ProcessSample(sample)
		# Check for end of preamble sequence in bit buffer
			# if we have it, flush the buffer
		# Else if we've received more bits than expected in the preamble, reset to kWaitRisingEdge
		# TODO Periodically re-sync on edges
	elif state_ == 'kData':
		ProcessSample(sample)
		pass

# 000000000111100001111000011110000
# 100000000101100001110000011110010
# 10101010101110100
# 100 1111 0000 1



# Wait for an edge
# Edge received, wait up to kMaxBitDuration_us for another edge

for t in np.arange(min(df['t']), max(df['t']), kLoopDuration_us):
	DoRfReceive(sample_rf_(t, df), t)

