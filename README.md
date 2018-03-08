# Travelling Officer Problem: Managing Car Parking Violations Efficiently Using Sensor Data

Abstract
The on-street parking system is an indispensable part of civil projects, which provides travellers and shoppers with parking spaces. With the recent in-ground sensors deployed throughout the city, there is a significant problem on how to use the sensor data to manage parking violations and issue infringement notices in a short time-window efficiently. In this paper, we use a large real-world dataset with on-street parking sensor data from the local city council, and establish a formulation of the Travelling Officer Problem with a general probability-based model. We propose two solutions using a spatio-temporal probability model for parking officers to maximize the number of infringing cars caught with limited time cost. Using real-world parking sensor data and Google Map road network information, the experimental results show that our proposed algorithms outperform the existing patrolling routes.

This repository contains resources developed within the following paper:

Shao, W., Salim, F. D., Gu, T., Dinh, N. T., & Chan, J. (2017). Travelling Officer Problem: Managing Car Parking Violations Efficiently Using Sensor Data. IEEE Internet of Things Journal.


You can find the paper and presentation in this repository.

## Contents of the repository
This repository contains resources used and described in the paper.

The repository is structured as follows:


- `data/`: Dataset used for this paper.
- `code/`: Include the algorithm implementation.
- `paper/`: PDF of paper.


## Code
C++ with Visual Studio 2012 Please run from main.cpp. All setting are in the main.cpp. Please place the data file in the same direction.

## Data
The data include sample data comprises of the location of the online parking slots and the parking events. Please contact me if you needs the complete data.

## Citation
If you use the resources presented in this repository, please cite (using the following BibTeX entry):
```
@article{shao2017travelling,
  title={Travelling Officer Problem: Managing Car Parking Violations Efficiently Using Sensor Data},
  author={Shao, Wei and Salim, Flora D and Gu, Tao and Dinh, Ngoc-Thanh and Chan, Jeffrey},
  journal={IEEE Internet of Things Journal},
  year={2017},
  publisher={IEEE}
}
```
