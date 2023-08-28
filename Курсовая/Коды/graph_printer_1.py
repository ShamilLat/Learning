import datetime
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import matplotlib.ticker as ticker

myFmt = mdates.DateFormatter("%H:%M")

one_hour = []

with open("1_hour_density.txt") as myfile:
    one_hour = [int(x) for x in (myfile.read()).split()]

# make up some data
x_hour_1 = [datetime.datetime(2, 2, 2) + datetime.timedelta(hours=i) for i in range(24)]

fig, fig1 = plt.subplots()

fig1.plot(x_hour_1, one_hour)

fig1.grid(True)
fig1.xaxis.set_major_locator(ticker.MultipleLocator(1/24))

fig.set_figwidth(23)
fig.set_figheight(8)

plt.xlim(datetime.datetime(2, 2, 2, 0, 0), datetime.datetime(2, 2, 2, 23, 0))
plt.gcf().autofmt_xdate()
plt.gca().xaxis.set_major_formatter(myFmt)
plt.savefig("schedule_1_hour_distribution.png")
#plt.show()