#!/usr/bin/python/
import matplotlib.pyplot as plt
import math
import time

N = 4096
points = []

startTime = time.perf_counter()
for i in range(N+1):
    theta = (2*math.pi*(i/N))%(2*math.pi)
    y = math.sin(theta)
    uY = int(y * 32767)
    points.append((i, uY))

endTime = time.perf_counter()
timeElapsed = endTime - startTime
rate = N / timeElapsed

print(f"Calculated {N} values in {timeElapsed:.10f} seconds")
print(f"Effective rate: {rate:.3f} calculations/s")
x, y = zip(*points)

plt.plot(x, y)
plt.xlabel("Sample Number")
plt.ylabel("Amplitude")
plt.title("Wavetable Plot")
plt.show()