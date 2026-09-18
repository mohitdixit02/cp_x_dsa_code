#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

// Sqrt Decomposition for Range Sum Queries and Point Updates
class SqrtDecomposition
{
private:
    int n, b_size;
    vector<long long> arr;
    vector<long long> blocks;

public:
    SqrtDecomposition(const vector<int> &input)
    {
        n = input.size();
        b_size = sqrt(n);

        arr.assign(input.begin(), input.end());
        int num_blocks = (n + b_size - 1) / b_size;
        blocks.assign(num_blocks, 0);

        for (int i = 0; i < n; i++)
        {
            blocks[i / b_size] += arr[i];
        }
    }

    void update(int idx, long long val)
    {
        int b_idx = idx / b_size;
        blocks[b_idx] += val - arr[idx];
        arr[idx] = val;
    }

    // Range Query: sum in range [L, R] in O(sqrt(N))
    long long query(int L, int R)
    {
        long long sum = 0;
        int start_block = L / b_size;
        int end_block = R / b_size;

        // Case 1: L and R in the same block
        if (start_block == end_block)
        {
            for (int i = L; i <= R; i++)
            {
                sum += arr[i];
            }
            return sum;
        }

        // Case 2: L and R in different blocks
        // 1. Partial Left Block
        int left_end = (start_block + 1) * b_size - 1;
        for (int i = L; i <= left_end; i++)
        {
            sum += arr[i];
        }

        // 2. Full Middle Blocks (O(1) per block!)
        for (int b = start_block + 1; b < end_block; b++)
        {
            sum += blocks[b];
        }

        // 3. Partial Right Block
        int right_start = end_block * b_size;
        for (int i = right_start; i <= R; i++)
        {
            sum += arr[i];
        }

        return sum;
    }
};

// Sqrt Decomposition with Lazy Propagation for Range Updates and Range Queries
class SqrtDecompositionLazy
{
private:
    int n, b_size;
    vector<long long> arr;
    vector<long long> blocks;
    vector<long long> lazy;   // Pending addition tag for each block

    // Push down pending lazy tag of block b to its elements
    void push(int b){
        if (lazy[b] == 0)
            return;

        int start = b * b_size;
        int end = min(n - 1, (b + 1) * b_size - 1);

        for (int i = start; i <= end; i++){
            arr[i] += lazy[b];
        }
        lazy[b] = 0; // Reset lazy tag
    }

public:
    SqrtDecompositionLazy(const vector<int> &input){
        n = input.size();
        b_size = sqrt(n);

        arr.assign(input.begin(), input.end());
        int num_blocks = (n + b_size - 1) / b_size;

        blocks.assign(num_blocks, 0);
        lazy.assign(num_blocks, 0);

        for (int i = 0; i < n; i++){
            blocks[i / b_size] += arr[i];
        }
    }

    // Range Update: Add 'val' to all elements in range [L, R] in O(sqrt(N))
    void rangeUpdate(int L, int R, long long val)
    {
        int start_block = L / b_size;
        int end_block = R / b_size;

        // Case 1: L and R in the same block
        if (start_block == end_block)
        {
            push(start_block);
            for (int i = L; i <= R; i++){
                arr[i] += val;
                blocks[start_block] += val;
            }
            return;
        }

        // Case 2: L and R in different blocks

        // 1. Left Partial Block
        push(start_block);
        int left_end = (start_block + 1) * b_size - 1;
        for (int i = L; i <= left_end; i++){
            arr[i] += val;
            blocks[start_block] += val;
        }

        // 2. Middle Full Blocks (O(1) per block!)
        for (int b = start_block + 1; b < end_block; b++){
            lazy[b] += val;
            blocks[b] += val * b_size;
        }

        // 3. Right Partial Block
        push(end_block);
        int right_start = end_block * b_size;
        for (int i = right_start; i <= R; i++){
            arr[i] += val;
            blocks[end_block] += val;
        }
    }

    // Range Query: Sum of elements in range [L, R] in O(sqrt(N))
    long long query(int L, int R)
    {
        int start_block = L / b_size;
        int end_block = R / b_size;
        long long sum = 0;

        // Case 1: Same block
        if (start_block == end_block){
            for (int i = L; i <= R; i++){
                sum += arr[i] + lazy[start_block];
            }
            return sum;
        }

        // Case 2: Different blocks
        // 1. Left Partial Block
        int left_end = (start_block + 1) * b_size - 1;
        for (int i = L; i <= left_end; i++){
            sum += arr[i] + lazy[start_block];
        }

        // 2. Middle Full Blocks
        for (int b = start_block + 1; b < end_block; b++){
            sum += blocks[b]; // blocks[b] ALREADY contains lazy[b] * b_size
        }

        // 3. Right Partial Block
        int right_start = end_block * b_size;
        for (int i = right_start; i <= R; i++){
            sum += arr[i] + lazy[end_block];
        }

        return sum;
    }
};