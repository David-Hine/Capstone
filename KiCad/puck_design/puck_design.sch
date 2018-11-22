EESchema Schematic File Version 4
LIBS:puck_design-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Microcontroller and peripherals"
Date "2018-11-21"
Rev "v01"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Author: Team 2"
$EndDescr
$Comp
L puck_library:ITG-3701 U?
U 1 1 5BF49DCF
P 2300 3850
F 0 "U?" H 3041 3946 50  0000 L CNN
F 1 "ITG-3701" H 3041 3855 50  0000 L CNN
F 2 "" H 2300 3850 50  0001 C CNN
F 3 "" H 2300 3850 50  0001 C CNN
	1    2300 3850
	1    0    0    -1  
$EndComp
$Comp
L puck_library:TE832-M1 U?
U 1 1 5BF49E68
P 5750 2200
F 0 "U?" H 5275 2515 50  0000 C CNN
F 1 "TE832-M1" H 5275 2424 50  0000 C CNN
F 2 "" H 5300 2500 50  0001 C CNN
F 3 "" H 5300 2500 50  0001 C CNN
	1    5750 2200
	1    0    0    -1  
$EndComp
$Comp
L puck_library:nRF52840 U?
U 1 1 5BF58B8B
P 5250 4500
F 0 "U?" H 5250 4600 50  0000 C CNN
F 1 "nRF52840" H 5250 4500 50  0000 C CNN
F 2 "Package_DFN_QFN:Nordic_AQFN-73-1EP_7x7mm_P0.5mm" H 5250 2450 50  0001 C CNN
F 3 "" H 4600 5100 50  0001 C CNN
	1    5250 4500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 5BF58DBC
P 3950 2750
F 0 "C14" H 4065 2796 50  0000 L CNN
F 1 "1uF" H 4065 2705 50  0000 L CNN
F 2 "" H 3988 2600 50  0001 C CNN
F 3 "~" H 3950 2750 50  0001 C CNN
	1    3950 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5BF58E70
P 3450 2800
F 0 "C5" H 3565 2846 50  0000 L CNN
F 1 "100nF" H 3565 2755 50  0000 L CNN
F 2 "" H 3488 2650 50  0001 C CNN
F 3 "~" H 3450 2800 50  0001 C CNN
	1    3450 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5BF58EAC
P 4900 1350
F 0 "C15" H 5015 1396 50  0000 L CNN
F 1 "1uF" H 5015 1305 50  0000 L CNN
F 2 "" H 4938 1200 50  0001 C CNN
F 3 "~" H 4900 1350 50  0001 C CNN
	1    4900 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5BF58EE0
P 5300 1350
F 0 "C16" H 5415 1396 50  0000 L CNN
F 1 "47nF" H 5415 1305 50  0000 L CNN
F 2 "" H 5338 1200 50  0001 C CNN
F 3 "~" H 5300 1350 50  0001 C CNN
	1    5300 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5BF58F16
P 6250 2000
F 0 "C13" H 6365 2046 50  0000 L CNN
F 1 "N.C." H 6365 1955 50  0000 L CNN
F 2 "" H 6288 1850 50  0001 C CNN
F 3 "~" H 6250 2000 50  0001 C CNN
	1    6250 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5BF58F52
P 6550 2700
F 0 "C12" H 6665 2746 50  0000 L CNN
F 1 "100nF" H 6665 2655 50  0000 L CNN
F 2 "" H 6588 2550 50  0001 C CNN
F 3 "~" H 6550 2700 50  0001 C CNN
	1    6550 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5BF58F8C
P 7300 4250
F 0 "C3" H 7415 4296 50  0000 L CNN
F 1 "1pF" H 7415 4205 50  0000 L CNN
F 2 "" H 7338 4100 50  0001 C CNN
F 3 "~" H 7300 4250 50  0001 C CNN
	1    7300 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5BF58FC8
P 7900 4250
F 0 "C4" H 8015 4296 50  0000 L CNN
F 1 "1pF" H 8015 4205 50  0000 L CNN
F 2 "" H 7938 4100 50  0001 C CNN
F 3 "~" H 7900 4250 50  0001 C CNN
	1    7900 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C22
