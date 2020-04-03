# YOLOv2.1 Training (Python)

*M. Fränzl*, Molecular Nanophtonics Group

## Discription

This repository contains Jupyter notebooks and Python modules for synthetic image generation, training and exporting YOLOv2.1 models with Python/Keras using the TensorFlow backend.

## Requirements 

- [Anaconda](https://www.anaconda.com/distribution/) with Python 3.x
- GPU that supports CUDA Toolkit 10.0

## Setup Instructions
- `conda install tensorflow-gpu=1.14.0`
- `conda install keras`
- `conda install -c conda-forge imgaug`

## User's Guide

- [ImageGenerator.ipynb](ImageGenerator.ipynb): This notebook shows how to generate a synthetic image dataset for training. It depends on the **image_generator** and **xml_writer** module. The **image_generator** module implements the synthetic image generation whereas the **xml_writer** provides functions to save the annotations the Pascal VOC format. A sample dataset is contained in the **Dataset** directory. To limit the size of this reposity only a small fraction of the dataset is provided. 

- [Training+Export.ipynb](Training+Export.ipynb): This notebook implements TinyYOLOv2.1 using Keras and demonstrates how to train and export a model. It requires a **Dataset** directory with datasets for training, validation and testing and depends on the **preprocessing** and **utils** Python modules. The **preprocessing** module comprises functions to parse the annotation files and implements the *BatchGenerator* required for training. The **utils** module provides functions for to decode the network output and to draw the overlay. The trained model graph is exported as protocol buffer file `*.pb` and the parameters required to decode the YOLOv2.1 output are exported as `*.ini` file to the **Dataset** directory. The model weights are stored in a `*_weights.h5*` file that is not included in this repository due to size limitations.

- [Inference.ipynb](Inference.ipynb): Notebook that shows how to load the exported `*.pb` and `*.ini` files from the **Dataset** directory and run a model inference. It requires the **utils** module for the output decoding.

For details refer to the documentation and comments in the individual scripts and notebooks.

