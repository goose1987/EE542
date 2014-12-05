# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\USER\Documents\GitHub\EE542\firmware\invert\invert.cydsn\invert.cyprj
# Date: Fri, 05 Dec 2014 06:39:10 GMT
#set_units -time ns
create_clock -name {ADC_DelSig_V_Ext_CP_Clk(routed)} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_DelSig_V_Ext_CP_Clk} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {ADC_DelSig_V_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 11 23} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_clock -name {ADC_DelSig_V_theACLK(fixed-function)} -period 458.33333333333331 -waveform {0 229.166666666667} [get_pins {ClockBlock/aclk_glb_ff_0}]
create_generated_clock -name {Clock_3} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {Clock_4} -source [get_pins {ClockBlock/clk_sync}] -edges {1 25 49} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 313 627} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 41.666666666666664 -waveform {0 20.8333333333333} [get_pins {ClockBlock/clk_bus_glb_ff}]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\USER\Documents\GitHub\EE542\firmware\invert\invert.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\USER\Documents\GitHub\EE542\firmware\invert\invert.cydsn\invert.cyprj
# Date: Fri, 05 Dec 2014 06:39:00 GMT
