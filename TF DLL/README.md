# TF DLL 

*M. Fränzl*, Molecular Nanophtonics Group

## Discription

`TF.dll` is a dynamic link library for model inference build on top of the GPU supported [TensorFlow C API](https://www.tensorflow.org/install/lang_c). The `TF.dll` is located in [x64/Release](x64/Release) and defined in [TF.h](TF.h)

## Requirements 

### ... To Use

- [CUDA Toolkit 10.0](https://developer.nvidia.com/cuda-10.0-download-archive)
- [cdDNN 7.6.4](https://developer.nvidia.com/rdp/cudnn-archive)
- `tensorflow.dll` from [libtensorflow-gpu-windows-x86_64-1.13.1](https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-gpu-windows-x86_64-1.13.1.zip) located in the same dirctory as `TF.dll`

### ... To Compile from Source Code

- [Visual Studio 2015](https://visualstudio.microsoft.com/de/vs/older-downloads/)
- [CUDA Toolkit 10.0](https://developer.nvidia.com/cuda-10.0-download-archive) + Visual Studion Integration
- [cuDNN 7.6.4](https://developer.nvidia.com/rdp/cudnn-archive)
- [libtensorflow-gpu-windows-x86_64-1.13.1](https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-gpu-windows-x86_64-1.13.1.zip) located at "C:\\"


