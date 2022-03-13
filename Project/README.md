Boring Robot
===
This is a boring demo that a robot solves a maze.

Challenge and Solve
===
The challenge is determining where should robot turns to when it reaches a corner. The soultion is using three sensors, one points to x-positive directions and the other points to both positive and negative direction of y. Make sure robot turns to the direction that the bigger sensor_vlaue holds.

Setting Up Docker
===

To start the docker image environment, do
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash
```
Make sure your device connected with Internet so that it automatically download container for you if first time.

The Project Structure
===
The project structure should looks like
```
Makefile
config.json
defs/
lib/
src/
```

Running The Project
===
```
esm start
make
enviro
```
Navigate to `http://localhost`, the page will show you a robot is escaping from a maze
