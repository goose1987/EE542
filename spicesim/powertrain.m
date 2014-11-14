
clear all;
close all;

Vg=20; %input voltage
Vout=15; %output voltage
Iload=5; %load current

Vm=4; %PWM amplitude

%inductance 
L=100e-6;

%capacitance
C=10e-6;

%switching frequency
fs=50e3;

R=Vout/Iload;



A=[	0	-1/L;
	1/C -1/(R*C) ];

B=[	1/L;
	0   ];



