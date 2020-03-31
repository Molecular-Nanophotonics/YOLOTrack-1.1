/* 
Description:    This function returns the TensorFlow version. 
Parameters:     tf_version (char*): Pointer to a array of characters allocated by the user.
Return:         int 
                1  No Error. 
                0  Error.
*/    
extern "C" __declspec(dllexport) int getVersion(char* tf_version);


/* 
Description:    This function returns the name of the GPU device. 
Parameters:     gpu_name (char*): Pointer to a array of characters allocated by the user.
Return:         int 
                1  No Error. 
                0  Error.
*/  
extern "C" __declspec(dllexport) int getDeviceName(char* gpu_name);

/*
Description:    This function returns the number of available GPUs. 
Parameters:     num_gpus (int*): Number of available GPUs.
Return:         int:
                1  No Error.
                0  Error.
*/
extern "C" __declspec(dllexport) int getGPUs(int* gpu_out);


/*
Description:    This function sets up the TensorFlow session. 
Parameters:     file (char*): File name of the model *.pb file.
                in_shape (int64_t*): Shape of the input tensor.
                in_dim (int): Dimension of the input tensor.
                in_name (char*): Name of the input node.
                out_shape (int64_t*): Shape of the output tensor.
                out_dim (int): Dimension of the output tensor.
                out_name (char*): Name of the output node.
Return:         int:
                1  No Error.
                0  Error.
*/
extern "C" __declspec(dllexport) int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name);


/*
Description:    This functions runs the TensorFlow session.
Parameters:     input_tensor (float*): Input tensor.
                output_tensor (float*): Output tensor.
Return:         int:
                1  No Error.
                0  Error.
*/
extern "C" __declspec(dllexport) int runTF(float* input_tensor, float* output_tensor);
