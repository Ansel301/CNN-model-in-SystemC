The CNN model - Lenet-5 contains 8 layers:
1. Input layer: 1 28x28 image of the number 7 from MNIST
2. Convolution layer 1: Kernel size is 5x5, output data channel is 6, stride is 1 and activation function is ReLU in this layer. Hence, there are six 24x24 output feature maps.
3. Max pooling layer 1: The kernel size is 2x2 and the stride is 2. Hence, there are six 12x12 output feature maps.
4. Convolution layer 2: Kernel size is 5x5, output data channel is 16, stride is 1 and activation function is ReLU in this layer. Hence, there are sixteen 8x8 output feature maps.
5. Max pooling layer 2: The operation of this layer is as same as the Max Pooling layer 1. Hence, there are sixteen 4x4 output feature maps.
6. Dense layer 1: The output feature maps are being flattened before doing the Dense layer operation. Input neuron number is 256, output neuron number is 120, and activation function is ReLU in this layer.
7. Dense layer 2: Input neuron number is 120, output neuron number is 84, and activation function is ReLU in this layer.
8. Dense layer 3: Input neuron number is 84, output neuron number is 10, and there is no activation function in this layer. The value of these neurons is the output data.

The ROM is used to store the weights and input data of CNN model. The convolution weight is arranged by kernel. The order of each kernel is first horizontal, then vertical and finally depth. The order of fully connected layer weight is arranged by neuron. We provide a RAM that you can store the temporary data. The RAM has 16KB entry. The RAM can read/write data. When the ram_wr becomes 0 (write valid), you can write data to RAM. When the ram_wr becomes to 1 (read valid), you can read data from RAM. The Monitor is used to print the output value. When the output_valid signal change to 1, the result is valid. When all the results are collected (10 outputs in total), the simulation will end.

Finally, you must complete two version of the final project by use floating-point (float) and fixed-point (16-bit) and compare the difference between the results in two version. The define.h file is used to determine the data type of the system, you can undefine/define fixed_DATA_TYPE to change the current mode. In addition, in fixedpoint version system, floating-point number type such as Double or Float cannot be used. 

Besides, we provide an input image (number 7) for testing. In the calculation results of the final layer (10 results, sequentially represent the prediction results from 0 to 9 in MNIST), the neuron of 7 should have the maximum value. 
