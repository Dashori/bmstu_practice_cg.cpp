import matplotlib.pyplot as plot

file = open("result.txt", "r") 

faces = []
time = []

while True:
    line = file.readline()

    if not line:
        break

    faces.append([int(x) for x in line.split()][0])
    time.append([int(x) for x in line.split()][1])


plot.xlabel("Faces")
plot.ylabel("Time")
plot.grid(True)

plot.plot(faces, time, color = "red")
plot.savefig("result.png")

