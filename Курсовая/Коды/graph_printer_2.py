import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as ticker

myFmt = mdates.DateFormatter("%H:%M")

minutes_30 = []

with open("30_min_density.txt") as myfile:
    minutes_30 = [int(x) for x in (myfile.read()).split()]

# make up some data
x_min_30 = [datetime.datetime(2, 2, 2) + datetime.timedelta(minutes=i) for i in range(0, 48*30, 30)]

fig, fig2 = plt.subplots()

fig2.plot(x_min_30, minutes_30)

fig2.grid(True)
fig2.xaxis.set_major_locator(ticker.MultipleLocator(1/48))

fig.set_figwidth(23)
fig.set_figheight(8)

plt.xlim(datetime.datetime(2, 2, 2, 0, 0), datetime.datetime(2, 2, 2, 23, 30))
plt.gcf().autofmt_xdate()
plt.gca().xaxis.set_major_formatter(myFmt)
plt.savefig("schedule_30_min_distribution.png")
plt.show()