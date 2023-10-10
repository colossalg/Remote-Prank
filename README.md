# Remote-Prank
A silly device that records and replays IR signals (after 10 seconds) from TV remotes as a prank.

| | |
| --- | --- |
| ![20230407_161507](https://github.com/colossalg/Remote-Prank/assets/39691679/1c0fd683-e837-4a1e-87fb-7041da55c3fb) | ![20230407_161523](https://github.com/colossalg/Remote-Prank/assets/39691679/d99a44be-13f4-466e-b529-d296997f2782) |
| ![20230407_161501](https://github.com/colossalg/Remote-Prank/assets/39691679/0c87ee7a-eaf4-4fe1-9905-40361802942e) | ![20230407_161545](https://github.com/colossalg/Remote-Prank/assets/39691679/090b6cd6-132d-4992-bda4-863bf6201ab0) |

## Parts

The parts required for this project are:
- 1x Arduino Nano (with male header pin strips)
- 1x IR receiver
- 1x IR transmitter
- 1x 1kΩ resistor
- 2x Female header pin strips
- 1x 2 position wire to board mount
- 2x 3 position wire to board mount
- 1x prototyping board (or etch a PCB using the 1.25 scale PDF)
- 1x 4AAA switched battery pack
- Plenty of wire for both the connections on the prototype board as well as the IR reciever/transmitter cables
- Heat shrink tubing

## Flashing

This project uses the Arduino Nano, as such the flashing should be performed as usual via the Arduino IDE.

This project utilizes the Arduino-IRremote library found [here](https://github.com/Arduino-IRremote/Arduino-IRremote).

This should be installed as per the usual processes for adding a library to the Arduino IDE.

## Assembly

The components should be soldered together (using the prototype board) as per the circuit diagram below with one nuance; where the Arduino Nano is placed the female header pin strips should be soldered instead.

To the IR reciever and transmitter, 3 wires should be soldered.

These wires may then be wrapped in heat shrink tubing to make them more aesthetic.

To complete assembly:
- The battery pack may be connected to the 2 position wire to board mount as indicated by the schematic ($U4)
- The IR reciever may be connected to the 3 position wire to board mount as indicated by the schematic ($U3)
- The IR transmitter may be connected to the 3 position wire to board mount as indicated by the schematic ($U2)
- Zip-tie the battery pack to the prototype board.

![Screenshot 2023-10-10 113935](https://github.com/colossalg/Remote-Prank/assets/39691679/00877f4d-86fb-41f2-92bf-ee285f3a9ab9)

