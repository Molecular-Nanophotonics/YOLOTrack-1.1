#include "tensorflow/c/c_api.h"

#include <iostream>
#include <vector>
#include <memory>

std::string GPUDeviceName(TF_Session* session) {
	std::unique_ptr<TF_Status, decltype(&TF_DeleteStatus)> status(TF_NewStatus(), TF_DeleteStatus);
	TF_Status* s = status.get();

	std::unique_ptr<TF_DeviceList, decltype(&TF_DeleteDeviceList)> list(TF_SessionListDevices(session, s), TF_DeleteDeviceList);
	TF_DeviceList* device_list = list.get();

	//CHECK_EQ(TF_OK, TF_GetCode(s)) << TF_Message(s);

	const int num_devices = TF_DeviceListCount(device_list);
	std::cout << "There are " << num_devices << " devices." << std::endl;
	for (int i = 0; i < num_devices; ++i) {
		const char* device_name = TF_DeviceListName(device_list, i, s);
		//CHECK_EQ(TF_OK, TF_GetCode(s)) << TF_Message(s);
		const char* device_type = TF_DeviceListType(device_list, i, s);
		//CHECK_EQ(TF_OK, TF_GetCode(s)) << TF_Message(s);
		std::cout << "Device " << i << " has name " << device_name << ", type "	<< device_type << std::endl;
		if (std::string(device_type) == "GPU") { 
			return device_name;
		}
	}
	// No GPU device found.
	return "";
}

std::string GPUDeviceName() {
	std::unique_ptr<TF_Status, decltype(&TF_DeleteStatus)> status(TF_NewStatus(), TF_DeleteStatus);
	TF_Status* s = status.get();
	std::unique_ptr<TF_Graph, decltype(&TF_DeleteGraph)> graph(TF_NewGraph(), TF_DeleteGraph);

	TF_SessionOptions* opts = TF_NewSessionOptions();
	TF_Session* sess = TF_NewSession(graph.get(), opts, s);
	TF_DeleteSessionOptions(opts);

	const std::string gpu_device_name = GPUDeviceName(sess);
	TF_DeleteSession(sess, s);
	//CHECK_EQ(TF_OK, TF_GetCode(s)) << TF_Message(s);
	return gpu_device_name;
}


int main()
{
	_putenv_s("TF_CPP_MIN_LOG_LEVEL", "1");

	std::cout << "Hello from TensorFlow " << TF_Version() << std::endl;

	GPUDeviceName();

	std::cout << "Press any key to exit...";
	std::cin.get();

	return 0;
}