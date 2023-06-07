#include <QDebug>

void heapify(QVector<int> &arr, int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(QVector<int> &arr, int n, int steps) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i=n-1; i>=0 && steps > 0; i--, steps--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(const QVector<int> &arr) {
    for (int i=0; i<arr.size(); ++i)
        qDebug() << arr[i] << " ";
    }

void pyramid_sort (int steps, QString mas){
    QList numbers = mas.split(" ");
    QVector<int> arr;
    for (int i = 0; i < numbers.size(); ++i)
    {
        int num = numbers[i].toInt();
        arr.append(num);
    }
    int n = arr.size();

    heapSort(arr, n, steps);

    qDebug() << "Array after " << steps << " steps of heap sort: \n";
    printArray(arr);
}


void Parsing(QString message){
    QList<QString> parts = message.split('&');
        qDebug() << parts[0];
        if(parts[0] == "sort"){
            if (parts.length() != 3) {
                qDebug() << "error";
            } else {
                int step = parts[1].toInt();
                QString mas = parts[2];
                pyramid_sort(step, mas);

    }
}
}



