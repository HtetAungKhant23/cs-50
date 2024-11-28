#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      int average = (int)round(
          (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) /
          3.0);
      image[h][w].rgbtBlue = average;
      image[h][w].rgbtGreen = average;
      image[h][w].rgbtRed = average;
    }
  }
  return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < width; w++) {
      int red = (int)round((0.393 * image[h][w].rgbtRed) +
                           (0.769 * image[h][w].rgbtGreen) +
                           (0.189 * image[h][w].rgbtBlue));
      int green = (int)round((0.349 * image[h][w].rgbtRed) +
                             (0.686 * image[h][w].rgbtGreen) +
                             (0.168 * image[h][w].rgbtBlue));
      int blue = (int)round((0.272 * image[h][w].rgbtRed) +
                            (0.534 * image[h][w].rgbtGreen) +
                            (0.131 * image[h][w].rgbtBlue));
      image[h][w].rgbtRed = red > 255 ? 255 : red;
      image[h][w].rgbtGreen = green > 255 ? 255 : green;
      image[h][w].rgbtBlue = blue > 255 ? 255 : blue;
    }
  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  int range = width / 2;
  for (int h = 0; h < height; h++) {
    for (int w = 0; w < range; w++) {
      RGBTRIPLE temp = image[h][w];
      image[h][w] = image[h][width - w - 1];
      image[h][width - w - 1] = temp;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  RGBTRIPLE copy[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      float totalRed = 0, totalGreen = 0, totalBlue = 0;
      int count = 0;
      for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
          int ni = i + di;
          int nj = j + dj;
          if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
            totalRed += image[ni][nj].rgbtRed;
            totalGreen += image[ni][nj].rgbtGreen;
            totalBlue += image[ni][nj].rgbtBlue;
            count++;
          }
        }
      }
      copy[i][j].rgbtRed = round(totalRed / count);
      copy[i][j].rgbtGreen = round(totalGreen / count);
      copy[i][j].rgbtBlue = round(totalBlue / count);
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = copy[i][j];
    }
  }

  return;
}
