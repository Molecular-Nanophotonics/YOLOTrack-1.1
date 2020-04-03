# YOLOv2 Training (Python)

*M. Fränzl*, Molecular Nanophtonics Group

## Discription

This repository contains Jupyter notebooks and Python modules for synthetic image generation, training and exporting YOLOv2 models with Python/Keras using the TensorFlow backend.

## Requirements 

- [Anaconda](https://www.anaconda.com/distribution/) with Python 3.x
- GPU that supports CUDA Toolkit 10.0

## Setup Instructions
- `conda install tensorflow-gpu=1.14.0`
- `conda install keras`
- `conda install -c conda-forge imgaug`

## User's Guide

- [ImageGenerator.ipynb](ImageGenerator.ipynb): This notebook shows how to generate a synthetic image dataset for training. It depends on the **image_generator** and **xml_writer** module. The **image_generator** module implements the synthetic image generation whereas the **xml_writer** provides functions to save the annotations the Pascal VOC format. A sample dataset generated with this notebook is contained in the **images** directory. 

- [Training.ipynb](Training.ipynb): This notebook implements YOLOv2 using Keras and demonstrates how to train a model and how to export a trained model. It depends on the **preprocessing** and **utils** modules. The **preprocessing** module comprises functions to parse the annotation files and implements the *BatchGenerator* required for training. The **utils** module provides functions for the output decoding as well as for the model export.

- [Inference.ipynb](Inference.ipynb): Notebook that shows how to load the exported `model.pb` and `model.ini` files and run a model inference. It requires the **utils** module for the output decoding.

For details refer to the documentation and comments in the individual scripts and notebooks.

