# FluoroLED

Drive LEDs like they're fluorescent indicators

## Goal

Make a rough simulation of calcium indicator fluorescence in a spiking neuron. Poisson spikes are randomly generated and modulate the brightness of an LED with fast on- and slow off-kinetics as well as saturation. This roughly approximates what a spiking neuron expressing a slow GCaMP would look like.

## Usage

| Potentiometer setting | Behavior |
| --- | --- |
| 0-5% | LED off |
| 5-95% | Variable spike rate mode: 0.5-10Hz as potentiometer increases |
| 95-100% | LED on |