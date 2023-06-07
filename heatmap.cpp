#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

// Constants for the heatmap
const int heatmapWidth = 100;
const int heatmapHeight = 100;
const int cellSize = 10;

// Function to read heatmap data from a file
void readHeatmapData(std::ifstream& file, int heatmapData[heatmapWidth][heatmapHeight])
{
    for (int j = 0; j < heatmapHeight; ++j)
    {
        for (int i = 0; i < heatmapWidth; ++i)
        {
            file >> heatmapData[i][j];
        }
    }
}

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(heatmapWidth * cellSize, heatmapHeight * cellSize), "Heatmap");

    // Create a 2D array to store the heatmap data
    int heatmapData[heatmapWidth][heatmapHeight] = {0};

    // Open the heatmap data file
    std::ifstream file("output.dat");
    if (!file)
    {
        std::cerr << "Failed to open heatmap data file." << std::endl;
        return 1;
    }

    while (window.isOpen())
    {
        // Read the heatmap data from the file
        readHeatmapData(file, heatmapData);

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the heatmap
        for (int j = 0; j < heatmapHeight; ++j)
        {
            for (int i = 0; i < heatmapWidth; ++i)
            {
                int intensity = heatmapData[i][j];

                // Map intensity to color based on a color gradient or custom rules
                sf::Color cellColor = sf::Color::Blue; // Replace with your own color mapping logic

                if (intensity == 1)  {
                    // std::cout<<"ya";
                    cellColor = sf::Color::Red;
                }

                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(i * cellSize, j * cellSize);
                cell.setFillColor(cellColor);

                window.draw(cell);
            }
        }

        // Display the window
        window.display();
    }

    // Close the heatmap data file
    file.close();

    return 0;
}
