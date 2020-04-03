/* Copyright 2020 Martin Fränzl, Molecular Nanophotonics Group. All Rights Reserved.

Licensed under the GNU General Public License, Version 3.0;
You may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://opensource.org/licenses/GPL-3.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

#include <windows.h>
#include <vector>

#include "YOLOv21.h"

int IMAGE_W = 416;
int IMAGE_H = 416;
int GRID_W = 13;
int GRID_H = 13;
int BOXES = 5;
int CLASSES = 3;
float* ANCHORS;
int N_MAX;

float* _x;
float* _y;
float* _w;
float* _h;
float* _p; // !!!
int* _c;
float* _score;
int* idx_list;

float sigmoid(float x);
int entry_index(int row, int col, int box, int entry);
float box_iou(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

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
		break;
	}
	return TRUE;
}


__declspec(dllexport) int setupYOLO(int image_w, int image_h, int grid_h, int grid_w, int boxes, int classes, float* anchors, int n_max)
{
	IMAGE_W = image_w;
	IMAGE_H = image_h;
	GRID_W = grid_w;
	GRID_H = grid_h;
	BOXES = boxes;
	CLASSES = classes;
	ANCHORS = (float*)calloc(2 * BOXES, sizeof(float));
	ANCHORS = anchors;
	N_MAX = n_max;

	_x = (float*)calloc(N_MAX, sizeof(float));
	_y = (float*)calloc(N_MAX, sizeof(float));
	_w = (float*)calloc(N_MAX, sizeof(float));
	_h = (float*)calloc(N_MAX, sizeof(float)); 
	_p = (float*)calloc(N_MAX, sizeof(float)); // !!!
	_c = (int*)calloc(N_MAX, sizeof(int));
	_score = (float*)calloc(N_MAX, sizeof(float));
	idx_list = (int*)calloc(N_MAX, sizeof(int));

	return 0;
}

// Decode the YOLO output tensor. See the YOLO papers for details.
__declspec(dllexport) int decodeYOLO(float* output_tensor, float obj_threshold, float iou_threshold, int* n_out, float *x_out, float *y_out, float *w_out, float *h_out, float *p_out, int* c_out)
{
	/*
	The 416 x 416 image is divided into a 13 x 13 grid (GRID_W, GRID_H).
	Each of these grid cells will predict 5 bounding boxes (BOXES).
	A bounding box consists of five data items: x, y, width, height, and a confidence score.
	Each grid cell also predicts which class each bounding box belongs to.
	*/
	int _n = 0;
	for (int row = 0; row < GRID_W; row++) {
		for (int col = 0; col < GRID_H; col++) {
			for (int box = 0; box < BOXES; box++) {
				int obj_idx = entry_index(row, col, box, 5); // !!!
				float objectness = sigmoid(output_tensor[obj_idx]); // The confidence value for the bounding box. Use logistic sigmoid to turn this into a probability.
				if (objectness > obj_threshold) {
					int box_idx = entry_index(row, col, box, 0);
					float x = output_tensor[box_idx];
					float y = output_tensor[box_idx + 1];
					float w = output_tensor[box_idx + 2];
					float h = output_tensor[box_idx + 3];
					float p = output_tensor[box_idx + 4]; // !!!
					int class_idx = entry_index(row, col, box, 6); // !!!
					int class_max_idx = 0;
					float class_max = sigmoid(output_tensor[class_idx]);
					// Find the index of the class with the largest score.
					for (int c = 1; c < CLASSES; c++) {
						if (sigmoid(output_tensor[class_idx + c]) > class_max) {
							class_max = sigmoid(output_tensor[class_idx + c]);
							class_max_idx = c;
						}
					}
					if (_n < N_MAX) {
						/*
						The predicted x and y coordinates are relative to the location of the grid cell.
						We use the logistic sigmoid to constrain these coordinates to the range 0-1.
						Then we add the cell coordinates and divide by the number of grid cells.
						Now x and y respresent the center of the bounding box units of the image width and height.
						*/
						_x[_n] = (row + sigmoid(x)) / GRID_W;
						_y[_n] = (col + sigmoid(y)) / GRID_H;
						/*
						The size of the bounding box w and h, is predicted relative to size of an anchor box.
						Here we also transform the width and height into units of the image width and height.
						*/
						_w[_n] = exp(w)*ANCHORS[2 * box] / GRID_W;
						_h[_n] = exp(h)*ANCHORS[2 * box + 1] / GRID_H;
						_p[_n] = sigmoid(p); // !!!
						_c[_n] = class_max_idx;
						_score[_n] = class_max;
						_n++;
					}
				}
			}
		}
	}
	/*
	We already filtered out any bounding boxes that have very low scores, but there still may be boxes that overlap too much with others.
	We use "Non-Maximum Supression" to remove those duplicate bounding boxes.
	*/
	for (int c = 0; c < CLASSES; c++) {
		int idx_max = 0;
		for (int i = 0; i < _n; i++) {
			if (_c[i] == c) {
				idx_list[idx_max] = i;
				idx_max++;
			}
		}
		for (int i = 0; i < idx_max; i++) {
			int idx_i = idx_list[i];
			for (int j = i + 1; j < idx_max; j++) {
				int idx_j = idx_list[j];
				if (box_iou(_x[idx_i], _y[idx_i], _w[idx_i], _h[idx_i], _x[idx_j], _y[idx_j], _w[idx_j], _h[idx_j]) > iou_threshold) {
					_score[idx_j] = 0;
				}
			}
		}
	}

	// Copy to output. 
	int n = 0;
	for (int i = 0; i < _n; i++) {
		if (_score[i] > 0) {
			x_out[n] = _x[i];
			y_out[n] = _y[i];
			w_out[n] = _w[i];
			h_out[n] = _h[i];
			p_out[n] = _p[i]; // !!!
			c_out[n] = _c[i];
			n++;
		}
	}
	*n_out = n;

	return 0;
}


float sigmoid(float x)
{
	return 1. / (1. + exp((float)-x));
}


int entry_index(int row, int col, int box, int entry)
{
	return entry + (5 + 1 + CLASSES)*(box + BOXES * (row + GRID_H*col));
}


float interval_intersec(float x1, float x2, float  x3, float  x4)
{
	if (x3 < x1) {
		if (x4 < x1)
			return 0;
		else
			return min(x2, x4) - x1;
	}
	else {
		if (x2 < x3)
			return 0;
		else
			return min(x2, x4) - x3;
	}
}


float box_iou(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	float w = interval_intersec(x1 - w1 / 2, x1 + w1 / 2, x2 - w2 / 2, x2 + w2 / 2);
	float h = interval_intersec(y1 - h1 / 2, y1 + h1 / 2, y2 - h2 / 2, y2 + h2 / 2);
	float area_intersec = w * h;
	float area_union = w1*h1 + w2*h2 - area_intersec;

	return area_intersec / area_union;
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