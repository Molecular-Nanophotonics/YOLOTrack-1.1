/* Copyright 2020 Martin Fränzl, Molecular Nanophotonics Group. All Rights Reserved.

Licensed under the GNU General Public License, Version 3.0;
You may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://opensource.org/licenses/GPL-3.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

#include "tensorflow/c/c_api.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <windows.h>
#include <vector>
//#include <memory> // Required for std::unique_ptr

# include "TF.h"

TF_Status* status;
TF_Graph* graph;
TF_Buffer* graph_def;
TF_ImportGraphDefOptions* graph_opts;
TF_SessionOptions* sess_opts;
TF_Session* session;

float* values;
int input_dim;
int64_t* input_shape;
int input_size;
std::vector<TF_Output> inputs;
std::vector<TF_Tensor*> input_values;

int output_dim;
int64_t* output_shape;
int output_size;
std::vector<TF_Output> outputs;
std::vector<TF_Tensor*> output_values;

//#define ERROR_READ_PROTOCOL_BUFFER 1001;
int STATUS = 1;

TF_Buffer* read_file(char* file);

void free_buffer(void* data, size_t length) {}
static void Deallocator(void* data, size_t length, void* arg) {}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, // Handle to DLL module.
	DWORD fdwReason,    // Reason for calling function.
	LPVOID lpReserved)  // Reserved.
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.            
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		TF_CloseSession(session, status);
		TF_DeleteSession(session, status);
		TF_DeleteSessionOptions(sess_opts);
		TF_DeleteImportGraphDefOptions(graph_opts);
		TF_DeleteGraph(graph);
		TF_DeleteStatus(status);
		break;
	}
	return TRUE;
}


__declspec(dllexport) int getVersion(char* tf_version)
{
	sprintf(tf_version, TF_Version());
	return 0;
}

__declspec(dllexport) int getDeviceName(char* gpu_name)
{
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, 0);
	sprintf(gpu_name, prop.name);
	
	return 0;
}

__declspec(dllexport) int getGPUs(int* gpu_out) // ../tensorflow/c/c_api_test.cc
{
	//std::unique_ptr<TF_Status, decltype(&TF_DeleteStatus)> _status(TF_NewStatus(), TF_DeleteStatus);
	//TF_Status* status = _status.get();
	TF_Status* status = TF_NewStatus();

	//std::unique_ptr<TF_Graph, decltype(&TF_DeleteGraph)> _graph(TF_NewGraph(), TF_DeleteGraph);
	//TF_Graph* graph = _graph.get();
	TF_Graph* graph = TF_NewGraph();

	TF_SessionOptions* session_options = TF_NewSessionOptions();
	TF_Session* session = TF_NewSession(graph, session_options, status);
	TF_DeleteSessionOptions(session_options);

	//std::unique_ptr<TF_DeviceList, decltype(&TF_DeleteDeviceList)> _device_list(TF_SessionListDevices(session, status), TF_DeleteDeviceList);
	//TF_DeviceList* device_list = _device_list.get();
	TF_DeviceList* device_list = TF_SessionListDevices(session, status);

	const int num_devices = TF_DeviceListCount(device_list);
	int gpu = 0;
	for (int i = 0; i < num_devices; ++i) {
		const char* device_name = TF_DeviceListName(device_list, i, status);
		const char* device_type = TF_DeviceListType(device_list, i, status);
		if (std::string(device_type) == "GPU") {
			gpu++; // GPU device found.
		}
	}
	TF_DeleteSession(session, status);
	TF_DeleteGraph(graph);
	TF_DeleteDeviceList(device_list);
	TF_DeleteStatus(status);

	*gpu_out = gpu;
	return 0;
}

__declspec(dllexport) int setupTF(char* file, int64_t* in_shape, int in_dim, char* in_name, int64_t* out_shape, int out_dim, char* out_name)
{
	graph = TF_NewGraph();
	graph_def = read_file(file);
	graph_opts = TF_NewImportGraphDefOptions();
	status = TF_NewStatus();
	TF_GraphImportGraphDef(graph, graph_def, graph_opts, status);
	if (TF_GetCode(status) != TF_OK) {
		return -1; // ERROR graph import.
	}

	sess_opts = TF_NewSessionOptions();
	status = TF_NewStatus();
	session = TF_NewSession(graph, sess_opts, status);
	if (TF_GetCode(status) != TF_OK) {
		return -2; // ERROR new session.
	}
	
	input_dim = in_dim;
	input_shape = (int64_t*)calloc(input_dim, sizeof(int64_t));
	input_size = 1;
	for (int n = 0; n < input_dim; n++) {
		input_shape[n] = in_shape[n];
		input_size *= in_shape[n];
	}
	values = (float*)calloc(input_size, sizeof(float));
	inputs.push_back({ TF_GraphOperationByName(graph, in_name), 0 });
	input_values.push_back(TF_NewTensor(TF_FLOAT, input_shape, input_dim, values, input_size * sizeof(float), &Deallocator, 0));
	
	output_dim = out_dim;
	output_shape = (int64_t*)calloc(output_dim, sizeof(int64_t));
	output_size = 1;
	for (int n = 0; n < output_dim; n++) {
		output_shape[n] = out_shape[n];
		output_size *= out_shape[n];
	}
	
	outputs.push_back({ TF_GraphOperationByName(graph, out_name), 0 });
	output_values.push_back(TF_AllocateTensor(TF_FLOAT, output_shape, output_dim, output_size * sizeof(float)));	
}


__declspec(dllexport) int runTF(float* input_tensor, float* output_tensor) 
{
	input_values.clear();
	input_values.push_back(TF_NewTensor(TF_FLOAT, input_shape, input_dim, input_tensor, input_size * sizeof(float), &Deallocator, 0));
	
	// Run the session.
	TF_SessionRun(session, nullptr, &inputs[0], &input_values[0], 1, &outputs[0], &output_values[0], 1,	nullptr, 0, nullptr, status);

	TF_Tensor &out = *output_values[0];
	float* output = (float *)TF_TensorData(&out);

	// Copy to output. 
	for (int i = 0; i < output_size; i++) {
		output_tensor[i] = output[i];
	}
	
	return 0;
}


TF_Buffer* read_file(char* filename)
{
	TF_Buffer* buf = TF_NewBuffer();

	FILE *f = fopen(filename, "rb");
	if (f) {
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET);

		void* data = malloc(fsize);
		fread(data, fsize, 1, f);
		fclose(f);

		buf->data = data;
		buf->length = fsize;
		buf->data_deallocator = free_buffer;
	}
	else {
		STATUS= 0;
	}
	return buf;
}


// For debuging.
/*
FILE *f = fopen("Debug.txt", "w");
for (int i = 0; i < 10; i++)
{
fprintf(f, "%.10f\n", output_array[i]);
}
fclose(f);
*/


/* NOTES

Using CUDA in Visual Studio project (Supposed the CUDA Visual Stuio Integration is installed)

- Right click project name: Build Dependencies > Build Customization ...
	- Enable CUDA 10 (.targets, .props)
- In project "Properties":
	- Add $(CudaToolkitLibDir) to Linker > General > Additional Libary Directories
	- Add cudart_static.lib to Linker > Input > Additional Dependencies

*/