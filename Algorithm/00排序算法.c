/**
 *    title:  00排序算法.c
 *    author:  sleeeeeping
 *    created:  2024-07-25 10:17:21
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TYPE int
#define LEN 10
#define SWAP(a, b) do { typeof(a) t = (a); (a) = (b); (b) = t; } while (0);

typedef void (*sortFp)(TYPE *, size_t); 

// 经典排序
void classicSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[i]) {
                SWAP(arr[i], arr[j]);
            }
        }
    }
}

// 冒泡排序
void bubbleSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    bool suc = true;
    for (int i = n - 1; i > 0 && suc; --i) {
        suc = false;
        for (int j = 0; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                SWAP(arr[j + 1], arr[j]);
                suc = true;
            }
        }
    }
}

// 选择排序
void selectionSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    for (int i = 0; i < n - 1; ++i) {
        int k = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[k] > arr[j]) {
                k = j;
            }
        }
        if (k != i) {
            SWAP(arr[k], arr[i]);
        }
    }
}

// 插入排序
void insertionSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    for (int i = 1; i < n; ++i) {
        TYPE key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 希尔排序
void shellSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < n; ++i) {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                SWAP(arr[j], arr[j - h]);
            }
        }
        h = h / 3;
    }
}

void _quickSort(TYPE *arr, int l, int r) {
    if (l >= r) return ;
    int i = l - 1, j = r + 1, x = arr[l + r >> 1];
    while (i < j) {
        do i++; while (x > arr[i]);
        do j--; while (x < arr[j]);
        if (i < j) SWAP(arr[i], arr[j]);
    }
    _quickSort(arr, l, j), _quickSort(arr, j + 1, r);
}

// 快速排序
void quickSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    _quickSort(arr, 0, n - 1);
}

void _siftSort(TYPE *arr, int start, int end) {
    int root = start;
    int son = start << 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son - 1] < arr[son]) {
            son += 1;
        }
        if (arr[root - 1] < arr[son - 1]) {
            SWAP(arr[root - 1], arr[son - 1]);
            root = son;
            son <<= 1;
        } else return ;
    }
}

// 堆排序
void heapSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    for (int i = n / 2; i >= 1; --i) {
        _siftSort(arr, i, n);
    }
    for (int i = n; i > 1; --i) {
        SWAP(arr[0], arr[i - 1]);
        _siftSort(arr, 1, i - 1);
    }
}

void _mergeSort(TYPE *arr, TYPE *tmp, int l, int r) {
    if (l >= r) return ;
    int mid = l + r >> 1;
    _mergeSort(arr, tmp, l, mid);    
    _mergeSort(arr, tmp, mid + 1, r); 
    int a = l, b = mid + 1;
    for (int i = l; i <= r; ++i) {
        if (b > r || (a <= mid && arr[a] <= arr[b])) {
            tmp[i] = arr[a++];
        } else {
            tmp[i] = arr[b++];
        }
    }
    memcpy(arr + l, tmp + l, sizeof(TYPE) * (r - l + 1));
}

// 归并排序
void mergeSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    TYPE *temp = malloc(sizeof(TYPE) * n);
    _mergeSort(arr, temp, 0, n - 1);
}

// 计数排序
void countingSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    TYPE min = arr[0], max = arr[0];
    for (int i = 1; i < n; ++i) {
        min = min > arr[i] ? arr[i] : min;
        max = max < arr[i] ? arr[i] : max;
    }
    TYPE* hash = calloc(sizeof(TYPE), max - min + 1);
    for (int i = 0; i < n; ++i) {
        hash[arr[i] - min] += 1;
    }
    for (int i = 0, j = 0; i < max - min + 1; ++i) {
        while (hash[i]--) {
            arr[j++] = i + min;
        }
    }
    free(hash);
}

// 基数排序
void radixSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    int *brr = calloc(sizeof(TYPE), n);
    int *cnt = calloc(sizeof(TYPE), 1 << 8);
    int mask = (1 << 8) - 1;
    int *x = arr, *y = brr;
    for (int i = 0; i < 32; i += 8) {
        memset(cnt, 0, sizeof cnt);
        for (int j = 0; j < n; ++j) {
            ++cnt[x[j] >> i & mask];
        }
        for (int sum = 0, j = 0; j < (1 << 8); ++j) {
            sum += cnt[j];
            cnt[j] = sum - cnt[j];
        }
        for (int j = 0; j < n; ++j) {
            y[cnt[x[j] >> i & mask]++] = x[j];
        }
        SWAP(x, y);
    }
    free(brr);
    free(cnt);
}

// 分桶排序 cnt桶数 range桶中数据范围
void _bucketSort(TYPE *arr, size_t n, int cnt, TYPE range) {
    // 申请桶内存
    // bucket指向桶的开头 end指向桶的末尾 数据加入到end的位置
    TYPE *bucket[cnt], *end[cnt];
    for (int i = 0; i < cnt; ++i) {
        bucket[i] = malloc(sizeof(TYPE) * n);
        end[i] = bucket[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < cnt; ++j) {
            if (j * range <= arr[i] && arr[i] <= range*(j + 1)) {
                *(end[j]) = arr[i];
                end[j]++;
            }
        }
    }
    // 对每桶分别使用其他排序算法来排序
    for (int i = 0; i < cnt; ++i) {
        int size = end[i] - bucket[i];
        if (size > 1) {
            _quickSort(bucket[i], 0, size - 1);
        }
        memcpy(arr, bucket[i], sizeof(TYPE) * size);
        arr += size;
        free(bucket[i]);
    }
}

// 桶排序 只对正整数
void bucketSort(TYPE *arr, size_t n) {
    printf("%s: ", __func__);
    _bucketSort(arr, n, 4, 25);
}

void showArr(TYPE *arr, size_t n) {
    for (int i = 0; i < n; ++i) {
        printf("%d%c", arr[i], " \n"[i == n - 1]);
    }
}

int main() {
    sortFp sortArr[] = {
        classicSort,
        bubbleSort,
        selectionSort,
        insertionSort,
        shellSort,
        quickSort,
        heapSort,
        mergeSort,
        countingSort,
        radixSort,
        bucketSort
    };
    TYPE arr[LEN] = {};
    for (int i = 0; i < sizeof(sortArr) / sizeof(sortArr[0]); ++i) {
        for (int j = 0; j < LEN; ++j) {
            arr[j] = rand() % 100;
        }
        showArr(arr, LEN);
        sortArr[i](arr, LEN);
        showArr(arr, LEN);
        printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
    }
}