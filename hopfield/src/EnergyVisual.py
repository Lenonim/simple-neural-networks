from matplotlib.pyplot import figure, show
import keyboard

class ZoomPan:
    def __init__(self):
        self.press = None
        self.cur_xlim = None
        self.cur_ylim = None
        self.x0 = None
        self.y0 = None
        self.x1 = None
        self.y1 = None
        self.xpress = None
        self.ypress = None

    def zoom_factory(self, ax, base_scale = 2.):
        def zoom(event):
            cur_xlim = ax.get_xlim()
            cur_ylim = ax.get_ylim()

            xdata = event.xdata
            ydata = event.ydata

            if event.button == 'up':
                scale_factor = 1 / base_scale
            elif event.button == 'down':
                scale_factor = base_scale
            else:
                scale_factor = 1

            new_width = (cur_xlim[1] - cur_xlim[0]) * scale_factor
            new_height = (cur_ylim[1] - cur_ylim[0]) * scale_factor

            relx = (cur_xlim[1] - xdata) / (cur_xlim[1] - cur_xlim[0])
            rely = (cur_ylim[1] - ydata) / (cur_ylim[1] - cur_ylim[0])

            if (keyboard.is_pressed("shift")):
                ax.set_xlim([xdata - new_width * (1 - relx), xdata + new_width * (relx)])
            elif (keyboard.is_pressed("ctrl")):
                ax.set_ylim([ydata - new_height * (1 - rely), ydata + new_height * (rely)])
            else:
                ax.set_xlim([xdata - new_width * (1 - relx), xdata + new_width * (relx)])
                ax.set_ylim([ydata - new_height * (1 - rely), ydata + new_height * (rely)])

            ax.figure.canvas.draw()

        fig = ax.get_figure()
        fig.canvas.mpl_connect('scroll_event', zoom)

        return zoom

    def pan_factory(self, ax):
        def onPress(event):
            if event.inaxes != ax: return
            self.cur_xlim = ax.get_xlim()
            self.cur_ylim = ax.get_ylim()
            self.press = self.x0, self.y0, event.xdata, event.ydata
            self.x0, self.y0, self.xpress, self.ypress = self.press

        def onRelease(event):
            self.press = None
            ax.figure.canvas.draw()

        def onMotion(event):
            if self.press is None: return
            if event.inaxes != ax: return
            dx = event.xdata - self.xpress
            dy = event.ydata - self.ypress
            self.cur_xlim -= dx
            self.cur_ylim -= dy
            ax.set_xlim(self.cur_xlim)
            ax.set_ylim(self.cur_ylim)

            ax.figure.canvas.draw()

        fig = ax.get_figure()

        fig.canvas.mpl_connect('button_press_event',onPress)
        fig.canvas.mpl_connect('button_release_event',onRelease)
        fig.canvas.mpl_connect('motion_notify_event',onMotion)

        return onMotion


def zoom_visualisation(_x=[], _y=[]):
    fig = figure()

    max_y = 0.0
    min_y = 0.0
    for y in _y:
        if max_y < y:
            max_y = y
        elif min_y > y:
            min_y = y

    ax = fig.add_subplot(111, xlim=(_x[0], _x[len(_x) - 1]), ylim=(min_y, max_y), autoscale_on=False)

    ax.plot(_x, _y, color='b')
    ax.grid(True)

    scale = 1.1
    zp = ZoomPan()
    figZoom = zp.zoom_factory(ax, base_scale=scale)
    figPan = zp.pan_factory(ax)
    show()

# for data storage
error_target_value = []
error_time = []

# read data with primary data processing
file_name = "Energy.csv"
work_file = open(file_name, 'r')
for line in work_file.readlines():
    if line == '\n':
        break
    line = line.replace("\n", "")
    line_parts = line.split(';')
    error_time.append(int(line_parts[0]))
    error_target_value.append(float(line_parts[1]))
work_file.close()

zoom_visualisation(error_time, error_target_value)
