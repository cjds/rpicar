# RPICar

Small repo showing how to build an RPI Car code from scratch. This is stupidly overkill for this car but I'm having fun


## How to use:

I'm optimizing for Linux so if you're on Mac, good luck chuck.

Run `./build.sh` to build the Docker that this program uses as it's default docker
Run `./run.sh` to start a new instance of that Docker. 

### Compiling the code:

```
docker exec -it rpicar bash
```
to enter the Docker you have made.


```
bb
```
will by default compile the code for Raspberry Pi

```
bbx86
```
will compile the code for an x86 computer




