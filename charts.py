import sys
import glob
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import AutoMinorLocator

files = sys.argv
if len(files) <= 1:
    files = glob.glob('*.txt')
    print(files)

fig, ax = plt.subplots(figsize=(8, 6))
ax.set_title('Matrix testing', fontsize=16)
ax.set_xlabel('Matrix size (column or row count)', fontsize=14)
ax.set_ylabel('Measured time (seconds)', fontsize=14)
labels = ['Sequential', 'Threads: 12', 'Threads: 2', 'Threads: 4']
styles = ['o-r', 'o-b', 'o--r', 'o--b']

for file, style, label in zip(files, styles, labels):
    data = np.loadtxt(file, delimiter=';')
    x = data[:, 0]
    y = data[:, 1]
    ax.plot(x, y, style, label=label)


ax.grid(which="major", linewidth=1.2)
ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)
ax.legend()
ax.xaxis.set_minor_locator(AutoMinorLocator())
ax.yaxis.set_minor_locator(AutoMinorLocator())
ax.tick_params(which='major', length=10, width=2)
ax.tick_params(which='minor', length=5, width=1)
plt.show()