U 1 1 5BF5900D
P 8350 4250
F 0 "C22" H 8465 4296 50  0000 L CNN
F 1 "N.C." H 8465 4205 50  0000 L CNN
F 2 "" H 8388 4100 50  0001 C CNN
F 3 "~" H 8350 4250 50  0001 C CNN
	1    8350 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5BF590B7
P 7300 4950
F 0 "C9" H 7415 4996 50  0000 L CNN
F 1 "820pF" H 7415 4905 50  0000 L CNN
F 2 "" H 7338 4800 50  0001 C CNN
F 3 "~" H 7300 4950 50  0001 C CNN
	1    7300 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5BF590F9
P 7300 5900
F 0 "C8" H 7415 5946 50  0000 L CNN
F 1 "100nF" H 7415 5855 50  0000 L CNN
F 2 "" H 7338 5750 50  0001 C CNN
F 3 "~" H 7300 5900 50  0001 C CNN
	1    7300 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5BF5913D
P 5550 6550
F 0 "C7" H 5665 6596 50  0000 L CNN
F 1 "100nF" H 5665 6505 50  0000 L CNN
F 2 "" H 5588 6400 50  0001 C CNN
F 3 "~" H 5550 6550 50  0001 C CNN
	1    5550 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 5BF59255
P 3450 5750
F 0 "C19" H 3565 5796 50  0000 L CNN
F 1 "4.7uF" H 3565 5705 50  0000 L CNN
F 2 "" H 3488 5600 50  0001 C CNN
F 3 "~" H 3450 5750 50  0001 C CNN
	1    3450 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5BF592A1
P 2250 5300
F 0 "C6" H 2365 5346 50  0000 L CNN
F 1 "4.7uF" H 2365 5255 50  0000 L CNN
F 2 "" H 2288 5150 50  0001 C CNN
F 3 "~" H 2250 5300 50  0001 C CNN
	1    2250 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5BF595A8
P 7900 3150
F 0 "C11" V 8050 3100 50  0000 L CNN
F 1 "100pF" V 7750 3050 50  0000 L CNN
F 2 "" H 7938 3000 50  0001 C CNN
F 3 "~" H 7900 3150 50  0001 C CNN
	1    7900 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C10
U 1 1 5BF59610
P 7900 3650
F 0 "C10" V 8050 3600 50  0000 L CNN
F 1 "N.C." V 7750 3600 50  0000 L CNN
F 2 "" H 7938 3500 50  0001 C CNN
F 3 "~" H 7900 3650 50  0001 C CNN
	1    7900 3650
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L3
U 1 1 5BF5CDC6
P 4200 1700
F 0 "L3" H 4253 1746 50  0000 L CNN
F 1 "15nH" H 4253 1655 50  0000 L CNN
F 2 "" H 4200 1700 50  0001 C CNN
F 3 "~" H 4200 1700 50  0001 C CNN
	1    4200 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:L L2
U 1 1 5BF5CE28
P 4200 2100
F 0 "L2" H 4253 2146 50  0000 L CNN
F 1 "10uH" H 4253 2055 50  0000 L CNN
F 2 "" H 4200 2100 50  0001 C CNN
F 3 "~" H 4200 2100 50  0001 C CNN
	1    4200 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:L L1
U 1 1 5BF5CE82
P 7600 4050
F 0 "L1" V 7790 4050 50  0000 C CNN
F 1 "3.9nH" V 7699 4050 50  0000 C CNN
F 2 "" H 7600 4050 50  0001 C CNN
F 3 "~" H 7600 4050 50  0001 C CNN
	1    7600 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L4
U 1 1 5BF5CF71
P 3150 5250
F 0 "L4" V 3200 5250 50  0000 C CNN
F 1 "10uH" V 3100 5250 50  0000 C CNN
F 2 "" H 3150 5250 50  0001 C CNN
F 3 "~" H 3150 5250 50  0001 C CNN
	1    3150 5250
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5E83A
P 3450 3100
F 0 "#PWR?" H 3450 2850 50  0001 C CNN
F 1 "GND" H 3455 2927 50  0000 C CNN
F 2 "" H 3450 3100 50  0001 C CNN
F 3 "" H 3450 3100 50  0001 C CNN
	1    3450 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5E859
