#ifndef SPRITE_H
#include <vector>
#include <SFML/Graphics.hpp>
#define SPRITE_H

class Sprite {
	private:
			std::vector<std::string> imagePaths; //Store file paths to each image. We need a way to store images in memory for easy access
			std::vector<sf::Image *> images; //sf::Images are created after image is loaded from a file
	public:
			int xOffset;
			int yOffset;
			
			/*
				Returns 0 on success -1 on failure. Should declare a new image, load it from a file and place that image in our 
				images vector
			*/
			int addImage(std::string filePath);
			/*
				Remove an image from the Sprite based on its' location in the images array
			*/
			int removeImage(int index); 

};
#endif
