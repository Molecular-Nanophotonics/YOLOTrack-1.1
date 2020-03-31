
extern "C" __declspec(dllexport) int setupYOLO(int image_w, int image_h, int grid_w, int grid_h, int boxes, int classes, float* anchors, int n);
extern "C" __declspec(dllexport) int decodeYOLO(float* output_tensor, float obj_threshold, float nms_threshold, int* n_out, float* x_out, float* y_out, float* w_out, float* h_out, int* c_out);