P 3950 3000
F 0 "#PWR?" H 3950 2750 50  0001 C CNN
F 1 "GND" H 3955 2827 50  0000 C CNN
F 2 "" H 3950 3000 50  0001 C CNN
F 3 "" H 3950 3000 50  0001 C CNN
	1    3950 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5E878
P 4900 1600
F 0 "#PWR?" H 4900 1350 50  0001 C CNN
F 1 "GND" H 4905 1427 50  0000 C CNN
F 2 "" H 4900 1600 50  0001 C CNN
F 3 "" H 4900 1600 50  0001 C CNN
	1    4900 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5E897
P 6250 2250
F 0 "#PWR?" H 6250 2000 50  0001 C CNN
F 1 "GND" H 6255 2077 50  0000 C CNN
F 2 "" H 6250 2250 50  0001 C CNN
F 3 "" H 6250 2250 50  0001 C CNN
	1    6250 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5E8B6
P 6550 2900
F 0 "#PWR?" H 6550 2650 50  0001 C CNN
F 1 "GND" H 6555 2727 50  0000 C CNN
F 2 "" H 6550 2900 50  0001 C CNN
F 3 "" H 6550 2900 50  0001 C CNN
	1    6550 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5ED74
P 5550 6750
F 0 "#PWR?" H 5550 6500 50  0001 C CNN
F 1 "GND" H 5555 6577 50  0000 C CNN
F 2 "" H 5550 6750 50  0001 C CNN
F 3 "" H 5550 6750 50  0001 C CNN
	1    5550 6750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5EDB2
P 3450 6050
F 0 "#PWR?" H 3450 5800 50  0001 C CNN
F 1 "GND" H 3455 5877 50  0000 C CNN
F 2 "" H 3450 6050 50  0001 C CNN
F 3 "" H 3450 6050 50  0001 C CNN
	1    3450 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5EE03
P 2250 5600
F 0 "#PWR?" H 2250 5350 50  0001 C CNN
F 1 "GND" H 2255 5427 50  0000 C CNN
F 2 "" H 2250 5600 50  0001 C CNN
F 3 "" H 2250 5600 50  0001 C CNN
	1    2250 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5F066
P 7300 4450
F 0 "#PWR?" H 7300 4200 50  0001 C CNN
F 1 "GND" H 7305 4277 50  0000 C CNN
F 2 "" H 7300 4450 50  0001 C CNN
F 3 "" H 7300 4450 50  0001 C CNN
	1    7300 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5F085
P 7300 5150
F 0 "#PWR?" H 7300 4900 50  0001 C CNN
F 1 "GND" H 7305 4977 50  0000 C CNN
F 2 "" H 7300 5150 50  0001 C CNN
F 3 "" H 7300 5150 50  0001 C CNN
	1    7300 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5F0A4
P 7300 6100
F 0 "#PWR?" H 7300 5850 50  0001 C CNN
F 1 "GND" H 7305 5927 50  0000 C CNN
F 2 "" H 7300 6100 50  0001 C CNN
F 3 "" H 7300 6100 50  0001 C CNN
	1    7300 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5F118
P 7900 4450
F 0 "#PWR?" H 7900 4200 50  0001 C CNN
F 1 "GND" H 7905 4277 50  0000 C CNN
F 2 "" H 7900 4450 50  0001 C CNN
F 3 "" H 7900 4450 50  0001 C CNN
	1    7900 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BF5F137
