from m_wave import *
from itertools import *
import sys

def ncycles(iterable, n):
	return chain.from_iterable(repeat(tuple(iterable), n))

def waves():
	l = int(44100*1.000000)

	return chain(islice(damped_wave(frequency=494), l*0.500000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=330), l*0.333000),islice(damped_wave(frequency=294), l*0.333000),islice(damped_wave(frequency=494), l*0.334000),islice(damped_wave(frequency=349), l*0.750000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=262), l*0.500000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=494), l*0.500000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=294), l*0.333000),islice(damped_wave(frequency=392), l*0.333000),islice(damped_wave(frequency=294), l*0.334000),islice(damped_wave(frequency=494), l*0.500000),islice(damped_wave(frequency=294), l*0.166000),islice(damped_wave(frequency=494), l*0.166000),islice(damped_wave(frequency=392), l*0.168000),islice(damped_wave(frequency=330), l*0.500000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=440), l*0.500000),islice(damped_wave(frequency=392), l*0.166000),islice(damped_wave(frequency=494), l*0.166000),islice(damped_wave(frequency=330), l*0.168000),islice(damped_wave(frequency=294), l*0.500000),islice(damped_wave(frequency=294), l*0.166000),islice(damped_wave(frequency=392), l*0.166000),islice(damped_wave(frequency=294), l*0.168000),islice(damped_wave(frequency=330), l*0.500000),islice(damped_wave(frequency=440), l*0.166000),islice(damped_wave(frequency=494), l*0.166000),islice(damped_wave(frequency=494), l*0.168000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=330), l*0.500000),islice(damped_wave(frequency=262), l*0.166000),islice(damped_wave(frequency=392), l*0.166000),islice(damped_wave(frequency=330), l*0.168000),islice(damped_wave(frequency=440), l*0.500000),islice(damped_wave(frequency=294), l*0.166000),islice(damped_wave(frequency=493), l*0.166000),islice(damped_wave(frequency=392), l*0.168000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=440), l*0.750000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=494), l*0.500000),islice(damped_wave(frequency=349), l*0.166000),islice(damped_wave(frequency=294), l*0.166000),islice(damped_wave(frequency=494), l*0.168000),islice(damped_wave(frequency=494), l*0.500000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=440), l*0.500000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=494), l*0.333000),islice(damped_wave(frequency=262), l*0.333000),islice(damped_wave(frequency=294), l*0.334000),islice(damped_wave(frequency=262), l*0.750000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=392), l*0.750000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=440), l*0.500000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=440), l*0.333000),islice(damped_wave(frequency=349), l*0.333000),islice(damped_wave(frequency=494), l*0.334000),islice(damped_wave(frequency=262), l*0.500000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=330), l*0.750000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=330), l*0.750000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=494), l*0.500000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=261), l*0.250000),islice(damped_wave(frequency=440), l*0.333000),islice(damped_wave(frequency=349), l*0.333000),islice(damped_wave(frequency=493), l*0.334000),islice(damped_wave(frequency=349), l*0.500000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=440), l*0.500000),islice(damped_wave(frequency=294), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=392), l*0.500000),islice(damped_wave(frequency=293), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=330), l*0.500000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=392), l*0.750000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=440), l*0.333000),islice(damped_wave(frequency=349), l*0.333000),islice(damped_wave(frequency=440), l*0.334000),islice(damped_wave(frequency=294), l*0.750000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=262), l*0.500000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=330), l*0.333000),islice(damped_wave(frequency=349), l*0.333000),islice(damped_wave(frequency=349), l*0.334000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=493), l*0.250000),islice(damped_wave(frequency=262), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=330), l*0.250000),islice(damped_wave(frequency=392), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=440), l*0.250000),islice(damped_wave(frequency=349), l*0.333000),islice(damped_wave(frequency=262), l*0.333000),islice(damped_wave(frequency=294), l*0.334000),islice(damped_wave(frequency=440), l*0.500000),islice(damped_wave(frequency=349), l*0.166000),islice(damped_wave(frequency=349), l*0.166000),islice(damped_wave(frequency=494), l*0.168000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=349), l*0.250000),islice(damped_wave(frequency=494), l*0.250000),islice(damped_wave(frequency=494), l*0.250000))

channels = ((waves(),), (waves(), white_noise(amplitude=0.001),))
samples = compute_samples(channels, None)
write_wavefile(sys.stdout, samples, None)
