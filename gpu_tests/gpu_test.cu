#include <stdio.h>

__global__ void vector_add(int *a, int *b, int *result, int n) {
    int i = threadIdx.x;
    if (i < n)
        result[i] = a[i] + b[i];
}

int main() {
    int n = 4;
    int size = n * sizeof(int);

    // Host memory
    int h_a[] = {1, 2, 3, 4};
    int h_b[] = {10, 20, 30, 40};
    int h_result[4];

    // Device memory
    int *d_a, *d_b, *d_result;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_result, size);

    // Copy to device
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    // Launch 1 block with 4 threads
    vector_add<<<1, 4>>>(d_a, d_b, d_result, n);

    // Copy result back to host
    cudaMemcpy(h_result, d_result, size, cudaMemcpyDeviceToHost);

    // Print result
    for (int i = 0; i < n; i++)
        printf("%d + %d = %d\n", h_a[i], h_b[i], h_result[i]);

    // Free device memory
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_result);

    return 0;
}