P 8350 4450
F 0 "#PWR?" H 8350 4200 50  0001 C CNN
F 1 "GND" H 8355 4277 50  0000 C CNN
F 2 "" H 8350 4450 50  0001 C CNN
F 3 "" H 8350 4450 50  0001 C CNN
	1    8350 4450
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5BF5FC3E
P 3950 2500
F 0 "#PWR?" H 3950 2350 50  0001 C CNN
F 1 "VDD" H 3967 2673 50  0000 C CNN
F 2 "" H 3950 2500 50  0001 C CNN
F 3 "" H 3950 2500 50  0001 C CNN
	1    3950 2500
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5BF5FCEB
P 6550 2450
F 0 "#PWR?" H 6550 2300 50  0001 C CNN
F 1 "VDD" H 6567 2623 50  0000 C CNN
F 2 "" H 6550 2450 50  0001 C CNN
F 3 "" H 6550 2450 50  0001 C CNN
	1    6550 2450
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5BF5FD6E
P 7300 5700
F 0 "#PWR?" H 7300 5550 50  0001 C CNN
F 1 "VDD" H 7317 5873 50  0000 C CNN
F 2 "" H 7300 5700 50  0001 C CNN
F 3 "" H 7300 5700 50  0001 C CNN
	1    7300 5700
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5BF5FF44
P 5550 6350
F 0 "#PWR?" H 5550 6200 50  0001 C CNN
F 1 "VDD" H 5567 6523 50  0000 C CNN
F 2 "" H 5550 6350 50  0001 C CNN
F 3 "" H 5550 6350 50  0001 C CNN
	1    5550 6350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5BF5FF63
P 2250 5050
F 0 "#PWR?" H 2250 4900 50  0001 C CNN
F 1 "VDD" H 2267 5223 50  0000 C CNN
F 2 "" H 2250 5050 50  0001 C CNN
F 3 "" H 2250 5050 50  0001 C CNN
	1    2250 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3650 3750 3650
Wire Wire Line
	3750 3650 3750 2650
Wire Wire Line
	3750 2650 3450 2650
Wire Wire Line
	3450 2950 3450 3100
Wire Wire Line
	4500 3000 4500 2600
Wire Wire Line
	4500 2600 3950 2600
Wire Wire Line
	3950 2500 3950 2600
Connection ~ 3950 2600
Wire Wire Line
	3950 2900 3950 3000
Wire Wire Line
	4600 3000 4600 2500
Wire Wire Line
	4600 2500 4200 2500
Wire Wire Line
	4200 2500 4200 2250
Wire Wire Line
	4200 1850 4200 1950
Wire Wire Line
	4900 1500 4900 1600
Wire Wire Line
	5300 1500 4900 1500
Connection ~ 4900 1500
Connection ~ 4900 1200
Wire Wire Line
	4900 1200 5300 1200
Wire Wire Line
	4700 1200 4900 1200
Wire Wire Line
	5900 3000 5900 1850
Wire Wire Line
	5900 1850 6250 1850
Wire Wire Line
	6250 2150 6250 2250
Wire Wire Line
	6550 2850 6550 2900
Wire Wire Line
	6200 3000 6200 2550
Wire Wire Line
	6200 2550 6550 2550
Wire Wire Line
	6550 2450 6550 2550
Connection ~ 6550 2550
Wire Wire Line
	6750 3750 7400 3750
Wire Wire Line
	6750 3850 7500 3850
Wire Wire Line
	7500 3850 7500 3650
Wire Wire Line
	7500 3650 7650 3650
$Comp
L power:GND #PWR?
U 1 1 5BF62E34
P 8300 3650
F 0 "#PWR?" H 8300 3400 50  0001 C CNN
F 1 "GND" H 8305 3477 50  0000 C CNN
F 2 "" H 8300 3650 50  0001 C CNN
F 3 "" H 8300 3650 50  0001 C CNN
	1    8300 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 3650 8300 3650
Wire Wire Line
	6750 4050 7300 4050
Wire Wire Line
	7300 4100 7300 4050
Connection ~ 7300 4050
Wire Wire Line
	7300 4050 7450 4050
Wire Wire Line
	7750 4050 7900 4050
Wire Wire Line
	7900 4050 7900 4100
Wire Wire Line
	8350 4400 8350 4450
Wire Wire Line
	7900 4400 7900 4450
Wire Wire Line
	7300 4400 7300 4450
Wire Wire Line
	6750 3950 7050 3950
Wire Wire Line
	7050 3950 7050 4400
Wire Wire Line
	7050 4400 7300 4400
Connection ~ 7300 4400
Wire Wire Line
	6750 4350 6950 4350
Wire Wire Line
	6950 4350 6950 4800
Wire Wire Line
	6950 4800 7300 4800
Wire Wire Line
	7300 5100 7300 5150
Wire Wire Line
	6750 5350 7100 5350
