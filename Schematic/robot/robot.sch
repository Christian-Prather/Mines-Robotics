EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Lab 3 Robot"
Date "2020-10-19"
Rev "Version 3"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Author: Christian Prather"
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5F8E5CBD
P 2750 2400
F 0 "A1" H 2750 3581 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 2750 3490 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 2750 2400 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2750 2400 50  0001 C CNN
	1    2750 2400
	1    0    0    -1  
$EndComp
$Comp
L OPB620:OPB620 S2
U 1 1 5F8E7D7F
P 5900 1750
F 0 "S2" H 5850 2120 50  0000 C CNN
F 1 "OPB620" H 5850 2029 50  0000 C CNN
F 2 "Schematic:OPTO_OPB620" H 5900 1750 50  0001 L BNN
F 3 "Optex" H 5900 1750 50  0001 L BNN
	1    5900 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F8EBF51
P 4800 1300
F 0 "R1" H 4870 1346 50  0000 L CNN
F 1 "R" H 4870 1255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4730 1300 50  0001 C CNN
F 3 "~" H 4800 1300 50  0001 C CNN
	1    4800 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5F8EF4E7
P 6250 1150
F 0 "R4" H 6320 1196 50  0000 L CNN
F 1 "R" H 6320 1105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6180 1150 50  0001 C CNN
F 3 "~" H 6250 1150 50  0001 C CNN
	1    6250 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5F8F058A
P 3750 1800
F 0 "R2" V 3957 1800 50  0000 C CNN
F 1 "R" V 3866 1800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3680 1800 50  0001 C CNN
F 3 "~" H 3750 1800 50  0001 C CNN
	1    3750 1800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5F8F0A1B
P 5200 1850
F 0 "R3" V 4993 1850 50  0000 C CNN
F 1 "R" V 5084 1850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 5130 1850 50  0001 C CNN
F 3 "~" H 5200 1850 50  0001 C CNN
	1    5200 1850
	0    1    1    0   
$EndComp
$Comp
L Driver_Motor:L298HN U1
U 1 1 5F8F49D9
P 5400 3200
F 0 "U1" H 5400 4081 50  0000 C CNN
F 1 "L298HN" H 5400 3990 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-15_P2.54x2.54mm_StaggerOdd_Lead4.58mm_Vertical" H 5450 2550 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000240.pdf" H 5550 3450 50  0001 C CNN
	1    5400 3200
	1    0    0    -1  
$EndComp
$Comp
L OPB620:OPB620 S1
U 1 1 5F8E73E2
P 4500 1700
F 0 "S1" H 4450 2070 50  0000 C CNN
F 1 "OPB620" H 4450 1979 50  0000 C CNN
F 2 "Schematic:OPTO_OPB620" H 4500 1700 50  0001 L BNN
F 3 "Optex" H 4500 1700 50  0001 L BNN
	1    4500 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1400 3350 1400
Wire Wire Line
	3600 1400 3600 1800
Wire Wire Line
	3900 1800 4100 1800
Wire Wire Line
	4800 1450 4800 1500
Wire Wire Line
	4800 1150 4650 1150
Wire Wire Line
	3600 1150 3600 1400
Connection ~ 3600 1400
Text GLabel 2750 3500 3    50   Input ~ 0
GND
Text GLabel 4100 1600 0    50   Input ~ 0
GND
Text GLabel 4800 1800 3    50   Input ~ 0
GND
Text GLabel 4900 1500 2    50   Input ~ 0
PIN_8
Wire Wire Line
	4900 1500 4800 1500
Connection ~ 4800 1500
Wire Wire Line
	4800 1500 4800 1600
Text GLabel 2000 2600 0    50   Input ~ 0
PIN_8
Wire Wire Line
	3600 1800 3600 2250
Wire Wire Line
	3600 2250 5050 2250
Wire Wire Line
	5050 2250 5050 1850
Connection ~ 3600 1800
Wire Wire Line
	5350 1850 5500 1850
Wire Wire Line
	6200 1650 6250 1650
Wire Wire Line
	6250 1650 6250 1450
Wire Wire Line
	6250 1000 4650 1000
Wire Wire Line
	4650 1000 4650 1150
Connection ~ 4650 1150
Wire Wire Line
	4650 1150 3600 1150
Text GLabel 6200 1850 3    50   Input ~ 0
GND
Text GLabel 5500 1650 1    50   Input ~ 0
GND
Text GLabel 6400 1450 2    50   Input ~ 0
PIN_7
Wire Wire Line
	6400 1450 6250 1450
Connection ~ 6250 1450
Wire Wire Line
	6250 1450 6250 1300
Text GLabel 2000 2500 0    50   Input ~ 0
PIN_7
Wire Wire Line
	2000 2500 2250 2500
Wire Wire Line
	2000 2600 2250 2600
Text GLabel 4800 2700 0    50   Input ~ 0
PIN_9
Text GLabel 4800 2800 0    50   Input ~ 0
PIN_10
Text GLabel 4800 3100 0    50   Input ~ 0
PIN_5
Text GLabel 4800 3200 0    50   Input ~ 0
PIN_6
Text GLabel 2000 2700 0    50   Input ~ 0
PIN_9
Text GLabel 2050 2800 0    50   Input ~ 0
PIN_10
Text GLabel 2000 2300 0    50   Input ~ 0
PIN_5
Text GLabel 2000 2400 0    50   Input ~ 0
PIN_6
Wire Wire Line
	2000 2700 2250 2700
Wire Wire Line
	2050 2800 2250 2800
Wire Wire Line
	2000 2300 2250 2300
Wire Wire Line
	2000 2400 2250 2400
Wire Wire Line
	2850 3500 2850 4050
Wire Wire Line
	2850 4050 5400 4050
Wire Wire Line
	5400 4050 5400 3900
Wire Wire Line
	3350 1400 3350 2300
Wire Wire Line
	3350 2300 5500 2300
Wire Wire Line
	5500 2300 5500 2500
Connection ~ 3350 1400
Wire Wire Line
	3350 1400 3600 1400
Text GLabel 5400 2500 0    50   Input ~ 0
VIN
Text GLabel 2650 1400 0    50   Input ~ 0
VIN
$EndSCHEMATC
