import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as ticker

myFmt = mdates.DateFormatter("%H:%M")

minutes_15 = []

with open("15_min_density.txt") as myfile:
    minutes_15 = [int(x) for x in (myfile.read()).split()]

# make up some data
x_min_15 = [datetime.datetime(2, 2, 2) + datetime.timedelta(minutes=i) for i in range(0, 96*15, 15)]

fig, fig3 = plt.subplots()

fig3.plot(x_min_15, minutes_15)

fig3.grid(True)
fig3.xaxis.set_major_locator(ticker.MultipleLocator(1/48))

fig.set_figwidth(23)
fig.set_figheight(8)

plt.xlim(datetime.datetime(2, 2, 2, 0, 0), datetime.datetime(2, 2, 2, 23, 30))
plt.gcf().autofmt_xdate()
plt.gca().xaxis.set_major_formatter(myFmt)
plt.savefig("schedule_15_min_distribution.png")
plt.show()