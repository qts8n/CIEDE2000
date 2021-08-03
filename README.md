# CIE Delta E 2000 (CIEDE2000)

A C-library containing a function to determine how similar two colors are.
The code here is based on this [C++ implementation](https://github.com/gfiumara/CIEDE2000)
of psuedocode written in the paper
[The CIEDE2000 Color-Difference Formula](http://www.ece.rochester.edu/~gsharma/ciede2000/),
by Gaurav Sharma, Wencheng Wu, and Edul N. Dalal.

## Build

```bash
make
```

## To Note
The `CIEDE2000` algorithm uses colors from the 
[LAB colorspace](http://en.wikipedia.org/wiki/Lab_color_space), not RGB.
To use the library methods, convert the image colorspace first.
