# Neural Network Classifier for Iris Dataset in C

This project implements a simple neural network in C for the classification of the Iris dataset. The neural network consists of an input layer, a hidden layer, and an output layer.

## Files

- `neuralnetwork_latih.c`: Training code for the neural network.
- `neuralnetwork_test_satu.c`: Testing code for a single data point.
- `neuralnetwork_test_banyak.c`: Testing code for multiple data points.
- `iris_datalatih.txt`: Training data for the Iris dataset.
- `iris_target_latih.txt`: Target labels for the training data.
- `iris_datauji.txt`: Testing data for the Iris dataset.
- `iris_bobot1.txt`, `iris_bobot2.txt`: Initial weights for the neural network.
- `iris_weights1_new2.txt`, `iris_weights2_new2.txt`: Updated weights after training.

## Dependencies

- C standard library
- `math.h` for mathematical functions
- `time.h` for seeding the random number generator
- `stdlib.h` for dynamic memory allocation

## Usage

1. Train the neural network:
gcc neuralnetwork_latih.c -o neuralnetwork_latih -lm
./neuralnetwork_latih

2. Test the neural network on a single data point:
gcc neuralnetwork_test_satu.c -o neuralnetwork_test_satu -lm
./neuralnetwork_test_satu

3. Test the neural network on multiple data points:
gcc neuralnetwork_test_banyak.c -o neuralnetwork_test_banyak -lm
./neuralnetwork_test_banyak

## Notes

- The paths to the data and weight files are hardcoded in the source files. Make sure to update these paths to match your directory structure.
- The neural network parameters (such as the number of iterations, learning rate, and network architecture) can be adjusted in the source code.

## License

This project is open-source and available under the [MIT License](LICENSE).
