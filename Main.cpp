#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int n = 80;
float recHs[n];
bool sorted = false;

sf::RenderWindow* window = nullptr; 

void dispSort(int index) {
    window->clear();
    for (int i = 0; i < n; i++) {
        if (recHs[i] < 0 || recHs[i] > 600) {
            std::cout << "Invalid height value at index " << i << ": " << recHs[i] << "\n";
            continue;
        }

        sf::RectangleShape block(sf::Vector2f(10, recHs[i]));
        block.setPosition(i * 12, 600 - recHs[i]);
        block.setFillColor(sorted || i == index ? sf::Color::Green : sf::Color::White);
        window->draw(block);
    }
    window->display();
}

void insertionSort() {
    
    int i, j;
    float key;

    for (i = 1; i < n; i++) {
        key = recHs[i];
        j = i - 1;

        while (j >= 0 && recHs[j] > key) {
            recHs[j + 1] = recHs[j];
            j = j - 1;
            dispSort(j >= 0 ? j : 0);
        }
        recHs[j + 1] = key;
        dispSort(i);
    }

    sorted = true;
    dispSort(n - 1);
}

int partition(int low, int high) {
    float pivot = recHs[high]; 
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (recHs[j] <= pivot) {
            i++;
            std::swap(recHs[i], recHs[j]);
            dispSort(j);  
        }
    }

    std::swap(recHs[i + 1], recHs[high]);
    dispSort(high); 
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        sf::sleep(sf::milliseconds(50));
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void gnomeSort()
{
    int index = 0;
    while (index < n)
    {
        sf::sleep(sf::milliseconds(100));
        dispSort(index);
        if (index == 0)
            index++;
        if (recHs[index] >= recHs[index - 1])
            index++;
        else
        {
            std::swap(recHs[index], recHs[index - 1]);
            index--;
        }
    }
    return;
}


int main() {
    srand(static_cast<unsigned>(time(0)));
    
    int choose;

    for (int i = 0; i < n; i++) {
        recHs[i] = (rand() % 500) + 50;
    }

    sf::RenderWindow win(sf::VideoMode(960, 600), "Sorter");
    window = &win; 

    std::cout << "Enter sort type: 1 - QuickSort 2 - Insertion Sort 3 - Gnome Sort\n";
    std::cin >> choose;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        if (!sorted) {
            if (choose == 1)
            {
                dispSort(0);
                quickSort(0, n - 1);
                sorted = true;
                dispSort(0);
            }
            if (choose == 2)
            {
                dispSort(0);
                insertionSort();
            }
            if (choose == 3)
            {
                dispSort(0);
                gnomeSort();
                sorted = true;
            }
        }
    }

    return 0;
}
