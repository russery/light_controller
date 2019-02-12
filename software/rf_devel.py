
import matplotlib.pyplot as plt
import pandas


SOURCE_FILE_NAME = "transmitted_data.csv"
SOURCE_FILE_NAME = "received_data.csv"

BIT_WIDTH_MS = 6
BIT_TOLERANCE_MS = 0.5


df = pandas.read_csv(SOURCE_FILE_NAME, header=None, names=["t", "val"])
df['t'] = df['t'] * 1000  # convert to ms
df['dt'] = df['t'].diff()
df.plot('t', 'val')
plt.show()
df.plot('t', 'dt')
plt.show()

for dt in df['dt']:
	print('edge: {}'.format(dt))
	# Verify that we haven't missed an edge, and discard it if we have
	# If bit width is within valid range, add it to bit buffer
	# Keep a buffer of the last x edges
	# If 
