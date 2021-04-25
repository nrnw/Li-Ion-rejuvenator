# Hybrid vehicle battery charger with automated battery charging and discharging cycles to enhance the battery cell performance. 


## Motivation

It is found that Li-Ion batteries in hybrid vehicles will have the memory effect up to some level [1]. Inside a battery pack usually a few of the cells will degrade the performance with usage due to this memory effect. 

Currently these faulty cells were separated from the battery pack and charged discharged using a seperate charger to remove the memory effect. However monitoring of the cell voltages and switching from the discharging  to charging and vise versa is currently done manually.   Ultimate goal of this project is to design a battery charger that can automatically do this process. 


## Requirements 

Need a method to monitor voltage and current drawn by each cell. The mechanism should be able to monitor about 20 cells simultaneously. 

SMPS need to be designed with the possibility to control the voltage using microcontroller. 

Need to make a load where its resistance can be changed using a microcontroller

Need to find how the charging/discharging actually need to be happened to enhance the cell performance.

If the requirement is to cut the charging voltage when reached a threshold, this can be done using opamp as a comparator without using any microcontrollers. 

Charging=ON, Discharging=OFF
SMPS_vout= f(cell_voltage,current_drawn,cell_temperatue)

Charging=OFF, Discharging=ON
Discharging_current= f(cell_voltage,current_drawn,cell_temperatue)
Discharging_on= cell_voltage > threshold_voltage

Hybrid battery pack