Wire Wire Line
	7100 5350 7100 5750
Wire Wire Line
	7100 5750 7300 5750
Wire Wire Line
	7300 5700 7300 5750
Connection ~ 7300 5750
Wire Wire Line
	7300 6050 7300 6100
Wire Wire Line
	5400 6000 5400 6400
Wire Wire Line
	5400 6400 5550 6400
Wire Wire Line
	5550 6350 5550 6400
Connection ~ 5550 6400
Wire Wire Line
	5550 6700 5550 6750
Wire Wire Line
	3850 5250 3300 5250
Wire Wire Line
	3850 5050 3000 5050
Wire Wire Line
	2250 5150 2250 5050
Connection ~ 2250 5050
Wire Wire Line
	2250 5450 2250 5600
Wire Wire Line
	3000 5250 3000 5050
Connection ~ 3000 5050
Wire Wire Line
	3000 5050 2250 5050
Wire Wire Line
	3450 5900 3450 6050
Wire Wire Line
	4800 1500 4900 1500
Wire Wire Line
	7400 3150 7750 3150
Wire Wire Line
	7400 3150 7400 3750
Wire Wire Line
	8050 3150 8300 3150
Wire Wire Line
	8300 3150 8300 3650
Connection ~ 8300 3650
Wire Wire Line
	8350 4100 8350 4050
Wire Wire Line
	8350 4050 7900 4050
Connection ~ 7900 4050
Connection ~ 4500 2600
Wire Wire Line
	4950 2500 4800 2500
Wire Wire Line
	5600 2500 5600 2700
Wire Wire Line
	5600 2700 4900 2700
Wire Wire Line
	5600 2350 5700 2350
Wire Wire Line
	5700 2350 5700 2800
Wire Wire Line
	5700 2800 5100 2800
Wire Wire Line
	4800 2500 4800 3000
Wire Wire Line
	4500 2200 4500 2600
Wire Wire Line
	4900 2700 4900 3000
Wire Wire Line
	5100 2800 5100 3000
Wire Wire Line
	5600 2200 5800 2200
Wire Wire Line
	5800 2200 5800 2900
Wire Wire Line
	4700 1200 4700 3000
Connection ~ 4800 2500
Wire Wire Line
	4800 1500 4800 2500
Wire Wire Line
	4950 2200 4500 2200
Wire Wire Line
	4700 1200 4200 1200
Wire Wire Line
	4200 1200 4200 1550
Connection ~ 4700 1200
Wire Wire Line
	5300 1200 7650 1200
Wire Wire Line
	7650 1200 7650 3650
Connection ~ 5300 1200
Connection ~ 7650 3650
Wire Wire Line
	7650 3650 7750 3650
Wire Wire Line
	5800 2900 5300 2900
Wire Wire Line
	5300 2900 5300 3000
$Comp
L power:GND #PWR?
U 1 1 5BF642BA
P 4500 6150
F 0 "#PWR?" H 4500 5900 50  0001 C CNN
F 1 "GND" H 4505 5977 50  0000 C CNN
F 2 "" H 4500 6150 50  0001 C CNN
F 3 "" H 4500 6150 50  0001 C CNN
	1    4500 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 6000 4500 6150
$Comp
L Device:Battery_Cell BT1/VDDH
U 1 1 5BF7601E
P 2700 5800
F 0 "BT1/VDDH" H 2818 5896 50  0000 L CNN
F 1 "Battery_Cell" H 2818 5805 50  0000 L CNN
F 2 "" V 2700 5860 50  0001 C CNN
F 3 "~" V 2700 5860 50  0001 C CNN
	1    2700 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5600 3450 5600
Wire Wire Line
	3850 5150 3450 5150
Wire Wire Line
	3450 5150 3450 5600
Connection ~ 3450 5600
$Comp
L power:GND #PWR?
U 1 1 5BF8D1C5
P 2700 6050
F 0 "#PWR?" H 2700 5800 50  0001 C CNN
F 1 "GND" H 2705 5877 50  0000 C CNN
F 2 "" H 2700 6050 50  0001 C CNN
F 3 "" H 2700 6050 50  0001 C CNN
	1    2700 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5900 2700 6050
$EndSCHEMATC
