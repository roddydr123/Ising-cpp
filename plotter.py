import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np


def updateFigure(i, im, filename):
    try:
        data = np.genfromtxt(filename, delimiter=" ")
        im.set_data(data)
    except FileNotFoundError:
        pass
    return im
    


def main():
    filename = "output.dat"
    data = np.genfromtxt(filename, delimiter=" ")
    fig, ax = plt.subplots()
    im = ax.imshow(data)
    ani = FuncAnimation(fig, updateFigure, fargs=(im, filename))
    plt.show()

main()