#include <floatfann.h>
#include <stdio.h>

int main() {
    struct fann *ann = fann_create_standard(3, 2, 3, 1);
    if (!ann) {
        printf("Failed to create ANN\n");
        return 1;
    }

    fann_set_activation_function_hidden(ann, FANN_SIGMOID);
    fann_set_activation_function_output(ann, FANN_SIGMOID);

    fann_type input[2] = {0.0f, 1.0f};
    fann_type *output = fann_run(ann, input);
    if (output) {
        printf("Output: %f\n", (double)output[0]);
    }

    fann_destroy(ann);
    return 0;
}
